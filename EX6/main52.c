

#include <stdio.h>
#include <string.h>

typedef struct movie {
    char name[32];
    int ranking;
} movie_t;

movie_t* fill_movie() {
    static movie_t m;
    strcpy(m.name, "BE ALL YOU CAN BE");
    m.ranking = 1;
    return &m;
}

int main() {
    movie_t* r_m = NULL;
    r_m = fill_movie();
    printf("name = %s\n", r_m->name);
    printf("ranking = %d\n", r_m->ranking);
    return 0;
}
