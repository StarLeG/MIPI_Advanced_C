/*
    Префикс и суффикс
    На стандартном потоке ввода задаются две символьные строки, разделённые символом перевода строки.
    Каждая из строк не превышает подлине 104. В строках не встречаются пробельные символы.
    На стандартный поток вывода напечатайте два числа, разделённых пробелом:
    первое число — длина наибольшего префикса первойстроки, являющегося суффиксом второй;
    второе число — наоборот, длина наибольшего суффикса первой строки, являющегося префиксомвторой.
    Сравнение символов проводите с учётом регистра (т.е. символы 'a' и 'A' различны).
*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN 10005


int max_prefix_suffix(const char* str1, const char* str2); 

int max_suffix_prefix(const char* str1, const char* str2);

int main() {
    char str1[MAX_LEN], str2[MAX_LEN];
        
    fgets(str1, MAX_LEN, stdin);
    fgets(str2, MAX_LEN, stdin);
        
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';    
  
    int result1 = max_prefix_suffix(str1, str2);
    int result2 = max_suffix_prefix(str1, str2);    
   
    printf("%d %d\n", result1, result2);
    
    return 0;
}

int max_prefix_suffix(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);    
   
    int max_possible = len1 < len2 ? len1 : len2;    
   
    for (int i = max_possible; i > 0; i--) {
        int match = 1;        
        
        for (int j = 0; j < i; j++) {
            if (str1[j] != str2[len2 - i + j]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            return i;
        }
    }
    
    return 0;
}

int max_suffix_prefix(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);    

    int max_possible = len1 < len2 ? len1 : len2;    
  
    for (int i = max_possible; i > 0; i--) {
        int match = 1;        
  
        for (int j = 0; j < i; j++) {
            if (str1[len1 - i + j] != str2[j]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            return i;
        }
    }
    
    return 0;
}