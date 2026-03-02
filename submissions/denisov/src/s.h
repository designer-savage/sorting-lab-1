#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int comp;
extern int swap;
extern int av_comp_sel;
extern int av_comp_heap;
extern int av_swap_sel;
extern int av_swap_heap;

int compare(const void *a, const void *b);
int compare_rev(const void *a, const void *b);

void nullify(void);
void sw(int *a, int *b);
void arr_pr(int *arr, int n);

void sel_sort(int *arr, int n);
void heapify(int *arr, int n, int i);
void heap_sort(int *arr, int n);

void generate(int n, int type, int *ar1, int *ar2);

#endif // SORTING_H