# 


Operand | Value
--------|--------
%ebx| 0x100
$0x150|0x150
0x170|0x17
(%ebx)|0x10
(%ebx,%eax)|0x11
0x30(%ebx)|0x13
80(%ebx,%eax,2)|0x20

Instruction|Destination|Value
-----------|-----------|------
addl %eax,%ebx|%ebx|0x110
subl %eax,(%ebx)|0x100|0
leal 0x50(%eax),%edx|%edx|0x60
movzbl %al,%ebx|%ebx|0x10
movsbl %bh,%ecx|%ecx|0x1

Instruction|OF|SF|ZF|CF
-----------|---|---|---
leal (%eax),%ebx |0|0|0|0
subl %ebx, %eax |0|1|0|0
xorl %eax, %eax |0|0|1|0
test %eax, %ebx |0|0|1|0

## 题目二

```C
int main(){
    int a = 3;
    int b = 2;
    int c = 1;
    if(a<=5){
        int k = c;
        c = b;
        b = k;
        a++;
    }
    return b;
}
