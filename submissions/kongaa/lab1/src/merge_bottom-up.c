#include <stdlib.h>
#include "sort.h"

extern long long cmp_count;
extern long long mov_count;

// слияние двух отсортированных частей
static void merge(double* arr, double* tmp, int left, int mid, int right) {
    int i = left, j = mid, k = left;

    while (i < mid && j < right) {
        cmp_count++;
        tmp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
        mov_count++;
    }

    while (i < mid) {
        tmp[k++] = arr[i++];
        mov_count++;
    }
    while (j < right) {
        tmp[k++] = arr[j++];
        mov_count++;
    }

    for (int t = left; t < right; t++) {
        arr[t] = tmp[t];
        mov_count++;
    }
}

// сортировка слиянием
void merge_sort_bottom_up(double* arr, int n) {
    double* tmp = malloc(n * sizeof(double));

    for (int currSize = 1; currSize < n; currSize *= 2) {
        for (int i = 0; i < n; i += 2 * currSize) {
            int left = i;
            int mid = (i + currSize < n) ? i + currSize : n;
            int right = (i + 2 * currSize < n) ? i + 2 * currSize : n;

            merge(arr, tmp, left, mid, right);
        }
    }

    free(tmp);
}