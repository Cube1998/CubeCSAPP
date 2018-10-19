#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <time.h>
#define random(x) (rand()%x)
using namespace std;
void print(int x){printf("%x\n",x);}
int strlonger(char* s,char* t){
	return strlen(s)-strlen(t)>0;
}
int satMul2(int x) {
  ///*
  int get_sign = x >> 31; //Make all bits the same as the first bit;
  print(get_sign);
  int xMul2 = x<<1;
  print(xMul2);
  int tmin = 1<<31;
  int check_same_sign = (xMul2^x)>>31;
  print(check_same_sign);
  int result = ((~check_same_sign)&xMul2) + ((tmin+(~get_sign))&check_same_sign);
  return result;
  //*/
  /*
 int a=x<<1;
    int b=x>>31;
    int c=(x^a)>>31;
    int tmin=1<<31;
    return ((~c)&a)+(c&(~b+tmin));
*/
}
int test(int x){
	
	return !((x<<16>>16)^x);;
}
int isTmax(int x) {
  return ((!((~x)<<1))&&(!!x));
  
}
int upperBits(int n) {
   int k = 33+(~n);
  return ((~0)<<k)&(~((~(!n))+1));
}
int divpwr2(int x, int n) {
    //int sign_mark = (x>>31);

    return (((x>>n))+~(x>>31)+1);
}
int leastBitPos(int x) {
  return (~x +1)& x;
}
int main(){
	/*
	int a = 24;
	
	//even_ones(a);
	printkk(a,1);
	*/

   	//printf("%x\n",test(330000));
	   //printf("%x\n",isTmax(0x7fffffff));
	// for(int i = 0;i<=32;i++)
 //printf("%x\n",i+(~0));
 //printf("%x\n",leastBitPos(0x50000000));
 //int a = 0x7f,b = 0xba;
 //printf("%x\n",satMul2(0x80000000));
 //cout<<(0x80000000<<1);
 //printf("%x\n",upperBits(i));

    //palindromeCheckQueue();



	int x = 1<<31, y = 1<<31;
	for(;y<(~x);y+=0x1)
	if(!(((x+y)<<4)+y-x == 17*y+15*x)) printf("OK\n");
}
