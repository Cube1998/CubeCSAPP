# Homework1 Report

## 题目1



Binary  |  Octal |  Decimal| Hexdecimal
--------|----------|---------|-------
10101010110 | 2526 | 1366 |556
111111111 |777| 511| 0x1ff
111000101 |705 |453 |0x1c5
11111011111 |3737 |2015| 0x7df
10000001101 |2015 |1037 |0x40d


## 题目2
#### a) 0x3a
#### b) 0xff
#### c) 0xc5
#### d) 0xffffffc5
#### e) 0x1
#### f) 0x1

<br>
<br>
<br>
<br>
<br>


## 题目3.1
#### a)
` return !(~x);`
#### b)
` return !x ;`
#### c)
`//if problem means least significant byte is ff`<br>
` return !((x & 0xff)^0xff) ;` <br>
`//if problem means least significant byte is 01`<br>
` return !((x & 0xff)^0x1) ;`
#### d)
` return !((x & 0xff)^0x0) ;`

## 题目3.2

```
   return (y>>16<<16+0xffff)&(((~0)<<16) | x);
```

学号:2017202034 <br>
姓名:张大方