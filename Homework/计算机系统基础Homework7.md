# Homework7 Report
**学号:2017202034 <br>**
**姓名:张大方**


## 题目一




```
int fun(short c, char d, int * p, int x){
    *p = d;
    return x-c;
}
```




## 题目二

Instruction|Value of %esp|Value of %ebp
------|------|------
Instruction1| 0x7FFFFFC4|0x7FFFFFF4
Instruction2| 0x7FFFFFC4 |0x7FFFFFC4
Instruction3| 0x7FFFFFC4 |0x7FFFFFC4

## 题目三

### 1.
```
int main(){
    int a,b;
    scanf("%d %d",a,b);
    printf("%d %d %d\n",a^b,b,a);
}
```

### 2.
```
 --------------
| 0x8000420    |
 --------------      %edi : .LC1
    ···              %esi : a^b
    ···              %edx : b
    ···              %ecx : a
 --------------      %rsp : 0x8000408
| 0x8000414 :a |
 --------------
 --------------
| 0x8000410 :b |
 --------------
 --------------
| 0x8000408    |
 --------------
     


```