# TODO - My Shell Project

## ✅ Infraestrutura Base (Concluído)
- [x] Configurar Makefile com libft e ft_printf
- [x] Criar estrutura de headers modular (shell.h, types.h, structs.h)
- [x] Implementar loop principal com readline
- [x] Adicionar histórico de comandos
- [x] Configurar signal handlers (SIGINT, SIGQUIT)
- [x] Criar signal handlers para diferentes modos (interactive, executing, heredoc)
- [x] Criar banner de inicialização
- [x] Implementar prompt colorido básico com seta ➜
- [x] Corrigir wrapping do prompt com readline

## ✅ Estruturas de Dados (Concluído)
- [x] Definir enum e_token_type (expandido com 11 tipos)
- [x] Definir struct s_token (linked list com pos, length, quote_type)
- [x] Definir struct s_command (linked list)
- [x] Implementar token_utils (new, free, add_back, list_free)
- [x] Implementar command_utils (new, free, add_back, list_free)
- [x] Adicionar campos length e quote_type em s_token

## ✅ Builtins Básicos (Parcial)
- [x] Implementar builtin exit
- [ ] Implementar builtin cd
- [ ] Implementar builtin pwd
- [ ] Implementar builtin echo (com -n)
- [ ] Implementar builtin env
- [ ] Implementar builtin export
- [ ] Implementar builtin unset
✅ Lexer Básico (Concluído)
- [x] Implementar tokenização básica (espaços)
- [x] Suportar palavras simples (TOKEN_WORD)
- [x] Detectar pipes (|) e OR lógico (||)
- [x] Detectar redirecionamentos (<, >, >>)
- [x] Detectar heredoc (<<)
- [x] Detectar AND lógico (&&)
- [x] Separar tipos TOKEN_APPEND e TOKEN_HEREDOC
- [x] Refatorar em arquivos modulares (lexer_commands.c, lexer_words.c)
- [x] Criar funções específicas (create_pipe_token, create_redirect_in_token, etc)
- [x] Implementar print_tokens para debug
- [x] Adicionar pasta debug/ com lexer_debug.c
- [x] Criar helper is_word_char para melhor detecção
- [x] Testes básicos do lexer

## 🔄 Lexer Avançado (Em Progresso)
- [ ] Suportar aspas simples (')
- [ ] Suportar aspas duplas (")
- [ ] Expansão de variáveis ($VAR, $?, $$)
- [ ] Tratar caracteres de escape (\)
- [ ] Validar sintaxe (quotes não fechadas)
- [ ] Testes completos com edge casesuotes não fechadas)
- [ ] Testes unitários do lexer

## ⏳ Parser (Pendente)
- [ ] Converter lista de tokens em lista de comandos
- [ ] Extrair argumentos (args[])
- [ ] Identificar pipes entre comandos
- [ ] Identificar redirecionamentos de entrada (<)
- [ ] Identificar redirecionamentos de saída (>, >>)
- [ ] Processar heredoc (<<)
- [ ] Validar sintaxe (pipes órfãos, redirs inválidos)
- [ ] Testes unitários do parser

## ⏳ Executor (Pendente)
- [ ] Implementar execução de comandos simples
- [ ] Fork e execve para comandos externos
- [ ] Busca de comandos no PATH
- [ ] Execução de builtins
- [ ] Implementar pipes (comunicação entre processos)
- [ ] Implementar redirecionamentos (<, >)
- [ ] Implementar append (>>)
- [ ] Implementar heredoc (<<)
- [ ] Configurar signals para processos filhos
- [ ] Aguardar processos filhos (wait/waitpid)
- [ ] Capturar exit codes

## ⏳ Expansões (Pendente)
- [ ] Expansão de variáveis de ambiente ($VAR)
- [ ] Expansão de exit code ($?)
- [ ] Expansão de tilde (~)
- [ ] Wildcard básico (*) - opcional

## ⏳ Funcionalidades Avançadas (Opcional)
- [ ] Operadores lógicos (&& e ||)
- [ ] Subshells com parênteses ()
- [ ] Comandos em background (&)
- [ ] Job control (fg, bg, jobs)
- [ ] Autocompleção de comandos
- [ ] Histórico persistente (~/.my_shell_history)

## 🎨 Melhorias de UX (Opcional)
- [ ] Prompt com diretório atual
- [ ] Prompt com branch do git
- [ ] Prompt com exit code (vermelho se erro)
- [ ] Prompt responsivo ao tamanho do terminal
- [x] Script de testes do lexer (test_lexer.sh)
- [x] Documento de testes manuais (TESTS.md)
- [x] Testes básicos de operadores (test_new_operators.sh)
- [ ] Testes do parser
- [x] TODO.md atualizado
- [ ] README.md completo
- [ ] ARCHITECTURE.md (design do projeto)
- [ ] API.md (documentação de funções)
- [ ] CHANGELOG.md (histórico de versões)
- [ ] Comentários em todas as funções
- [ ] Documentar tipos de token e sumatizados
- [ ] Testes com valgrind (memória(s))
- [ ] CHANGELOG.md (histórico de versões)
- [ ] Comentários em todas as funções

## 🧪 Testes
- [ ] Testes do lexer
- [ ] Testes do parser
- [ ] Testes de builtins
- [ ] Testes de redirecionamentos
- [ ] Testes de pipes
- [ ] Testes de edge cases
- [ ] Script de testes automatizados
35%
- **Última Atualização:** 2025-12-17
- **Próximo Milestone:** Implementar Parser
- **Arquivos Criados:** 20+
- **Funções Implementadas:** 30+
- **Tipos de Token:** 11

## 🎯 Próximas Prioridades (Em Ordem)
1. **Parser** - Converter tokens em comandos executáveis
2. **Quotes** - Aspas simples e duplas no lexer
3. **Variáveis** - Expansão de $VAR no lexer
4. **Executor** - Executar comandos simples
5. **Pipes** - Comunicação entre processos
6. **Redirects** - Implementar <, >, >>, <<
7. **Builtins** - cd, pwd, echo, env, export, unset

## 📊 Estatísticas
- **Progresso Geral:** ~15%
- **Última Atualização:** 2025-12-17
- **Próximo Milestone:** Implementar Lexer

---

## Como Usar Este Arquivo
- `[x]` = Tarefa concluída
- `[ ]` = Tarefa pendente
- `🔄` = Em progresso
- `⏳` = Planejado
- `✅` = Concluído

**Comando para marcar como concluído:** Troque `[ ]` por `[x]`
