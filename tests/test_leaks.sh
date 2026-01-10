#!/bin/bash

# Script para testar memory leaks no my_shell
# Usa valgrind com suppressions para readline

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "================================================"
echo "  Memory Leak Test - my_shell"
echo "================================================"
echo ""

# Compilar
echo -n "Compilando... "
make re > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "${GREEN}OK${NC}"
else
    echo -e "${RED}ERRO${NC}"
    exit 1
fi

echo ""

# Função para executar teste
run_test() {
    local test_name="$1"
    local commands="$2"
    
    echo -n "[$test_name] "
    
    # Executar valgrind
    output=$(echo -e "$commands" | valgrind --leak-check=full \
        --show-leak-kinds=definite,possible \
        --suppressions=./readline.supp \
        --error-exitcode=42 \
        ./my_shell 2>&1)
    
    # Extrair informações
    definitely_lost=$(echo "$output" | grep "definitely lost:" | awk '{print $4}')
    possibly_lost=$(echo "$output" | grep "possibly lost:" | awk '{print $4}')
    
    if [ "$definitely_lost" = "0" ] && [ "$possibly_lost" = "0" ]; then
        echo -e "${GREEN}✓ OK${NC}"
        return 0
    else
        echo -e "${RED}✗ LEAK${NC}"
        echo "  Definitely lost: $definitely_lost bytes"
        echo "  Possibly lost: $possibly_lost bytes"
        return 1
    fi
}

# Testes
echo "Executando testes:"
echo ""

run_test "Comando simples      " "pwd\nexit"
run_test "Pipe                 " "echo hello | grep h\nexit"
run_test "Redirecionamento >   " "echo test > /tmp/test.txt\nrm /tmp/test.txt\nexit"
run_test "Redirecionamento <   " "echo test > /tmp/test.txt\ncat < /tmp/test.txt\nrm /tmp/test.txt\nexit"
run_test "Redirecionamento >>  " "echo a > /tmp/test.txt\necho b >> /tmp/test.txt\nrm /tmp/test.txt\nexit"
run_test "Heredoc              " "cat << EOF\nhello\nworld\nEOF\nexit"
run_test "Operador &&          " "echo a && echo b\nexit"
run_test "Operador ||          " "false || echo b\nexit"
run_test "Export/Unset         " "export TEST=value\necho \$TEST\nunset TEST\nexit"
run_test "Builtin cd           " "cd /tmp\npwd\ncd -\nexit"
run_test "Múltiplos pipes      " "echo test | cat | cat | cat\nexit"
run_test "Comandos complexos   " "ls | grep t && echo ok || echo fail\nexit"

echo ""
echo "================================================"
echo -e "${GREEN}Todos os testes concluídos!${NC}"
echo "================================================"
