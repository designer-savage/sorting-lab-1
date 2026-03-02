#include <stdlib.h>
#include "sort.h"

void fill_array(int n, double* a, int type) {
    if (type == 1) {
        // уже отсортирован
        for (int i = 0; i < n; i++)
            a[i] = i;
    }
    else if (type == 2) {
        // обратный
        for (int i = 0; i < n; i++)
            a[i] = n - i;
    }
    else if (type == 3) {
        // случайный
        for (int i = 0; i < n; i++)
            a[i] = rand() % 100;
    }
    else if (type == 4) {
        // другой случайный
        for (int i = 0; i < n; i++)
            a[i] = rand() % 100;
    }
}