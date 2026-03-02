#include "sort.h"

long long cmp_count = 0;
long long mov_count = 0;

void selection_sort(double* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minn = i;

        for (int j = i + 1; j < n; j++) {
            cmp_count++;
            if (arr[j] < arr[minn])
                minn = j;
        }

        if (minn != i) {
            double t = arr[i];
            arr[i] = arr[minn];
            arr[minn] = t;
            mov_count += 3;
        }
    }
}