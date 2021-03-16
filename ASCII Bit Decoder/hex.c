// PID: 730331666
// I pledge the COMP211 honor code.

#include <stdlib.h>
#include <stdio.h>

int main(){
    int linecounter = 0;
    int alpha;
    int c;
    void printer(int alpha);
    while ((c = getchar()) != EOF){
       if (linecounter == 40){
                printf("\n");
                linecounter = 0;
            }
            alpha = c >> 4;
            printer(alpha);
            alpha = c & 15;
            printer(alpha);
            linecounter++;
    }     
    printf("\n");
    return EXIT_SUCCESS;
}
void printer(int alpha){
    char holder;
    if (alpha > 9) {
        holder = alpha + 55;
        putchar(holder);
    } else {  
        printf("%d", alpha);
    }
}
