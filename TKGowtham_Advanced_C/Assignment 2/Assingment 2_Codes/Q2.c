#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig) {
    printf("\nSIGINT received. Preventing termination. Press Ctrl+\\ to force quit.\n");
}

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0) return 0;
    return 1;
}

void* threadA(void* arg) {
    int N = *((int*)arg);
    int count = 0, num = 2, sum = 0;

    clock_t start = clock();

    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Thread A: Sum of first %d primes = %d\n", N, sum);
    printf("Thread A completed in %.2f seconds.\n", duration);
    pthread_exit(NULL);
}

void* threadB(void* arg) {
    time_t start = time(NULL);
    while (keep_running && time(NULL) - start < 100) {
        printf("Thread B running\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

void* threadC(void* arg) {
    time_t start = time(NULL);
    while (keep_running && time(NULL) - start < 100) {
        printf("Thread C running\n");
        sleep(3);
    }
    pthread_exit(NULL);
}

int main() {
    signal(SIGINT, handle_sigint); 

    int N;
    printf("Enter N: ");
    scanf("%d", &N);

    pthread_t t1, t2, t3;

    time_t overall_start = time(NULL);

    pthread_create(&t1, NULL, threadA, &N);
    pthread_create(&t2, NULL, threadB, NULL);
    pthread_create(&t3, NULL, threadC, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    time_t overall_end = time(NULL);
    printf("All threads completed in %ld seconds.\n", overall_end - overall_start);

    return 0;
}
