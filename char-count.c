// PID: 730331666
// I pledge the COMP211 honor code.
#include <stdlib.h>
#include <stdio.h>

void printCounts(int countArr[], char alphabet[]);
void percents(int countArr[], char alphabet[], int totChars);
void graph();

int main(){
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                         'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char upperAlphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                         'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int countArr[26] = {0};
    int c;
    int totChars = 0;
    int largest = 0;

    while ((c = getchar()) != EOF){
        for (int i = 0; i < 26; ++i){
            if ((c == alphabet[i]) || (c == upperAlphabet[i])){
               countArr[i] = countArr[i] + 1;
               totChars = totChars + 1;
               if (countArr[i] > largest){
                   largest = countArr[i];
               }
            }

        }
    }

   //counts
   printCounts(countArr, alphabet);

   //percents
   percents(countArr, alphabet, totChars);

   //graph
   graph(countArr, alphabet, largest);


   return EXIT_SUCCESS;
}
void printCounts(int countArr[], char alphabet[]){
    printf("Counts:\n");
    for (int i = 0; i < 26; ++i){
        if (countArr[i] > 0){
              printf("%c", alphabet[i]);
              printf(": ");
              printf("%d", countArr[i]);
              printf("\n\n");
       }
    }
}

void percents(int countArr[], char alphabet[], int totChars){
    printf("Percents:\n");
    for (int i = 0; i < 26; i++){
        if (countArr[i] > 0){
            float perc = ((float) countArr[i])/((float)totChars)*100;
            printf("%c", alphabet[i]);
            printf(": ");
            printf("%.1f", perc);
            printf("%%");
            printf("\n\n");

            }
     }
}

void graph(int countArr[], char alphabet[], int largest){
    printf("Chart:");
    printf("\n");
    for (int i = 10; i > 0; --i){
        for (int j = 0; j < 26; ++j){
            float scaler = (((float) countArr[j]) / ((float) largest) * 10 );
            if (scaler >= i){
               printf("|");
            } else {
               printf(" ");
            }

        }
        printf("\n");
    }

    for (int i = 0; i < 26; ++i){
        printf("%c", alphabet[i]);
        }
}
