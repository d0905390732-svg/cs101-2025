#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define TOTAL_SETS 5     // 每張彩券包含 5 組號碼
#define NUM_PER_SET 7    // 每組彩券有 7 個號碼
#define MAX_LOTTO_NUM 69 // 樂透號碼最大值
#define COUNT_FILE "lotto_count.txt" // 用於儲存當前單號的檔案名


int get_and_increment_ticket_number() {
    FILE *count_fp;
    int current_number = 0;

    count_fp = fopen(COUNT_FILE, "r");
    if (count_fp != NULL) {
    
        if (fscanf(count_fp, "%d", &current_number) != 1) {
            current_number = 0; 
        }
        fclose(count_fp);
    } 

    current_number++; 

    count_fp = fopen(COUNT_FILE, "w");
    if (count_fp == NULL) {
        fprintf(stderr, "Error: Unable to write to lotto_count.txt. Ticket number cannot be saved.\n");
        
    } else {
        fprintf(count_fp, "%d", current_number);
        fclose(count_fp);
    }

    return current_number;
}



void generate_lotto_set(int lotto_numbers[]) {
    int is_selected[MAX_LOTTO_NUM + 1] = {0}; 
    int count = 0;
    
   
    srand(time(NULL) + clock()); 

    while (count < NUM_PER_SET) {
        int num = (rand() % MAX_LOTTO_NUM) + 1; 
        if (is_selected[num] == 0) {
            is_selected[num] = 1; 
            lotto_numbers[count] = num;   
            count++;                      
        }
    }
}

// 主程式
int main() {
    int ticket_number;
    char filename[30];
    FILE *fp;
    
  
    ticket_number = get_and_increment_ticket_number();

 
    sprintf(filename, "lotto%05d.txt", ticket_number); 

    time_t rawtime;
    struct tm *info;
    char time_str[30];
    
    time(&rawtime);
    info = localtime(&rawtime);
    
   
    strftime(time_str, sizeof(time_str), "%a %b %e %H:%M:%S %Y", info); 

    fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening %s for writing.\n", filename);
        return 1;
    }

    fprintf(fp, "======== lotto649 ========\n");
    fprintf(fp, "======== No.%05d ========\n", ticket_number);
    fprintf(fp, "= %s =\n", time_str);
    
   
    for (int i = 1; i <= TOTAL_SETS; i++) {
        int lotto_set[NUM_PER_SET];
        
       
        generate_lotto_set(lotto_set);
        
     
        fprintf(fp, "[%d]:", i); 
        
        for (int j = 0; j < NUM_PER_SET; j++) {
            fprintf(fp, " %02d", lotto_set[j]);
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "======== csie@CGU ========\n");

    fclose(fp);
    
    printf("成功產生彩券檔: %s\n", filename);

    return 0;
}
