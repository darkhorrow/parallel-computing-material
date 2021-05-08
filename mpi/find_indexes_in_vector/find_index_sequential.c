#include <stdio.h>
#include <stdlib.h>  

#define MESSAGE_SIZE 10000
#define k 6

int main(int argc, char **argv ) {
    int vector [MESSAGE_SIZE];
    int positions[MESSAGE_SIZE];
    srand (50);

    for(int i = 0; i < MESSAGE_SIZE; i++) {
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



