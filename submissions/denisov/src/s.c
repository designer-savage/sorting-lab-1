#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp = 0, swap = 0;

void nullify() {
    comp = 0; swap = 0;
}

void sw(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swap++;
}

void sel_sort(int *arr, int n) {
    nullify();

    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comp++;
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
            swap++;
        }
    }
    printf("comp:%d swap:%d\n", comp, swap);
}

void heapify(int *arr, int n, int i) {
    int big = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n) {
        if (arr[l] > arr[big]) {
            big = l;
            // comp++;
        }
        comp++;
    }
    if (r < n) {
        if (arr[r] > arr[big]) {
            big = r;
            // comp++;
        }
        comp++;
    }

    if (big != i) {
        sw(&arr[i], &arr[big]);
        heapify(arr, n, big);
    }
}

void heap_sort(int *arr, int n) {
    nullify();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        sw(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void arr_pr(int *arr, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* generate(int n) {
    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }

    return arr;
}

int main(void) {
    srand(time(NULL));
    int n = 1000;

    for (int i = 0; i < 3; i++) {
        int *arr = generate(n);
        sel_sort(arr, n);
    }

    printf("############");

    for (int i = 0; i < 3; i++) {
        int *arr = generate(n);
        heap_sort(arr, n);
        printf("\ncomp:%d swap:%d", comp, swap);
    }

    return 0;
}