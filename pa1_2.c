#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 500
#define MAX_LEN 5
#define INT_MAX 2147483647 // INT_MAX 직접 정의

typedef struct {
    char word[MAX_LEN];
    int step;
} Node;

char wordList[MAX_WORDS][MAX_LEN];
int wordListSize;
char yul[MAX_LEN], myung[MAX_LEN];

bool canTransform(const char* src, const char* dest) {
    int diff = 0;
    for (int i = 0; src[i]; ++i) {
        if (src[i] != dest[i]) diff++;
    }
    return diff == 1;
}

void mirror(const char* src, char* dest) {
    int len = strlen(src);
    for (int i = 0; i < len; ++i) {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = '\0';
}

bool isInWordList(const char* word) {
    for (int i = 0; i < wordListSize; ++i) {
        if (strcmp(word, wordList[i]) == 0) return true;
    }
    return false;
}

int bfs() {
    if (!isInWordList(myung)) return 0;

    Node queue[MAX_WORDS * MAX_LEN];
    int front = 0, rear = 0;
    bool visited[MAX_WORDS] = {false};
    int paths = 0, minSteps = INT_MAX;

    queue[rear++] = (Node){ .word = "", .step = 0 };
    strcpy(queue[0].word, yul);

    while (front < rear) {
        Node current = queue[front++];
        
        if (current.step > minSteps) break;

        if (strcmp(current.word, myung) == 0) {
            minSteps = current.step;
            paths++;
            continue;
        }

        for (int i = 0; i < wordListSize; ++i) {
            if (!visited[i] && canTransform(current.word, wordList[i])) {
                visited[i] = true;
                queue[rear++] = (Node){ .word = "", .step = current.step + 1 };
                strcpy(queue[rear - 1].word, wordList[i]);
            }
        }
    }

    return paths;
}

int main() {
    scanf("%s %s %d", yul, myung, &wordListSize);
    for (int i = 0; i < wordListSize; ++i) {
        scanf("%s", wordList[i]);
    }

    int result = bfs();
    printf("%d\n", result);

    return 0;
}



