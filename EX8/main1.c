
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define TOTAL_SETS 5
#define NUM_PER_SET 7
#define MAX_LINE_LENGTH 100


int check_win(const int lotto_set[], const int winning_numbers[], int num_winning) {
    int matches = 0;
    for (int i = 0; i < num_winning; i++) {
        bool found = false;
        for (int j = 0; j < NUM_PER_SET; j++) {
            if (winning_numbers[i] == lotto_set[j]) {
                found = true;
                break;
            }
        }
        if (found) {
            matches++;
        }
    }
    return (matches == num_winning);
}

int main() {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    int winning_numbers[3];
    int set_index, j;
    bool has_winning_ticket = false; 

  
    printf("請輸入中獎號碼三個：");
    if (scanf("%d %d %d", &winning_numbers[0], &winning_numbers[1], &winning_numbers[2]) != 3) {
        fprintf(stderr, "輸入格式錯誤。\n");
        return 1;
    }

  
    printf("輸入中獎號碼為：%02d %02d %02d\n", winning_numbers[0], winning_numbers[1], winning_numbers[2]);
    printf("以下為中獎彩券：\n");

 
    fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening lotto.txt for reading.\n");
        return 1;
    }

  
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        if (sscanf(line, "[%d]:", &set_index) == 1) { 
            int lotto_set[NUM_PER_SET];
            char *p_start = line; 
            int num_count = 0;

            char *colon_pos = strchr(line, ':');
            if (colon_pos == NULL) {
                continue;
            }
            p_start = colon_pos + 1; 

            char *temp_line = strdup(p_start);
            if (temp_line == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                fclose(fp);
                return 1;
            }

            char *num_str = strtok(temp_line, " \t\n"); 
            
            while (num_str != NULL && num_count < NUM_PER_SET) {
                if (strcmp(num_str, "__") == 0) {
                    lotto_set[num_count++] = -1;
                } else {
                    lotto_set[num_count++] = atoi(num_str);
                }
                num_str = strtok(NULL, " \t\n");
            }

            free(temp_line);

        
            if (num_count == NUM_PER_SET) {
                bool all_generated = true;
                for(j = 0; j < NUM_PER_SET; j++) {
                    if (lotto_set[j] == -1) {
                        all_generated = false;
                        break;
                    }
                }

                if (all_generated && check_win(lotto_set, winning_numbers, 3)) {
              
                    
                 
                    printf("售出時間：March 13 2025: [%d]:", set_index); 
                    
                    for (j = 0; j < NUM_PER_SET; j++) {
                        printf(" %02d", lotto_set[j]);
                    }
                    printf("\n");
                    has_winning_ticket = true;
                }
            }
        } 
    }


    fclose(fp);
    
    return 0;
}
