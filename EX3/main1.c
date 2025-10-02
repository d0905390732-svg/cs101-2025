#include <stdio.h>

int main() {
    int n = 7;  // 固定 7 層

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + i - 1; j++) {
            if (j <= n - i) {
                // 左邊補空格
                printf(" ");
            } else {
                // 印數字 (第 i 層印 i 個 i，之間加空格)
                if (j <= n - i + i) {
                    printf("%d ", i);
                }
            }
        }
        printf("\n");
    }

    return 0;
}
