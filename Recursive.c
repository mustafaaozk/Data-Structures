#include <stdio.h>

int find(int x){
    if (x == 10)
    {
        return 3;
    }else if (x<10){
        return 5;
    } else {
        return 3 * find(x-3) + 5;
    }
}

int fact(int x){
    if(x == 0){
        return 1;
    } else
    {
        return x * fact(x-1);
    }
    
}

int fib(int n){
    if( n == 0 || n == 1){
        return n;
    } else{
        return fib(n-2) + fib(n-1);
    }
}


int main(void){

    printf("%d \n",find(15));

    printf("Factorial: %d",fact(5));
    printf("\n");
    printf("Fibonacci: %d",fib(3));
}