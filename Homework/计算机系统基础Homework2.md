# Homework2 Report
**学号:2017202034 <br>**
**姓名:张大方**
## 题目1
Value | two's complement
------|-----------------
37| 00100101
-15|11110001
    85|01010101
 -86   |10101010


## 题目2

Expression | Binary Representation
------|-----------------
us| 0011
ui| 00110100
us<<1 | 0110
 i>>2   |11100110
ui>>2 | 00001101
(short) i|1100
(int) s |11111101
## 题目3
Write a function with the following prototype: 
 * Determine whether arguments can be added without overflow 
* This function should return 0 if arguments x and y can be added without causing overflow
```C 
int uadd_ok(unsigned x,unsigned y){
    unsigned sum = x + y;
    return sum >= x;

} 

```
