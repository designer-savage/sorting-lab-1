#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

extern long long cmp_count;
extern long long mov_count;

static void copy_array(int n, double* dst, double* src) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

int main(void) {
    srand((unsigned)time(NULL));

    int sizes[] = { 10, 100, 1000, 10000 };
    int types[] = { 1, 2, 3, 4 };
    int runs = 5; // dlya usredneniya

    printf("--------------------------------------------------------------------------\n");
    printf("|   n   | param |   1  |   2  |   3  |   4  |  avg  |\n");
    printf("--------------------------------------------------------------------------\n");

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];

        double* orig = malloc(n * sizeof(double));
        double* a = malloc(n * sizeof(double));

        long long cmp_vals[4];
        long long mov_vals[4];

        // ===== Selection =====
        for (int t = 0; t < 4; t++) {
            long long cmp_sum = 0, mov_sum = 0;

            for (int r = 0; r < runs; r++) {
                fill_array(n, orig, types[t]);
                copy_array(n, a, orig);

                cmp_count = 0;
                mov_count = 0;

                selection_sort(a, n);

                cmp_sum += cmp_count;
                mov_sum += mov_count;
            }

            cmp_vals[t] = cmp_sum / runs;
            mov_vals[t] = mov_sum / runs;
        }

        long long cmp_avg = (cmp_vals[0] + cmp_vals[1] + cmp_vals[2] + cmp_vals[3]) / 4;
        long long mov_avg = (mov_vals[0] + mov_vals[1] + mov_vals[2] + mov_vals[3]) / 4;

        printf("| %5d | cmp   | %4lld | %4lld | %4lld | %4lld | %5lld |\n",
            n, cmp_vals[0], cmp_vals[1], cmp_vals[2], cmp_vals[3], cmp_avg);

        printf("|       | mov   | %4lld | %4lld | %4lld | %4lld | %5lld |\n",
            mov_vals[0], mov_vals[1], mov_vals[2], mov_vals[3], mov_avg);

        printf("--------------------------------------------------------------------------\n");

        // ===== Merge =====
        for (int t = 0; t < 4; t++) {
            long long cmp_sum = 0, mov_sum = 0;

            for (int r = 0; r < runs; r++) {
                fill_array(n, orig, types[t]);
                copy_array(n, a, orig);

                cmp_count = 0;
                mov_count = 0;

                merge_sort_bottom_up(a, n);

                cmp_sum += cmp_count;
                mov_sum += mov_count;
            }

            cmp_vals[t] = cmp_sum / runs;
            mov_vals[t] = mov_sum / runs;
        }

        cmp_avg = (cmp_vals[0] + cmp_vals[1] + cmp_vals[2] + cmp_vals[3]) / 4;
        mov_avg = (mov_vals[0] + mov_vals[1] + mov_vals[2] + mov_vals[3]) / 4;

        printf("| %5d | cmp   | %4lld | %4lld | %4lld | %4lld | %5lld |\n",
            n, cmp_vals[0], cmp_vals[1], cmp_vals[2], cmp_vals[3], cmp_avg);

        printf("|       | mov   | %4lld | %4lld | %4lld | %4lld | %5lld |\n",
            mov_vals[0], mov_vals[1], mov_vals[2], mov_vals[3], mov_avg);

        printf("--------------------------------------------------------------------------\n");

        free(orig);
        free(a);
    }

    return 0;
}