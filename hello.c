#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 5
#define MAX_WORDS 500

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// 미러링 함수 구현
void mirror(const char *word, char *mirrored) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        mirrored[i] = word[len - 1 - i];
    }
    mirrored[len] = '\0';
}

// 한 글자 차이나는지 확인하는 함수
bool isOneLetterDiff(const char *a, const char *b) {
    int diffCount = 0, len = strlen(a);
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) diffCount++;
        if (diffCount > 1) return false;
    }
    return diffCount == 1;
}

// 주어진 문제를 해결하는 함수
int findYulMyungPaths(const char *yul, const char *myung, char **wordList, int wordListSize) {
    // 방문 배열, 경로 수 초기화
    bool visited[MAX_WORDS] = {0};
    int pathCount = 0;

    // 단어 큐와 현재 단계에서의 단어 큐 크기
    int queueIndex[MAX_WORDS], queueSize = 0;
    int nextQueue[MAX_WORDS], nextSize = 0;

    // yul을 큐에 추가
    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(yul, wordList[i]) == 0 || isOneLetterDiff(yul, wordList[i])) {
            queueIndex[queueSize++] = i;
            visited[i] = true;
        }
    }

    // BFS 실행
    while (queueSize > 0) {
        nextSize = 0;

        for (int i = 0; i < queueSize; i++) {
            if (strcmp(wordList[queueIndex[i]], myung) == 0) {
                pathCount++;
                continue;
            }

            char mirroredWord[MAX_WORD_LENGTH + 1];
            mirror(wordList[queueIndex[i]], mirroredWord);

            if (strcmp(mirroredWord, myung) == 0) {
                pathCount++;
                continue;
            }

            for (int j = 0; j < wordListSize; j++) {
                if (!visited[j] && (isOneLetterDiff(wordList[queueIndex[i]], wordList[j]) || strcmp(mirroredWord, wordList[j]) == 0)) {
                    nextQueue[nextSize++] = j;
                    visited[j] = true;
                }
            }
        }

        // 다음 단계의 큐로 업데이트
        memcpy(queueIndex, nextQueue, nextSize * sizeof(int));
        queueSize = nextSize;
    }

    return pathCount;
}

int main() {
    char yul[MAX_WORD_LENGTH + 1], myung[MAX_WORD_LENGTH + 1];
    char line[(MAX_WORDS + 1) * (MAX_WORD_LENGTH + 1) + 1];
    char *wordList[MAX_WORDS];
    int wordListSize = 0;

    printf("Enter yul: ");
    scanf("%s", yul);
    clear_input_buffer();

    printf("Enter myung: ");
    scanf("%s", myung);
    clear_input_buffer();

    printf("Enter words separated by spaces: ");
    if (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, " ");
        while (token != NULL && wordListSize < MAX_WORDS) {
            wordList[wordListSize] = (char *)malloc(strlen(token) + 1);
            if (wordList[wordListSize] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            strcpy(wordList[wordListSize], token);
            wordListSize++;
            token = strtok(NULL, " ");
        }
    }

    int result = findYulMyungPaths(yul, myung, wordList, wordListSize);
    printf("Total paths with minimum word transformation: %d\n", result);

    for (int i = 0; i < wordListSize; i++) {
        free(wordList[i]);
    }

    return 0;
}








