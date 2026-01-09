# Verificação de Memory Leaks

## Sobre os "Still Reachable"

Os blocos marcados como **"still reachable"** pelo Valgrind não são leaks propriamente ditos. São alocações que:

1. **Ainda têm ponteiros válidos** apontando para elas
2. São **mantidas intencionalmente** por bibliotecas (como readline)
3. Seriam **liberadas automaticamente** quando o processo termina

### Por que a readline mantém ~208KB em memória?

A biblioteca `readline` mantém:
- **Histórico de comandos** em memória
- **Keymaps e configurações** para melhor performance
- **Buffers internos** para próximas leituras
- **Estruturas globais** que são reutilizadas entre chamadas

Isso é um **padrão de design válido** em bibliotecas - liberar tudo no `exit()` seria desperdício de CPU.

### Posso reduzir isso?

**NÃO naturalmente.** Mesmo chamando funções como:
- `rl_clear_history()` - limpa histórico (reduz ~6 bytes)
- `_rl_clean_up_for_exit()` - cleanup interno (reduz ~6KB)

Os ~200KB de buffers internos **permanecerão** porque a readline os mantém propositalmente para eficiência.

**Teste prático:**
```bash
# Programa SEM readline: 0 bytes still reachable
# Programa COM readline: ~208KB still reachable
```

A única forma de "eliminar" isso seria **não usar readline**, o que não é uma opção viável para um shell interativo.

---

## Como Testar Corretamente

### 1. Teste Rápido (focar em leaks reais)
```bash
echo -e 'pwd\nexit' | valgrind --leak-check=full --show-leak-kinds=definite ./my_shell
```

Só mostra **"definitely lost"** - os leaks reais que você deve corrigir.

### 2. Teste Completo (com suppressions)
```bash
./test_leaks.sh
```

Executa bateria de testes ignorando os leaks conhecidos da readline.

### 3. Teste Manual Detalhado
```bash
valgrind --leak-check=full \
         --show-leak-kinds=definite,possible \
         --suppressions=./readline.supp \
         --track-origins=yes \
         ./my_shell
```

---

## Arquivo de Suppressions

O arquivo `readline.supp` contém regras para ignorar os "still reachable" da readline:

```
{
   readline_malloc
   Memcheck:Leak
   match-leak-kinds: reachable
   ...
   obj:*/libreadline.so.*
}
```

Isso diz ao Valgrind: "ignore alocações reachable vindas da libreadline".

---

## Interpretando Resultados

### ✅ **BOM** (Sem problemas)
```
definitely lost: 0 bytes in 0 blocks
possibly lost: 0 bytes in 0 blocks
```

### ⚠️ **ATENÇÃO** (Possível leak)
```
possibly lost: 64 bytes in 2 blocks
```

### ❌ **RUIM** (Leak confirmado)
```
definitely lost: 128 bytes in 4 blocks
```

### 🔵 **NORMAL** (Biblioteca)
```
still reachable: 214,647 bytes in 450 blocks
```

---

## Tipos de Leak

| Tipo | Significado | Ação |
|------|-------------|------|
| **definitely lost** | Memória sem ponteiro - leak real | ❌ **Corrigir** |
| **indirectly lost** | Leak derivado de outro leak | ❌ **Corrigir o pai** |
| **possibly lost** | Ponteiro interno - suspeito | ⚠️ **Investigar** |
| **still reachable** | Ponteiro válido existe | ✅ **OK** (geralmente) |

---

## Status Atual

✅ **0 leaks definitivos**
✅ **0 leaks possíveis**
✅ **Todos os testes passando**

```
LEAK SUMMARY:
   definitely lost: 0 bytes in 0 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 214,647 bytes in 450 blocks (readline)
        suppressed: 0 bytes in 0 blocks
```

---

## Leaks Corrigidos

1. **Token duplicado no lexer** (2 bytes por operador)
   - **Arquivo**: `src/lexer/token_utils.c`
   - **Função**: `create_single_token`
   - **Causa**: Duplo `strdup` - um antes de passar para `token_new`
   - **Correção**: Criar token diretamente sem chamar `token_new`
