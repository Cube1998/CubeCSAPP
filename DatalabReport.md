# Datalab Report
姓名: 张大方
学号: 2017202034<br>

## Problem 1 : bitAnd

注意到逻辑表达式: <br>
`!(x&&y) = ((!x)||(!y))`<br>
转换成位运算: <br>
`~(x&y) = ((~x)|(~y)) ` <br>
因而有如下解法:
```C
int bitAnd(int x, int y) {
  return ~((~x)|(~y));
}
```
性能分析: <br>
Max ops : 8 <br>
Using ops : 4 <br>

## Problem 2 : evenBits

用8bits的0x55扩展到32bits即可 <br>
注意此处的evenbits即偶数位是从 **最右端是第0位** 开始计数的 <br>
因而代码如下:
```C
int evenBits(void) {
  int a = 0x55;
  a = (a<<8)+a;
  a = (a<<16)+a;
  return a;
}
```
性能分析:<br>
Max ops : 8 <br>
Using ops: 4 <br>
 
## Problem 3 : fitsShort

只需验证前17位是否相同即可 <br>
代码实现如下:
```C
int fitsShort(int x) {
    return !((x<<16>>16)^x);   
}
```
性能分析: <br>
Max ops :  8 <br>
Using ops : 4<br>

## Problem 4 : isTmax

要求就是检查是否是0x7FFFFFFF <br>
分为两部分判定: <br>
第一部分是确定从弟0位到第30位全部都是1 <br>
`((x+1)^x)+1)` <br>
第二部分是判定是否是0xFFFFFFFF <br>
`(!!(~x)`<br>
两部分按位取与，然后再取非，得到最终代码 <br>
`!(((x+1)^x)+1)&(!!(~x))` <br>
注意到两个"+"可以合并，'&'换成'|'后可以少一个'!'
优化后的代码实现:
```C
int isTmax(int x) {
  return !(((x+x)+2)|(!(~x)));
}
```
性能分析:
Max ops : 8
Using ops : 6

## Problem 5 : minusOne

大水题，返回0xFFFFFFFF,对0x0按位取反即可<br>
代码实现:<br>
```C
int minusOne(void) {
  return ~0;  //Take opposite of 0;
}
```
性能分析: <br>
Max ops : 2 <br>
Using ops : 1 <br>

## Problem 6 : upperBits

要求返回前n位为1的int型数 <br>
直观上思考只需将0xFFFFFFFF向右移位(32-n)即可，即 <br>
```C
  int k = 33+(~n);
  return (~0)<<k ;
```
但是注意到这里的n的范围为0 <= n <= 32<br>
所以当n为0时，左移操作32位是不会被计算机所接受的<br>
因而我们加入对n = 0时的特判<br>
代码实现如下: <br>
```C
int upperBits(int n) {
   int k = 33+(~n);
  return ((~0)<<k)&(~((~(!n))+1));
}
```
性能分析: <br>
Max ops : 10 <br>
Using ops : 9 <br>

## Problem 7 : allEvenBits

要求判断给定数字的所有偶数位是否都是1 <br>
首先把所有奇数位数字置0，再与0x55555555按位取异或，结果再取反并输出<br>
代码实现如下:<br>
```C
int allEvenBits(int x) {
  int m= 0x55;
	m = (m<<8)|m;
  m = (m<<16)|m;
	return !((x&m)^m);
  
}
```
性能分析: <br>
Max ops : 12 <br>
Using ops : 7 <br>

## Problem 8 : byteSwap
非常有意思的一道题<br>
有点像无线电波的加密和解码的过程<br>
注意到异或操作有如下性质:<br>
`y = x ^ (x^y)` <br>
所以我们考虑把第m个和第n个字节提取出来，按位取异或得到mask<br>
再把mask放到第m个和第n个字节的位置，和原数取异或<br>
具体代码实现如下:<br>
```C
int byteSwap(int x, int n, int m) {
      //注意到异或可以储存和复原信息
      int m_8 = m<<3;
      int n_8 = n<<3;
      int mask = ((x>>m_8)^(x>>n_8))&0xff;
      return x^((mask<<m_8)|(mask<<n_8));
}
```
性能分析:
Max ops : 25
Using ops : 10

## Problem 9 : copyLSB
要求所有bit与最低位相同，利用计算机处理右移时保号的性质即可<br>
代码实现如下:
```C
int copyLSB(int x) {
  return x<<31>>31;
}
```
性能分析:
Max ops : 5
Using ops : 2

## Problem 10 : divpwr2
注意到题意是向零靠近取整
正数部分，只需右移n位即可
但是对于负数部分，由于一对相反数，补码为取反加1
因而对于负数，应该首先加上(2^n -1)，再进行移位
即关键在于构造出来一个x为正就无影响，为负时不做操作
代码实现如下:
```C
int divpwr2(int x, int n) {
    
    int sign_mark = (x>>31);
    int k = (0x1<<n)+(~0);//考虑如何做出一个右(n)位为1的数
    int right_n_1 = sign_mark & k;
    return (x+right_n_1)>>n;
}
```
性能分析:
Max ops : 15
Using ops : 7

## Problem 11 : leastBitPos

考虑到100···000的尾串取反加1后与自身相等
而前面的串取反加一后刚好相异
进而得解
代码实现如下:
```C
int leastBitPos(int x) {
  return (~x +1)& x;
}
```
性能分析:
Max ops : 6
Using ops : 3

## Problem 12 : oddBits

返回0xAAAAAAAA即可
```C
int oddBits(void) {
  int t = 0xaa;
  t = (t<<8)|t;
  t = (t<<16)|t;
  return t;
}
```
性能分析:
Max ops : 8
Using ops : 4

## Problem 13 : bitMask
用高位全为1的两组数取异或即可
代码实现如下:
```C
int bitMask(int highbit, int lowbit) {
  //Make right are 1s
  int ffffffff = ~0;
  int high_one = (ffffffff<<(highbit)<<1);
  int low_one = (ffffffff<<lowbit);
  return (high_one^low_one)&low_one; //防止错位
}

```
性能分析:
Max ops : 16
Using ops : 6

## Problem 14 : isLess

考虑到三种情况:
```
  1). x < 0 , y > 0
  2). x > 0 , y > 0 , x - y<0
  3). x > 0 , y < 0 
```
需要满足1)或2)，但是不满足3)

应该还能优化,想到再写
代码实现如下:
```C
int isLess(int x, int y) {
    int x_sign = (x >> 31) & 0x1;
    int y_sign = (y >> 31) & 0x1;

    return ((x_sign & ~y_sign) | !(((~x+y)>>31)&0x1))&(!((~x_sign) &y_sign));
}
```
再次优化,对符号的处理不再与0x1做按位与
只考虑两种情况：
**二者符号相同,差sub小于零**
**x为负数,y为正数(按最高位0/1考虑)**
优化后代码实现如下:
```C
int isLess(int x, int y) {
  int x_sign = (x >> 31) ;
    int y_sign = (y >> 31) ;
    int sign_sub = ((x + (~y))+1)>>31;
    int result_if_sign_same = (sign_sub)&(!(x_sign^y_sign));
    int result_if_sign_diff = x_sign&(!y_sign);
    return result_if_sign_same|result_if_sign_diff;
}
```

性能分析:
Max ops : 24
Using ops : 16(first)==>>12(final)

## Problem 15 : logicalShift

由于需要将移位之后的x前n位置0，考虑和一个前n位全部为0的数进行按位与操作
代码实现如下:
```C
int logicalShift(int x, int n) {
  int mask = ~((0x1<<31)>>n<<1);
  return (mask)&(x>>n);
}
```
性能分析:
Max ops : 20
Using ops : 6

## Problem 16 : satMul2

这道题emmmm云端能过，本地不能过
就先放上代码吧，优化了再做说明
代码实现如下:
```C
int satMul2(int x) {
  int get_sign = x >> 31; //Make all bits the same as the first sign bit;
  int xMul2 = x<<1;
  int tmin = 1<<31;
  int check_same_sign = (xMul2^x)>>31;
  int result = ((~check_same_sign)&xMul2) + ((tmin+(~get_sign))&check_same_sign);
  return result;
 
}
```
Max ops : 20
Using ops : 11

死活没有办法更进一步优化，借用了一下大佬的巧妙设计

陈大佬NB！！！
```C
int satMul2(int x) {
  int x2 = x<<1;
  int flag = (x^x2)>>31;
  return (((x2>>31)^(flag<<31))& flag) | (x2 & (~flag));
}
```
Max ops : 20
Using ops : 10

## Problem 17 : subOK 

注意到只有x,y异号的时候才会发生溢出
且溢出时:
若x < 0 , y > 0 ,则sub > 0 ;
若x > 0 , y < 0 ,则sub < 0 ;
观察发现规律:
当且仅当,sub和y都与x异号
代码实现如下:
```C
int subOK(int x, int y) {
  int sub = x + (~y) + 1;
  return !(((sub^x)&(y^x))>>31);
}
```
性能分析:
Max ops : 20
Using ops : 8

## Problem 18 : bang

注意到0x0的一个特性:
` (~0) + 1 = 0 `
而当x != 0 时
`(((~x)+1)|x)>>31 == 0xFFFFFFFF`
进而得解
代码实现如下:
```C
int bang(int x) {
  return (((~x+1)|x)>>31)+1;
}
```
性能分析:
Max ops : 12
Using ops : 5

## Problem 19 : bitParity

折半取异或,只关心最后一位最终的结果，与0x1按位取与
代码实现如下:
```C
int bitParity(int x) {
  //Every step fold the bits
  x = (x>>16)^x;
  x = (x>>8)^x;
  x = (x>>4)^x;
  x = (x>>2)^x;
  x = (x>>1)^x;
  return (x&0x1);
}
```
性能分析:
Max ops : 20
Using ops : 11

## Problem 20 : isPower2

做三个判断:
```
  1.是否为负
  2.是否为零
  3.是否只有一个1

```
其中1和2是简单的
对于3，注意到当且仅当(x & (x + ~0))==0的x满足题意
于是得解
代码实现如下:
```C
int isPower2(int x) {
    int check_if_only_1 = (x & (x + ~0));
    int check_negtive = x >> 31;
    int check_zero = !x;
    return !(check_zero | check_negtive | check_if_only_1);
}
```
性能分析:
Max ops : 20
Using ops : 8

## Problem 21 : float_i2f

很完善的算法
按照书上的算法思想完善代码并优化一下就好
代码实现如下:
```C
unsigned float_i2f(int x) {
   int e = 158;
    int mask = 1<<31;
    int sign = x&mask;
    int frac;
    if (x == mask)
        return mask | (158<<23);
    if (!x)
        return 0;
    if (sign)
        x = ~x + 1;
    while (!(x&mask)) {
        x = x<<1;
        e = e -1;
    }
    frac = (x&(~mask)) >> 8;
    if (x&0x80 && ((x&0x7F) > 0 || frac&1))
        frac = frac + 1;
    return sign + (e<<23) + frac;
}

```

Max ops : 30
Using ops : 25


## Problem 22 : leftBitCount

通过不断二分，来逼近前几位连续的1
若前16位为连续的1，右移16位之后再加1，则变零，取非后变1
若不是，右移16位加一后为非零，取非之后置0
对应结果乘16，相应得到16和0两种结果
分别对应前16位全部为1和不全为1
若前十六位全部为1，则左移16位，相当与对原数后16位的前八位进行处理
若前十六位不全为1，则左移0位，对前8位进行下一步处理
以此类推
代码实现如下:
```C
int leftBitCount(int x) {
    int check_all_1,num_of_1;
    int sum1,sum2,sum3,sum4,sum5;
    check_all_1 = !((x >> 16) + 1);
    num_of_1 = check_all_1 << 4;
    sum1=num_of_1;
    x = x << num_of_1;
    
    check_all_1 = !((x >> 24) + 1);
    num_of_1 = check_all_1 << 3;
    sum2=num_of_1;
    x = x << num_of_1;
    
    check_all_1 = !((x >> 28) + 1);
    num_of_1 = check_all_1 << 2;
    sum3=num_of_1;
    x = x << num_of_1;
    
    check_all_1 = !((x >> 30) + 1);
    num_of_1 = check_all_1 << 1;
    sum4=num_of_1;
    x = x << num_of_1;
    
    check_all_1 = !((x >> 31) + 1);
    num_of_1 = check_all_1;
    sum5=num_of_1;
    x = x << num_of_1;      
    
    return ((sum1+sum2+sum3+sum4+sum5) + (x >> 31 & 0x1)); 

}
```
Max ops : 50
Using ops : 30


经过操作符优化之后
优化了1个操作符2333
代码实现如下:
```C
int leftBitCount(int x) {
 int temp = x;
	int result;	
	int shift;
	int one = !(~x); 
	/* Check the top 16 bits and add them 
   * to our result if they exist
   */
	result = !(~(temp>>16)) << 4; 
  /*if there are no 1s in the front, we just shift 
   *temp by a huge number, so temp is zero. 
   */
	temp = temp << result;
	// check the remaining 8 bits (32-24)
	shift = !(~(temp >> 24)) << 3;
	temp = temp << shift;
	result = result | shift;
	// remaining 4 bits
	shift = !(~(temp>>28)) << 2;
	temp = temp << shift;
	result = result | shift;
	// remaining 2 bits
	shift = !(~(temp >> 30)) << 1;
	temp = temp << shift;
	result = result | shift;
	// remaining 1 bits
	result= result ^ (1&((temp>>31)));

	//rememer to add one if we have 32 on bits
	return result + one;
}
```

Max ops : 50
Using ops : 29




