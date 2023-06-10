This is a super simplified version of the C language. I named it C--.

This compiler compiles C-- to 64-bit LLVM IR with no optimizations. Since I try not to use any third-party libraries, it's quite a challenge even though the resulting code is pretty crude.

### Build

```
clang -O3 main.cpp parser.cpp -o c--
```

### Usage

To compile C-- to LLVM IR, run

```
./c-- name.c-- name.ll
```

To generate a native executable from LLVM IR, run

```
clang -m64 -O3 name.ll -o name
```

### C-- Grammar

\*See *sqrt2.c--* and *bf.c--* for examples.\*

The program starts with the first statement and ends after the last statement.

All identifiers are global variables. All operands and results are 64-bit signed integers (aka `int64_t` in C/C++). The type turns to `int64_t *` temporarily when accessing memory with square brackets.

Comments start with '#' and end at the end of the current line.

Reserved words and their equivalents in C/C++:

-   $\mathbf{if}~exp$: `if(exp)`
-   $\mathbf{elif}~exp$: `else if(exp)`
-   $\mathbf{while}~exp$: `while(exp)`
-   $\mathbf{getc}$: `getchar()`
-   $\mathbf{putc}~rval$: `putchar(rval)`
-   $\mathbf{alloc}~rval$: `new int64_t[rval]`
-   $\mathbf{free}~rval$: `delete rval`, except this always returns 0

Operators: `= < == + - * / % & | ^ []`. They do exactly the same operations as in C/C++.

| Precedence | Operator        |
| ---------- | --------------- |
| 1          | () []           |
| 2          | putc alloc free |
| 3          | * / %           |
| 4          | + -             |
| 5          | <               |
| 6          | ==              |
| 7          | &               |
| 8          | ^               |
| 9          | \|              |
| 10         | =               |

### Context-Free Grammar of C--

program $\rightarrow$ stmt-seq **\<EOF\>**

stmt-seq $\rightarrow$ $\varepsilon$ | stmt-seq stmt **\<SEMI, ';'\>**

stmt $\rightarrow$ if-stmt | while-stmt | exp

if-stmt $\rightarrow$ **\<if\>** exp stmt-seq | if-stmt **\<elif\>** exp stmt-seq

while-stmt $\rightarrow$ **\<while\>** exp stmt-seq

array-op $\rightarrow$ **\<LBRAC, '['\>** exp **\<RBRAC, ']'\>**

func-op $\rightarrow$ **\<putc\>** | **\<alloc\>** | **\<free\>**

calc-op $\rightarrow$ **\<AND, '&'\>** | **\<OR, '|'\>** | **\<XOR, '^'\>** | **\<LT, '<'\>** | **\<EQ, '=='\>** | **\<PLUS, '+'\>** | **\<MINUS, '-'\>** | **\<TIMES, '*'\>** | **\<DIV, '/'\>** | **\<MOD, '%'\>**

exp $\rightarrow$ rval | **\<ID\>** **\<ASSIGN, '='\>** exp | factor array-op **\<ASSIGN, '='\>** exp

rval $\rightarrow$ factor | **\<getc\>** | func-op rval | rval calc-op rval

factor $\rightarrow$ operand | factor array-op

operand $\rightarrow$ **\<INT\>** | **\<ID\>** | **\<LPARE, '('\>** exp **\<RPARE, ')'\>**

