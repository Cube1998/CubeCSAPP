#include <stdio.h>

int edi = 1;
int esi = 0;
int edx = 14;

int eax;
int ebx;
/*
void fun_4(){
    eax = edx;
    eax = eax - esi;
    ebx = eax;
    ebx = ebx>>31;
    eax = eax + ebx;
    eax = eax>>1;
    ebx = eax - esi;
    if(ebx<=edi){
        eax = ebx;
        if(ebx>=edi){
            return;
        }
        else {
            esi = ebx -1;
            fun_4();
            eax = eax + ebx;
            return;
        }

    }
    else{
        edx = ebx -1;
        fun_4();
        eax = eax + ebx;
        return;
    } 
}*/

int fun(int x,int y ,int z){
    int a = x- y;
    int t = a>>31;
    t = ((a+t)>>1)+y;
    if(x == t)return t;
    if(t<x)return t+fun(x,t+1,z);
    else return t+fun(x,y,t-1);

}


int main(){
    for(int i = 1;i<=14;i++)
    {
       
      // fun_4();
       printf("%d eax :%d\n",i,fun(i,0,14));
    }
}