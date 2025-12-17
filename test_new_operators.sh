#!/bin/bash

echo "=== TESTE: NOVOS OPERADORES ==="
echo ""
echo "Testando >> (append)..."
echo "echo hello >> file.txt" | ./my_shell

echo ""
echo "Testando && (AND lógico)..."
echo "ls && echo success" | ./my_shell

echo ""
echo "Testando || (OR lógico)..."
echo "false || echo fallback" | ./my_shell

echo ""
echo "Testando << (heredoc)..."
echo "cat << EOF" | ./my_shell

echo ""
echo "Testando combinação complexa..."
echo "ls -la && cat < input.txt | grep test >> output.txt || echo failed" | ./my_shell

echo ""
echo "=== TESTES CONCLUÍDOS ==="
