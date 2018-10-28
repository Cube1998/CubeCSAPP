# Bomblab Report
**学号:2017202034**
**姓名:张大方**
**bombID:bomb3**
## GDB调试器

### 反汇编指令
```C
objdump -d bomb > bomb.asm //得到含有整个程序所有汇编代码的文件
objdump -t bomb > func.asm //得到含有整个程序所有函数入口地址的文件
```
### 常用指令
```
r：运行程序
b *0x400e65：在地址为0x400e65处设置断点
d 1：删除第一个断点，以此类推
c：继续运行
stepi：执行一条指令
stepi 2：执行两条指令，以此类推
disas：反汇编当前函数
disas 0x400e65：反汇编0x400e65为入口地址的函数
disas main：反汇编以main为函数名的函数
info frame：查看有关栈帧的信息
info registers：查看有关寄存器的信息
p $rax：查看寄存器%rax内储存的值
x $rax：查看以寄存器%rax内储存的值为地址处的值
p或x /s $rax：以字符串形式输出
p或x /t $rax：以二进制形式输出
p或x /x $rax：以十六进制形式输出
x /32b $rsp：查看栈帧的前32字节
x /8g $rax：查看以%rax中储存的值位地址开始的8个字
```

### 记录答案
为了在破解前面的关卡之后，不用再反复输入相同的答案<br>
将答案存放在input.txt中<br>
并在dgb中执行
```
set args ./input.txt
```
每次运行时就不再需要重新输入

## 破解过程
### 前期准备
首先用`disas main`对主函数进行汇编<br>
发现如下几个函数:<br>