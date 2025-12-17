#!/bin/bash

# Script de Testes do Lexer
# Execute: bash test_lexer.sh

echo "==================================="
echo "  TESTES DO LEXER - MY_SHELL"
echo "==================================="
echo ""

SHELL="./my_shell"

if [ ! -f "$SHELL" ]; then
    echo "❌ Erro: $SHELL não encontrado. Compile primeiro com 'make'"
    exit 1
fi

# Contador de testes
TOTAL=0
PASSED=0

# Função para rodar teste
run_test() {
    TOTAL=$((TOTAL + 1))
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "Teste $TOTAL: $1"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "$2" | $SHELL
    echo ""
    read -p "✓ Tokens corretos? (s/n): " resposta
    if [ "$resposta" = "s" ]; then
        PASSED=$((PASSED + 1))
        echo "✅ PASSOU"
    else
        echo "❌ FALHOU"
    fi
    echo ""
}

# TESTE 1: Comando simples
run_test "Comando simples" "ls"

# TESTE 2: Comando com argumentos
run_test "Comando com argumentos" "ls -la"

# TESTE 3: Múltiplos argumentos
run_test "Múltiplos argumentos" "echo hello world"

# TESTE 4: Pipe simples
run_test "Pipe simples" "ls | grep test"

# TESTE 5: Múltiplos pipes
run_test "Múltiplos pipes" "cat file | grep word | wc -l"

# TESTE 6: Redirecionamento de entrada
run_test "Redirecionamento entrada" "cat < input.txt"

# TESTE 7: Redirecionamento de saída
run_test "Redirecionamento saída" "echo hello > output.txt"

# TESTE 8: Append
run_test "Append" "echo hello >> output.txt"

# TESTE 9: Heredoc
run_test "Heredoc" "cat << EOF"

# TESTE 10: Múltiplos espaços
run_test "Múltiplos espaços" "ls    -la     |    grep    test"

# TESTE 11: Arquivo com extensão
run_test "Arquivo com extensão" "cat file.txt"

# TESTE 12: Path absoluto
run_test "Path absoluto" "/bin/ls -la"

# TESTE 13: Mix de operadores
run_test "Mix de operadores" "cat < in.txt | grep test > out.txt"

# TESTE 14: Comando vazio (só Enter)
run_test "Comando vazio" ""

# TESTE 15: Só espaços
run_test "Só espaços" "    "

# Resultado final
echo "==================================="
echo "  RESULTADO DOS TESTES"
echo "==================================="
echo "Total de testes: $TOTAL"
echo "Passou: $PASSED"
echo "Falhou: $((TOTAL - PASSED))"
echo ""
if [ $PASSED -eq $TOTAL ]; then
    echo "🎉 TODOS OS TESTES PASSARAM! 🎉"
else
    echo "⚠️  Alguns testes falharam"
fi
echo "==================================="
