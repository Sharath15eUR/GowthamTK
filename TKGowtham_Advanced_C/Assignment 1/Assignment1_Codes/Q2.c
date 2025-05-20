#include <stdio.h>

void rearrage(int *arr, int size) {
    int even[10];
    int odd[10];
    int osize = 0;
    int esize = 0;

    for(int i = 0; i < size; i++){
        if (*(arr + i) % 2 == 0) {
           *(even + esize) = *(arr + i);
           esize++;
        } else {
            *(odd + osize) = *(arr + i);
            osize++;
        }
    }

    int* ptr = arr;
    for(int i = 0; i < esize; i++){
        *(ptr++) = *(even + i);
    }

    for(int i = 0; i < osize; i++) {
        *(ptr++) = *(odd + i);
    }
}

int main() {
    int size = 10;
    int arr[] = {5, 15, 2, 8, 10, 9, 4, 3, 1, 6};

    rearrage(arr, size);

    for(int i = 0; i < size; i++) {
        printf("%d ",arr[i]);
    }

    return 0;
}