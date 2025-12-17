# TESTES MANUAIS DO LEXER

Execute o shell: `./my_shell`

## Checklist de Testes:

### ✅ Testes Básicos

1. **Comando simples:**
   ```
   Input: ls
   Esperado: [0] WORD: 'ls'
   ```

2. **Comando com argumento:**
   ```
   Input: ls -la
   Esperado: 
   [0] WORD: 'ls'
   [1] WORD: '-la'
   ```

3. **Múltiplos argumentos:**
   ```
   Input: echo hello world
   Esperado:
   [0] WORD: 'echo'
   [1] WORD: 'hello'
   [2] WORD: 'world'
   ```

### ✅ Testes de Operadores

4. **Pipe:**
   ```
   Input: ls | grep test
   Esperado:
   [0] WORD: 'ls'
   [1] PIPE: '|'
   [2] WORD: 'grep'
   [3] WORD: 'test'
   ```

5. **Redirect entrada:**
   ```
   Input: cat < file.txt
   Esperado:
   [0] WORD: 'cat'
   [1] REDIR_IN: '<'
   [2] WORD: 'file.txt'
   ```

6. **Redirect saída:**
   ```
   Input: echo hello > output.txt
   Esperado:
   [0] WORD: 'echo'
   [1] WORD: 'hello'
   [2] REDIR_OUT: '>'
   [3] WORD: 'output.txt'
   ```

7. **Append:**
   ```
   Input: echo hello >> output.txt
   Esperado:
   [0] WORD: 'echo'
   [1] WORD: 'hello'
   [2] REDIR_OUT: '>>'
   [3] WORD: 'output.txt'
   ```

8. **Heredoc:**
   ```
   Input: cat << EOF
   Esperado:
   [0] WORD: 'cat'
   [1] REDIR_IN: '<<'
   [2] WORD: 'EOF'
   ```

### ✅ Testes de Edge Cases

9. **Múltiplos espaços:**
   ```
   Input: ls    -la     |    grep
   Esperado: Mesmo resultado que 'ls -la | grep'
   ```

10. **Espaços no início:**
    ```
    Input:     ls
    Esperado: [0] WORD: 'ls'
    ```

11. **Comando vazio (só Enter):**
    ```
    Input: (vazio)
    Esperado: Nenhum token, volta ao prompt
    ```

12. **Só espaços:**
    ```
    Input:      
    Esperado: Nenhum token, volta ao prompt
    ```

### ✅ Testes Complexos

13. **Múltiplos pipes:**
    ```
    Input: cat file | grep test | wc -l
    Esperado: 7 tokens alternando WORD e PIPE
    ```

14. **Mix de operadores:**
    ```
    Input: cat < in.txt | grep test > out.txt
    Esperado: 7 tokens corretos
    ```

15. **Arquivo com extensão:**
    ```
    Input: cat file.txt
    Esperado:
    [0] WORD: 'cat'
    [1] WORD: 'file.txt'
    ```

16. **Path absoluto:**
    ```
    Input: /bin/ls -la
    Esperado:
    [0] WORD: '/bin/ls'
    [1] WORD: '-la'
    ```

## O que Verificar:

- [ ] Número correto de tokens
- [ ] Tipo correto de cada token (WORD, PIPE, REDIR_IN, REDIR_OUT)
- [ ] Valor correto de cada token
- [ ] Posição correta (índice sequencial)
- [ ] Não vaza memória (testar com valgrind)
- [ ] Não quebra com entrada vazia
- [ ] Não quebra com múltiplos espaços

## Comandos Úteis:

**Rodar shell:**
```bash
./my_shell
```

**Testar memória:**
```bash
valgrind --leak-check=full ./my_shell
# Digite alguns comandos
# Digite 'exit' ou Ctrl+D
```

**Recompilar:**
```bash
make fclean && make
```
