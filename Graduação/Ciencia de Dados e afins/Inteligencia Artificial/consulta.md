# 🧩 Prolog Quick Reference Guide

Este guia contém a sintaxe básica e os princípios fundamentais da linguagem **Prolog** (Programming in Logic). Ideal para consulta rápida durante o desenvolvimento de sistemas baseados em regras e lógica de primeira ordem.

---

## 1. Elementos de Dados (Termos)

Prolog não possui tipos de dados tradicionais (como `int` ou `string`); tudo é tratado como um **Termo**.

| Termo | Descrição | Exemplo |
| :--- | :--- | :--- |
| **Átomos** | Constantes que começam com letra minúscula ou entre aspas simples. | `pedro`, `'Maria'`, `x_12` |
| **Números** | Inteiros ou decimais. | `42`, `3.14` |
| **Variáveis** | Começam com letra **maiúscula** ou underscore `_`. | `X`, `Resultado`, `_temp` |
| **Termos Compostos** | Um funtor seguido de argumentos entre parênteses. | `pai(joao, maria)` |

> **Nota:** A variável `_` é a **variável anônima**, usada quando o valor de um argumento não é relevante para a lógica da cláusula.

---

## 2. Fatos, Regras e Consultas

A base de conhecimento (**Knowledge Base**) é composta por cláusulas terminadas obrigatoriamente por um ponto (`.`).

### 📌 Fatos

Declaram verdades incondicionais sobre o mundo.

```prolog
progenitor(jose, maria).
animal(cachorro).
quente(sol).
```

### 📌 Regras

Declaram verdades condicionais. Seguem o formato:

**Cabeça :- Corpo.**

- `:-` significa **"se"** (implicação lógica)  
- `,` representa **E lógico (AND)**  
- `;` representa **OU lógico (OR)**  

```prolog
filho(X, Y) :- 
    progenitor(Y, X), 
    homem(X).
```

### 📌 Consultas (Queries)

Feitas no console do interpretador (`?-`) para verificar afirmações ou encontrar valores.

```prolog
?- progenitor(jose, maria). % Retorna true ou false
?- progenitor(jose, X).     % Retorna valores de X
```

---

## 3. Unificação e Comparação

A **unificação (`=`)** é o coração do Prolog: tenta tornar dois termos iguais.

| Operador | Significado |
| :--- | :--- |
| `X = Y` | Tenta unificar X e Y |
| `X \= Y` | Verifica se não podem ser unificados |
| `is` | Avalia expressão matemática |
| `X =:= Y` | Igualdade aritmética |
| `X =\= Y` | Diferença aritmética |

---

## 4. Listas

Listas são delimitadas por colchetes `[]`.

- `[]` → lista vazia  
- `[a, b, c]` → lista com elementos  
- `[H | T]` → separa **cabeça (Head)** e **cauda (Tail)**  

### Exemplo: Predicado de Pertencimento

```prolog
membro(X, [X|_]).            % Caso base
membro(X, [_|Cauda]) :-      % Caso recursivo
    membro(X, Cauda).
```

---

## 5. Operadores Aritméticos

A aritmética precisa do operador `is` para ser avaliada.

| Operador | Função |
| :--- | :--- |
| `+, -, *, /` | Operações básicas |
| `//, mod` | Divisão inteira e resto |
| `X > Y, X < Y` | Maior / menor |
| `X >= Y, X =< Y` | Maior ou igual / menor ou igual |

---

## 6. Controle de Fluxo

- **Cut (`!`)**: impede o *backtracking*  
- **Fail**: força falha imediata  
- **Negação (`\+`)**: verdadeiro se não puder ser provado  

---

## 7. Predicados Úteis (Built-ins)

| Predicado | Função |
| :--- | :--- |
| `write(X)` | Exibe valor |
| `nl` | Nova linha |
| `read(X)` | Lê entrada |
| `consult('arquivo.pl')` | Carrega arquivo |
| `listing` | Mostra base de conhecimento |
| `halt` | Encerra Prolog |

---

## 8. Comentários

```prolog
% Comentário de uma linha

/* Comentário
   de múltiplas linhas */
```

---

Este resumo foi gerado pelo chatGPT e será usado apenas para consulta de informações