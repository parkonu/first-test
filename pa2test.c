#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 5
#define MAX_WORDS 500

typedef struct {
    char word[MAX_WORD_LENGTH + 1];
    int length;
} Path;

typedef struct {
    Path *paths; // 동적 할당을 위해 포인터로 변경
    int front, rear, capacity;
} Queue;

void initQueue(Queue *q) {
    q->capacity = MAX_WORDS * MAX_WORD_LENGTH; // 초기 크기 설정
    q->paths = malloc(q->capacity * sizeof(Path)); // 초기 메모리 할당
    q->front = 0;
    q->rear = 0;
    if (!q->paths) {
        
        exit(EXIT_FAILURE);
    }
}

bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, Path path) {
    if (q->rear == q->capacity) {
        // 큐의 용량이 가득 찼다면 크기를 늘림
        q->capacity *= 2; // 용량을 2배로 증가
        Path *newPaths = realloc(q->paths, q->capacity * sizeof(Path));
        if (!newPaths) {
            
            free(q->paths);
            exit(EXIT_FAILURE);
        }
        q->paths = newPaths;
    }
    q->paths[q->rear++] = path;
}

Path dequeue(Queue *q) {
    return q->paths[q->front++];
}

bool isOneLetterDiffOrMirrored(const char *a, const char *b) {
    int diffCount = 0, len = strlen(a);
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) diffCount++;
    }
    if (diffCount == 1) return true; // 한 글자만 다른 경우

    bool isMirrored = true;
    for (int i = 0; i < len; i++) {
        if (a[i] != b[len-i-1]) {
            isMirrored = false;
            break;
        }
    }
    return isMirrored;
}

bool isInWordList(const char *word, char **wordList, int wordListSize) {
    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(word, wordList[i]) == 0) return true;
    }
    return false;
}

int findYulMyungPaths(const char *yul, const char *myung, char **wordList, int wordListSize) {
    if (!isInWordList(myung, wordList, wordListSize)) return 0; // `myung`이 wordList에 없으면 0 반환

    Queue q;
    initQueue(&q);
    Path startPath = {.length = 1};
    strcpy(startPath.word, yul);
    enqueue(&q, startPath);

    int minPathLength = MAX_WORDS + 1; // 최소 경로 길이를 매우 큰 값으로 초기화
    int pathCounts = 0; // 최소 경로의 수

    while (!isEmpty(&q)) {
        Path currentPath = dequeue(&q);

        if (currentPath.length > minPathLength) continue;

        if (isOneLetterDiffOrMirrored(currentPath.word, myung)) {
            if (currentPath.length < minPathLength) {
                minPathLength = currentPath.length;
                pathCounts = 1;
            } else if (currentPath.length == minPathLength) {
                pathCounts++;
            }
            continue;
        }

        for (int i = 0; i < wordListSize; i++) {
            if (isOneLetterDiffOrMirrored(currentPath.word, wordList[i])) {
                Path newPath = {.length = currentPath.length + 1};
                strcpy(newPath.word, wordList[i]);
                enqueue(&q, newPath);
            }
        }
    }
    
    free(q.paths); // 큐 사용 후 메모리 해제
    return pathCounts;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}



int main() {
    char yul[MAX_WORD_LENGTH+1], myung[MAX_WORD_LENGTH+1];
	char line[(MAX_WORDS+1)*(MAX_WORD_LENGTH + 1)+1];
    char *wordList[MAX_WORDS];
    int wordListSize = 0;

    printf("Enter yul: ");
    scanf("%s", yul);
    clear_input_buffer();  // Clear the newline left by scanf

    printf("Enter myung: ");
    scanf("%s", myung);
    clear_input_buffer();  // Clear the newline left by scanf


    printf("Enter words separated by spaces: ");
    if (fgets(line, sizeof(line), stdin)) {
        // Remove trailing newline, if any
        line[strcspn(line, "\n")] = 0;

        // Tokenize the input string
        char *token = strtok(line, " ");
        while (token != NULL && wordListSize < MAX_WORDS) {
            wordList[wordListSize] = malloc(strlen(token) + 1);
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





