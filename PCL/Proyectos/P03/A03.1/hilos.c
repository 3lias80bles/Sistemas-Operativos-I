#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N_DATOS_H2O 40
#define N_DATOS_CO2 40
#define N_DATOS_POS 40

void* sim_H2O(void* arg) {
    char s;
    srandom(getpid());

    for (int i = 0; i < N_DATOS_H2O; i++) {
        sleep(1);
        s = (char)((random() % 6) + 'a');
        putchar(s); fflush(stdout);
    }
    return NULL;
}

void* sim_CO2(void* arg) {
    char s;
    srandom(getpid() + 1);

    for (int i = 0; i < N_DATOS_CO2; i++) {
        sleep(1);
        s = (char)((random() % 6) + '0');
        putchar(s); fflush(stdout);
    }
    return NULL;
}

void* sim_pos(void* arg) {
    char p = 'N';
    srandom(time(NULL) + 2);

    for (int i = 0; i < N_DATOS_POS; i++) {
        putchar(p); fflush(stdout);
        sleep(random() % 5 + 1);
        p = p + (random() % 7 - 3);
        if (p < 'A') p = 'A';
        if (p > 'Z') p = 'Z';
    }
    return NULL;
}

int main() {
    pthread_t hilo_H2O, hilo_CO2, hilo_pos;

    pthread_create(&hilo_H2O, NULL, sim_H2O, NULL);
    pthread_create(&hilo_CO2, NULL, sim_CO2, NULL);
    pthread_create(&hilo_pos, NULL, sim_pos, NULL);

    pthread_join(hilo_H2O, NULL);
    pthread_join(hilo_CO2, NULL);
    pthread_join(hilo_pos, NULL);

    putchar('\n'); // salto de línea final
    return 0;
}
