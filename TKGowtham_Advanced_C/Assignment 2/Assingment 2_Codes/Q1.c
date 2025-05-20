#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int N;

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0) return 0;
    return 1;
}

void* threadA(void* arg) {
    int count = 0, num = 2, sum = 0;
    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }
    printf("Sum of first %d prime numbers: %d\n", N, sum);
    return NULL;
}

void* threadB(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start < 100) {
        printf("Thread 1 running\n");
        sleep(2);
    }
    return NULL;
}

void* threadC(void* arg) {
    time_t start = time(NULL);
    while (time(NULL) - start < 100) {
        printf("Thread 2 running\n");
        sleep(3);
    }
    return NULL;
}

int main() {
    pthread_t tA, tB, tC;

    printf("Enter N: ");
    scanf("%d", &N);

    pthread_create(&tA, NULL, threadA, NULL);
    pthread_create(&tB, NULL, threadB, NULL);
    pthread_create(&tC, NULL, threadC, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    return 0;
}
