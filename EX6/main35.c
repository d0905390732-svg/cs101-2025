#include <stdio.h>

int main() {
    int* p, c;
    c = 5;
    p = &c;
    
    printf("Value of c: %d\n", c);
    printf("Address of c: %x\n", &c);
    printf("Address stored in p: %x\n", p);
    printf("Value of *p: %d\n", *p);
    return 0;
}
