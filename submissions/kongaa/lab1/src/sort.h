#ifndef SORT_H
#define SORT_H

extern long long cmp_count;
extern long long mov_count;

void selection_sort(double* arr, int n);
void merge_sort_bottom_up(double* arr, int n);
void fill_array(int n, double* a, int type);

#endif