#pragma once

// Struct of array with generic array 
typedef struct Array SortedArray;
// function pointer for comparison
typedef int (*Cmp)(void*, void*);


SortedArray* sortedArray_new();

void sortedArray_free(SortedArray* sa);

void sortedArray_insert(SortedArray* sa, void* obj);

void* sortedArray_get(SortedArray* sa, int i);

int sortedArray_size(SortedArray* sa);

void insertion_sort(SortedArray* sa, int n, Cmp compare);

void quick_sort(SortedArray* sa, int p, int u, Cmp compare);
