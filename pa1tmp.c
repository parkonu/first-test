#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LENGTH 100000


int findMaxLength(char *food) {
    int maxLength = 0, n = strlen(food);

    for (int i = 0; i < n; i++) {
        if(maxLength>=n-i)break;
        int changebit = 0;
        for (int j = i; j < n; j++) {
            changebit ^= (1 << (food[j] - 'A')); 

            int length = j - i + 1;
            if(length <= maxLength) {
                continue;
            }

            
            int oddcnt = 0;
            int k = changebit;
            while (k) {
                oddcnt += k & 1;
                k >>= 1;
            }

           
            if (oddcnt <= 1) {
                maxLength = length;
            }
        }
    }

    return maxLength;
}


int findSavedStrength(char *food) {
    int eatlength = findMaxLength(food);
    int savedStrength = 0;
    savedStrength=(eatlength * 100) / 2; 
    return savedStrength;
}

int main() {
    char *food = (char*)malloc(MAX_LENGTH * sizeof(char));
    if(food == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    printf("Enter Food: ");
    scanf("%s", food);

    printf("Saved Strength is: %d\n", findSavedStrength(food));
    free(food);
    
    return 0;
}