/*
                                    Вычеркивание
    Сколько различных трехзначных чисел можно получить из заданного натурального N,
    вычеркивая цифры из его десятичной записи?
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char input[1000];  
    scanf("%s", input);  
    
    int len = strlen(input);
    
    
    int digit_count[10] = {0};
    for (int i = 0; i < len; i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            digit_count[input[i] - '0']++;
        }
    }
    
   
    bool seen[1000] = {false};
    int count = 0;
    
    
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            for (int k = j + 1; k < len; k++) {               
                int num = (input[i] - '0') * 100 + 
                         (input[j] - '0') * 10 + 
                         (input[k] - '0');              
               
                if (num >= 100 && !seen[num]) {
                    seen[num] = true;
                    count++;
                }
            }
        }
    }
    
    printf("%d\n", count);
    return 0;
}