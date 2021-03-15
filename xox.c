// PID: 123456789
// I pledge the COMP211 honor code.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

//here are my generic constants to be used throughout
#define binbase 2
#define bias 7
#define negbit 256

//here are my latitude constants, in descending order
#define startpoint 63
#define latsign 62
#define beginlatdeg 61
#define endlatdeg 54
#define beginlatmin 53
#define endlatmin 48
#define latsecsign 47
#define beginlatsecexpo 46
#define endlatsecexpo 43
#define beginlatsecsigni 42
#define endlatsecsigni 32

//here are my longitude constants, in descending order
#define longsign 30
#define beginlongdeg 29
#define endlongdeg 22
#define beginlongmin 21
#define endlongmin 16
#define longsecsign 15
#define beginlongsecexpo 14
#define endlongsecexpo 11
#define beginlongsecsigni 10

//general variables
int c;
long dectotal(char[]);
int count = startpoint;
char arr[64];
int sign = 1;

//latitude functions
int latdegrees(char[]);
int latminutes(char[]);
float latseconds(char[]);
int latexpo = 0;

//longitude functions
int longdegrees(char[]);
int longminutes(char[]);
float longseconds(char[]);
int longexpo = 0;

//main function takes in the data and stores it in an array, then has 
//print statements for each task that will call the necessary function on the data
int main(){
    while((c = getchar()) != EOF){
        if (c != 'x' && c != 'o' && c != '\n'){
            return EXIT_FAILURE;
        }
        if (count < -1){
            return EXIT_FAILURE;
        }
        if (c != '\n'){
            arr[count] = c;
            count--;
        }
    }        
    
    printf("=== 64-bit COORDINATE FOUND ===\n");
    printf("Unsigned: %lu\n", dectotal(arr));
    printf("Latitude: %dd %dm %fs\n", latdegrees(arr), latminutes(arr), latseconds(arr));
    printf("Longitude: %dd %dm %fs\n", longdegrees(arr), longminutes(arr), longseconds(arr));

                
}
    
//finds the unsigned binary int for the data
long dectotal(char array[]){
    long unsigned total = 0;
    for (int i = startpoint; i >= 0; i--){
        if(array[i] == 'x'){
            total += pow(binbase, i);
        }
    }
    return total;
}

//finds the latitude degrees for the data
int latdegrees(char array[]){
    int total = 0;
    if (array[latsign] == 'x'){
        total -= negbit;
    } 
    for (int i = beginlatdeg; i >= endlatdeg; i--){
        if (array[i] == 'x'){
            total += pow(binbase, i -endlatdeg);
        }
    }
   return total;
}

//finds the latitude minutes for the data
int latminutes(char array[]){
    int total = 0;
    for (int i = beginlatmin; i >= endlatmin; i--){
        if (array[i] == 'x'){
            total += pow(binbase, i - endlatmin);
        }
    }
    return total;
}

//finds the latitude seconds for the data
float latseconds(char array[]){
    int sign = 1;
    int expo = 0;
    float signi = 0;
    if (array[latsecsign] == 'x'){
       sign = -1; 
    }
    for (int i = beginlatsecexpo; i >= endlatsecexpo; i --){
        if (array[i] == 'x'){
            expo += pow(binbase, i - endlatsecexpo);
        }
    }
    for (int i = beginlatsecsigni; i >= endlatsecsigni; i--){
        if (array[i] == 'x'){
            signi += (float) pow(binbase, (i - endlatsecexpo));
        }
    } 
    return ((float)(signi + sign) * (pow(binbase, expo - bias)));
} 

//finds the longitude degrees for the data
int longdegrees(char array[]){
    int total = 0;
    if (array[longsign] == 'x'){
        total -= negbit;
    } 
    for (int i = beginlongdeg; i >= endlongdeg; i--){
        if (array[i] == 'x'){
            total += pow(binbase, i - endlongdeg
                    );
        }
    }
   return total;
}

//finds the longitude minutes for the data
int longminutes(char array[]){
    int total = 0;
    for (int i = beginlongmin; i >= endlongmin; i--){
        if (array[i] == 'x'){
            total += pow(binbase, i - endlongmin);
        }
    }
    return total;
}

//finds the longitude seconds for the data
float longseconds(char array[]){
    int sign = 1;
    int expo = 0;
    float signi = 0;
    if (array[longsecsign] == 'x'){
       sign = -1; 
    }
    for (int i = beginlongsecexpo; i >= endlongsecexpo; i--){
        if (array[i] == 'x'){
            expo += pow(binbase, i - endlongsecexpo);
        }
    }
    for (int i = beginlongsecsigni; i >= 0; i--){
        if (array[i] == 'x'){
            signi += (float) pow(binbase, (i - endlongsecexpo));
        }
    } 
    return ((float)(signi + sign) * (pow(binbase, expo - bias)));
} 





