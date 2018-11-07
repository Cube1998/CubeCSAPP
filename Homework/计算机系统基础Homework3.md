# Homework3 Report
**学号:2017202034 <br>**
**姓名:张大方**
## 题目1

### 题目描述

Consider the following function 
typedef unsigned char * byte_pointer;
```C
void show_bytes(byte_pointer start, int len) { 
int i;
for (i=0; i<len; i++) 
printf(“%.2x”, start[i]); 
} 
int val = 0x140A0233;
byte_pointer valp = (byte_pointer) & val; 
```
What is the output of the following call to show_bytes on big-endian 
and little-endian machines respectively? 


### 题解

   show_bytes()     |  Big Endian |  Small Endian
--------|----------|---------
show_bytes(valp,1) | 33 | 33 
show_bytes(valp,2) |3302| 0233
show_bytes(valp,4) |33020A14 |140A0233 




## 题目2
### 题目描述
Fill in the missing information in the following table: 

### 题解

    Fractional value|  Binary representation |  Decimal representation
--------|----------|---------
1/8 |  0.001 |0.125  
3/4 | 0.11 | 0.75
43/16 |10.1011 | 2.6875
 25/16 | 1.1001 | 1.5625
 51/16| 11.0011 | 3.1875




## 题目3

### 题目描述

Given a floating-point format with a k-bit exponent and an n-bit fraction, 
write formulas for the exponent E, significand M, the fraction f, and the 
value V for the quantities that follow. In addition, describe the bit 
representation.

### 题解

A. The number 5.0<br>
Sol: V = 5.0 = 101 = 1.01×2^2 = M×2^E<br>
 => M = 1.01 and E = 2<br>
 => M = 1+ .01 = 1 + frac×(2^(-n))<br>
 => frac = 1100..0 with (n-2) bits of zeros.<br>
 exp = E + Bias = 2 + 2^(k-1) - 1 = 2^(k-1) + 1
     = 100..01 with (k-2) bits of zeros<br>
 Its bit representation is<br>
 100.(k-2 zeroes).01, 1100.(n-2 zeroes).0<br>
--------

B.The largest odd integer that can be represented
exactly.

Sol: Assume k,n are fixed values.<br>
 V = M×2^E<br>
   = [1+frac× 2^(-n)]×2^E<br>
   =[2^n + frac] ×2^(E-n)<br>
   =[2^n + frac] ×2^(exp-Bias-n)<br>
   =[2^n + frac] ×2^(exp-(2^(k-1)-1)-n)<br>

 Let T = exp - (2^(k-1) -1) - n, <br>
 then V = [2^n + frac] × 2^T<br>
 if (T>=1) , then 2^T is even, <br>
 so is V, no matter what value frac is.<br>
 Therefore in order to have the largest odd value, T = 0<br>

 i.e., exp - (2^(k-1)-1) - n = 0 => exp = 2^(k-1) + n-1<br>
 exp = 1 xx..x with the significant bit 1 and its total <br>
 value is 2^(k-1) + n-1.<br>

 Also we want *2^n+frac* to be the largest odd value, <br>
 which means frac to be odd and the largest value for <br>
 *frac* is 11..1 with n bits of 1.<br>
 Its bit representation is<br>
exp | frac
-----|-----
1 xx..x | 11..1
Its last k-1 bits value is n-1 | All n bits be 1
-------
C.  The reciprocal of the smallest positive normalized value.<br>
Sol: smallest normalized value Vmin<br>
=> exp = 00..01 <br>
=> E = 1 - Bias <br>
     = 1 - (2^(k-1)-1)<br> 
     = 2-2^(k-1)<br>
and frac = 00..0 <br>
=> M = 1 + frac×2^(-n)<br>
= 1<br>
 Vmin= M×2E =1×2E<br>
Let V' =1/Vmin = 2^(-E)<br>
       = 2^(2^(k-1)-2)<br>
       =M' × 2E'<br>
 So M' = 1.0 = 1 + frac' × 2^(-n)<br>
=> frac' = 00..0<br>
 E' = exp'-Bias' <br>
 => exp' = E'+Bias'<br>
         = 2^(k-1)-2+ 2^(k-1)-1<br>
         =(2^(k-1))-2<br>
 Therefore exp' = 11..101<br>
 Its bit representation is<br>
 11...101, 00...0<br>


## 题目4

### 题目描述
Consider the following two 9-bit floating-point representations based on the IEEE floating-point format.
* Format A <br>
There is one sign bit. <br>
There are k = 5 exponent bits. The exponent bias is 15.  <br>
There are n = 3 fraction bits.<br>
* Format B<br>
There is one sign bit.<br> 
There are k = 4 exponent bits. The exponent bias is 7.<br>
There are n = 4 fraction bits.<br>
Below, you are given some bit patterns in Format A, and your task is to convert <br>
them to the closest value in Format B. If rounding is necessary, you should round <br>
toward *Infinity*<br>
In addition, give the values of numbers given by the Format A and Format B bit <br> 
patterns. Given these as whole numbers(eg.,17) or as fractions(eg.,17/64 or 17/26). <br>


### 题解
    Format A|   Format A  | Format B |  Format B
--------|----------|---------|--------
Bits |  Value |Bits | Value  
1 01110 001 | -9/16 | 1 0110 0010 | -9/16
0 10110 101 | 208 | 0 1110 1010 | 208
1 00111 110 | -7/1024 |1 0000 0111| -7/1024   
0 00000 101 | 5/131072 |0 0000 0001| 1/1024
1 11011 000 | - 4096 | 1 1110 1111| -248
0 11000 100 | 256|  0 1111 0000  | Infinite

学号:2017202034 
姓名:张大方