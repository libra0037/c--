This is a super simplified version of the C language. I named it C--.

This compiler compiles C-- to 32-bit LLVM IR with no optimizations. Since I try not to use any third-party libraries, it's quite a challenge even though the resulting code is pretty crude.

### Build

```
g++ main.cpp parser.cpp -O2 -o c--
```

### Usage

To compiles C-- to LLVM IR, run

```
./c-- name.c-- name.ll
```

To generate a native (e.g. x86) executable from LLVM IR, run

```
llc -march=x86 name.ll
gcc -m32 name.s -o name
```

### C-- Grammar

\*See *sqrt2.c--* and *bf.c--* for examples.\*

All operands and results are 32-bit signed integers, equivalent to `int` in C/C++. The type turns to `int *` temporarily when accessing memory with square brackets.

Comments start with '#' and end at the end of the current line.

Reserved words and their equivalents in C/C++:

-   $\mathbf{if}~exp$: `if(exp)`
-   $\mathbf{elif}~exp$: `else if(exp)`
-   $\mathbf{while}~exp$: `while(exp)`
-   $\mathbf{getc}$: `getchar()`
-   $\mathbf{putc}~fact$: `putchar(fact)`
-   $\mathbf{alloc}~fact$: `new int[fact]`
-   $\mathbf{free}~fact$: `delete fact`, except this always returns 0

Operators: `= < == + - * / & | ^ []`. They do exactly the same operations as in C/C++.

### Context-Free Grammar of C--

program $\rightarrow$ stmt-seq **\<EOF\>**

stmt-seq $\rightarrow$ $\varepsilon$ | stmt-seq stmt **\<SEMI, ';'\>**

stmt $\rightarrow$ if-stmt | while-stmt | exp

if-stmt $\rightarrow$ **\<if\>** exp stmt-seq | if-stmt **\<elif\>** exp stmt-seq

while-stmt $\rightarrow$ **\<while\>** exp stmt-seq

array-op $\rightarrow$ **\<LBRAC, '['\>** exp **\<RBRAC, ']'\>**

func-op $\rightarrow$ **\<putc\>** | **\<alloc\>** | **\<free\>**

calc-op $\rightarrow$ **\<AND, '&'\>** | **\<OR, '|'\>** | **\<XOR, '^'\>** | **\<LT, '<'\>** | **\<EQ, '=='\>** | **\<PLUS, '+'\>** | **\<MINUS, '-'\>** | **\<TIMES, '*'\>** | **\<DIV, '/'\>**

exp $\rightarrow$ rval | **\<ID\>** **\<ASSIGN, '='\>** exp | factor array-op **\<ASSIGN, '='\>** exp

rval $\rightarrow$ factor | func-op factor | rval calc-op rval

factor $\rightarrow$ operand | factor array-op

operand $\rightarrow$ **\<INT\>** | **\<ID\>** | **\<getc\>** | **\<LPARE, '('\>** exp **\<RPARE, ')'\>**

