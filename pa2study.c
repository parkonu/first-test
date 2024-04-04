#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 5
#define MAX_WORDS 500

typedef struct
{
    char word[MAX_WORD_LENGTH];
    int length;
} Path;
/*path구조체는 변환 경로의 한 단계를 나타냅니다. word는 해당 단계의 단어를 의미하고
length는 시작 단어에서 해당 단어에 이르기까지의 변환 횟수를 저장합니다*/

typedef struct
{
    Path paths[MAX_WORD_LENGTH * MAX_WORDS]; // 큐에 저장될 경로들
    int front, rear;                         // 큐의 앞과 뒤 인덱스
} Queue;
/*Queue구조체는 BFS 탐색에 사용될 큐를 정의합니다. paths는 큐에 저장된
경로들을, front와 rear는 큐의 앞과 뒤 인덱스를 나타냅니다*/

void iniitQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}
// 큐를 초기화합니다. 큐의 앞과 뒤 인덱스를 0으로 설정합니다

bool isEmpty(Queue *q)
{
    return q->front == q->rear;
}
// 큐가 비어 있는지 확인합니다. front와 rear가 같으면 큐가 비어 있다는 것을 의미하고 true를 반환

void enqueue(Queue *q, Path path)
{
    q->paths[q->rear++] = path;
}
// 큐에 새로운 경로를 추가합니다.큐의 끝(rear)에 경로를 추가하고 rear 인덱스를 1증가시킵니다

Path dequeue(Queue *q)
{
    return q->paths[q->front++];
}
/*큐의 앞에서 경로를 하나 꺼냅니다. 큐의 앞(front)에 있는 경로를 반환하고
front인덱스를 1증가시킵니다.*/

bool isoneletterDifforMirror(const char *a, const char *b)
{
    int diffCount = 0, len = strlen(a);
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[i])
            diffCount++; // 문자열 비교하면서 다른개수 발견하면 diffcount증가
    }
    if (diffCount == 1)
        return true; // 어 하나만 다르다 true반환 만약 아니면 **if그냥 지나가겠지?

    bool isMirrored = true;
    for (int i = 0; i < len; i++)
    {
        if (a[i] != b[len - i - 1])
        {
            isMirrored = false; // 미러링해서 다르면 false반환
            break;
        }
    }
    return isMirrored; // ismirrored가 true면 미러링성공 **그럼 여기서 true든 false든 반환
}

bool isInWordList(const char *word, char **wordList, int wordListSize)
{
    for (int i = 0; i < wordListSize; i++)
    {
        if (strcmp(word, wordList[i] == 0))
            return true; // 매개변수로 들어온 두개의 문자열을 비교하여 문자열이 완전히 같다면 0을 반환 다르면 음수 혹은 양수를 반환
    }
    return false;
}
/*주어진 단어가 단어 목록에 있는지 확인합니다.단어 목록을 순회하면서 주어진
단어와 일치하는 단어가 있는지 검사합니다.*/

int findYulMyungPaths(const char *yul, const char *myung, char **wordList, int wordListSize)
{
    if (!isInWordList(myung, wordList, wordListSize))
        return 0;
    // 주어진 목표단어(myung)가 단어목록(wordList)에 없는 경우 0을 반환
    Queue q;
    intiQueue(&q);
    // Queue 타입의 변수 q를 선언하고 이 큐를 초기화. 큐는 BFS탐색을 위해 사용
    Path startPath = {"",1};
    strcpy(startPath.word, yul);
    /*시작 단어 yul을 포함하는 Path구조체 startPath를 생성하고
    변환 횟수를 1로 초기화
    strcpy함수를 사용하여 startPath.word에 yul을 복사*/
    enqueue(&q, startPath);
    /*초기화된 startPath를 큐 q에 추가 이는 BFS 탐색의 시작점*/
    int minPathLength = MAX_WORDS + 1; // 최소변환경로의 길이
    int pathCounts = 0;                // 최소변환 경로의 수
    /*minPathLength를 매우 큰 값으로 초기화하여, 이후 탐색 과정에서
    최소 변환 경로의 길이를 업데이트 할수있도록 함
    pathCounts는 yul에서 myung으로 변환하는 데 필요한
    최소변환 경로의 수를 카운트*/
    while (!isEmpty(&q))
    {                                   // 큐가 비어 있지않은 동안 BFS탐색을 계속함
        Path currentPath = dequeue(&q); // 큐에서 다음 경로를 꺼내 currentPath에 저장함
        if (currentPath.length > minPathLength)
            continue;
        /*현재 경로의 길이가 이미 발견된 최소 경로 길이보다 긴 경우,
        더 이상 탐색할 필요가 없으므로 다음 반복으로 넘어감.*/
        if (isoneletterDifforMirror(currentPath.word, myung)) // 현재 경로의 단어가 myung과 한 글자만 다르거나 미러링관계인 경우 최소경로길이와 경로수를 업데이트함
        {
            if (currentPath.length < minPathLength)
            {
                minPathLength = currentPath.length;
                pathCounts = 1; // 최소 변환 경로 수 1로 업데이트(새로찾은거니까)
            }
            else if (currentPath.length == minPathLength)
            {
                pathCounts++; // 갱신
            }
            continue;
        }
        /*현재 경로의 단어가 myung과 한 글자만 다르거나 미러링관계인 경우
        최소 경로 길이와 경로 수를 업데이트 함.
        만약 현재 경로의 길이가 최소 길이보다 짧은 경우,최소길이와 경로 수를
        현재 경로의 값으로 업데이트 함.
        현재 경로의 길이가 기존의 최소 길이와 같은 경우 경로 수만 증가*/
        for (int i = 0; i < wordListSize; i++)
        {
            if (isoneletterDifforMirror(currentPath.word, wordList[i]))
            {
                Path newPath = {"",currentPath.length + 1}; // 현재경로길이 업데이트
                strcpy(newPath.word, wordList[i]);
                enqueue(&q, newPath); // 큐에 추가
            }
        }
        /*단어 목록의 모든 단어에 대해,현재 경로의 단어와 한글자만 다르거나
        미러링 관계인 단어를 찾음.
        조건에 해당하는 각 단어에 대해, 새로운 Path를 생성하고,현재경로길이에 1을
        더한 값을 length로 설정한 후, 큐에 추가. 이 과정은 모든 가능한 변환 경로를 탐색*/
    }
    return pathCounts
}
/*최종적으로 yul에서 myung으로의 최소 변환 경로의 수를 반환
이 함수는 BFS알고리즘을 사용하여 주어진 시작 단어에서 목표 단어로의
최소 변환 경로의 수를 찾음. 탐색 과정에서 각 단계에서 가능한 모든
변환을 큐에 추가하고 이를 통해 최소 변환 경로를 찾음.*/