#include <stdio.h>
#include <stdlib.h>  

#define size 10000

int main(int argc, char **argv ) {

    int vector [size];
    int positions[size];
    int k = 6;
    srand (50);

    for(int i = 0; i < size; i++) {
        vector[i] = rand()%100;
    }


    int pos = 0;

    for(int i = 0; i < sizeof(vector)/sizeof(int); i++) {
        if (vector[i] == k) {
            positions[pos] = i;
            pos++;
        }

    }

    for(int i = 0; i < pos; i++) {
        printf("%d ", positions[i]);
    }

return 0;

}



