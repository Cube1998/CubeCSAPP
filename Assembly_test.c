#include <stdio.h>


int swap(int *a,int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
    return 1;
}

int main(){
    printf("mamamiya");
    return 0;
}