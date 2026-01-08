# Guia Completo de Git para iniciantes e intermediários
_Data:  2026-01-07_

> **Objetivo:** explicar **o que cada comando faz**, **quando usar**, **o que pode dar errado**, **cuidados** e **o que as flags significam**. 
>
> Git é poderoso porque registra histórico e permite trabalho paralelo, mas muitos comandos **podem descartar mudanças** ou **reescrever histórico**. Este guia destaca esses pontos.

---

## Índice

### Fundamentos
- [0. Modelo mental:  onde as mudanças "moram"](#0-modelo-mental-onde-as-mudanças-moram)
- [0.1. Como ler flags e parâmetros](#01-como-ler-flags-e-parâmetros-sem-confusão)
- [1. Configuração e identidade](#1-configuração-e-identidade)
- [2. Criar/obter repositório](#2-criarobter-repositório)
- [3. Entender o estado atual](#3-entender-o-estado-atual-do-repo)
- [4. Adicionar e commitar](#4-adicionar-e-commitar-mudanças)
- [5. Ignorar arquivos](#5-ignorar-arquivos)

### Trabalho com Branches
- [6. Branches (trabalho paralelo)](#6-branches-trabalho-paralelo)
- [7. Remotos e sincronização](#7-remotos-e-sincronização)
- [8. Integrar mudanças:  merge vs rebase](#8-integrar-mudanças-merge-vs-rebase)

### Desfazer e Recuperar
- [9. Desfazer mudanças](#9-desfazer-mudanças-sem-perder-controle)
- [10. Guardar trabalho temporariamente](#10-guardar-trabalho-temporariamente)
- [11. Conflitos](#11-conflitos-como-reconhecer-e-resolver)

### Ferramentas Avançadas
- [12. Tags (marcar releases)](#12-tags-marcar-releases)
- [13. Cherry-pick (pegar commits específicos)](#13-cherry-pick-pegar-commits-específicos)
- [14. Inspeção e debug](#14-inspeção-e-debug-de-histórico)
- [15. Limpeza e manutenção](#15-limpeza-e-manutenção-do-repositório)

### Workflows e Boas Práticas
- [16. Workflows de time](#16-workflows-de-time-git-flow-github-flow)
- [17. Boas práticas de commit](#17-boas-práticas-de-commit)
- [18. Trabalhar com forks](#18-trabalhar-com-forks-e-múltiplos-remotes)

### Problemas Comuns
- [19. Troubleshooting (problemas comuns)](#19-troubleshooting-problemas-comuns)
- [20. FAQ rápido](#20-faq-rápido)

### Tópicos Especiais
- [21. Hooks do Git](#21-hooks-do-git)
- [22. Aliases úteis](#22-aliases-úteis)
- [23. Ferramentas visuais](#23-ferramentas-visuais-e-guis)
- [24. Git LFS (arquivos grandes)](#24-git-lfs-large-file-storage)
- [25. Submodules e Subtrees](#25-submodules-e-subtrees)
- [26. Diferenças entre plataformas](#26-diferenças-entre-plataformas-windows-mac-linux)
- [27. Segurança](#27-segurança)
- [28. Comandos raramente usados mas úteis](#28-comandos-raramente-usados-mas-úteis)

### Referência Final
- [29. Glossário completo](#29-glossário-completo)
- [30. Próximos passos](#30-próximos-passos)

---

## 0) Modelo mental: onde as mudanças "moram"

Antes de comandos, entenda as 4 áreas: 

1. **Working tree (diretório de trabalho)**  
   Onde você edita arquivos no seu computador. 

2. **Staging area (index)**  
   Uma "prévia do próximo commit".  Você escolhe o que entra no commit.

3. **Repositório local (`.git`)**  
   Onde ficam commits, branches, tags e o histórico.

4. **Remoto (ex.:  GitHub/GitLab)**  
   Uma cópia para compartilhar e sincronizar com outras pessoas/máquinas.

**Fluxo típico:**
```
Working tree → [git add] → Staging → [git commit] → Repo local → [git push] → Remoto
```

**Atalho mental (importante):**
- `add` = escolhe o que entra no próximo commit
- `commit` = grava no histórico local
- `push` = publica no remoto
- `fetch` = "olha o que mudou no remoto" sem mexer no seu trabalho
- `pull` = `fetch` + integra (merge ou rebase)

---

## 0.1) Como ler flags e parâmetros (sem confusão)

Em Git, a maioria dos comandos segue a ideia: 

```bash
git <comando> [flags/opções] [argumentos]
```

- **Flags/opções** mudam o comportamento do comando.   
  Exemplos:  `-m`, `--global`, `--staged`, `--hard`.
- **Argumentos** geralmente são nomes de arquivos, branches, remotes, hashes, etc.  
  Exemplos: `arquivo.txt`, `main`, `origin`, `a1b2c3d`.

**Flags curtas vs longas:**
- `-m` (curta) geralmente tem uma versão longa `--message` (nem sempre).
- `--global` (longa) costuma não ter versão curta. 

**Dica prática:** quando bater dúvida, rode: 
```bash
git help <comando>
# ou: 
git <comando> --help
```

---

## 1) Configuração e identidade

### `git config`
**O que faz:** lê/escreve configurações do Git (nome, email, editor, comportamento de pull, etc).

#### Níveis de configuração
- `--system`: config do sistema (todos os usuários). Requer admin.
- `--global`: config do seu usuário (vale para todos os repos).
- `--local`: config apenas do repositório atual (padrão quando dentro de um repo).

A prioridade é:  local > global > system

#### Flags e opções importantes
- `--global`: grava/consulta config no seu usuário. 
- `--list`: lista todas as configs.
- `--show-origin`: mostra de qual arquivo veio cada config. 
- `--unset`: remove uma configuração.
- `--get`: obtém valor de uma config específica. 

#### Comandos essenciais
```bash
# Identidade (obrigatório)
git config --global user.name "Seu Nome"
git config --global user.email "voce@exemplo.com"

# Branch padrão
git config --global init.defaultBranch main

# Editor (escolha o seu)
git config --global core. editor "code --wait"    # VS Code
git config --global core. editor "vim"             # Vim
git config --global core.editor "nano"            # Nano

# Ver todas as configs
git config --list --show-origin
```

#### Configurações que evitam confusão (recomendadas para iniciantes)
```bash
# Pull faz merge (mais explícito que rebase)
git config --global pull.rebase false

# Remove branches remotas que não existem mais ao fazer fetch
git config --global fetch.prune true

# Mostra conflitos no estilo diff3 (mais informação)
git config --global merge. conflictStyle diff3

# Reutiliza resoluções de conflitos gravadas
git config --global rerere.enabled true

# Colorir output (geralmente já vem ativo)
git config --global color. ui auto
```

#### Configurações específicas por sistema operacional

**Windows:**
```bash
# Converte LF para CRLF ao checkout, CRLF para LF ao commit
git config --global core.autocrlf true
```

**Mac/Linux:**
```bash
# Não converte, mas avisa sobre CRLF
git config --global core.autocrlf input
```

#### Ver/editar configuração específica
```bash
# Ver valor
git config --get user.name

# Remover configuração
git config --global --unset user.name

# Editar arquivo de config diretamente
git config --global --edit
```

**Cuidados:**
- Email errado causa commits com autoria incorreta.
- `--global` afeta todos os repos:  use com consciência.
- Alguns projetos exigem email corporativo:  use config `--local` nesses casos.

---

## 2) Criar/obter repositório

### `git init`
**O que faz:** cria um repositório Git no diretório atual (cria a pasta `.git`).

```bash
git init
```

#### Flags úteis
- `-b <nome>` ou `--initial-branch <nome>`: define o nome do branch inicial.
  ```bash
  git init -b main
  ```
- `--bare`: cria repositório "bare" (sem working tree, usado em servidores).
  ```bash
  git init --bare
  ```

**Quando usar:**
- Iniciar versionamento em projeto novo ou existente.
- Criar repositório central em servidor. 

**Cuidados:**
- Não rode `git init` dentro de pasta que já é repo (cria repo aninhado, confuso).
- Apagar `.git` remove todo histórico local. 
- Repositório "bare" não permite trabalho direto (só push/pull).

---

### `git clone`
**O que faz:** baixa repositório remoto, configura `origin`, e cria working tree.

```bash
git clone <url>
```

#### Flags e opções importantes
- `-b <branch>`: clona e já faz checkout desse branch.
- `--depth <n>`: "shallow clone" (histórico limitado).
- `--single-branch`: baixa apenas um branch.
- `--recurse-submodules`: clona também submódulos. 
- `--mirror`: clona tudo (todas branches, refs) - usado para backup/migração. 
- `--no-checkout`: clona mas não cria working tree.

#### Exemplos
```bash
# Clone básico
git clone git@github.com:owner/repo.git

# Clone com HTTPS (pede autenticação)
git clone https://github.com/owner/repo. git

# Clone de branch específico
git clone -b develop git@github.com:owner/repo.git

# Clone "raso" (histórico curto, mais rápido)
git clone --depth 1 --single-branch git@github.com:owner/repo.git

# Clone com submodules
git clone --recurse-submodules git@github. com:owner/repo.git

# Clone para pasta com nome diferente
git clone git@github.com:owner/repo.git meu-projeto
```

**Cuidados:**
- `--depth 1` economiza espaço/tempo mas atrapalha algumas operações (rebase em histórico antigo, bisect).
- HTTPS pede senha/token; SSH precisa de chave configurada.
- Submodules não vêm automaticamente (precisa `--recurse-submodules` ou atualizar depois).

---

## 3) Entender o estado atual do repo

### `git status`
**O que faz:** mostra estado do working tree, staging, e relação com remoto.

```bash
git status
```

#### Flags úteis
- `-s` ou `--short`: saída curta (2 colunas de status).
- `-b` ou `--branch`: mostra info do branch. 
- `--ignored`: mostra também arquivos ignorados.
- `-u` ou `--untracked-files`: controla como mostra untracked (normal/no/all).

#### Exemplos
```bash
git status
git status -sb              # curto + branch (recomendado)
git status --ignored        # ver . gitignore funcionando
```

**Como ler output curto (`-s`):**
```
XY arquivo.txt
```
- `X` = staging
- `Y` = working tree
- `M` = modificado
- `A` = adicionado
- `D` = deletado
- `R` = renomeado
- `?? ` = untracked

Exemplo: 
```
 M arquivo1.txt    # modificado no working tree
M  arquivo2.txt    # modificado no staging
MM arquivo3.txt    # modificado no staging E no working tree
? ? novo. txt        # untracked
```

**Cuidados:**
- Use sempre antes de comandos destrutivos (restore/reset/rebase).

---

### `git diff`
**O que faz:** mostra diferenças linha a linha. 

```bash
git diff
```

#### Flags e opções importantes
- `--staged` (ou `--cached`): compara staging vs último commit.
- `--name-only`: só nomes de arquivos.
- `--name-status`: nomes + status (M/A/D).
- `--stat`: resumo estatístico.
- `--word-diff`: diff palavra por palavra (bom para textos).
- `--color-words`: similar, com cores. 
- `-- <path>`: limita diff a arquivos/pastas específicos. 
- `-U<n>`: quantidade de linhas de contexto (padrão 3).

#### Exemplos práticos
```bash
# Working tree vs staging
git diff

# Staging vs último commit
git diff --staged

# Só nomes
git diff --name-only

# Resumo
git diff --stat

# Entre dois commits
git diff <hash1> <hash2>

# Entre branches
git diff main..feature/x

# Um arquivo específico
git diff -- arquivo.txt

# Diff de um arquivo em dois branches
git diff main feature/x -- arquivo.txt

# Word diff (bom para textos/markdown)
git diff --word-diff
```

**Cuidados:**
- `git diff` não mostra untracked (use `git status`).
- Antes de commitar, `git diff --staged` é essencial.

---

### `git log`
**O que faz:** mostra histórico de commits. 

```bash
git log
```

#### Flags e opções importantes

**Formatação:**
- `--oneline`: 1 linha por commit.
- `--graph`: desenha grafo de branches/merges.
- `--decorate`: mostra branches/tags. 
- `--all`: inclui todos os branches.
- `--pretty=<format>`: formato customizado. 

**Filtragem:**
- `-n <N>` ou `--max-count=<N>`: limita quantidade. 
- `--since="2 weeks ago"`: commits desde data.
- `--until="2024-01-01"`: commits até data.
- `--author=<nome>`: filtra por autor.
- `--grep=<texto>`: busca em mensagens de commit. 
- `-- <path>`: histórico de arquivo/pasta. 
- `-S<texto>`: "pickaxe" - commits que adicionaram/removeram texto no código.

**Visualização:**
- `-p`: mostra patch (diff) de cada commit.
- `--stat`: mostra estatísticas.
- `--name-only`: só nomes de arquivos. 

#### Exemplos práticos
```bash
# Visualização recomendada
git log --oneline --graph --decorate --all

# Últimos 10 commits
git log --oneline -n 10

# Histórico de um arquivo
git log --oneline -- arquivo. txt

# Commits das últimas 2 semanas
git log --since="2 weeks ago"

# Commits de um autor
git log --author="loenasci"

# Buscar em mensagens
git log --grep="fix bug"

# Ver patches
git log -p -n 3

# Commits que mexeram em texto específico no código
git log -S"função_importante"

# Formato customizado
git log --pretty=format:"%h - %an, %ar : %s"
```

**Aliases úteis para `.bashrc` ou `.zshrc`:**
```bash
alias glog="git log --oneline --graph --decorate --all"
alias glg="git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
```

---

### `git show`
**O que faz:** mostra detalhes de commit/tag/objeto (mensagem + diff).

#### Flags úteis
- `--stat`: resumo. 
- `--name-only`: só arquivos.
- `--pretty=oneline`: formato simplificado. 

```bash
git show HEAD
git show --stat HEAD
git show --name-only <hash>
git show <tag>
git show <branch>: <arquivo>    # conteúdo de arquivo em branch específico
```

---

## 4) Adicionar e commitar mudanças

### `git add`
**O que faz:** coloca mudanças no staging (prepara para commit).

```bash
git add arquivo.txt
```

#### Flags e opções importantes (explicadas de forma simples)

- **`.`**:  adiciona tudo **do diretório atual para baixo**.
  - ⚠️ Confusão comum: se você está em `src/`, `git add . ` não pega mudanças fora de `src/`.

- **`-A` ou `--all`**: adiciona **tudo no repositório** (inclusive removidos).
  - É o "mais completo". 

- **`-u` ou `--update`**: adiciona apenas mudanças em arquivos já rastreados (não inclui novos).
  - Bom quando você quer evitar "pegar arquivo novo sem querer".

- **`-p` ou `--patch`**: modo interativo (você escolhe pedaços do diff).
  - **Muito recomendado para aprender e evitar commits misturados**.

- **`-n` ou `--dry-run`**: simula, sem adicionar de verdade.
  - Ótimo para checar o que seria adicionado. 

- **`-v` ou `--verbose`**: mostra mais detalhes. 

- **`-f` ou `--force`**: força adicionar arquivo ignorado.

- **`-i` ou `--interactive`**: modo interativo completo (menu).

#### Entendendo `git add -p` (patch mode)

Quando você roda `git add -p`, o Git mostra cada "pedaço" (hunk) de mudança e pergunta o que fazer:

```
y - adiciona este hunk
n - não adiciona
q - sair (não adiciona este nem os seguintes)
a - adiciona este e todos os seguintes no arquivo
d - não adiciona este nem os seguintes no arquivo
s - dividir hunk em peda��os menores
e - editar manualmente o hunk
? - ajuda
```

#### Exemplos
```bash
# Interativo (recomendado)
git add -p

# Tudo no repo
git add -A

# Só arquivos já rastreados
git add -u

# Simular
git add -n . 

# Forçar arquivo ignorado
git add -f arquivo-ignorado.txt
```

**Cuidados importantes:**
- Evite `git add .` sem revisar `git status` e `git diff`.
- `git add -p` é um "superpoder" para evitar commits misturados. 
- Adicionar arquivo com segredo (`.env`, chaves) por engano é comum:  use `.gitignore`.

---

### `git commit`
**O que faz:** cria commit com o conteúdo staged.

```bash
git commit -m "Mensagem"
```

#### Flags e opções importantes

- **`-m "<msg>"`**: define a mensagem inline.
- **`-a`**: adiciona automaticamente mudanças **somente** em arquivos já rastreados e commita.
  - ⚠️ Confusão comum: não inclui arquivo novo (untracked).
- **`--amend`**: reescreve o último commit (mensagem e/ou conteúdo).
- **`--no-edit`**: usado com `--amend` para manter mensagem antiga. 
- **`--allow-empty`**: cria commit mesmo sem mudanças (raro, útil em CI).
- **`--allow-empty-message`**: permite commit sem mensagem (não recomendado).
- **`-v` ou `--verbose`**: mostra diff no editor de commit.
- **`--no-verify`**: pula hooks (pre-commit, commit-msg).
- **`--date=<data>`**: define data do commit manualmente (avançado).
- **`--author="Nome <email>"`**: define autor diferente (pair programming).

#### Exemplos
```bash
# Básico
git commit -m "Adiciona validação no login"

# Stage + commit (só arquivos rastreados)
git commit -am "Ajusta logs"

# Corrigir último commit (mensagem)
git commit --amend -m "Corrige mensagem"

# Adicionar mudanças esquecidas ao último commit
git add arquivo-esquecido.txt
git commit --amend --no-edit

# Commit com co-autor (pair programming)
git commit -m "Implementa feature X

Co-authored-by: João Silva <joao@exemplo.com>"

# Ver diff enquanto escreve mensagem
git commit -v
```

**Boas práticas de mensagem (detalhadas na seção 17):**
- Curta e direta, no imperativo:  "Adiciona", "Remove", "Corrige"
- Evite:  "Update", "Fix", "coisas", "WIP"
- Primeira linha: resumo (max 50 chars)
- Linha em branco
- Detalhes adicionais se necessário

**Cuidados:**
- `git commit -am` NÃO inclui arquivos novos (untracked).
- `--amend` reescreve histórico:  evite se já deu push e outras pessoas puxaram.
- `--no-verify` pula validações importantes (linters, testes): use com cautela.

---

## 5) Ignorar arquivos

### `.gitignore`
**O que faz:** evita que arquivos untracked sejam sugeridos para commit.

#### Sintaxe básica
```gitignore
# Comentário

# Arquivo específico
arquivo.txt

# Todos arquivos . log
*.log

# Pasta inteira
node_modules/
dist/
build/

# Arquivo em qualquer subpasta
**/*.tmp

# Exceto (negação)
!importante.log

# Apenas na raiz
/raiz. txt

# Qualquer pasta chamada temp
**/temp/
```

#### Exemplos por linguagem/framework

**Node.js:**
```gitignore
node_modules/
npm-debug.log
. env
dist/
build/
. DS_Store
```

**Python:**
```gitignore
__pycache__/
*.py[cod]
*$py.class
. venv/
venv/
ENV/
. env
*. egg-info/
dist/
build/
```

**Java:**
```gitignore
*.class
*. jar
*.war
target/
. idea/
*. iml
```

**C/C++:**
```gitignore
*. o
*.out
*.exe
*.so
*.a
build/
```

**IDE/Editor:**
```gitignore
.vscode/
.idea/
*.swp
*.swo
*~
.DS_Store
```

#### Recursos úteis
- [gitignore.io](https://gitignore.io) - gera `.gitignore` para qualquer stack
- [GitHub gitignore templates](https://github.com/github/gitignore) - templates oficiais

**Cuidados:**
- `.gitignore` não "desrastreia" arquivos já commitados.
- Se comitar segredo, `.gitignore` não resolve:  precisa reescrever histórico.

---

### `git rm` (remover arquivo do Git)

#### Flags importantes
- `--cached`: remove do Git, mas mantém no disco.
- `-r`: recursivo (pastas).
- `-f`: força remoção. 

#### Cenários comuns

**Parar de rastrear arquivo já commitado (sem apagar do disco):**
```bash
git rm --cached . env
git commit -m "Para de rastrear . env"
```

**Remover pasta inteira do Git:**
```bash
git rm -r --cached node_modules/
git commit -m "Remove node_modules do Git"
```

**Remover arquivo e do disco:**
```bash
git rm arquivo.txt
git commit -m "Remove arquivo. txt"
```

---

### `git clean` (remover arquivos untracked)

**O que faz:** remove arquivos que não estão sendo rastreados.

#### Flags importantes
- `-n` ou `--dry-run`: simula (mostra o que seria removido).
- `-f`: força remoção (obrigatório).
- `-d`: inclui diretórios.
- `-x`: inclui arquivos ignorados (. gitignore).
- `-i`: modo interativo.

#### Exemplos
```bash
# Ver o que seria removido
git clean -n

# Remover arquivos untracked
git clean -f

# Remover arquivos e pastas untracked
git clean -fd

# Remover tudo (inclusive ignorados) - cuidado!
git clean -fdx

# Modo interativo
git clean -i
```

**Cuidados:**
- `git clean` pode apagar trabalho importante.
- Sempre use `-n` antes para conferir.
- `-x` remove também coisas do `.gitignore` (node_modules, build, etc).

---

## 6) Branches (trabalho paralelo)

### `git branch`
**O que faz:** lista/cria/deleta/renomeia branches.

#### Flags e opções importantes

**Listagem:**
- *(sem flags)*: lista branches locais.
- `-a` ou `--all`: mostra locais e remotos.
- `-r` ou `--remote`: só remotos.
- `-v` ou `--verbose`: mostra também último commit.
- `-vv`: mostra upstream (tracking).

**Criação:**
- `<nome>`: cria branch (não muda para ele).

**Deleção:**
- `-d`: deleta branch só se já estiver merged.
- `-D`: força deleção (perigoso).

**Renomeação:**
- `-m <novo>`: renomeia branch atual.
- `-m <antigo> <novo>`: renomeia outro branch. 
- `-M`: renomeia forçado (sobrescreve se já existir).

**Outros:**
- `--show-current`: mostra nome do branch atual.
- `--contains <commit>`: lista branches que contêm o commit. 
- `--merged`: lista branches já merged.
- `--no-merged`: lista branches não merged.

#### Exemplos
```bash
# Listar
git branch
git branch -a
git branch -vv

# Ver branch atual
git branch --show-current

# Criar
git branch feature/nova-funcionalidade

# Renomear
git branch -m nome-antigo nome-novo

# Deletar
git branch -d feature/concluida
git branch -D feature/abandonada

# Ver branches merged
git branch --merged main
git branch --no-merged main

# Ver quais branches contém um commit
git branch --contains <hash>
```

**Cuidados:**
- `-D` pode jogar fora commits não merged (use `git reflog` para recuperar).
- Deletar branch local não deleta no remoto (precisa `git push origin --delete <branch>`).

---

### `git switch` (recomendado desde Git 2.23)
**O que faz:** troca de branch e cria branches. 

#### Flags importantes
- `-c <nome>` ou `--create <nome>`: cria branch e muda. 
- `-C <nome>`: cria forçado (sobrescreve se existir).
- `-`: volta para branch anterior (tipo "alt-tab").
- `--detach`: entra em detached HEAD. 
- `--discard-changes`: descarta mudanças locais (perigoso).
- `--merge`: tenta fazer merge de mudanças locais ao trocar.

#### Exemplos
```bash
# Trocar
git switch main

# Criar e trocar
git switch -c feature/minha-feature

# Voltar para anterior
git switch -

# Detached HEAD (exploração)
git switch --detach <hash>
```

**Cuidados:**
- Se tiver mudanças não commitadas, Git pode impedir troca ou carregar mudanças junto.
- Antes de trocar:  commitar ou usar `git stash`.

---

### `git checkout` (antigo, mas onipresente em tutoriais)
**O que faz:** troca branch, cria branch, restaura arquivo, navega por commits.

#### Por que evitar em favor de `switch` e `restore`?
- `checkout` faz coisas demais (confuso para iniciantes).
- `switch` (branches) e `restore` (arquivos) são mais claros. 

#### Equivalências
```bash
# Antigo                           # Moderno
git checkout main                  git switch main
git checkout -b feature/x          git switch -c feature/x
git checkout -- arquivo.txt        git restore arquivo.txt
git checkout <hash> -- arquivo.txt git restore --source=<hash> arquivo.txt
```

#### Uso que ainda aparece
```bash
# Detached HEAD (explorar histórico)
git checkout <hash>

# Pegar arquivo de outro branch
git checkout main -- arquivo.txt
```

**Cuidados com detached HEAD:**
- Você está "num commit", não num branch.
- Commits feitos aqui ficam órfãos se você sair sem criar branch.
- Para salvar: `git switch -c salva-meu-trabalho`.

---

## 7) Remotos e sincronização

### `git remote`
**O que faz:** gerencia remotes (apelidos para repos remotos).

#### Subcomandos
- `add <nome> <url>`: adiciona remote.
- `remove <nome>`: remove remote.
- `rename <antigo> <novo>`: renomeia. 
- `set-url <nome> <nova-url>`: muda URL.
- `get-url <nome>`: mostra URL.
- `show <nome>`: mostra detalhes.
- `-v`: lista com URLs.

#### Exemplos
```bash
# Ver remotes
git remote -v

# Adicionar
git remote add origin git@github.com:owner/repo.git

# Mudar URL (ex.:  migrar de HTTPS para SSH)
git remote set-url origin git@github.com:owner/repo.git

# Remover
git remote remove origin

# Renomear
git remote rename origin upstream

# Ver detalhes
git remote show origin
```

**Workflow com fork (comum em open source):**
```bash
# Seu fork
git remote add origin git@github.com:seu-usuario/repo.git

# Repo original
git remote add upstream git@github.com:usuario-original/repo.git

# Buscar atualizações do original
git fetch upstream

# Atualizar seu main com o original
git switch main
git merge upstream/main
```

**Cuidados:**
- Remote errado pode fazer você dar push no lugar errado.
- Sempre confira com `git remote -v`.

---

### `git fetch`
**O que faz:** baixa atualizações do remoto **sem integrar** no seu trabalho.

#### Flags importantes
- `--all`: busca de todos os remotes.
- `--prune` (`-p`): remove referências remotas que não existem mais.
- `--tags`: baixa tags. 
- `--dry-run`: simula. 

#### Exemplos
```bash
# Do remote principal
git fetch origin

# De todos os remotes
git fetch --all

# Limpar branches "mortos"
git fetch --prune

# Só tags
git fetch --tags
```

**Por que fetch é "seguro":**
- Atualiza referências remotas (`origin/main`) mas não mexe no seu branch atual.
- Você pode inspecionar antes de integrar.

**Workflow recomendado:**
```bash
# 1. Buscar atualizações
git fetch origin

# 2. Ver diferenças
git log --oneline main..origin/main

# 3. Integrar quando quiser
git merge origin/main
# ou
git rebase origin/main
```

**Cuidados:**
- Após fetch, precisa integrar manualmente (merge/rebase).

---

### `git pull`
**O que faz:** `fetch` + integra (merge ou rebase, dependendo da config).

#### Flags importantes
- `--rebase`: integra via rebase em vez de merge.
- `--no-rebase`: força merge.
- `--ff-only`: só aceita fast-forward (se precisar merge commit, falha).
  - Muito útil para evitar merges "sem querer". 
- `--no-ff`: cria merge commit mesmo podendo fast-forward. 
- `--autostash`: faz stash automático de mudanças locais, puxa, e reaplica.

#### Exemplos
```bash
# Pull padrão
git pull origin main

# Pull com rebase
git pull --rebase

# Só fast-forward (seguro)
git pull --ff-only

# Com autostash (útil)
git pull --autostash
```

**Diferença entre pull com merge vs rebase:**

**Pull com merge (padrão):**
```bash
git pull origin main
# = git fetch origin + git merge origin/main
```
- Pode criar merge commit.
- Preserva histórico completo. 

**Pull com rebase:**
```bash
git pull --rebase origin main
# = git fetch origin + git rebase origin/main
```
- Histórico linear. 
- Reescreve seus commits locais.

**Configuração recomendada:**
```bash
# Definir comportamento padrão
git config --global pull.rebase false    # sempre merge
# ou
git config --global pull. rebase true     # sempre rebase
# ou
git config --global pull. ff only         # só fast-forward
```

**Cuidados:**
- `pull` pode surpreender com merge commit.
- Se working tree não está limpo, pode falhar ou conflitar. 
- Para mais controle:  `fetch` + `merge` ou `rebase` manualmente.

---

### `git push`
**O que faz:** envia commits locais para o remoto.

#### Flags importantes
- `-u` ou `--set-upstream`: define upstream (tracking).
- `--force`: força push reescrevendo remoto (perigoso).
- `--force-with-lease`: força, mas falha se remoto mudou desde última vez (mais seguro).
- `--tags`: envia tags.
- `--all`: envia todos os branches. 
- `--dry-run`: simula. 
- `--delete`: deleta branch/tag remoto.

#### Exemplos
```bash
# Push básico (se upstream já definido)
git push

# Primeira vez no branch (define upstream)
git push -u origin feature/minha-feature

# Push de todas as tags
git push --tags

# Push forçado (cuidado!)
git push --force-with-lease

# Deletar branch remoto
git push origin --delete feature/antiga

# Deletar tag remota
git push origin --delete v1.0.0

# Simular
git push --dry-run
```

**Entendendo upstream (tracking):**

Quando você faz `git push -u origin feature/x`:
- Cria branch `feature/x` no remoto.
- Define `origin/feature/x` como upstream do seu branch local.
- Depois disso, pode usar só `git push` e `git pull` sem argumentos.

**Ver upstream atual:**
```bash
git branch -vv
```

**Definir upstream manualmente:**
```bash
git branch --set-upstream-to=origin/feature/x
```

**Push forçado:  quando usar? **
- Após `git commit --amend` (reescreveu último commit).
- Após `git rebase` (reescreveu histórico).
- **Só em branches seus**, nunca em `main` compartilhada.

**`--force` vs `--force-with-lease`:**
- `--force`: sobrescreve cegamente (pode apagar trabalho de outros).
- `--force-with-lease`: verifica se o remoto está no estado que você viu por último.

**Cuidados:**
- Push forçado pode apagar trabalho de outras pessoas.
- Sempre combine com o time antes de force push em branch compartilhado. 
- Alguns repos protegem branches importantes (ex.: `main`) contra force push.

---

## 8) Integrar mudanças:  merge vs rebase

### `git merge`
**O que faz:** integra outro branch/commit no branch atual, preservando histórico.

#### Flags importantes
- `--no-ff`: cria merge commit mesmo podendo fast-forward.
- `--ff-only`: só aceita fast-forward (falha se precisar merge commit).
- `--squash`: junta todos os commits do branch em 1 commit (não cria merge commit).
- `--abort`: cancela merge em conflito. 
- `--continue`: continua após resolver conflitos (raramente necessário, só `commit`).
- `-s <estratégia>` ou `--strategy=<estratégia>`: define estratégia de merge.

#### Estratégias de merge
- `recursive` (padrão): para merge de 2 branches.
- `ours`: em conflito, fica com "nosso lado" automaticamente.
- `theirs`: em conflito, fica com "outro lado" (precisa usar com opção `-X`).
- `octopus`: merge de 3+ branches (raramente usado).

#### Exemplos
```bash
# Merge básico
git merge origin/main

# Merge sem fast-forward (sempre cria merge commit)
git merge --no-ff feature/x

# Merge squash (junta commits em 1)
git merge --squash feature/x
git commit -m "Adiciona feature X completa"

# Merge com estratégia "ours" (em conflitos, prefere nosso lado)
git merge -s recursive -X ours origin/main

# Merge com estratégia "theirs" (em conflitos, prefere outro lado)
git merge -s recursive -X theirs origin/main

# Cancelar merge em conflito
git merge --abort
```

**Fast-forward vs merge commit:**

**Fast-forward (sem merge commit):**
```
main:      A - B - C
                   \
feature:             D - E

# git merge feature (estando em main)

main:     A - B - C - D - E
```

**Merge commit (com --no-ff ou quando há divergência):**
```
main:     A - B - C -------- M
                   \        /
feature:            D ----- E
```

**Quando usar cada um:**
- `--ff-only`: quando você quer garantir que está só "puxando atualizações" (não integrar trabalho paralelo).
- `--no-ff`: quando você quer sempre ter merge commit (facilita ver "quando feature X foi integrada").
- `--squash`: quando você quer branch limpo mas histórico linear (comum em PR que tem "commits de WIP").

**Cuidados:**
- Conflitos podem ocorrer:  resolver, `git add`, `git commit`.
- Merge commit pode "poluir" histórico (alguns times evitam, outros preferem).

---

### `git rebase`
**O que faz:** "reaplica" commits do branch atual em cima de outra base (histórico linear).

#### Flags importantes
- `-i` ou `--interactive`: rebase interativo (squash, reword, reorder).
- `--continue`: continua após resolver conflitos.
- `--abort`: cancela e volta ao estado anterior.
- `--skip`: pula commit atual (se der conflito irresolvível).
- `--onto <nova-base>`: rebase avançado (muda a base).
- `--autosquash`: usado com `commit --fixup` (avançado).
- `--autostash`: faz stash automático.

#### Exemplos
```bash
# Rebase básico
git rebase origin/main

# Rebase interativo (últimos 3 commits)
git rebase -i HEAD~3

# Rebase avançado (--onto)
git rebase --onto main feature-antiga feature-nova

# Continuar após resolver conflito
git rebase --continue

# Cancelar rebase
git rebase --abort
```

**Rebase interativo (`-i`):**

Quando você roda `git rebase -i HEAD~3`, abre editor com: 

```
pick a1b2c3d Commit 1
pick d4e5f6g Commit 2
pick h7i8j9k Commit 3
```

Comandos disponíveis:
- `pick` (p): mantém commit.
- `reword` (r): mantém commit mas edita mensagem.
- `edit` (e): para para editar commit (código + mensagem).
- `squash` (s): junta com commit anterior (mantém ambas mensagens).
- `fixup` (f): junta com commit anterior (descarta mensagem deste).
- `drop` (d): remove commit. 
- Você pode reordenar linhas para reordenar commits.

**Exemplo de squash:**
```
pick a1b2c3d Implementa feature X (parte 1)
squash d4e5f6g Implementa feature X (parte 2)
squash h7i8j9k Fix typo
```
Resultado: 1 commit com mensagem combinada.

**Exemplo de reword:**
```
pick a1b2c3d Comit com erro de ortografia
reword d4e5f6g Adiciona validação
```
Editor abrirá para você corrigir primeira mensagem.

**Rebase vs Merge:  quando usar o quê?**

| Situação | Recomendação |
|----------|-------------|
| Atualizar seu branch com `main` | Rebase (histórico linear) |
| Integrar feature no `main` | Merge (preserva contexto) |
| "Limpar" commits locais antes de PR | Rebase interativo |
| Commits já publicados/compartilhados | Nunca rebase (use merge) |
| Projeto prefere histórico linear | Rebase |
| Projeto prefere histórico completo | Merge |

**Cuidados (CRÍTICO):**
- Rebase **reescreve histórico** (novos hashes).
- **Nunca rebase commits já publicados** que outras pessoas puxaram.
- Regra de ouro: rebase só commits seus (locais).
- Se precisar force push após rebase, avise o time.

---

### `git rebase --onto` (avançado)

Útil para "mover" série de commits de uma base para outra. 

**Cenário:** você criou `feature-B` a partir de `feature-A`, mas agora `feature-A` mudou muito e você quer rebasear `feature-B` direto na `main`.

```bash
# Situação: 
#   main: A - B - C
#   feature-A: C - D - E
#   feature-B: E - F - G

# Rebasear feature-B de "E" (feature-A) para "C" (main)
git rebase --onto main feature-A feature-B

# Resultado:
#   main: A - B - C
#   feature-B: C - F' - G'
```

---

## 9) Desfazer mudanças (sem perder controle)

### Resumo rápido:  qual comando usar?

| Situação | Comando |
|----------|---------|
| Descartei arquivo sem querer, não commitei | `git restore arquivo.txt` |
| Adicionei arquivo errado ao staging | `git restore --staged arquivo.txt` |
| Quero "desfazer" último commit mas manter mudanças | `git reset --soft HEAD~1` |
| Quero desfazer último commit e staging, mas manter arquivos | `git reset --mixed HEAD~1` |
| Quero desfazer último commit e apagar mudanças | `git reset --hard HEAD~1` (cuidado!) |
| Quero desfazer commit já publicado (sem reescrever histórico) | `git revert <hash>` |
| Fiz bagunça e quero voltar ao estado de ontem | `git reflog` + `git reset --hard <hash>` |

---

### `git restore`
**O que faz:** restaura estado de arquivos (working tree e/ou staging).

#### Flags importantes
- `--staged`: mexe no staging (tira do staging).
- `--worktree`: mexe no working tree (padrão).
- `--source=<ref>`: restaura a partir de commit/branch específico.
- `-p` ou `--patch`: modo interativo. 

#### Exemplos
```bash
# Descartar mudanças em arquivo (volta ao último commit)
git restore arquivo.txt

# Tirar arquivo do staging (mas manter mudanças)
git restore --staged arquivo.txt

# Restaurar arquivo de um commit específico
git restore --source=HEAD~2 arquivo. txt

# Restaurar de outro branch
git restore --source=main arquivo.txt

# Modo interativo
git restore -p
```

**Cuidados:**
- `git restore arquivo.txt` **apaga mudanças não commitadas** (difícil recuperar).
- Sempre use `git diff` antes.

---

### `git revert`
**O que faz:** cria novo commit que **desfaz** outro commit (sem reescrever histórico).

#### Flags importantes
- `--no-edit`: usa mensagem padrão.
- `-n` ou `--no-commit`: aplica revert no working tree/staging mas não commita ainda.
- `-m <parent-number>`: necessário para reverter merge commit. 

#### Exemplos
```bash
# Revert de um commit
git revert <hash>

# Revert sem abrir editor
git revert --no-edit <hash>

# Revert de vários commits (não commita cada um)
git revert -n <hash1>
git revert -n <hash2>
git commit -m "Reverte mudanças X e Y"

# Revert de merge commit (precisa especificar parent)
git revert -m 1 <merge-hash>
```

**Reverter merge commit:**

Merge commit tem 2 parents (ou mais):
- Parent 1: branch onde você estava (geralmente `main`)
- Parent 2: branch que foi integrado (geralmente feature)

`-m 1` significa "manter parent 1" (desfazer o que veio do parent 2).

**Quando usar:**
- Commit já publicado que precisa ser desfeito.
- Quer manter histórico completo (auditoria).
- Seguro para trabalho em equipe.

**Cuidados:**
- Revert não "apaga" commit do histórico, cria outro que neutraliza.
- Reverter um merge pode ser confuso depois (se quiser re-merge).

---

### `git reset` (avançado, use com cautela)
**O que faz:** move ponteiro do branch (e opcionalmente mexe em staging/working tree).

#### Modos (flags)
- `--soft`: move HEAD, **mantém** staging e working tree.
- `--mixed` (padrão): move HEAD, **limpa** staging, mantém working tree.
- `--hard`: move HEAD e **apaga** staging e working tree (perigoso).

#### Visualização dos modos

**Situação inicial:**
```
HEAD → main → C3
Staging:  mudanças de C3
Working tree: mudanças adicionais
```

**`git reset --soft HEAD~1`:**
```
HEAD → main → C2
Staging: mudanças de C3 (mantido)
Working tree: mudanças de C3 + adicionais (mantido)
```
Uso: "quero refazer o commit com mensagem melhor". 

**`git reset --mixed HEAD~1`** (padrão):
```
HEAD → main → C2
Staging: vazio
Working tree: mudanças de C3 + adicionais (mantido)
```
Uso: "quero re-organizar o que vai em cada commit".

**`git reset --hard HEAD~1`:**
```
HEAD → main → C2
Staging: vazio
Working tree: estado de C2 (mudanças PERDIDAS)
```
Uso: "quero descartar tudo" (perigoso).

#### Exemplos
```bash
# Desfazer último commit, manter mudanças
git reset --soft HEAD~1

# Desfazer último commit, tirar do staging
git reset --mixed HEAD~1

# Desfazer último commit e apagar mudanças
git reset --hard HEAD~1

# Voltar para commit específico
git reset --hard <hash>

# Mover branch para outro lugar sem mexer em arquivos
git reset --soft <hash>
```

**Cenários práticos:**

**1. Commitei cedo demais, quero adicionar mais:**
```bash
git reset --soft HEAD~1
# faz mais mudanças
git add .
git commit -m "Mensagem completa"
```

**2. Commitei no branch errado:**
```bash
# Salva hash do commit
git log --oneline  # anota o hash

# Desfaz commit mas mantém mudanças
git reset --soft HEAD~1

# Troca de branch
git switch branch-correto

# Commita
git commit -m "Mensagem"
```

**3. Quero refazer últimos 3 commits:**
```bash
git reset --soft HEAD~3
git commit -m "Refaz trabalho em 1 commit"
```

**Cuidados (CRÍTICO):**
- `--hard` pode **apagar trabalho** sem volta fácil.
- Reset em commits já publicados exige force push (perigoso para equipe).
- Use `git reflog` para recuperar de desastres.

---

### `git reflog` (SALVA-VIDAS)
**O que faz:** mostra histórico local de onde HEAD apontou (inclusive após reset/rebase).

#### Flags úteis
- `-n <N>`: limita quantidade. 
- `--date=iso`: data mais legível.
- `--all`: inclui refs de todos os branches.

#### Exemplos
```bash
# Ver reflog
git reflog

# Com datas
git reflog --date=iso

# Últimas 20 entradas
git reflog -n 20

# Reflog de um branch específico
git reflog show main
```

**Output típico:**
```
a1b2c3d (HEAD -> main) HEAD@{0}: commit:  Adiciona feature X
d4e5f6g HEAD@{1}: commit: Corrige bug Y
h7i8j9k HEAD@{2}:  reset: moving to HEAD~1
k9l0m1n HEAD@{3}: commit: Commit que foi desfeito
```

**Recuperação típica:**

**Cenário:  fiz `git reset --hard` e me arrependi**
```bash
# 1. Ver reflog
git reflog

# 2. Encontrar o hash antes do reset
# Exemplo: k9l0m1n

# 3. Voltar para ele
git reset --hard k9l0m1n
```

**Cenário: deletei branch sem querer**
```bash
# 1. Ver reflog do branch deletado
git reflog show nome-do-branch

# 2. Recriar branch apontando para último commit
git branch nome-do-branch <hash>
```

**Cuidados:**
- Reflog é **local** (não vai para remoto).
- Reflog "expira" depois de ~90 dias (configurável).
- Não é backup eterno, mas ajuda muito em emergências.

---

## 10) Guardar trabalho temporariamente

### `git stash`
**O que faz:** guarda mudanças não commitadas numa "pilha" e limpa working tree.

#### Flags e subcomandos importantes

**Criar stash:**
- `push -m "<msg>"`: cria stash com mensagem. 
- `-u` ou `--include-untracked`: inclui untracked. 
- `-a` ou `--all`: inclui também ignorados (raro).
- `-p` ou `--patch`: stash interativo. 
- `--keep-index`: mantém staging.

**Listar:**
- `list`: lista stashes. 

**Ver:**
- `show`: mostra resumo.
- `show -p`: mostra diff completo. 

**Aplicar:**
- `apply`: aplica e mantém stash.
- `pop`: aplica e remove stash.

**Remover:**
- `drop`: remove um stash.
- `clear`: remove todos (cuidado).

**Criar branch:**
- `branch <nome>`: cria branch a partir do stash. 

#### Exemplos
```bash
# Stash básico (só tracked)
git stash push -m "WIP: ajustando layout"

# Stash com untracked
git stash push -u -m "WIP: inclui arquivos novos"

# Stash interativo
git stash push -p

# Listar
git stash list

# Ver conteúdo
git stash show stash@{0}
git stash show -p stash@{0}

# Aplicar último stash e remover
git stash pop

# Aplicar stash específico e manter
git stash apply stash@{2}

# Remover stash
git stash drop stash@{0}

# Limpar todos
git stash clear

# Criar branch a partir do stash
git stash branch novo-branch stash@{0}
```

**Workflow típico:**

**Preciso trocar de branch mas tenho mudanças não commitadas:**
```bash
# 1. Guardar trabalho
git stash push -u -m "WIP: feature X"

# 2. Trocar de branch
git switch outra-branch

# 3. Fazer o que precisa

# 4. Voltar
git switch feature-x

# 5. Recuperar trabalho
git stash pop
```

**Stash com conflito ao aplicar:**
```bash
git stash pop
# Auto-merging arquivo.txt
# CONFLICT (content): Merge conflict in arquivo.txt

# Resolver conflito, então: 
git add arquivo.txt
git stash drop  # Remove o stash já que aplicou
```

**Cuidados:**
- Stash pode gerar conflitos ao aplicar.
- Evite acumular muitos stashes (vira "gaveta de bagunça").
- Use mensagens descritivas. 
- `stash push` sem `-u` **não inclui untracked** (confusão comum).

---

## 11) Conflitos:  como reconhecer e resolver

### Quando acontecem
- `git merge` quando mudanças conflitam.
- `git rebase` quando commits conflitam.
- `git pull` (que é fetch + merge/rebase).
- `git cherry-pick` quando commit conflita. 
- `git stash apply/pop` quando stash conflita com estado atual.

---

### Como reconhecer

#### No terminal:
```
Auto-merging arquivo.txt
CONFLICT (content): Merge conflict in arquivo.txt
Automatic merge failed; fix conflicts and then commit the result. 
```

#### Com `git status`:
```bash
git status
# On branch main
# You have unmerged paths.
#   (fix conflicts and run "git commit")
#
# Unmerged paths:
#   (use "git add <file>..." to mark resolution)
#
#     both modified:    arquivo.txt
```

---

### Como resolver (passo a passo detalhado)

#### 1) Ver o que está em conflito
```bash
git status
```

#### 2) Abrir arquivo e procurar marcadores
```text
<<<<<<< HEAD
(seu lado - estado atual do branch)
=======
(outro lado - o que está sendo integrado)
>>>>>>> origin/main
```

**Com `merge. conflictStyle = diff3` (recomendado):**
```text
<<<<<<< HEAD
(seu lado)
||||||| merged common ancestors
(ancestral comum - como era antes)
=======
(outro lado)
>>>>>>> origin/main
```

Configurar diff3:
```bash
git config --global merge.conflictStyle diff3
```

#### 3) Editar para resultado final
- Escolher um lado, ou
- Combinar ambos, ou
- Escrever algo novo

**Remover os marcadores** (`<<<<<<<`, `=======`, `>>>>>>>`).

#### 4) Marcar como resolvido
```bash
git add arquivo.txt
```

#### 5) Concluir operação

**Se era merge:**
```bash
git commit
# (editor abre com mensagem padrão, pode editar ou manter)
```

**Se era rebase:**
```bash
git rebase --continue
```

**Se era cherry-pick:**
```bash
git cherry-pick --continue
```

#### 6) Se precisar cancelar a operação
```bash
git merge --abort
git rebase --abort
git cherry-pick --abort
```

---

### Ferramentas para resolver conflitos

#### Linha de comando
```bash
# Ver arquivos em conflito
git diff --name-only --diff-filter=U

# Ver conflito com mais contexto
git diff
```

#### Merge tool (gráfico)
```bash
# Configurar (exemplos)
git config --global merge.tool vimdiff
git config --global merge.tool meld
git config --global merge. tool kdiff3

# Usar
git mergetool
```

Ferramentas populares:
- **VS Code**: suporte nativo (mostra "Accept Current Change", "Accept Incoming Change", etc).
- **meld**: GUI simples e clara.
- **kdiff3**:  3-way merge. 
- **p4merge**: visual intuitivo.

#### Em VS Code:
VS Code detecta conflitos automaticamente e mostra botões: 
- Accept Current Change
- Accept Incoming Change
- Accept Both Changes
- Compare Changes

---

### Estratégias para conflitos complexos

#### Preferir um lado inteiro (ours/theirs)

**Durante merge:**
```bash
# Preferir "nosso" lado (branch atual)
git checkout --ours arquivo.txt
git add arquivo.txt

# Preferir "outro" lado (branch sendo integrado)
git checkout --theirs arquivo.txt
git add arquivo.txt
```

**Durante rebase:**
```bash
# "Ours" e "theirs" são invertidos no rebase! 
# (porque commits estão sendo reaplicados)

# Preferir versão original do commit sendo reaplicado
git checkout --theirs arquivo.txt

# Preferir versão da nova base
git checkout --ours arquivo. txt
```

#### Estratégia de merge que prefere um lado
```bash
# Merge preferindo "nosso" lado em conflitos
git merge -s recursive -X ours origin/main

# Merge preferindo "outro" lado em conflitos
git merge -s recursive -X theirs origin/main
```

---

### Rerere (Reuse Recorded Resolution)

**O que faz:** grava como você resolveu conflito e reutiliza automaticamente se conflito igual aparecer de novo.

```bash
# Ativar
git config --global rerere.enabled true

# Funcionamento: 
# 1. Você resolve conflito manualmente
# 2. Git grava a resolução
# 3. Se mesmo conflito aparecer (ex.:  durante rebase), Git aplica automaticamente
```

Muito útil em rebases longos.

---

### Cuidados importantes
- **Não faça `git add . ` sem revisar** durante conflito (pode "aceitar" lixo).
- Entenda qual é "seu lado" vs "outro lado": 
  - Em **merge**: HEAD é seu branch atual, outro é o que está sendo integrado.
  - Em **rebase**: invertido (commits sendo reaplicados).
- Teste após resolver (rode testes, compile, etc).
- Conflitos em arquivos binários (imagens, etc) geralmente exigem escolher um lado inteiro.

---

## 12) Tags (marcar releases)

### `git tag`
**O que faz:** marca um commit com um nome (geralmente versão).

#### Tipos de tags
- **Lightweight tag**: só um ponteiro para commit (como branch que não muda).
- **Annotated tag**: objeto completo com autor, data, mensagem, pode ser assinado (recomendado para releases).

#### Flags importantes
- `-a`: cria tag anotada. 
- `-m "<msg>"`: mensagem (usado com `-a`).
- `-s`: assina tag com GPG (segurança).
- `-d`: deleta tag local. 
- `-l` ou `--list`: lista tags (com pattern opcional).
- `-f`: força recriar tag (sobrescreve).

#### Exemplos
```bash
# Tag lightweight (não recomendado para releases)
git tag v1.0.0

# Tag anotada (recomendado)
git tag -a v1.0.0 -m "Release 1.0.0"

# Tag anotada com descrição longa
git tag -a v1.0.0
# (abre editor)

# Tag em commit específico (não o atual)
git tag -a v0.9.0 <hash> -m "Release 0.9.0"

# Listar tags
git tag
git tag -l "v1.*"

# Ver informações da tag
git show v1.0.0

# Deletar tag local
git tag -d v1.0.0

# Push de tag específica
git push origin v1.0.0

# Push de todas as tags
git push origin --tags

# Deletar tag remota
git push origin --delete v1.0.0
# ou
git push origin :refs/tags/v1.0.0
```
