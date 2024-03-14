---
title: Title
separator: <!--s-->
verticalSeparator: <!--v-->
theme: simple
highlightTheme: monokai-sublime
css:
    - custom.css
    - dark.css
revealOptions:
  transition: 'slide'
  transitionSpeed: fast
  center: false
  width: 1520
  height: 950
  margin: 0.04
  slideNumber: true
---

# 浙江大学朋辈辅学之初窥C语言

### Time: 9/23 14:00

## 主讲人：Mix2207 杜宗泽

<!--s-->



## Table of content

* Some Basic knowledge of computer
* Basic Language of C
* Some advanced use of C
* How to code in Vscode（compiler）

<!--s-->



## Some Basic knowledge of computer

1. How does the data stored in the computer ?
2. How does the number calculate in the computer ?
3. How does the program being executed in the computer?

<!--v-->

### Part 1   How does the data stored in the computer ?

Basic conception: Byte is a sequence of 8 bits.

Different data type has different Storage size.(IEE754 \ Binary \ ASCII)

**Address is crucial in C language!**

<!--v-->

### Part 2   How does the number calculate in the computer ?

The ALU(can be abstracted as one part in CPU) could help us solve this problem.

<img src="graph\Snipaste_2023-09-21_23-53-55.png" style="zoom: 67%;" >

<!--v-->

### Part 3  How does the program being executed in the computer?

Put the binary file into memory first !

<img src="graph\20200214222908921.jpg" style="zoom:67%;" />

<!--s-->



## Basic Language of C

We approach the outline from the perspective of program structure

* Preprocessor Directives.
* Variable.
* Expression.(You need focus on the priority!)
* Function.
* Annotation.

<!--v-->

### Part 0 A program

```c
#include <stdio.h>
#define N 10
typedef 100 max
    
void print_N()
{
    printf("%d", N);
}

int main (void)
{
	print_N();	
    return 0;
}
```

<!--v-->

### Part 1 Preprocessor Directives

* Header File
* #define
* typedef

<!--v-->

### Part ２ Variable.

* Integer
* Double
* Float
* long long
* Unsigned
* char(No string!!!)

<!--v-->

### Part 3 Expression

* Some Calculation.(Something easily wrong when you are freshman)
* Some Logic expression.
* Loop & Judgement.

<!--v-->

### Part 4 Function

* We need Declare correctly!
* Parameter
* Return value

<!--v-->

### Part 5 Annotation

Annotation is very Necessory!

<!--s-->



## Some advanced C

* static extern const
* Array & Pointer.
* Malloc & Free

<!--v-->

### Part 1 static extern const

<!--v-->

### Part 2 Array & pointer

<!--v-->

### Part 3 Malloc & Free

<!--s-->



## Code style

Most teachers won't even mention it to you, but I think it's truly important for the freshman which is often **overlooked** !!

**Basic Rule:**

<!--s-->



## How to code in Vscode（compiler）

I've already tell you the link. Basically you could configure it by yourself. Just like a stumbling block on your CS road.

Know I'll show you some operation in shell.

<!--s-->



## Homework

Input n, and output the spiral number use the two dimension array.

> Hint: Do focus on the algorithm design instead of code language itself !!!

<!--s-->



## 谢谢大家

<!--s-->











