# Heredoc Test Suite Documentation

## 📋 Overview

O test suite de heredoc (`test_heredoc.sh`) valida a implementação completa do sistema de heredoc, incluindo:
- Criação e gerenciamento de file descriptors
- Processamento de diferentes tipos de delimitadores
- Integração com pipes e operadores lógicos
- Detecção de erros de sintaxe

## 🎯 Objetivos dos Testes

### 1. Verificar Estrutura `t_redirect`
Cada heredoc deve ter:
- `delimiter`: string do delimitador
- `heredoc_fd`: file descriptor inicializado (-1 ou válido)
- `type`: TOKEN_HEREDOC

### 2. Validar Debug Output
O parser debug deve mostrar:
```
Redirects: << DELIMITER [fd:N]
```
Onde:
- `N = -1`: FD não criado ainda (inicialização)
- `N >= 0`: FD válido criado via pipe()

### 3. Detectar Erros
O parser deve rejeitar:
- Delimitadores vazios: `<< ''`
- Delimitadores undefined: `<< $UNDEF`
- Sintaxe incompleta: `cat <<`

## 📊 Categorias de Testes

### Basic Heredoc (3 tests)
```bash
cat << EOF          # Delimitador padrão
cat << END          # Delimitador alternativo
cat << E            # Delimitador de 1 caractere
```

**Validação**: Parser cria redirect com `delimiter` correto e `heredoc_fd = -1`

### Heredoc with Quotes (2 tests)
```bash
cat << 'EOF'        # Single quotes (literal)
cat << "EOF"        # Double quotes (com expansão)
```

**Validação**: Quotes são processadas e removidas do delimiter

### Heredoc with Variables (2 tests)
```bash
cat << $VAR         # Variável como delimitador
cat << ${DELIMITER} # Variável com chaves
```

**Validação**: Variáveis expandidas para valor final

### Multiple Heredocs (2 tests)
```bash
cat << EOF << END   # Dois heredocs
cat << EOF > out    # Heredoc + redirect
```

**Validação**: Ambos heredocs processados, FDs gerenciados corretamente

### Heredoc in Pipes (2 tests)
```bash
cat << EOF | grep   # Heredoc antes do pipe
echo | cat << EOF   # Heredoc depois do pipe
```

**Validação**: AST construído corretamente, heredoc processado antes da execução

### Heredoc with Logical Operators (2 tests)
```bash
cat << EOF && echo  # Heredoc + AND
cat << EOF || echo  # Heredoc + OR
```

**Validação**: Heredoc processado no primeiro comando, operadores preservados

### Error Cases (3 tests)
```bash
cat << ''           # Empty literal delimiter
cat << $UNDEF       # Empty from expansion
cat <<              # Missing delimiter
```

**Validação**: Parser retorna erro de sintaxe

## 🔍 Debug Output Esperado

### Exemplo 1: Heredoc Simples
```
Input: cat << EOF

=== ABSTRACT SYNTAX TREE ===
Node: COMMAND
  Command: [cat]
  Redirects: << EOF [fd:-1]
===========================
```

### Exemplo 2: Heredoc com FD Criado
```
Input: cat << EOF
line1
line2
EOF

=== ABSTRACT SYNTAX TREE ===
Node: COMMAND
  Command: [cat]
  Redirects: << EOF [fd:3]
===========================
```

O `[fd:3]` indica que `pipe()` foi chamado e retornou FD 3.

### Exemplo 3: Múltiplos Heredocs
```
Input: cat << EOF << END

=== ABSTRACT SYNTAX TREE ===
Node: COMMAND
  Command: [cat]
  Redirects: << EOF [fd:-1] << END [fd:-1]
===========================
```

### Exemplo 4: Erro de Sintaxe
```
Input: cat << ''

syntax error: empty heredoc delimiter
```

## 🧪 Executando os Testes

### Teste Individual
```bash
./tests/test_heredoc.sh
```

### Teste Específico (Manual)
```bash
echo "cat << EOF" | ./my_shell
```

### Todos os Testes
```bash
./run_tests.sh
```

## ✅ Critérios de Sucesso

Um teste passa se:
1. ✅ Parser cria estrutura `t_redirect` correta
2. ✅ `heredoc_fd` inicializado com -1
3. ✅ Debug output mostra `[fd:N]`
4. ✅ Delimiter correto (após expansão/processamento)
5. ✅ Erros detectados e reportados

## 🐛 Troubleshooting

### Problema: FD sempre -1
**Causa**: `process_all_heredocs()` não está sendo chamado
**Solução**: Verificar [parser_command.c](../src/parser/parser_command.c) - deve chamar após validação

### Problema: FD não fechado
**Causa**: `close_heredoc_fd()` não chamado no cleanup
**Solução**: Verificar [redirect_utils.c](../src/parser/redirect_utils.c) - `redirect_free()` deve chamar

### Problema: Debug não mostra [fd:]
**Causa**: [parser_debug_utils.c](../src/debug/parser_debug_utils.c) não atualizado
**Solução**: Atualizar `print_redirects()` para incluir heredoc_fd

### Problema: Syntax error não detectado
**Causa**: Validação de delimiter vazio não implementada
**Solução**: Verificar `has_valid_redirect_target()` em [parser_empty.c](../src/parser/parser_empty.c)

## 📈 Cobertura de Testes

| Funcionalidade | Testes | Status |
|----------------|--------|--------|
| Basic heredoc | 3 | ✅ |
| Quoted delimiters | 2 | ✅ |
| Variable delimiters | 2 | ✅ |
| Multiple heredocs | 2 | ✅ |
| Pipe integration | 2 | ✅ |
| Logical operators | 2 | ✅ |
| Error detection | 3 | ✅ |
| **TOTAL** | **15** | **✅** |

## 🔗 Arquivos Relacionados

- [test_heredoc.sh](../tests/test_heredoc.sh) - Suite de testes
- [heredoc_file_utils.c](../src/parser/heredoc_file_utils.c) - Gerenciamento de FDs
- [parser_empty.c](../src/parser/parser_empty.c) - Validação de delimiters vazios
- [parser_debug_utils.c](../src/debug/parser_debug_utils.c) - Debug output
- [structs.h](../include/structs.h) - Estrutura `t_redirect`

## 📝 Notas de Implementação

### FD Lifecycle
1. **Inicialização**: `heredoc_fd = -1` em `redirect_new()`
2. **Criação**: `heredoc_fd = pipe()` em `process_heredoc()`
3. **Armazenamento**: Salvo em `redir->heredoc_fd`
4. **Uso**: Read end passado para execução
5. **Cleanup**: `close(heredoc_fd)` em `redirect_free()`

### Convenção UNIX
- `-1`: Indica FD inválido/não inicializado
- `>= 0`: FD válido retornado por `pipe()` ou `open()`
- Sempre verificar `fd >= 0` antes de `close(fd)`

---

**Criado:** Janeiro 5, 2026  
**Autor:** Shell Parser Team  
**Versão:** 1.0
