#include <stdio.h>

    /* 2.27
     * Determine whether arguments can be added
     */
int uadd_ok(unsigned x,unsigned y){
    unsigned sum = x + y;
    return sum >= x;

}
    /*

     */


/*2.71*/
//int xbyte(packed_t word)

int kk(int x){
    return !((x & 0xff)^0x00);
}
int kkk(int x, int y){
    return (((y>>16)<<16)|0xffff)&(((~0)<<16) | x);
}
int overflowCheck(int a,int b){
    return a + b;
}
int main(){
printf("%x\n",kkk(0xffffaaaa,0xccccbbbb));
printf("%d\n",overflowCheck(0x7fffffff,0x7fffffff));
}