/*
문자열 길이 반환: int len(char* s)
문자열의 길이를 계산: int my_strlen(char *str)
문자열 복사: void copy_string(char* dst, char* src)
문자열 복사: char* my_strcpy(char *dest, const char *src)
문자열 일부 복사: void copy_n_string(char* dst, char* src, int n)
문자열 일부 복사: char* my_strncpy(char *dest, const char *src, size_t n)
두 문자열을 연결: char* my_strcat(char *dest, const char *src)
문자열의 일부를 연결: char* my_strncat(char *dest, const char *src, size_t n) 
두 문자열을 비교: int my_strcmp(const char *str1, const char *str2)
문자열의 일부를 비교: int my_strncmp(const char *str1, const char *str2, size_t n)
문자열에서 특정 문자를 찾기: char *my_strchr(const char *str, int c)
문자열 내에서 부분 문자열을 찾기: char *my_strstr(const char *haystack, const char *needle)
문자열을 구분자로 나누기: char *my_strtok(char *str, const char *delim) 
*/

#include <stdio.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 문자열 길이 반환 함수
int len(char* s) {
    int cnt = 0;
    // 문자열의 끝을 나타내는 널 문자('\0')를 만날 때까지 반복
    while (*s++ != '\0') {
        cnt++;  // 문자열의 각 문자를 읽으며 길이를 증가
    }
    return cnt;  // 문자열의 길이 반환
}

// int main() {
//     char str[] = "Hello";  // Initialize the string with English text
//     int length = len(str);  // Call the len function to calculate the string length

//     printf("The length of the string is %d.\n", length);  // Print the result
//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 문자열의 길이를 계산하는 함수
int my_strlen(char *str) {
    int length = 0;
    // 문자열의 끝을 나타내는 널 문자('\0')를 만날 때까지 반복
    while (str[length] != '\0') {
        length++;  // 각 문자를 확인하며 길이를 증가
    }
    return length;  // 계산된 문자열의 길이를 반환
}

// int main() {
//     char str[] = "Hello, World!";  // 문자열 초기화
//     int length = my_strlen(str);  // my_strlen 함수 호출하여 문자열 길이 계산

//     printf("The length of the string is %d.\n", length);  // 결과 출력 (영어로)
//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 문자열을 복사하는 함수
void copy_string(char* dst, char* src) {
    while (*src != '\0') {  // src가 가리키는 문자가 널 문자('\0')가 아닐 때까지 반복
        *dst++ = *src++;    // src의 현재 문자를 dst에 복사하고, 둘 다 다음 위치로 이동
    }
    *dst = '\0';  // 마지막에 dst에 널 문자('\0') 추가하여 문자열 종료
}

// int main() {
//     char src[] = "Hello, World!";  // Original string
//     char dst[50];  // Array to store the copied string

//     copy_string(dst, src);  // Call copy_string function to copy the string

//     printf("Original string: %s\n", src);  // Print the original string
//     printf("Copied string: %s\n", dst);  // Print the copied string

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 문자열을 복사하는 함수
char* my_strcpy(char *dest, const char *src) {
    char *d = dest;  // dest를 가리키는 포인터를 d에 저장
    const char *s = src;  // src를 가리키는 포인터를 s에 저장
    while ((*d++ = *s++)) ;  // src에서 문자를 하나씩 복사하여 dest에 저장, 널 문자를 만나면 종료
    return dest;  // 복사된 문자열이 저장된 dest를 반환
}

// int main() {
//     char src[] = "Hello, World!";  // 원본 문자열
//     char dest[50];  // 복사된 문자열을 저장할 배열

//     my_strcpy(dest, src);  // my_strcpy 함수 호출하여 문자열 복사

//     printf("Original string: %s\n", src);  // 원본 문자열 출력
//     printf("Copied string: %s\n", dest);  // 복사된 문자열 출력

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 문자열의 일부(n개의 문자)를 복사하는 함수
void copy_n_string(char* dst, char* src, int n) {
    int i;
    // src에서 n개의 문자를 dst로 복사
    for (i = 0; i < n; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';  // 복사가 끝난 후 널 문자 추가하여 문자열 종료
}

// int main(void) {
//     char* s = "zzzzz";    // 복사할 원본 문자열
//     char string[10];       // 복사된 문자열을 저장할 배열
//     int size = 3;          // 복사할 문자의 개수

//     // copy_n_string 함수 사용
//     copy_n_string(string, s, size);
//     printf("copy_n_string: %s\n", string); // 출력 결과: "zzz"

//     // strncpy 함수 사용
//     // (void)strncpy(string, s, size);
//     // string[size] = '\0'; // 널 문자로 문자열 종료
//     // printf("strncpy: %s\n", string); // 출력 결과: "zzz"

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 문자열의 일부(n개의 문자)를 복사하는 함수
char* my_strncpy(char *dest, const char *src, size_t n) {
    char *d = dest;  // dest를 가리키는 포인터
    const char *s = src;  // src를 가리키는 포인터
    size_t i;

    // n이거나 src의 끝까지 문자를 복사
    for (i = 0; i < n && (*d++ = *s++); i++) ;
    
    // n 바이트를 채우지 못한 경우, 남은 부분에 널 문자 추가
    if (i < n) *d = '\0';  

    return dest;  // 복사된 문자열이 있는 dest를 반환
}

// int main() {
//     char dest[100];

//     // 테스트 케이스 1: 일반적인 문자열 복사 (n이 충분히 큰 경우)
//     const char *src1 = "Hello, World!";
//     size_t n1 = 8;
//     my_strncpy(dest, src1, n1);
//     printf("Test 1: %s\n", dest);  // 기대 출력: Hello, W

//     // 테스트 케이스 2: n이 문자열 길이보다 큰 경우
//     const char *src2 = "Short";
//     size_t n2 = 10;
//     my_strncpy(dest, src2, n2);
//     printf("Test 2: '%s'\n", dest);  // 기대 출력: Short

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 두 문자열을 연결하는 함수
char* my_strcat(char *dest, const char *src) {
    char *d = dest;

    // dest 문자열의 끝으로 이동
    while (*d) d++;  // dest 문자열 끝을 찾음

    // src 문자열을 dest의 끝에 추가
    while ((*d++ = *src++)) ;  // src의 문자를 dest에 복사, 널 문자를 만나면 종료

    return dest;  // 연결된 문자열을 반환
}

// int main() {
//     // 충분히 큰 배열을 선언하여 문자열 연결 테스트
//     char dest[100];

//     // 테스트 케이스 1: 일반적인 문자열 연결
//     char src1[] = "World!";
//     char dest1[100] = "Hello, ";  // 연결할 문자열 준비
//     my_strcat(dest1, src1);  // src1을 dest1에 연결
//     printf("Test 1: %s\n", dest1);  // 기대 출력: Hello, World!

//     // 테스트 케이스 2: 빈 src 문자열을 연결
//     char src2[] = "";
//     char dest2[100] = "Empty src ";  // 연결할 문자열 준비
//     my_strcat(dest2, src2);  // 빈 src를 dest2에 연결
//     printf("Test 2: '%s'\n", dest2);  // 기대 출력: Empty src 

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 문자열의 일부(n 바이트)를 연결하는 함수
char* my_strncat(char *dest, const char *src, size_t n) {
    char *d = dest;

    // dest 문자열의 끝으로 이동
    while (*d) d++;  // dest 문자열의 끝을 찾음

    // src 문자열을 최대 n 바이트만 dest의 끝에 추가
    while (n-- && (*d++ = *src++)) ;  // n 바이트만 복사하며, src의 문자를 dest에 추가

    // 문자열 끝에 null 문자 추가
    *d = '\0';  // 연결된 문자열을 종료하기 위해 널 문자 추가

    return dest;  // 연결된 문자열을 반환
}

// int main() {
//     // 충분히 큰 배열을 선언하여 문자열 연결 테스트
//     char dest[100];

//     // 테스트 케이스 1: 일반적인 문자열 연결 (n이 충분히 큰 경우)
//     char src1[] = "World!";
//     char dest1[100] = "Hello, ";
//     size_t n1 = 4;  // src1에서 최대 4 문자만 추가
//     my_strncat(dest1, src1, n1);  // src1의 첫 4문자만 dest1에 추가
//     printf("Test 1: %s\n", dest1);  // 기대 출력: Hello, Worl

//     // 테스트 케이스 2: n이 src 문자열 길이보다 큰 경우
//     char src2[] = "Short";
//     char dest2[100] = "String: ";
//     size_t n2 = 10;  // src2의 길이보다 큰 값
//     my_strncat(dest2, src2, n2);  // src2의 전체 문자열을 dest2에 추가
//     printf("Test 2: %s\n", dest2);  // 기대 출력: String: Short

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 두 문자열을 비교하는 함수
// 두 문자열이 같으면 0을, 첫 번째 문자열이 더 크면 양수, 두 번째 문자열이 더 크면 음수를 반환
int my_strcmp(const char *str1, const char *str2) {
    // 두 문자열이 같을 때까지 하나씩 비교
    while (*str1 && (*str1 == *str2)) {
        str1++;  // str1을 다음 문자로 이동
        str2++;  // str2를 다음 문자로 이동
    }
    // 두 문자열이 다르면 그 차이를 반환
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// int main() {
//     // 테스트 케이스 1: 두 문자열이 동일한 경우
//     const char *str1 = "Hello";
//     const char *str2 = "Hello";
//     int result1 = my_strcmp(str1, str2);
//     printf("Test 1: %d\n", result1);  // 기대 출력: 0 (두 문자열이 같으면 0 반환)

//     // 테스트 케이스 2: 두 문자열이 서로 다른 경우
//     const char *str3 = "Hello";
//     const char *str4 = "World";
//     int result2 = my_strcmp(str3, str4);
//     printf("Test 2: %d\n", result2);  // 기대 출력: 음수 (예: -15, 'H'와 'W'의 차이)

//     // 테스트 케이스 3: 문자열의 길이가 다른 경우
//     const char *str5 = "Hello";
//     const char *str6 = "Hello, World!";
//     int result3 = my_strcmp(str5, str6);
//     printf("Test 3: %d\n", result3);  // 기대 출력: 음수 (예: -44, ','와 ' '의 차이)

//     // 테스트 케이스 4: 첫 번째 문자열이 두 번째 문자열의 접두사인 경우
//     const char *str7 = "Hello, World!";
//     const char *str8 = "Hello";
//     int result4 = my_strcmp(str7, str8);
//     printf("Test 4: %d\n", result4);  // 기대 출력: 양수 (예: 44, ','와 ' '의 차이)

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 두 문자열의 일부(n 개의 문자)를 비교하는 함수
// 두 문자열이 n 문자까지 같으면 0을 반환, 다르면 차이를 반환
int my_strncmp(const char *str1, const char *str2, size_t n) {
    // n이 0보다 크고 두 문자열이 다를 때까지 비교
    while (n-- && *str1 && (*str1 == *str2)) {
        str1++;  // str1을 다음 문자로 이동
        str2++;  // str2를 다음 문자로 이동
    }

    // n이 0인 경우 두 문자열이 n 문자까지 동일하므로 0을 반환
    // 그렇지 않으면 첫 번째 서로 다른 문자의 차이를 반환
    return (n == (size_t)-1) ? 0 : *(unsigned char *)str1 - *(unsigned char *)str2;
}

// int main() {
//     // 테스트 케이스 1: n이 충분히 큰 경우 (문자열이 동일할 때)
//     const char *str1 = "Hello, World!";
//     const char *str2 = "Hello, World!";
//     size_t n1 = 20;  // 문자열 길이보다 큰 n
//     int result1 = my_strncmp(str1, str2, n1);
//     printf("Test 1: %d\n", result1);  // 기대 출력: 0 (두 문자열이 동일하므로)

//     // 테스트 케이스 2: n이 문자열 길이보다 작은 경우 (문자열이 동일할 때)
//     const char *str3 = "Hello, World!";
//     const char *str4 = "Hello, Universe!";
//     size_t n2 = 7;  // str1과 str2의 첫 7문자까지 동일하므로 0 반환
//     int result2 = my_strncmp(str3, str4, n2);
//     printf("Test 2: %d\n", result2);  // 기대 출력: 0 (첫 7문자가 동일)

//     // 테스트 케이스 3: n이 문자열 길이보다 작은 경우 (문자열이 다를 때)
//     const char *str5 = "Hello, World!";
//     const char *str6 = "Hello, Universe!";
//     size_t n3 = 8;  // str1과 str2의 첫 8문자까지 비교, 'W'와 'U' 비교
//     int result3 = my_strncmp(str5, str6, n3);
//     printf("Test 3: %d\n", result3);  // 기대 출력: 'W' - 'U'의 차이 (양수 값)

//     // 테스트 케이스 4: n이 0인 경우 (비교하지 않음)
//     const char *str7 = "Hello";
//     const char *str8 = "World";
//     size_t n4 = 0;  // 비교하지 않으므로 0 반환
//     int result4 = my_strncmp(str7, str8, n4);
//     printf("Test 4: %d\n", result4);  // 기대 출력: 0 (비교하지 않음)

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// strchr: 문자열에서 특정 문자를 찾는 함수
// str: 검색할 문자열, c: 찾고자 하는 문자
char *my_strchr(const char *str, int c) {
    // 문자를 검색하는 루프
    while (*str) {
        // 현재 문자가 찾고자 하는 문자와 같다면
        if (*str == (char)c) {
            return (char *)str;  // 문자 위치를 반환
        }
        str++;  // 문자열의 다음 문자로 이동
    }
    
    // 문자열의 끝까지 도달했는데도 문자를 찾지 못한 경우
    // 찾고자 하는 문자가 null 문자일 때도 반환
    if ((char)c == '\0') {
        return (char *)str;  // null 문자 위치를 반환
    }
    
    return NULL;  // 문자를 찾지 못한 경우 NULL 반환
}

// int main() {
//     // 테스트 케이스 1: 문자가 문자열에 있는 경우
//     const char *str1 = "Hello, World!";
//     int c1 = 'W';
//     char *result1 = my_strchr(str1, c1);
//     if (result1) {
//         printf("Test 1: '%c' found at position %ld\n", c1, result1 - str1);  // 문자가 발견되면 위치 출력
//     } else {
//         printf("Test 1: '%c' not found\n", c1);  // 문자가 없으면 출력
//     }
//     // 기대 출력: W found at position 7

//     // 테스트 케이스 2: 문자가 문자열에 없는 경우
//     const char *str2 = "Hello, World!";
//     int c2 = 'x';
//     char *result2 = my_strchr(str2, c2);
//     if (result2) {
//         printf("Test 2: '%c' found at position %ld\n", c2, result2 - str2);
//     } else {
//         printf("Test 2: '%c' not found\n", c2);
//     }
//     // 기대 출력: x not found

//     // 테스트 케이스 3: 문자가 문자열의 첫 번째 위치에 있는 경우
//     const char *str3 = "Hello, World!";
//     int c3 = 'H';
//     char *result3 = my_strchr(str3, c3);
//     if (result3) {
//         printf("Test 3: '%c' found at position %ld\n", c3, result3 - str3);
//     } else {
//         printf("Test 3: '%c' not found\n", c3);
//     }
//     // 기대 출력: H found at position 0

//     // 테스트 케이스 4: 문자가 문자열의 끝에 있는 경우
//     const char *str4 = "Hello, World!";
//     int c4 = '!';
//     char *result4 = my_strchr(str4, c4);
//     if (result4) {
//         printf("Test 4: '%c' found at position %ld\n", c4, result4 - str4);
//     } else {
//         printf("Test 4: '%c' not found\n", c4);
//     }
//     // 기대 출력: ! found at position 12

//     // 테스트 케이스 5: 문자가 null 문자인 경우
//     const char *str5 = "Hello";
//     int c5 = '\0';
//     char *result5 = my_strchr(str5, c5);
//     if (result5) {
//         printf("Test 5: Null character found at position %ld\n", result5 - str5);
//     } else {
//         printf("Test 5: Null character not found\n");
//     }
//     // 기대 출력: Null character found at position 5

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// strstr: 문자열 내에서 부분 문자열을 찾는 함수
// haystack: 검색할 문자열, needle: 찾을 부분 문자열
char *my_strstr(const char *haystack, const char *needle) {
    // 빈 needle인 경우, haystack의 시작 위치를 반환
    if (*needle == '\0') return (char *)haystack;

    // haystack에서 needle을 검색
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;

        // haystack의 현재 위치에서 needle의 각 문자를 비교
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }

        // needle의 모든 문자를 다 비교했다면, 해당 위치를 반환
        if (*n == '\0') return (char *)haystack;

        // haystack의 다음 위치로 이동
        haystack++;
    }

    // needle을 찾지 못한 경우 NULL 반환
    return NULL;
}

// int main() {
//     // 테스트 케이스 1: needle이 haystack에 있는 경우
//     const char *haystack1 = "Hello, World!";
//     const char *needle1 = "World";
//     char *result1 = my_strstr(haystack1, needle1);
//     if (result1) {
//         printf("Test 1: '%s' found at position %ld\n", needle1, result1 - haystack1);
//     } else {
//         printf("Test 1: '%s' not found\n", needle1);
//     }
//     // 기대 출력: World found at position 7

//     // 테스트 케이스 2: needle이 haystack에 없는 경우
//     const char *haystack2 = "Hello, World!";
//     const char *needle2 = "Universe";
//     char *result2 = my_strstr(haystack2, needle2);
//     if (result2) {
//         printf("Test 2: '%s' found at position %ld\n", needle2, result2 - haystack2);
//     } else {
//         printf("Test 2: '%s' not found\n", needle2);
//     }
//     // 기대 출력: Universe not found

//     // 테스트 케이스 3: needle이 haystack의 시작 부분에 있는 경우
//     const char *haystack3 = "Hello, World!";
//     const char *needle3 = "Hello";
//     char *result3 = my_strstr(haystack3, needle3);
//     if (result3) {
//         printf("Test 3: '%s' found at position %ld\n", needle3, result3 - haystack3);
//     } else {
//         printf("Test 3: '%s' not found\n", needle3);
//     }
//     // 기대 출력: Hello found at position 0

//     // 테스트 케이스 4: needle이 haystack의 끝 부분에 있는 경우
//     const char *haystack4 = "Hello, World!";
//     const char *needle4 = "World!";
//     char *result4 = my_strstr(haystack4, needle4);
//     if (result4) {
//         printf("Test 4: '%s' found at position %ld\n", needle4, result4 - haystack4);
//     } else {
//         printf("Test 4: '%s' not found\n", needle4);
//     }
//     // 기대 출력: World! found at position 7

//     // 테스트 케이스 5: 빈 needle인 경우
//     const char *haystack5 = "Hello, World!";
//     const char *needle5 = "";
//     char *result5 = my_strstr(haystack5, needle5);
//     if (result5) {
//         printf("Test 5: Empty needle found at position %ld\n", result5 - haystack5);
//     } else {
//         printf("Test 5: Empty needle not found\n");
//     }
//     // 기대 출력: Empty needle found at position 0

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// strtok: 문자열을 구분자로 나누기
// str: 분할할 문자열, delim: 구분자
char *my_strtok(char *str, const char *delim) {
    static char *last = NULL;  // 이전 호출에서의 위치를 기억
    
    if (str != NULL) {
        last = str;  // 새 문자열의 시작점으로 last를 설정
    }
    
    if (last == NULL) {
        return NULL;  // 문자열이 없으면 NULL 반환
    }

    // 구분자가 포함된 문자열을 찾는다.
    char *start = last;
    while (*start && strchr(delim, *start)) {
        start++;  // 구분자가 나오면 skip
    }

    if (*start == '\0') {
        last = NULL;
        return NULL;  // 문자열의 끝에 도달했을 때
    }

    // 구분자가 아닌 문자열이 시작된 지점 찾기
    char *end = start;
    while (*end && !strchr(delim, *end)) {
        end++;  // 구분자가 아닌 문자 계속 찾기
    }

    if (*end) {
        *end = '\0';  // 구분자 위치에 NULL 문자 추가 (문자열 끝으로 취급)
        last = end + 1;  // 다음 호출에서는 구분자 뒤에서부터 시작
    } else {
        last = NULL;  // 문자열의 끝에 도달했을 때
    }

    return start;  // 현재 구분된 토큰 반환
}

// int main() {
//     // 테스트 케이스 1: 기본적인 문자열 분리
//     char str1[] = "Hello, World! How are you?";
//     const char *delim1 = " ,!?";  // 공백, 쉼표, 느낌표, 물음표가 구분자
//     char *token1 = my_strtok(str1, delim1);
//     while (token1) {
//         printf("Token 1: '%s'\n", token1);  // 각 토큰 출력
//         token1 = my_strtok(NULL, delim1);  // 이후 토큰을 계속 얻음
//     }
//     // 기대 출력: Hello, World, How, are, you

//     // 테스트 케이스 2: 문자열에 구분자가 없는 경우
//     char str2[] = "SingleToken";
//     const char *delim2 = " ,!?";  // 구분자들
//     char *token2 = my_strtok(str2, delim2);
//     while (token2) {
//         printf("Token 2: '%s'\n", token2);
//         token2 = my_strtok(NULL, delim2);  // 이후 토큰을 계속 얻음
//     }
//     // 기대 출력: SingleToken

//     // 테스트 케이스 3: 빈 문자열
//     char str3[] = "";
//     const char *delim3 = " ,!?";  // 구분자들
//     char *token3 = my_strtok(str3, delim3);
//     while (token3) {
//         printf("Token 3: '%s'\n", token3);
//         token3 = my_strtok(NULL, delim3);
//     }
//     // 기대 출력: (출력 없음)

//     // 테스트 케이스 4: 구분자가 문자열의 시작과 끝에 위치한 경우
//     char str4[] = "   Leading and trailing spaces   ";
//     const char *delim4 = " ";  // 공백을 구분자로 사용
//     char *token4 = my_strtok(str4, delim4);
//     while (token4) {
//         printf("Token 4: '%s'\n", token4);
//         token4 = my_strtok(NULL, delim4);  // 이후 토큰을 계속 얻음
//     }
//     // 기대 출력: Leading, and, trailing, spaces

//     return 0;
// }