#include <stdio.h>
#include <stdlib.h> // 包含 exit() 函式，用於錯誤處理
#include <string.h> // 雖然這裡用不到 strlen，但包含常用

// 定義陣列的大小，讓程式碼更清晰
#define ARRAY_SIZE_A 3
#define ARRAY_SIZE_B 3 // "ABC" 不包含 '\0'
#define ARRAY_SIZE_C 3

void file_error(const char *op) {
    // 統一的錯誤處理函式
    fprintf(stderr, "Error during file %s operation.\n", op);
    exit(1);
}

int main() {
    // 原始數據
    int a[ARRAY_SIZE_A] = {0, 1, 2};
    // 注意：char b[] = "ABC"; 只有 3 個字符，不包含結束符 \0
    char b[ARRAY_SIZE_B] = {'A', 'B', 'C'}; 
    float c[ARRAY_SIZE_C] = {1.1, 1.2, 1.3};
    
    // 用於讀取的緩衝區
    int ra[ARRAY_SIZE_A]; 
    char rb[ARRAY_SIZE_B + 1] = {0}; // 多一個空間給 '\0'
    float rc[ARRAY_SIZE_C];
    
    FILE *fp;
    size_t count;

    // ======================== 階段一：二進位寫入 (Write) ========================
    
    // 以二進位寫入模式 ('wb') 開啟檔案
    fp = fopen("a.bin", "wb");
    if (fp == NULL) {
        file_error("write (open)");
    }

    // 1. 寫入 int 陣列 a
    count = fwrite(a, sizeof(int), ARRAY_SIZE_A, fp);
    if (count != ARRAY_SIZE_A) file_error("write (a)");
    
    // 2. 寫入 char 陣列 b
    count = fwrite(b, sizeof(char), ARRAY_SIZE_B, fp);
    if (count != ARRAY_SIZE_B) file_error("write (b)");
    
    // 3. 寫入 float 陣列 c
    count = fwrite(c, sizeof(float), ARRAY_SIZE_C, fp);
    if (count != ARRAY_SIZE_C) file_error("write (c)");

    // 關閉檔案
    fclose(fp);
    
    printf("二進位寫入完成。\n");
    
    // ======================== 階段二：二進位讀取 (Read) ========================
    
    // 以二進位讀取模式 ('rb') 開啟檔案
    fp = fopen("a.bin", "rb");
    if (fp == NULL) {
        file_error("read (open)");
    }
    
    // 1. 讀取 int 陣列 ra
    count = fread(ra, sizeof(int), ARRAY_SIZE_A, fp);
    if (count != ARRAY_SIZE_A) file_error("read (ra)");

    // 2. 讀取 char 陣列 rb
    count = fread(rb, sizeof(char), ARRAY_SIZE_B, fp);
    if (count != ARRAY_SIZE_B) file_error("read (rb)");
    rb[ARRAY_SIZE_B] = '\0'; // 為 char 陣列手動添加結束符

    // 3. 讀取 float 陣列 rc
    count = fread(rc, sizeof(float), ARRAY_SIZE_C, fp);
    if (count != ARRAY_SIZE_C) file_error("read (rc)");
    
    // 關閉檔案
    fclose(fp);
    
    // ======================== 階段三：輸出結果 (Output) ========================
    
    printf("\n讀取到的 int 陣列內容:\n");
    for (int i = 0; i < ARRAY_SIZE_A; i++) {
        printf("%d ", ra[i]);
    }
    printf("\n");

    printf("\n讀取到的 char 陣列內容:\n");
    printf("%s\n", rb);

    printf("\n讀取到的 float 陣列內容:\n");
    // 使用 %.6f 輸出，以符合投影片中 1.100000 格式
    for (int i = 0; i < ARRAY_SIZE_C; i++) {
        printf("%.6f ", rc[i]);
    }
    printf("\n");

    return 0;
}
