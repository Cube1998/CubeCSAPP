/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//Rating:1
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x)|(~y));
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  int a = 0x55;
  a = (a<<8)+a;
  a = (a<<16)+a;
  return a;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  
  return !((x<<16>>16)^x);    //Only have to check if first 16 bits are the same.
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  
  //return !(((x+1)^x)+1)&(!!(~x));
  //Take '|' to replace  '&', two '+' combine to one '+' 
  return !(((x+x)+2)|(!(~x)));
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return ~0;  //Take opposite of 0;
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
   int k = 33+(~n);
  return ((~0)<<k)&(~((~(!n))+1));
}
//Rating:2
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int m= 0x55;
	m = (m<<8)|m;
  m = (m<<16)|m;
	return !((x&m)^m);
  
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
      //注意到异或可以储存和复原信息
      int m_8 = m<<3;
      int n_8 = n<<3;
      int mask = ((x>>m_8)^(x>>n_8))&0xff;
      return x^((mask<<m_8)|(mask<<n_8));
      return 2;
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  return x<<31>>31;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    
    int sign_mark = (x>>31);
    int k = (0x1<<n)+(~0);//优先考虑如何做出一个右(n)位为1的数
    int right_n_1 = sign_mark & k;
    return (x+right_n_1)>>n;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  return (~x +1)& x;
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  int t = 0xaa;
  t = (t<<8)|t;
  t = (t<<16)|t;
  return t;
}
//Rating:3
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  //Make right are 1s
  int ffffffff = ~0;
  int high_one = (ffffffff<<(highbit)<<1);
  int low_one = (ffffffff<<lowbit);
  return (high_one^low_one)&low_one; //防止错位
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  //Using  x<y :  (x-y)^((x^y)&((x-y)^y))
  //And x-y = x + ~y +1
  //int x_minus_y = x + ~y +1;

  //return !(x_minus_y^((x^y)&(x_minus_y^y)));
  //  int x_sign = (x >> 31) & 0x1;
  //  int y_sign = (y >> 31) & 0x1;
  //  int sign_sub = ((x + (~y))+1)>>31;
    int x_sign = (x >> 31) ;
    int y_sign = (y >> 31) ;
    int sign_sub = ((x + (~y))+1)>>31;
    int result_if_sign_same = (sign_sub)&(!(x_sign^y_sign));
    int result_if_sign_diff = x_sign&(!y_sign);
    return result_if_sign_same|result_if_sign_diff;

    /*
      3 conditions:
      1. x<0 , y>0;
      2. x>0,y>0,x-y<0;
      3.x>0,y<0;
      1 or 2 fits while 3 doesn't  fit
      */
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  //Make a int that first n bits are "0", others are "1".
  int mask = ~((0x1<<31)>>n<<1);
  return (mask)&(x>>n);
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x7FFFFFFF (saturate to TMax)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  /*
  int get_sign = x >> 31; //Make all bits the same as the first sign bit;
  int xMul2 = x<<1;
  int tmin = 1<<31;
  int check_same_sign = (xMul2^x)>>31;
  int result = ((~check_same_sign)&xMul2) | ((tmin+(~get_sign))&check_same_sign);
  return result;
  */
  int x2 = x<<1;
  int flag = (x^x2)>>31;
  return (((x2>>31)^(flag<<31))& flag) | (x2 & (~flag));
  
 
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  // x<0,y>0 but sub>0  or x>0,y<0 ,sub<0;
  int sub = x + (~y) + 1;
  return !(((sub^x)&(y^x))>>31);
}
//Rating:4
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return (((~x+1)|x)>>31)+1;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  //Every step fold the bits
  x = (x>>16)^x;
  x = (x>>8)^x;
  x = (x>>4)^x;
  x = (x>>2)^x;
  x = (x>>1)^x;
  
  return (x&0x1);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
    int check_if_only_1 = (x & (x + ~0));
    int check_negtive = x >> 31;
    int check_zero = !x;
    return !(check_zero | check_negtive | check_if_only_1);
}
//Extra
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  
   
    /*
    int sign=x>>31&1;
    int i;
    int exponent; 
    int fraction; 
    int delta;
    int fraction_mask;
    if(x==0)//||x==0x8000000)
        return x;
    else if(x==0x80000000)
        exponent=158;
    else{
        if (sign)//turn negtive to positive
            x = -x;
        i = 30;
        while ( !(x >> i) )//see how many bits do x have(rightshift until 0) 
            i--;
        //printf("%x %d\n",x,i);
        exponent = i + 127;
        x = x << (31 - i);//clean all those zeroes of high bits
        fraction_mask = 0x7fffff;//(1 << 23) - 1;
        fraction = fraction_mask & (x >> 8);//right shift 8 bits to become the fraction,sign and exp have 8 bits total
        x = x & 0xff;
        delta = x > 128 || ((x == 128) && (fraction & 1));//if lowest 8 bits of x is larger than a half,or is 1.5,round up 1
        fraction += delta;
        if(fraction >> 23) {//if after rounding fraction is larger than 23bits
            fraction &= fraction_mask;
            exponent += 1;
        }
    }
    return (sign<<31)|(exponent<<23)|fraction;
    */
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
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
  /*
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
    */
     //make count dependent on position. 
    int temp = x;
	int result;	
	int shift;
	int one = !(~x); 
	// Check the top 16 bits and add them to our result if they exist
	result = !(~(temp>>16)) << 4; //if there are no ones in the front, we just shift temp by a huge number, so temp is zero. 
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
