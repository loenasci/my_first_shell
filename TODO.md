# TODO - My Shell Project

## ✅ Infraestrutura Base (Concluído)
- [x] Configurar Makefile com libft e ft_printf
- [x] Criar estrutura de headers modular (shell.h, types.h, structs.h)
- [x] Implementar loop principal com readline
- [x] Adicionar histórico de comandos
- [x] Configurar signal handlers (SIGINT, SIGQUIT)
- [x] Criar banner de inicialização
- [x] Implementar prompt colorido básico

## ✅ Estruturas de Dados (Concluído)
- [x] Definir enum e_token_type
- [x] Definir struct s_token (linked list)
- [x] Definir struct s_command (linked list)
- [x] Implementar token_utils (new, free, add_back, list_free)
- [x] Implementar command_utils (new, free, add_back, list_free)

## ✅ Builtins Básicos (Parcial)
- [x] Implementar builtin exit
- [ ] Implementar builtin cd
- [ ] Implementar builtin pwd
- [ ] Implementar builtin echo (com -n)
- [ ] Implementar builtin env
- [ ] Implementar builtin export
- [ ] Implementar builtin unset

## 🔄 Lexer (Em Progresso)
- [ ] Implementar tokenização básica (espaços)
- [ ] Suportar palavras simples (TOKEN_WORD)
- [ ] Detectar pipes (|)
- [ ] Detectar redirecionamentos (<, >, >>)
- [ ] Detectar heredoc (<<)
- [ ] Suportar aspas simples (')
- [ ] Suportar aspas duplas (")
- [ ] Tratar caracteres de escape (\)
- [ ] Validar sintaxe básica (quotes não fechadas)
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
- [ ] Syntax highlighting durante digitação
- [ ] Sugestões de comandos

## 📝 Documentação
- [ ] README.md completo
- [ ] ARCHITECTURE.md (design do projeto)
- [ ] API.md (documentação de funções)
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

## 🐛 Bugs Conhecidos
- [ ] (nenhum no momento)

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
