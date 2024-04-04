#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 5
#define MAX_WORDS 500

typedef struct
{
    char word[MAX_WORD_LENGTH];
    int cnt;
} Path;

typedef struct
{
    Path paths[MAX_WORDS * MAX_WORD_LENGTH]; // 큐에 저장될 경로들
    int front, rear;                         // 큐의 앞과 뒤 인덱스
} Queue;

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(Queue *q)
{
    return q->front == q->rear;
}

void enqueue(Queue *q, Path path) {
    // 큐가 가득 찼는지 확인
    if (q->rear >= MAX_WORDS * MAX_WORD_LENGTH) {
        
        return; // 더 이상 큐에 항목을 추가하지 않음
    }
    q->paths[q->rear++] = path;
}


Path dequeue(Queue *q)
{
    return q->paths[q->front++];
}

bool DifforMirror(const char *a, const char *b)
{
    int diffcnt = 0, len = strlen(a);
    bool Mirror = true;
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[i])
            diffcnt++;
        if (a[i] != b[len - i - 1])
            Mirror = false;
        if (diffcnt > 1 && !Mirror)
            return false; // 최적화: 조건을 더 이상 만족하지 않으면 바로 종료
    }
    return diffcnt == 1 || Mirror; // 한 글자만 다르거나 미러링되면 true 반환
}

bool YesorNoMyung(const char *word, char **wordList, int wordListSize)
{
    for (int i = 0; i < wordListSize; i++)
    {
        if (strcmp(word, wordList[i]) == 0)
            return true;
    }
    return false;
}



int findYulMyungPaths(const char *yul, const char *myung, char **wordList, int wordListSize)
{

    if (!YesorNoMyung(myung, wordList, wordListSize))
        return 0; // `myung`이 wordList에 없으면 0 반환
    

    Queue q;
    initQueue(&q);
    Path start = {"",1};
    strcpy(start.word, yul);
    enqueue(&q, start);

    int min = MAX_WORDS*MAX_WORD_LENGTH; // 최소 경로 길이를 매우 큰 값으로 초기화
    int YulMyungPaths = 0;                // 최소 경로의 수

    while (!isEmpty(&q))
    {
        Path current = dequeue(&q);

        // 현재 경로가 이미 최소 경로보다 길면 더 이상 탐색하지 않음
        if (current.cnt > min)
            continue;

        if (DifforMirror(current.word, myung))
        {
            // `myung`에 도달한 경우, 최소 경로 갱신
            if (current.cnt < min)
            {
                min = current.cnt;
                YulMyungPaths = 1;
            }
            else if (current.cnt == min)
            {
                YulMyungPaths++;
            }
            continue;
        }

        // 다음 단계 탐색
        for (int i = 0; i < wordListSize; i++)
        {
            if (DifforMirror(current.word, wordList[i]))
            {
                Path new = {"",current.cnt + 1};
                strcpy(new.word, wordList[i]);
                if(new.cnt<min){
                    enqueue(&q,new);
                }
            }
        }
    }

    return YulMyungPaths;
}

void clear_input_buffer();

int main()
{
    char yul[MAX_WORD_LENGTH + 1], myung[MAX_WORD_LENGTH + 1];
    char line[(MAX_WORDS + 1) * (MAX_WORD_LENGTH + 1) + 1];
    char *wordList[MAX_WORDS];
    int wordListSize = 0;

    printf("Enter yul: ");
    scanf("%s", yul);
    clear_input_buffer(); // Clear the newline left by scanf

    printf("Enter myung: ");
    scanf("%s", myung);
    clear_input_buffer(); // Clear the newline left by scanf

    printf("Enter words separated by spaces: ");
    if (fgets(line, sizeof(line), stdin))
    {
        // Remove trailing newline, if any
        line[strcspn(line, "\n")] = 0;

        // Tokenize the input string
        char *token = strtok(line, " ");
        while (token != NULL && wordListSize < MAX_WORDS)
        {
            wordList[wordListSize] = malloc(strlen(token) + 1);
            if (wordList[wordListSize] == NULL)
            {
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

    for (int i = 0; i < wordListSize; i++)
    {
        free(wordList[i]);
    }

    return 0;
}
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}