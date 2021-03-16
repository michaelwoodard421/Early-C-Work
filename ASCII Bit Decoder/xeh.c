// PID: 730331666
// I pledge the COMP211 honor code.

#include <stdlib.h>
#include <stdio.h>

int main(){
    int count = 1;
    int alpha;
    int beta;
    int c;
    int storage;
    while ((c = getchar()) != EOF){
        if (count % 2 == 1 && c != '\n'){
            alpha = c - '0';
            count ++;        
        } else if (c != 0 && c != '\n'){
            beta = c; if (beta < 58){
                beta = c - '0';
            } else if (beta < 91) {
                beta = c - 'A' + 10;
            } else {
                beta = c - 'a' + 10;
            }
            count ++;
            storage = alpha * 16 + beta;
            char temp = storage;
            putchar(temp); 
        }
    }
   return EXIT_SUCCESS;

}
