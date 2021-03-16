// PID: 730331666
// I pledge the COMP211 honor code.

#include <stdlib.h>
#include <stdio.h>
int bitcount(unsigned char x);
int storage;
int main(){
    int c;
    while ((c = getchar()) != EOF){
      int bits = bitcount(c);
      c = c << 1;
      if (bits & 1){
         c = c | 1;
      }
      printf("%c", c);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
          

int bitcount(unsigned char x){
      int b;
      for (b = 0; x != 0; x >>= 1){
          if (x & 0x01)
              b++;
      }
        return b;
}
