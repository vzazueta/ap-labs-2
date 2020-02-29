#include <stdio.h>

void reverse(void){
    char c;
    if((c = getchar()) != EOF) reverse();
    putchar(c);
}

int main(){
    printf("Escribir palabra a reversear: ");
    reverse();
    putchar('\n');

    return 0;
}
