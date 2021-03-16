// PID: 123456789
// I pledge the COMP211 honor code.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 900000

int read(char **lineptr, size_t maxlinelength);
void write(char **lineptr, int nlines);
void sort(char **lineptr, int left, int right);
void swap(char **lineptr, int first, int second);


int main(){
    char **lineptr = malloc((MAXLINES + 1) * sizeof(char*));
   
    if (lineptr == NULL) {
        fprintf(stderr, "Out of space");
        exit(EXIT_FAILURE);
    }

    int numlines = read(lineptr, MAXLINES);
    sort(lineptr, 0, numlines - 1);
    write(lineptr, numlines);
    free(lineptr);
    return EXIT_SUCCESS;
}

int read(char **lineptr, size_t maxlinelength){ // receives and input and fills it into the array
    int count = 0;
    char *line = malloc(maxlinelength + 1);
    while(fgets(line, maxlinelength + 1, stdin) != NULL){
        lineptr[count] = line;
        line = malloc(maxlinelength + 1);
        count++;
    }
    free(line);
    return count;
}

void write(char **lineptr, int numlines){ // prints input back 
    int count = 0;
    while(count < numlines){
       printf("%s", lineptr[count]);
       free(lineptr[count]);
       count++; 
    }
}

void sort(char **lineptr, int left, int right) { //sorts input using binary tree 
    int i, last;
    if (left >= right)
        return;
    swap(lineptr, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    sort(lineptr, left, last - 1);
    sort(lineptr, last + 1, right);
}

void swap(char **lineptr, int first, int second) { //swaps two elements
    char *temp;
    temp = lineptr[first];
    lineptr[first] = lineptr[second];
    lineptr[second] = temp;
}
