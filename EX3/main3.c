
#include <stdio.h>

int main() {
    int i = 10;
    if(i % 15 == 0) {
        printf("Love Hanni");
    }
    else if (i % 3 == 0) {
        printf("Love Minji");
    }
    else if ( i % 5 == 0) {
        printf("Love Haerin");
    }
    else {
        printf("%d\n", i);
    }
    return 0;
}
