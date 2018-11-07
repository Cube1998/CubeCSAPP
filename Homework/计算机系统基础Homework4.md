# Homework3 Report
**学号:2017202034 <br>**
**姓名:张大方**


## 题目描述

写一个Linux下的汇编程序，求解一个10个元素整型数组中的最小值，并且返回

## 汇编代码
```C
.section .data
data_items:
.long 1,3,8,10,5,7,6,9,20,31,100 
.section .text
.globl _start
_start:
movl $0, %edi
movl data_items(,%edi,4), %eax
movl %eax, %ebx
start_loop:
cmpl $100, %eax
je loop_exit
incl %edi
movl data_items(,%edi,4), %eax
cmpl %ebx, %eax
jnle start_loop
movl %eax, %ebx
jmp start_loop
loop_exit:
mov $1, %eax
int $0x80
```








## 反汇编代码
```C
00000000004000b0 <_start>:
  4000b0:	bf 00 00 00 00       	mov    $0x0,%edi
  4000b5:	67 8b 04 bd dd 00 60 	mov    0x6000dd(,%edi,4),%eax
  4000bc:	00 
  4000bd:	89 c3                	mov    %eax,%ebx

00000000004000bf <start_loop>:
  4000bf:	83 f8 64           	cmp    $0x64,%eax
  4000c2:	74 12        je     4000d6 <loop_exit>
  4000c4:	ff c7                	inc    %edi
  4000c6:	67 8b 04 bd dd 00 60	mov    0x6000dd(,%edi,4),%eax
  4000cd:	00 
  4000ce:	39 d8       	cmp    %ebx,%eax
  4000d0:	7f ed          	jg     4000bf <start_loop>
  4000d2:	89 c3         	mov    %eax,%ebx
  4000d4:	eb e9          	jmp    4000bf <start_loop>

00000000004000d6 <loop_exit>:
  4000d6:	b8 01 00 00 00       	mov    $0x1,%eax
  4000db:	cd 80                	int    $0x80
```

## 结果对比分析

经过优化之后的代码反汇编之后，数值表示均为16进制

对内存的操作全部直接替换为了地址

操作符后不再有后缀: movl -> mov cmpl->cmp