#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 5
#define MAX_WORDS 500


bool isOneLetterDiffOrMirrored(const char *word1, const char *word2) {
    int diffCount = 0;
    int len1 = strlen(word1), len2 = strlen(word2);
    if (len1 != len2) return false; // 길이가 다르면 바로 false 반환

    bool isMirrored = true;
    for (int i = 0; i < len1; i++) {
        if (word1[i] != word2[i]) diffCount++;
        if (word1[i] != word2[len1 - i - 1]) isMirrored = false;
    }

    return diffCount == 1 || isMirrored;
}


// 단어 변환 경로의 가짓수를 찾는 함수
int findPaths(const char *current, const char *target, char **wordList, int wordListSize, bool *visited) {
    if (strcmp(current, target) == 0) return 1; // 목표 단어에 도달한 경우
    int pathCount = 0;
    for (int i = 0; i < wordListSize; i++) {
        if (!visited[i] && isOneLetterDiffOrMirrored(current, wordList[i])) {
            visited[i] = true;
            pathCount += findPaths(wordList[i], target, wordList, wordListSize, visited); // 재귀 호출
            visited[i] = false; // 방문 상태를 다시 false로 변경하여 다른 경로 탐색 가능
        }
    }
    return pathCount;
}

// 한 글자만 다른지 확인하는 함수
// 한 글자만 다르거나 미러링되는지 확인하는 함수

int main() {
    char yul[MAX_WORD_LENGTH + 1], myung[MAX_WORD_LENGTH + 1];
    char *wordList[MAX_WORDS];
    bool visited[MAX_WORDS] = {false};
    int wordListSize = 0;

    // 입력 처리
    // 단어 입력 및 단어 목록 생성 로직은 문제 요구 사항에 따라 구현
    // 예: scanf, fgets 등을 사용하여 yul, myung, wordList, wordListSize를 입력받음

    int result = findPaths(yul, myung, wordList, wordListSize, visited);
    printf("Total paths with minimum word transformation: %d\n", result);

    // 할당된 메모리 해제
    for (int i = 0; i < wordListSize; i++) {
        free(wordList[i]);
    }

    return 0;
}



