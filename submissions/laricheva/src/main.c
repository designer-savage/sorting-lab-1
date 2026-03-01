#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long rnd(void){
    unsigned long long x = 0;
    unsigned long long base = (unsigned long long)RAND_MAX + 1ULL;
    for (int k = 0; k < 5; k++){
        x = x * base + (unsigned long long)rand();
    }
    return x;
}

void gen_array_int(int *a, int n, int param){
    if (param == 1){
        long long offset = (long long)(rnd() % 2000000001ULL) - 1000000000LL;
        for (int i = 0; i < n; i++)
            a[i] = (int)(offset + i);

    } else if (param == 2){
        long long offset = (long long)(rnd() % 2000000001ULL) - 1000000000LL;
        for (int i = 0; i < n; i++)
            a[i] = (int)(offset + (n - 1 - i));

    } else if (param == 3){
        for (int i = 0; i < n; i++){
            int v = (int)(rnd() % 2000000001ULL) - 1000000000;
            a[i] = v;
        }

    } else{
        for (int i = 0; i < n; i++){
            int v = (int)(rnd() % 2001ULL) - 1000;
            a[i] = v;
        }
    }
}

int compare(const void *a, const void *b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

void shakerSort(int *a, int n, long long *comp, long long *swaps){
    int left = 0, right = n - 1;
    int changed = 1;

    while (left < right && changed){
        changed = 0;

        for (int i = left; i < right; i++){
            (*comp)++;
            if (a[i] > a[i + 1]){
                int t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
                (*swaps)++;
                changed = 1;
            }
        }
        right--;

        for (int i = right; i > left; i--){
            (*comp)++;
            if (a[i] < a[i - 1]){
                int t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                (*swaps)++;
                changed = 1;
            }
        }
        left++;
    }
}

void selectionSort(int *a, int n, long long *comp, long long *swaps){
    for (int i = 0; i < n - 1; i++){
        int minI = i;

        for (int j = i + 1; j < n; j++){
            (*comp)++;
            if (a[j] < a[minI])
                minI = j;
        }

        if (minI != i){
            int t = a[i];
            a[i] = a[minI];
            a[minI] = t;
            (*swaps)++;
        }
    }
}

int main(void){
    srand((unsigned)time(NULL));

    int sizes[] = {10, 100, 1000, 10000};

    for (int si = 0; si < 4; si++){
        int n = sizes[si];

        int *orig  = (int*)malloc(n * sizeof(int));
        int *work  = (int*)malloc(n * sizeof(int));
        int *check = (int*)malloc(n * sizeof(int));

        if (!orig || !work || !check){
            printf("Memory alloc error\n");
            free(orig);
            free(work);
            free(check);
            return 1;
        }

        printf("\n============================\n");
        printf("n = %d\n", n);
        printf("============================\n");

        for (int type = 1; type <= 4; type++){

            if (type == 3) srand(12345 + n);
            if (type == 4) srand(54321 + n);

            gen_array_int(orig, n, type);

            memcpy(check, orig, n * sizeof(int));
            qsort(check, n, sizeof(int), compare);

            printf("\nТип массива %d\n", type);

            long long c1 = 0, s1 = 0;
            memcpy(work, orig, n * sizeof(int));
            shakerSort(work, n, &c1, &s1);
            printf("Shaker Sort:    comp = %lld, swaps = %lld, correct = %s\n",
                   c1, s1,
                   (memcmp(work, check, n * sizeof(int)) == 0) ? "YES" : "NO");

            long long c2 = 0, s2 = 0;
            memcpy(work, orig, n * sizeof(int));
            selectionSort(work, n, &c2, &s2);
            printf("Selection Sort: comp = %lld, swaps = %lld, correct = %s\n",
                   c2, s2,
                   (memcmp(work, check, n * sizeof(int)) == 0) ? "YES" : "NO");
        }

        free(orig);
        free(work);
        free(check);
    }

    return 0;
}