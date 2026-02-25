#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp = 0, swap = 0;
int av_comp_sel = 0, av_comp_heap = 0;
int av_swap_sel = 0, av_swap_heap = 0;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compare_rev(const void *a, const void *b) {
    return -(*(int*)a - *(int*)b);
}

void nullify() {
    comp = 0; swap = 0;
}

void sw(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swap++;
    av_swap_heap++;
}

void sel_sort(int *arr, int n) {
    nullify();

    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comp++;
            av_comp_sel++;
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
            swap++;
            av_swap_sel++;
        }
    }
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
        av_comp_heap++;
    }
    if (r < n) {
        if (arr[r] > arr[big]) {
            big = r;
            // comp++;
        }
        comp++;
        av_comp_heap++;
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
}

void generate(int n, int type, int *ar1, int *ar2) {
    if (type == 1) {
        for (int i = 0; i < n; i++) {
            ar1[i] = rand() % 10000;
        }
        qsort(ar1, n, sizeof(int), compare);
        for (int i = 0; i < n; i++) {
            ar2[i] = ar1[i];
        }
        
        printf("i.  SORTED\n");
        sel_sort(ar1, n);
        printf("SELEC\tcomp:%d\tswap:%d\n", comp, swap);
        heap_sort(ar2, n);
        printf("HEAP\tcomp:%d\tswap:%d\n", comp, swap);
    }
    if (type == 2) {
        for (int i = 0; i < n; i++) {
            ar1[i] = rand() % 10000;
        }
        qsort(ar1, n, sizeof(int), compare_rev);
        for (int i = 0; i < n; i++) {
            ar2[i] = ar1[i];
        }

        printf("ii. REVERSED\n");
        sel_sort(ar1, n);
        printf("SELEC\tcomp:%d\tswap:%d\n", comp, swap);
        heap_sort(ar2, n);
        printf("HEAP\tcomp:%d\tswap:%d\n", comp, swap);
    }
    if (type == 3) {
        for (int i = 0; i < n; i++) {
            ar1[i] = rand() % 10000;
            ar2[i] = ar1[i];
        }

        printf("iii.RANDOM\n");
        sel_sort(ar1, n);
        printf("SELEC\tcomp:%d\tswap:%d\n", comp, swap);
        heap_sort(ar2, n);
        printf("HEAP\tcomp:%d\tswap:%d\n", comp, swap);
    }
}

int main(void) {
    srand(time(NULL));
    int n = 1;

    for (int i = 0; i < 4; i++) {
        n *= 10;

        int *ar1 = (int *)malloc(n * sizeof(int));
        int *ar2 = (int *)malloc(n * sizeof(int));

        printf("N = %d\n", n);
        generate(n, 1, ar1, ar2);
        generate(n, 2, ar1, ar2);
        generate(n, 3, ar1, ar2);
        generate(n, 3, ar1, ar2);
        printf("AVERAGE\n");
        printf("SELEC\tcomp:%.2f\tswap:%.2f\n", (float)av_comp_sel / 4, (float)av_swap_sel / 4);
        printf("HEAPC\tcomp:%.2f\tswap:%.2f\n", (float)av_comp_heap / 4, (float)av_swap_heap / 4);
        av_comp_sel = 0; av_swap_sel = 0;
        av_comp_heap = 0; av_swap_heap = 0;
        printf("--------------------------\n");
    }

    // printf("AVERAGE\n");
    // printf("SELEC\tcomp:%f\tswap:%f\n", av_comp_sel / 4, av_swap_sel / 4);

    return 0;
}