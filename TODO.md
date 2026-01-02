# TODO - My Shell Project

## Project Status Overview

**Last Updated:** January 2, 2026  
**Overall Progress:** 🎯 **65%** Complete  
**Current Phase:** Builtins Implementation  
**Test Coverage:** 31/31 lexer tests + parser manual testing  
**Code Quality:** Norminette compliant

**Progress Summary:**
- ✅ Infrastructure: 100%
- ✅ Lexer: 100%
- 🔄 Parser: 85%
- ✅ Environment: 100%
- ⏳ Executor: 5%
- 🔄 Builtins: 30%

**Recent Progress (Jan 2, 2026):**
- ✅ Implemented complete environment management system
- ✅ Created env module (init, utils, conversion, node management)
- ✅ Integrated environment with main loop using envp
- ✅ Added SHLVL auto-increment
- ✅ Implemented env_to_array() for execve compatibility
- ✅ Reorganized builtins structure (individual files)
- ✅ Implemented builtin_pwd (working)
- ✅ Implemented builtin_exit (working)
- ✅ Shell compiles and runs successfully

---

## ✅ Phase 1: Infrastructure (COMPLETED)

### Base Infrastructure
- [x] Configure Makefile with libft and ft_printf
- [x] Create modular header structure (shell.h, types.h, structs.h, lexer.h)
- [x] Implement main loop with readline
- [x] Add command history
- [x] Configure signal handlers (SIGINT, SIGQUIT)
- [x] Create signal handlers for different modes (interactive, executing, heredoc)
- [x] Create startup banner
- [x] Implement colored prompt with arrow ➜
- [x] Fix prompt wrapping with readline

### Data Structures
- [x] Define e_token_type enum (11 types)
- [x] Define e_word_part_type enum (4 types)
- [x] Define s_token struct (with parts and value fields)
- [x] Define s_word_part struct (linked list)
- [x] Define s_command struct (linked list)
- [x] Implement token_utils (new, free, add_back, list_free)
- [x] Implement word_part_utils (new, free, add_back, list_free)
- [x] Implement command_utils (new, free, add_back, list_free)

---

## ✅ Phase 2: Lexer Module (COMPLETED - 100%)

### Core Lexer
- [x] Implement main lexer loop with delegation pattern
- [x] Create modular file structure (11 files)
- [x] Implement operator detection and tokenization
- [x] Implement word tokenization with composite parts
- [x] Create comprehensive debug output system

### Operators (7/7 implemented)
- [x] Pipe (|) - TOKEN_PIPE
- [x] Logical AND (&&) - TOKEN_AND
- [x] Logical OR (||) - TOKEN_OR
- [x] Redirect in (<) - TOKEN_REDIR_IN
- [x] Redirect out (>) - TOKEN_REDIR_OUT
- [x] Append (>>) - TOKEN_APPEND
- [x] Heredoc (<<) - TOKEN_HEREDOC

### Quotes (3/3 implemented)
- [x] Single quotes (') - PART_SINGLE_QUOTE
- [x] Double quotes (") - PART_DOUBLE_QUOTE
- [x] Escape sequences in double quotes (\\", \\\\)

### Variables (4/4 types implemented)
- [x] Name variables ($USER, $PATH) - extract_name_variable()
- [x] Braced variables (${VAR}) - extract_braced_variable()
- [x] Special variables ($?, $$, $#, $!, $@, $*) - extract_special_variable()
- [x] Positional variables ($0, $1, $2, $123) - extract_positional_variable()
- [x] Dollar literal ($) - fallback handling

### Word Parts System
- [x] PART_LITERAL - plain text
- [x] PART_SINGLE_QUOTE - single quoted content
- [x] PART_DOUBLE_QUOTE - double quoted content
- [x] PART_VARIABLE - variable names
- [x] Composite word support (prefix$VAR'literal'${TEST}"quoted")

### Lexer Architecture
- [x] lexer.c - Main entry point with handle_operator()
- [x] lexer_utils.c - Helper functions
- [x] lexer_logical.c - AND, OR, PIPE operators
- [x] lexer_arrows.c - Redirection operators
- [x] lexer_words.c - Word tokenization with handle_dollar()
- [x] lexer_quotes.c - Quote extraction
- [x] lexer_variables.c - Variable extraction manager
- [x] var_extraction_utils.c - Variable type extractors
- [x] variable_utils.c - Validation functions
- [x] token_utils.c - Token management
- [x] word_utils.c - Word part management

### Debug & Testing
- [x] lexer_debug.c - Token visualization with word parts
- [x] Comprehensive test suite (27 lexer tests)
- [x] Test infrastructure with master runner
- [x] Documentation (tests/README.md)

---

## 🔄 Phase 3: Parser (IN PROGRESS - 85%)

### AST Structure
- [x] Define e_ast_node_type enum (CMD, PIPE, AND, OR)
- [x] Define s_ast_node struct with left/right children
- [x] Define s_command struct with args and redirects
- [x] Define s_redirect struct with type and filename
- [x] Implement node_new(), node_new_command(), node_new_operator()
- [x] Implement node_free() for recursive AST cleanup
- [x] Implement command_new(), command_free(), command_add_arg()

### Basic Parser Structure
- [x] Create token-based parser with AST generation
- [x] Implement parser entry point (parse_tokens)
- [x] Implement recursive descent parsing
- [x] Define operator precedence (redirects > pipes > logical)

### Command Parsing
- [x] Extract command name from first WORD token
- [x] Extract arguments from subsequent WORD tokens
- [x] Expand word_parts into final strings (expand_word)
- [x] Handle empty commands
- [x] Parse simple commands (parse_simple_cmd)

### Operator Parsing
- [x] Parse pipe operators (parse_pipeline)
- [x] Parse logical AND (&&) operators (parse_logical)
- [x] Parse logical OR (||) operators (parse_logical)
- [x] Build correct operator precedence
- [x] Create command sequences with left-accumulation

### Redirection Parsing
- [x] Parse redirect in (<) with filename
- [x] Parse redirect out (>) with filename
- [x] Parse append (>>) with filename
- [x] Support multiple redirections per command
- [ ] Parse heredoc (<<) with delimiter (tokens recognized, processing pending)

### Variable Expansion
- [x] Implement expand_variable() with getenv lookup
- [x] Support special variables ($?, $$, $0)
- [x] Exit status management (getter/setter with encapsulation)
- [x] Handle PART_LITERAL, PART_SINGLE_QUOTE, PART_DOUBLE_QUOTE
- [x] Handle PART_VARIABLE expansion

### Code Quality & Safety
- [x] Replace strcmp with strncmp for security
- [x] Implement exit status encapsulation (static local variable)
- [x] Modular file structure (7 parser files)
- [x] Norminette compliance

### Syntax Validation
- [x] Basic validation (check for remaining tokens)
- [ ] Validate operator placement
- [ ] Check for orphan operators
- [ ] Validate redirection targets
- [ ] Comprehensive error reporting with position

### Debug & Testing
- [x] Implement print_ast() for tree visualization
- [x] Implement print_tree_recursive() with indentation
- [x] Implement print_command() for command details
- [x] Manual testing with echo, ls, pipes, logical operators
- [ ] Automated parser test suite
- [ ] Tests for complex combinations
- [ ] Error handling tests

### Parser Architecture
- [x] parser_build.c - parse_tokens(), parse_logical(), parse_pipeline()
- [x] parse_command.c - parse_simple_cmd(), process_token(), process_word()
- [x] parser_expansion.c - expand_word(), expand_variable()
- [x] parser_special.c - is_special_var(), expand_special_var()
- [x] parser_utils.c - is_word_or_redirect(), is_operator_token(), handle_redirect()
- [x] node_utils.c - node creation and cleanup
- [x] command_utils.c - command management with ft_realloc

---

## ✅ Phase 4: Environment Management (COMPLETED - 100%)

### Environment Initialization
- [x] Define t_env and t_env_var structures
- [x] Implement init_env() to copy system environment
- [x] Parse "KEY=VALUE" strings from envp
- [x] Build linked list of environment variables
- [x] Implement SHLVL auto-increment
- [x] Integrate with main() using envp parameter

### Environment Manipulation
- [x] Implement env_get() to find variables
- [x] Implement env_set() to add/update variables
- [x] Implement env_unset() to remove variables
- [x] Implement get_env_value() helper
- [x] Create/free environment nodes
- [x] Free complete environment structure

### Environment Conversion
- [x] Implement env_to_array() for execve compatibility
- [x] Count environment variables
- [x] Convert linked list to char** array
- [x] Ensure NULL termination
- [x] Implement free_env_array() for cleanup

### Environment Files Structure
- [x] env_init.c - Initialization functions (init_env, parse_env_string, increment_shlvl)
- [x] env_utils.c - Get/set/unset operations
- [x] env_node_utils.c - Node management and cleanup
- [x] env_conversion.c - Array conversion (env_to_array, free_env_array)
- [x] env.h - Function declarations

---

## ⏳ Phase 5: Executor (PENDING - 5%)

### Basic Execution
- [ ] Implement command execution from AST
- [ ] Fork and execve for external commands
- [ ] PATH search for executables
- [ ] Builtin detection and execution
- [ ] Exit code capture and storage

### Expansions
- [ ] Expand variables during execution (not in lexer)
- [ ] Expand $VAR with environment lookup
- [ ] Expand $? with last exit code
- [ ] Expand $$ with shell PID
- [ ] Expand $# with argument count
- [ ] Handle undefined variables (empty string)

### Quote Processing
- [ ] Process PART_SINGLE_QUOTE (no expansion)
- [ ] Process PART_DOUBLE_QUOTE (with expansion)
- [ ] Remove quote delimiters
- [ ] Preserve literal values

### Pipes
- [ ] Create pipe() for inter-process communication
- [ ] Set up pipe connections between commands
- [ ] Handle pipe chains (cmd1 | cmd2 | cmd3)
- [ ] Close unused file descriptors
- [ ] Wait for all processes

### Redirections
- [ ] Implement redirect in (<) with open()
- [ ] Implement redirect out (>) with open()
- [ ] Implement append (>>) with O_APPEND
- [ ] Implement heredoc (<<) with temp file or pipe
- [ ] Error handling for file operations

### Logical Operators
- [ ] Implement AND (&&) - execute right if left succeeds
- [ ] Implement OR (||) - execute right if left fails
- [ ] Short-circuit evaluation
- [ ] Exit code propagation

### Process Management
- [ ] Configure signals for child processes
- [ ] Handle SIGINT during execution
- [ ] Wait for processes (wait/waitpid)
- [ ] Clean up zombie processes
- [ ] Handle foreground/background execution

---

## 🔄 Phase 6: Builtins (IN PROGRESS - 30%)

### Code Organization (Completed)
- [x] Reorganize builtins into individual files
- [x] Create src/builtins/ directory structure
- [x] Move implementations from execution/ to builtins/
- [x] Update all function signatures to (char **args, t_env *env)
- [x] Create dispatcher functions in execute_builtin*.c
- [x] Update builtins.h with proper declarations
- [x] Update Makefile with BUILTINS_DIR section

### Builtin Files Structure
- [x] src/builtins/cd.c - Change directory (stub)
- [x] src/builtins/echo.c - Print arguments (stub)
- [x] src/builtins/env.c - Print environment (stub)
- [x] src/builtins/exit.c - Exit shell ✅ WORKING
- [x] src/builtins/export.c - Set variables (stub)
- [x] src/builtins/pwd.c - Print directory ✅ WORKING
- [x] src/builtins/unset.c - Unset variables (stub)

### Required Builtins Implementation
- [x] exit - Exit shell with optional code ✅ COMPLETE
  - [x] Validate numeric arguments
  - [x] Handle too many arguments error
  - [x] Use last_exit_status if no args
  - [x] Modulo 256 exit codes
- [x] pwd - Print working directory ✅ COMPLETE
  - [x] Use getcwd()
  - [x] Handle errors with perror
- [ ] cd - Change directory (stub)
  - [ ] Support absolute paths
  - [ ] Support relative paths
  - [ ] Support ~ (home directory)
  - [ ] Support - (previous directory)
  - [ ] Update PWD and OLDPWD
- [ ] echo - Print arguments (stub)
  - [ ] Print arguments separated by space
  - [ ] Support -n flag (no newline)
  - [ ] Handle multiple -n flags
- [ ] env - Print environment variables (stub)
  - [ ] Use env_to_array() to get variables
  - [ ] Print each variable on new line
  - [ ] No arguments support
- [ ] export - Set environment variables (stub)
  - [ ] Parse VAR=VALUE format
  - [ ] Validate variable names
  - [ ] Use env_set() to update
  - [ ] Print all variables if no args
- [ ] unset - Unset environment variables (stub)
  - [ ] Use env_unset() to remove
  - [ ] Support multiple arguments
  - [ ] Validate variable names

### Environment Integration
- [x] Store environment in shell structure (t_env)
- [x] Basic environment modification (env_set/env_unset implemented)
- [ ] Complete export builtin implementation
- [ ] Complete unset builtin implementation
- [ ] Complete env builtin implementation
- [x] Pass environment to execve (env_to_array ready)
- [ ] Handle PATH updates

---

## 📊 Testing & Quality (COMPLETED - 100%)

### Test Infrastructure
- [x] Master test runner (run_tests.sh)
- [x] Comprehensive test suite (27 tests)
- [x] Compilation tests (make, make re, make fclean)
- [x] Norminette validation
- [x] Test documentation (tests/README.md)
- [x] Color-coded output
- [x] Automated validation

### Test Coverage
- [x] Operators (7/7 tests)
- [x] Variables (9/9 tests)
- [x] Quotes (3/3 tests)
- [x] Word Parts (4/4 tests)
- [x] Edge Cases (4/4 tests)
- [x] Parser manual tests (commands, pipes, logical operators)
- [ ] Parser automated test suite
- [ ] Executor tests (0 tests)

### Code Quality
- [x] Norminette compliance (100%)
- [x] Modular architecture
- [x] Single Responsibility Principle
- [x] Memory management (no leaks in lexer)
- [ ] Valgrind testing
- [ ] Performance benchmarks

---

## 🎨 Advanced Features (OPTIONAL)

### Advanced Operators
- [ ] Subshells with parentheses ()
- [ ] Command grouping with braces {}
- [ ] Background execution (&)
- [ ] Command substitution $()
- [ ] Arithmetic expansion $(())

### Wildcards
- [ ] Asterisk (*) globbing
- [ ] Question mark (?) single char
- [ ] Bracket expressions ([abc])
- [ ] Tilde expansion (~)

### Job Control
- [ ] Job list tracking
- [ ] fg command (foreground)
- [ ] bg command (background)
- [ ] jobs command (list jobs)
- [ ] Process group management

### UX Improvements
- [ ] Prompt with current directory
- [ ] Prompt with git branch
- [ ] Prompt with exit code color
- [ ] Tab completion
- [ ] Persistent history (~/.my_shell_history)
- [ ] Multi-line command support
- [ ] Syntax highlighting

---

## 📝 Documentation

### Code Documentation
- [x] Lexer documentation (documentation/lexer.md)
- [x] Test documentation (tests/README.md)
- [x] Documentation guide (documentation/DOCUMENTATION_GUIDE.md)
- [ ] Parser documentation
- [ ] Executor documentation
- [ ] Architecture overview

### Project Documentation
- [x] TODO.md (this file)
- [ ] README.md for project root
- [ ] API documentation
- [ ] Usage examples

---

## 🎯 Next Immediate Steps

1. **Parser Completion**
   - ✅ AST structures defined
   - ✅ Basic parsing working
   - ✅ Variable expansion implemented
   - ⏳ Heredoc processing
   - ⏳ Comprehensive syntax validation
   - ⏳ Automated test suite

2. **Executor Implementation**
   - Design executor architecture
   - Implement simple command execution (fork + execve)
   - Add PATH search for executables
   - Implement pipe execution
   - Add redirection handling
   - Integrate with parser AST

3. **Builtins Completion**
   - Implement cd, pwd, echo
   - Implement env, export, unset
   - Test with parser integration

4. **Integration Testing**
   - Create integration test suite
   - Test parser + executor together
   - Add edge cases
   - Valgrind memory testing

---

## 📈 Project Statistics

| Metric | Value |
|--------|-------|
| Total Files | 40+ |
| Lines of Code | ~3500+ |
| Test Coverage | 31/31 lexer + manual parser tests |
| Norminette Status | ✅ All files pass |
| Compilation Status | ✅ Clean build |
| Memory Leaks | ✅ None detected |
| Parser Progress | 85% complete |

---

**Status Legend:**
- ✅ Completed
- 🔄 In Progress  
- ⏳ Pending
- 🎯 Next Priority
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
