#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LENGTH 100000

// 비트 마스킹을 활용해 대칭 부분 문자열의 최대 길이를 찾는 함수
int findMaxlength(char*food);
int findSavedStrength(char*food);

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

int findMaxLength(char *food) {
    int maxLength = 0, n = strlen(food);

    for (int i = 0; i < n; i++) {
        if(maxLength>=n-i)break;
        int changebit = 0; // 비트 마스크 초기화
        for (int j = i; j < n; j++) {
            changebit ^= (1 << (food[j] - 'A')); // 해당 알파벳의 비트를 토글

            int length = j - i + 1;
            if(length <= maxLength) {
                continue;
            }

            // countSetBits 로직을 여기에 직접 구현
            int oddcnt = 0;

            for(int k=changebit;k;k>>=1){
                oddcnt+=k&1;
                if(oddcnt>1)break;
            }
            // 홀수 개수 알파벳이 1개 이하이면 대칭 가능
            if (oddcnt <= 1) {
                maxLength = length;
            }
        }
    }

    return maxLength;
}

// 주어진 문자열에 대해 먹보당 저장된 힘을 계산하는 함수
int findSavedStrength(char *food) {
    int eatlength = findMaxLength(food);
    int savedStrength = (eatlength * 100)/2; // 저장된 힘 계산
    return savedStrength;
}

