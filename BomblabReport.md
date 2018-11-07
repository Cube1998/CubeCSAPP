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
```C
Dump of assembler code for function phase_4:
=> 0x0000000000401019 <+0>:	sub    $0x18,%rsp
   0x000000000040101d <+4>:	lea    0x8(%rsp),%rcx
   0x0000000000401022 <+9>:	lea    0xc(%rsp),%rdx
   0x0000000000401027 <+14>:	mov    $0x40278d,%esi
   0x000000000040102c <+19>:	mov    $0x0,%eax
   0x0000000000401031 <+24>:	callq  0x400c30 <__isoc99_sscanf@plt>
   0x0000000000401036 <+29>:	cmp    $0x2,%eax   
   //$eax 中存放着读入的数字个数
   0x0000000000401039 <+32>:	jne    0x401042 <phase_4+41>
   0x000000000040103b <+34>:	cmpl   $0xe,0xc(%rsp)  
   //判断第一个数是否小于等于0xe.
   0x0000000000401040 <+39>:	jbe    0x401047 <phase_4+46>
   0x0000000000401042 <+41>:	callq  0x401544 <explode_bomb>
   0x0000000000401047 <+46>:	mov    $0xe,%edx //第三个参数
   0x000000000040104c <+51>:	mov    $0x0,%esi //第二个参数
   0x0000000000401051 <+56>:	mov    0xc(%rsp),%edi //第一个参数
   0x0000000000401055 <+60>:	callq  0x400fe6 <func4>
   0x000000000040105a <+65>:	cmp    $0x12,%eax
   0x000000000040105d <+68>:	jne    0x401066 <phase_4+77>
   0x000000000040105f <+70>:	cmpl   $0x12,0x8(%rsp)
   0x0000000000401064 <+75>:	je     0x40106b <phase_4+82>
   0x0000000000401066 <+77>:	callq  0x401544 <explode_bomb>
   0x000000000040106b <+82>:	add    $0x18,%rsp
   0x000000000040106f <+86>:	retq   
End of assembler dump.
```
根据以往的经验,看到`<+24>`调用`<__isoc99_sscanf@plt>`,就找三个存参数的寄存器`%esi, %edx, %ecx`.<br>
发现`<+4> <+9> <+14>`中,分别把`0x40278d 0xc(%rsp) 0x8(%rsp)`当作三个参数<br>
查看`0x40278d`
```
(gdb) x/s 0x40278d
0x40278d:       "%d %d"
```
可知应该输入两个整数.<br>
由`<+34>`知,第一个数小于等于0xe,即小于等于14.<br>
`<+60>`告诉我们把`第一个输入的数`,`0x0`,`0xe`作为三个参数依次传入`<func4>` <br>

又由`<+65>`和`<+70>`知,`<func4>`的返回值为`0x12(18)`,第二个输入的数也为`0x12(18)` <br>

现在我们进入到`<func4>`中 <br>
```C
(gdb) disas func4 
Dump of assembler code for function func4:
   0x0000000000400fe6 <+0>:     push   %rbx
   0x0000000000400fe7 <+1>:     mov    %edx,%eax
   0x0000000000400fe9 <+3>:     sub    %esi,%eax
   0x0000000000400feb <+5>:     mov    %eax,%ebx
   0x0000000000400fed <+7>:     shr    $0x1f,%ebx
   0x0000000000400ff0 <+10>:    add    %ebx,%eax
   0x0000000000400ff2 <+12>:    sar    %eax
   0x0000000000400ff4 <+14>:    lea    (%rax,%rsi,1),%ebx
   0x0000000000400ff7 <+17>:    cmp    %edi,%ebx
   0x0000000000400ff9 <+19>:    jle    0x401007 <func4+33>
   0x0000000000400ffb <+21>:    lea    -0x1(%rbx),%edx
   0x0000000000400ffe <+24>:    callq  0x400fe6 <func4>
   0x0000000000401003 <+29>:    add    %ebx,%eax
   0x0000000000401005 <+31>:    jmp    0x401017 <func4+49>
   0x0000000000401007 <+33>:    mov    %ebx,%eax
   0x0000000000401009 <+35>:    cmp    %edi,%ebx
   0x000000000040100b <+37>:    jge    0x401017 <func4+49>
   0x000000000040100d <+39>:    lea    0x1(%rbx),%esi
   0x0000000000401010 <+42>:    callq  0x400fe6 <func4>
   0x0000000000401015 <+47>:    add    %ebx,%eax
   0x0000000000401017 <+49>:    pop    %rbx
   0x0000000000401018 <+50>:    retq   
End of assembler dump.
```

发现,当传入值为`11`时,返回值为`0x12` <br>
顺便把1~14的返回值都列出来:
```
1 eax :11
2 eax :13
3 eax :10
4 eax :13
5 eax :15
6 eax :21
7 eax :7
8 eax :35
9 eax :27
10 eax :37
11 eax :18  <=
12 eax :38
13 eax :41
14 eax :45
```
输入`11 18`
```
11 18
So you got that one.  Try this one.
```
破关.

### Phase_5
反汇编
```C
(gdb) disas phase_5
Dump of assembler code for function phase_5:
   0x0000000000401070 <+0>:	push   %rbx
   0x0000000000401071 <+1>:	sub    $0x10,%rsp
   0x0000000000401075 <+5>:	mov    %rdi,%rbx
   0x0000000000401078 <+8>:	callq  0x4012c1 <string_length>
   0x000000000040107d <+13>:	cmp    $0x6,%eax
   0x0000000000401080 <+16>:	je     0x4010c2 <phase_5+82>
   0x0000000000401082 <+18>:	callq  0x401544 <explode_bomb>
   0x0000000000401087 <+23>:	jmp    0x4010c2 <phase_5+82>
   0x0000000000401089 <+25>:	movzbl (%rbx,%rax,1),%edx
   0x000000000040108d <+29>:	and    $0xf,%edx
   0x0000000000401090 <+32>:	movzbl 0x402530(%rdx),%edx
   0x0000000000401097 <+39>:	mov    %dl,(%rsp,%rax,1)
   0x000000000040109a <+42>:	add    $0x1,%rax
   0x000000000040109e <+46>:	cmp    $0x6,%rax
   0x00000000004010a2 <+50>:	jne    0x401089 <phase_5+25>
   0x00000000004010a4 <+52>:	movb   $0x0,0x6(%rsp)
   0x00000000004010a9 <+57>:	mov    $0x4024e6,%esi
   0x00000000004010ae <+62>:	mov    %rsp,%rdi
   0x00000000004010b1 <+65>:	callq  0x4012de <strings_not_equal>
   0x00000000004010b6 <+70>:	test   %eax,%eax
   0x00000000004010b8 <+72>:	je     0x4010c9 <phase_5+89>
   0x00000000004010ba <+74>:	callq  0x401544 <explode_bomb>
   0x00000000004010bf <+79>:	nop
   0x00000000004010c0 <+80>:	jmp    0x4010c9 <phase_5+89>
   0x00000000004010c2 <+82>:	mov    $0x0,%eax
   0x00000000004010c7 <+87>:	jmp    0x401089 <phase_5+25>
   0x00000000004010c9 <+89>:	add    $0x10,%rsp
   0x00000000004010cd <+93>:	pop    %rbx
   0x00000000004010ce <+94>:	retq   
End of assembler dump.
```
根据经验和函数名,`<+8><+13><+16>`看出输入一串长度为6字符串<br>
有几个很可疑的字符串,调出来看看.
```
(gdb) x/s 0x402530
0x402530 <array.3161>:  "maduiersnfotvbylSo you think you can stop the bomb with ctrl-c, do you?"

(gdb) x/s 0x4024e6
0x4024e6:       "devils"
```
然后在`maduiersnfotvbyl`中按照`devils`取下标,得到`25d4f7`<br>
转换成16进制,在a~z中找对应的字母.<br>
得到`beldog`<br>
输入<br>
```
beldog
Good work!  On to the next...
```
破关.

### Phase_6
反汇编
```C
(gdb) disas phase_6
Dump of assembler code for function phase_6:
=> 0x00000000004010cf <+0>:	push   %r13
   0x00000000004010d1 <+2>:	push   %r12
   0x00000000004010d3 <+4>:	push   %rbp
   0x00000000004010d4 <+5>:	push   %rbx
   0x00000000004010d5 <+6>:	sub    $0x58,%rsp
   0x00000000004010d9 <+10>:	lea    0x30(%rsp),%rsi
   0x00000000004010de <+15>:	callq  0x40157a <read_six_numbers>
   0x00000000004010e3 <+20>:	lea    0x30(%rsp),%r13
   0x00000000004010e8 <+25>:	mov    $0x0,%r12d
   0x00000000004010ee <+31>:	mov    %r13,%rbp
   0x00000000004010f1 <+34>:	mov    0x0(%r13),%eax
   0x00000000004010f5 <+38>:	sub    $0x1,%eax
   0x00000000004010f8 <+41>:	cmp    $0x5,%eax
   0x00000000004010fb <+44>:	jbe    0x401102 <phase_6+51>
   0x00000000004010fd <+46>:	callq  0x401544 <explode_bomb>
   0x0000000000401102 <+51>:	add    $0x1,%r12d
   0x0000000000401106 <+55>:	cmp    $0x6,%r12d
   0x000000000040110a <+59>:	jne    0x401113 <phase_6+68>
   0x000000000040110c <+61>:	mov    $0x0,%esi
   0x0000000000401111 <+66>:	jmp    0x401155 <phase_6+134>
   0x0000000000401113 <+68>:	mov    %r12d,%ebx
   0x0000000000401116 <+71>:	movslq %ebx,%rax
   0x0000000000401119 <+74>:	mov    0x30(%rsp,%rax,4),%eax
   0x000000000040111d <+78>:	cmp    %eax,0x0(%rbp)
   0x0000000000401120 <+81>:	jne    0x401127 <phase_6+88>
   0x0000000000401122 <+83>:	callq  0x401544 <explode_bomb>
   0x0000000000401127 <+88>:	add    $0x1,%ebx
   0x000000000040112a <+91>:	cmp    $0x5,%ebx
   0x000000000040112d <+94>:	jle    0x401116 <phase_6+71>
   0x000000000040112f <+96>:	add    $0x4,%r13
   0x0000000000401133 <+100>:	jmp    0x4010ee <phase_6+31>
   0x0000000000401135 <+102>:	mov    0x8(%rdx),%rdx
   0x0000000000401139 <+106>:	add    $0x1,%eax
   0x000000000040113c <+109>:	cmp    %ecx,%eax
   0x000000000040113e <+111>:	jne    0x401135 <phase_6+102>
   0x0000000000401140 <+113>:	jmp    0x401147 <phase_6+120>
   0x0000000000401142 <+115>:	mov    $0x6042f0,%edx
   0x0000000000401147 <+120>:	mov    %rdx,(%rsp,%rsi,2)
   0x000000000040114b <+124>:	add    $0x4,%rsi
   0x000000000040114f <+128>:	cmp    $0x18,%rsi
   0x0000000000401153 <+132>:	je     0x40116a <phase_6+155>
   0x0000000000401155 <+134>:	mov    0x30(%rsp,%rsi,1),%ecx
   0x0000000000401159 <+138>:	cmp    $0x1,%ecx
   0x000000000040115c <+141>:	jle    0x401142 <phase_6+115>
   0x000000000040115e <+143>:	mov    $0x1,%eax
   0x0000000000401163 <+148>:	mov    $0x6042f0,%edx
   0x0000000000401168 <+153>:	jmp    0x401135 <phase_6+102>
   0x000000000040116a <+155>:	mov    (%rsp),%rbx
   0x000000000040116e <+159>:	lea    0x8(%rsp),%rax
   0x0000000000401173 <+164>:	lea    0x30(%rsp),%rsi
   0x0000000000401178 <+169>:	mov    %rbx,%rcx
   0x000000000040117b <+172>:	mov    (%rax),%rdx
   0x000000000040117e <+175>:	mov    %rdx,0x8(%rcx)
   0x0000000000401182 <+179>:	add    $0x8,%rax
   0x0000000000401186 <+183>:	cmp    %rsi,%rax
   0x0000000000401189 <+186>:	je     0x401190 <phase_6+193>
   0x000000000040118b <+188>:	mov    %rdx,%rcx
   0x000000000040118e <+191>:	jmp    0x40117b <phase_6+172>
   0x0000000000401190 <+193>:	movq   $0x0,0x8(%rdx)
   0x0000000000401198 <+201>:	mov    $0x5,%ebp
   0x000000000040119d <+206>:	mov    0x8(%rbx),%rax
   0x00000000004011a1 <+210>:	mov    (%rax),%eax
   0x00000000004011a3 <+212>:	cmp    %eax,(%rbx)
   0x00000000004011a5 <+214>:	jle    0x4011ac <phase_6+221> //从小到大
   0x00000000004011a7 <+216>:	callq  0x401544 <explode_bomb>
   0x00000000004011ac <+221>:	mov    0x8(%rbx),%rbx
   0x00000000004011b0 <+225>:	sub    $0x1,%ebp
   0x00000000004011b3 <+228>:	jne    0x40119d <phase_6+206>
   0x00000000004011b5 <+230>:	add    $0x58,%rsp
   0x00000000004011b9 <+234>:	pop    %rbx
   0x00000000004011ba <+235>:	pop    %rbp
   0x00000000004011bb <+236>:	pop    %r12
   0x00000000004011bd <+238>:	pop    %r13
   0x00000000004011bf <+240>:	retq   
End of assembler dump.
```
代码非常的长.<br>
但是发现有一个很突兀的地址:`0x6042f0`,调出来看看.
```
(gdb) x /32x 0x6042f0
0x6042f0 <node1>:       0xcb    0x02    0x00    0x00    0x01    0x00    0x00    0x00
0x6042f8 <node1+8>:     0x00    0x43    0x60    0x00    0x00    0x00    0x00    0x00
0x604300 <node2>:       0x43    0x00    0x00    0x00    0x02    0x00    0x00    0x00
0x604308 <node2+8>:     0x10    0x43    0x60    0x00    0x00    0x00    0x00    0x00
```
好像有很多node,多调出来一点看看
```C
(gdb) x/12g 0x6042f0
0x6042f0 <node1>:       0x00000001000002cb      0x0000000000604300
0x604300 <node2>:       0x0000000200000043      0x0000000000604310
0x604310 <node3>:       0x0000000300000225      0x0000000000604320
0x604320 <node4>:       0x0000000400000217      0x0000000000604330
0x604330 <node5>:       0x00000005000000a8      0x0000000000604340
0x604340 <node6>:       0x00000006000001e8      0x0000000000000000
```
从而明白了,每个node是一个节点,定义为
```C
typedef struct node{
    int index;
    int val;
    node* next;
};
```

回到原代码中<br>
发现有两个主要的判断循环<br>
到`<+59>`为止,判断输入的6个数是否是均小于等于6,且互不相等.<br>
即输入一个1~6的全排列.<br>
而从`<+214>`可以看出,第二个循环不断检测相应的每个节点是否比上一个节点数大.<br>
从而知道,该题需要输入从小到大排列的node的编号.
```C
0x6042f0 <node1>:	715	1	6308608	0
0x604300 <node2>:	67	2	6308624	0
0x604310 <node3>:	549	3	6308640	0
0x604320 <node4>:	535	4	6308656	0
0x604330 <node5>:	168	5	6308672	0
0x604340 <node6>:	488	6	0	0
```
输入
```
2 5 6 4 3 1
Congratulations! You've defused the bomb!
```
破关,至此，所有的正常关卡都已经完成.
YO~~

### 彩蛋!彩蛋! Secret_phase
浏览<phase_defused>函数的时候发现还有一个<secret_phase>的调用.<br>
但是正常的时候并没有出现.<br>
```C
Dump of assembler code for function phase_defused:
   0x00000000004016e2 <+0>:	sub    $0x68,%rsp
   0x00000000004016e6 <+4>:	mov    $0x1,%edi
   0x00000000004016eb <+9>:	callq  0x401480 <send_msg>
   0x00000000004016f0 <+14>:	cmpl   $0x6,0x2030a5(%rip)        # 0x60479c <num_input_strings>
   0x00000000004016f7 <+21>:	jne    0x401766 <phase_defused+132>
   0x00000000004016f9 <+23>:	lea    0x10(%rsp),%r8
   0x00000000004016fe <+28>:	lea    0x8(%rsp),%rcx
   0x0000000000401703 <+33>:	lea    0xc(%rsp),%rdx
   0x0000000000401708 <+38>:	mov    $0x4027d7,%esi
   0x000000000040170d <+43>:	mov    $0x6048b0,%edi
   0x0000000000401712 <+48>:	mov    $0x0,%eax
   0x0000000000401717 <+53>:	callq  0x400c30 <__isoc99_sscanf@plt>
   0x000000000040171c <+58>:	cmp    $0x3,%eax
   0x000000000040171f <+61>:	jne    0x401752 <phase_defused+112>
   0x0000000000401721 <+63>:	mov    $0x4027e0,%esi
   0x0000000000401726 <+68>:	lea    0x10(%rsp),%rdi
   0x000000000040172b <+73>:	callq  0x4012de <strings_not_equal>
   0x0000000000401730 <+78>:	test   %eax,%eax
   0x0000000000401732 <+80>:	jne    0x401752 <phase_defused+112>
   0x0000000000401734 <+82>:	mov    $0x402638,%edi
   0x0000000000401739 <+87>:	callq  0x400b40 <puts@plt>
   0x000000000040173e <+92>:	mov    $0x402660,%edi
   0x0000000000401743 <+97>:	callq  0x400b40 <puts@plt>
   0x0000000000401748 <+102>:	mov    $0x0,%eax
   0x000000000040174d <+107>:	callq  0x4011fe <secret_phase>
   0x0000000000401752 <+112>:	mov    $0x402698,%edi
   0x0000000000401757 <+117>:	callq  0x400b40 <puts@plt>
   0x000000000040175c <+122>:	mov    $0x4026c8,%edi
   0x0000000000401761 <+127>:	callq  0x400b40 <puts@plt>
   0x0000000000401766 <+132>:	add    $0x68,%rsp
   0x000000000040176a <+136>:	retq   
End of assembler dump.
```
把里面所有可疑的地址的字符串都看一遍.
```C
(gdb) x/s 0x402698
0x402698:	"Congratulations! You've defused the bomb!"
(gdb) x/s 0x4026c8
0x4026c8:	"Your instructor has been notified and will verify your solution."
(gdb) x/s 0x402660
0x402660:	"But finding it and solving it are quite different..."
(gdb) x/s 0x402638
0x402638:	"Curses, you've found the secret phase!"
(gdb) x/s 0x4027e0
0x4027e0:	"DrEvil"
(gdb) x/s 0x6048b0
0x6048b0 <input_strings+240>:	"11 18"
(gdb) x/s 0x4027d7
0x4027d7:	"%d %d %s"
```
`11 18`不是我们之前输入的第四题答案吗?<br>
发现原来第四关的时候是要输入三个参数`"%d %d %s"`,而之后输入的字符串和`DrEvil`比较<br>
从而更改第四题答案改一下.
```
11 18DrEvil
```
在Phase_6之后会有
```
Good work!  On to the next...
2 5 6 4 3 1
Curses, you've found the secret phase!
But finding it and solving it are quite different...
```
反汇编`<secret_phase>`
```C
(gdb) disas secret_phase 
Dump of assembler code for function secret_phase:
   0x00000000004011fe <+0>:     push   %rbx
   0x00000000004011ff <+1>:     callq  0x4015bc <read_line>
   0x0000000000401204 <+6>:     mov    $0xa,%edx
   0x0000000000401209 <+11>:    mov    $0x0,%esi
   0x000000000040120e <+16>:    mov    %rax,%rdi
   0x0000000000401211 <+19>:    callq  0x400c00 <strtol@plt>
   0x0000000000401216 <+24>:    mov    %rax,%rbx
   0x0000000000401219 <+27>:    lea    -0x1(%rax),%eax
   0x000000000040121c <+30>:    cmp    $0x3e8,%eax
   0x0000000000401221 <+35>:    jbe    0x401228 <secret_phase+42>
   0x0000000000401223 <+37>:    callq  0x401544 <explode_bomb>
   0x0000000000401228 <+42>:    mov    %ebx,%esi
   0x000000000040122a <+44>:    mov    $0x604110,%edi
   0x000000000040122f <+49>:    callq  0x4011c0 <fun7>
   0x0000000000401234 <+54>:    cmp    $0x7,%eax
   0x0000000000401237 <+57>:    je     0x40123e <secret_phase+64>
   0x0000000000401239 <+59>:    callq  0x401544 <explode_bomb>
   0x000000000040123e <+64>:    mov    $0x4024c0,%edi
   0x0000000000401243 <+69>:    callq  0x400b40 <puts@plt>
   0x0000000000401248 <+74>:    callq  0x4016e2 <phase_defused>
   0x000000000040124d <+79>:    pop    %rbx
   0x000000000040124e <+80>:    retq   
End of assembler dump.
```
老规矩,可疑内存看一看
```C
(gdb) x/64x 0x604110
0x604110 <n1>:  0x0000000000000024      0x0000000000604130
0x604120 <n1+16>:       0x0000000000604150      0x0000000000000000
0x604130 <n21>: 0x0000000000000008      0x00000000006041b0
0x604140 <n21+16>:      0x0000000000604170      0x0000000000000000
0x604150 <n22>: 0x0000000000000032      0x0000000000604190
0x604160 <n22+16>:      0x00000000006041d0      0x0000000000000000
0x604170 <n32>: 0x0000000000000016      0x0000000000604290
0x604180 <n32+16>:      0x0000000000604250      0x0000000000000000
0x604190 <n33>: 0x000000000000002d      0x00000000006041f0
0x6041a0 <n33+16>:      0x00000000006042b0      0x0000000000000000
0x6041b0 <n31>: 0x0000000000000006      0x0000000000604210
0x6041c0 <n31+16>:      0x0000000000604270      0x0000000000000000
0x6041d0 <n34>: 0x000000000000006b      0x0000000000604230
0x6041e0 <n34+16>:      0x00000000006042d0      0x0000000000000000
0x6041f0 <n45>: 0x0000000000000028      0x0000000000000000
0x604200 <n45+16>:      0x0000000000000000      0x0000000000000000
0x604210 <n41>: 0x0000000000000001      0x0000000000000000
0x604220 <n41+16>:      0x0000000000000000      0x0000000000000000
0x604230 <n47>: 0x0000000000000063      0x0000000000000000
0x604240 <n47+16>:      0x0000000000000000      0x0000000000000000
0x604250 <n44>: 0x0000000000000023      0x0000000000000000
0x604260 <n44+16>:      0x0000000000000000      0x0000000000000000
0x604270 <n42>: 0x0000000000000007      0x0000000000000000
0x604280 <n42+16>:      0x0000000000000000      0x0000000000000000
0x604290 <n43>: 0x0000000000000014      0x0000000000000000
0x6042a0 <n43+16>:      0x0000000000000000      0x0000000000000000
0x6042b0 <n46>: 0x000000000000002f      0x0000000000000000
0x6042c0 <n46+16>:      0x0000000000000000      0x0000000000000000
0x6042d0 <n48>: 0x00000000000003e9      0x0000000000000000
0x6042e0 <n48+16>:      0x0000000000000000      0x0000000000000000
0x6042f0 <node1>:       0x00000001000002cb      0x0000000000604300
0x604300 <node2>:       0x0000000200000043      0x0000000000604310
```
还原一下数据结构
```C
typedef struct treeNode{
    int data;
    node* left;
    node* right;
};
```
是树!<br>
那就画出来
```C
              36
        /           \
      8               50
    /    \          /    \
   /      \        /      \
  6       22      45      107
 / \     /  \    /  \    /   \
1   7   20  35  40  47  99  1001
```
回到原函数,不难发现就是输入一个数,使得`<fun7>`返回值为0x7.<br>
进入`<fun7>`看看
```
(gdb) disas fun7
Dump of assembler code for function fun7:
   0x00000000004011c0 <+0>:	sub    $0x8,%rsp
   0x00000000004011c4 <+4>:	test   %rdi,%rdi
   0x00000000004011c7 <+7>:	je     0x4011f4 <fun7+52>
   0x00000000004011c9 <+9>:	mov    (%rdi),%edx
   0x00000000004011cb <+11>:	cmp    %esi,%edx
   0x00000000004011cd <+13>:	jle    0x4011dc <fun7+28>
   0x00000000004011cf <+15>:	mov    0x8(%rdi),%rdi
   0x00000000004011d3 <+19>:	callq  0x4011c0 <fun7>
   0x00000000004011d8 <+24>:	add    %eax,%eax
   0x00000000004011da <+26>:	jmp    0x4011f9 <fun7+57>
   0x00000000004011dc <+28>:	mov    $0x0,%eax
   0x00000000004011e1 <+33>:	cmp    %esi,%edx
   0x00000000004011e3 <+35>:	je     0x4011f9 <fun7+57>
   0x00000000004011e5 <+37>:	mov    0x10(%rdi),%rdi
   0x00000000004011e9 <+41>:	callq  0x4011c0 <fun7>
   0x00000000004011ee <+46>:	lea    0x1(%rax,%rax,1),%eax
   0x00000000004011f2 <+50>:	jmp    0x4011f9 <fun7+57>
   0x00000000004011f4 <+52>:	mov    $0xffffffff,%eax
   0x00000000004011f9 <+57>:	add    $0x8,%rsp
   0x00000000004011fd <+61>:	retq   
End of assembler dump.
```
逆向工程一下,不难发现是这样一个函数
```C
int fun7(struct treeNode* p, int v)
{
    if (p == NULL)
        return -1;
    else if (v < p->data)
        return 2 * fun7(p->leftChild, v);
    else if (v == p->data)
        return 0;
    else 
        return 2 * fun7(p->rightChild, v) + 1;
}
```
发现要想得到返回值为`0x7`,需要输入底层从小到大第`7+1`个节点的值,即1001.
```
1001
Wow! You've defused the secret stage!
Congratulations! You've defused the bomb!
Your instructor has been notified and will verify your solution.
```
所以到这里,全部的炸弹都完成了!<br>
放个全家福
```
Starting program: /home/2017202034/bomb3/bomb input.txt 
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
Phase 1 defused. How about the next one?
That's number 2.  Keep going!
Halfway there!
So you got that one.  Try this one.
Good work!  On to the next...
Curses, you've found the secret phase!
But finding it and solving it are quite different...
Wow! You've defused the secret stage!
Congratulations! You've defused the bomb!
Your instructor has been notified and will verify your solution.
```