# Bomblab Report
**学号:2017202034**
**姓名:张大方**
**bombID:bomb3**
## GDB调试器

### 反汇编指令
得到含有整个程序所有汇编代码的文件
`objdump -d bomb > bomb.asm `
得到含有整个程序所有函数入口地址的文件
`objdump -t bomb > func.asm `

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

`set args ./input.txt`

每次运行时就不再需要重新输入

## 破解过程
### 前期准备
首先用`disas main`对主函数进行反汇编<br>
发现如下几个函数:<br>
```
phase_1
phase_2
phase_3
...
phase_6
secret_phase
explode_bomb
```
猜测phase_1~6   即为我们要闯关的函数<br>
-------

打开bomb.c,发现基本上很多都已经被掏空了<br>
但是通过观察函数的模式判断
```C
    input = read_line();             /* Get input                   */
    phase_1(input);                  /* Run the phase               */
    phase_defused();        
```
应该是每一关都要输入一行字符串,作为通关密匙.

### Phase_1
先反汇编出对应代码
`disas phase_1`
```
Dump of assembler code for function phase_1:
=> 0x0000000000400ef0 <+0>:     sub    $0x8,%rsp
   0x0000000000400ef4 <+4>:     mov    $0x402490,%esi
   0x0000000000400ef9 <+9>:     callq  0x4012de <strings_not_equal>
   0x0000000000400efe <+14>:    test   %eax,%eax
   0x0000000000400f00 <+16>:    je     0x400f07 <phase_1+23>
   0x0000000000400f02 <+18>:    callq  0x401544 <explode_bomb>
   0x0000000000400f07 <+23>:    add    $0x8,%rsp
   0x0000000000400f0b <+27>:    retq   
End of assembler dump.
```
发现在第三行(`<phase_1+9>`),调用了`<strings_not_equal>`函数,并把%rsp和%esi分别作为参数传入
顾名思义，应该是比较两者内字符串是否相等。
调取0x402490中的字符串 `x/s 0x402490`
得到
```C
(gdb) x/s 0x402490
0x402490:       "We have to stand with our North Korean allies."
```
从而第一题答案应该就是这个了.<br>
事实证明破关了
```
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
We have to stand with our North Korean allies.
Phase 1 defused. How about the next one?
```

### Phase_2
反汇编
`disas phase_2`
```
Dump of assembler code for function phase_2:
=> 0x0000000000400f0c <+0>:     push   %rbp
   0x0000000000400f0d <+1>:     push   %rbx
   0x0000000000400f0e <+2>:     sub    $0x28,%rsp
   0x0000000000400f12 <+6>:     mov    %rsp,%rsi
   0x0000000000400f15 <+9>:     callq  0x40157a <read_six_numbers>
   0x0000000000400f1a <+14>:    cmpl   $0x0,(%rsp)
   0x0000000000400f1e <+18>:    jne    0x400f27 <phase_2+27>
   0x0000000000400f20 <+20>:    cmpl   $0x1,0x4(%rsp)
   0x0000000000400f25 <+25>:    je     0x400f48 <phase_2+60>
   0x0000000000400f27 <+27>:    callq  0x401544 <explode_bomb>
   0x0000000000400f2c <+32>:    jmp    0x400f48 <phase_2+60>
   0x0000000000400f2e <+34>:    mov    -0x8(%rbx),%eax
   0x0000000000400f31 <+37>:    add    -0x4(%rbx),%eax
   0x0000000000400f34 <+40>:    cmp    %eax,(%rbx)
   0x0000000000400f36 <+42>:    je     0x400f3d <phase_2+49>
   0x0000000000400f38 <+44>:    callq  0x401544 <explode_bomb>
   0x0000000000400f3d <+49>:    add    $0x4,%rbx
   0x0000000000400f41 <+53>:    cmp    %rbp,%rbx
   0x0000000000400f44 <+56>:    jne    0x400f2e <phase_2+34>
   0x0000000000400f46 <+58>:    jmp    0x400f54 <phase_2+72>
   0x0000000000400f48 <+60>:    lea    0x8(%rsp),%rbx
   0x0000000000400f4d <+65>:    lea    0x18(%rsp),%rbp
   0x0000000000400f52 <+70>:    jmp    0x400f2e <phase_2+34>
   0x0000000000400f54 <+72>:    add    $0x28,%rsp
   0x0000000000400f58 <+76>:    pop    %rbx
   0x0000000000400f59 <+77>:    pop    %rbp
   0x0000000000400f5a <+78>:    retq   
End of assembler dump.
```

`<+6> mov %rsp,%rsi`将%rsp内的内存地址传给了%rsi作为<read_six_numbers>的参数,顾名思义,
应该是要输入六个整数<br>
继续看<+14>要求%rsp对应地址内的第一个数为0.<br>
<+20>要求第二个数为1.<br>
<+34> ~ <+60>循环比较每个数是否等于前两个数之和,即斐波那契数列<br>
从而得到答案`0 1 1 2 3 5` <br>
成功<br>
`That's number 2.  Keep going!`

### Phase_3

反汇编
```
Dump of assembler code for function phase_3:
=> 0x0000000000400f5b <+0>:     sub    $0x18,%rsp
   0x0000000000400f5f <+4>:     lea    0x8(%rsp),%rcx
   0x0000000000400f64 <+9>:     lea    0xc(%rsp),%rdx
   0x0000000000400f69 <+14>:    mov    $0x40278d,%esi
   0x0000000000400f6e <+19>:    mov    $0x0,%eax
   0x0000000000400f73 <+24>:    callq  0x400c30 <__isoc99_sscanf@plt>
   0x0000000000400f78 <+29>:    cmp    $0x1,%eax
   0x0000000000400f7b <+32>:    jg     0x400f82 <phase_3+39>
   0x0000000000400f7d <+34>:    callq  0x401544 <explode_bomb>
   0x0000000000400f82 <+39>:    cmpl   $0x7,0xc(%rsp)
   0x0000000000400f87 <+44>:    ja     0x400fc5 <phase_3+106>
   0x0000000000400f89 <+46>:    mov    0xc(%rsp),%eax
   0x0000000000400f8d <+50>:    jmpq   *0x4024f0(,%rax,8)
   0x0000000000400f94 <+57>:    mov    $0x277,%eax
   0x0000000000400f99 <+62>:    jmp    0x400fd6 <phase_3+123>
   0x0000000000400f9b <+64>:    mov    $0x2d5,%eax
   0x0000000000400fa0 <+69>:    jmp    0x400fd6 <phase_3+123>
   0x0000000000400fa2 <+71>:    mov    $0x62,%eax
   0x0000000000400fa7 <+76>:    jmp    0x400fd6 <phase_3+123>
   0x0000000000400fa9 <+78>:    mov    $0x137,%eax
   0x0000000000400fae <+83>:    jmp    0x400fd6 <phase_3+123>
   0x0000000000400fb0 <+85>:    mov    $0x1d6,%eax
   0x0000000000400fb5 <+90>:    jmp    0x400fd6 <phase_3+123>
   0x0000000000400fb7 <+92>:    mov    $0x2ca,%eax
   0x0000000000400fbc <+97>:    jmp    0x400fd6 <phase_3+123>
   0x0000000000400fbe <+99>:    mov    $0x383,%eax
   0x0000000000400fc3 <+104>:   jmp    0x400fd6 <phase_3+123>
   0x0000000000400fc5 <+106>:   callq  0x401544 <explode_bomb>
   0x0000000000400fca <+111>:   mov    $0x0,%eax
   0x0000000000400fcf <+116>:   jmp    0x400fd6 <phase_3+123>
   0x0000000000400fd1 <+118>:   mov    $0x14f,%eax
   0x0000000000400fd6 <+123>:   cmp    0x8(%rsp),%eax
   0x0000000000400fda <+127>:   je     0x400fe1 <phase_3+134>
   0x0000000000400fdc <+129>:   callq  0x401544 <explode_bomb>
   0x0000000000400fe1 <+134>:   add    $0x18,%rsp
   0x0000000000400fe5 <+138>:   retq   
End of assembler dump.
```
发现从<+57>到<+104>都有着极为相似的结构,猜测包含switch语句<br>
往上看发现<+24>调用了scanf函数,并把`$0x40278d`内的值传入,0x8(%rsp)作为第四个参数,
0xc(%rsp)作为第三个参数.<br>
调查`$0x40278d`
```
(gdb) x /s 0x40278d
0x40278d:       "%d %d"
```
所以此关是输入两个整数.<br>
<+29> ~ <+44>保证了第一个数<=7<br>
<+46>将第一个数放入%eax,<+50>根据%eax中的数做跳转,调查0x4024f0<br>
```
(gdb) x /4xb 0x4024f0
0x4024f0:       0x94    0x0f    0x40    0x00
```
从而是以`0x400f94`为基准值进行跳转.<br>
得到关系:
```
0 -> 0x400f94 ->0x277 ->631
1 -> 0x400fd1 ->0x14f ->335
2 -> 0x400f9b ->0x2d5 ->725
3 -> 0x400fa2 ->0x62  ->98
4 -> 0x400fa9 ->0x137 ->311
5 -> 0x400fb0 ->0x1d6 ->470
6 -> 0x400fb7 ->0x2ca ->714
7 -> 0x400fbe ->0x383 ->899
```
我们选取`0 631`<br>
破关
```
0 631
Halfway there!

```

### Phase_4
反汇编
