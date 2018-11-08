# Homework6 Report
**学号:2017202034 <br>**
**姓名:张大方**


## 题目一




Operand | Value
--------|--------
%eax| 0x10000000
%ecx|22
$0x10000004|0x10000004
0x10000012|0
0xFFFFFFF8|NONE
(%eax,%ecx,8)|44




## 题目二

```C
int dw_loop(int x, int y, int n) {
do{
x += n;
y *= n;
n--;
if(n<=0) break;
}while ( y < n );
returen x;
}
```
## 题目三
(1)
```C
conditionalmove:
 movl %edi, %eax
 imull %esi, %eax
 movl %esi, %ebx
 imull %ebx, %ebx
 cmpl %edi, %esi
 cmovle (%eax,%ebx,1), %eax
 ret
```
(2)
```
x*x和x*y的计算开销较大，使用条件传送时在条件满足时对x*y的计算是无效
的，这部分开销相对于条件跳转时判断错误的代价要高
```

## 题目四
```C
section .rodata
  .align 8
.L4:
  .quad .L1
  .quad .L9
  .quad .L3
  .quad .L2
  .quad .L2
  .quad .L6
  .quad .L6
  switch:
  movl $24, %eax
  movl $2, %ebx
  leal -24(,%eax,8), %ecx
  cmpl $24, %eax
  jl *.L4(%ebx)
  cmpl $30, %eax
  jg *.L4(%ebx)
  jmp *.L4(%ecx)
.L1:
  addl %eax, %eax
  jmp .L9
.L2:
  addl $10, %eax
  jmp .L9
.L3:
  shll %eax
.L6:
  addl $5, %eax
  jmp .L9
.L5:
  movl $3, %eax
  jmp .L9
.L9:
  ret
```
