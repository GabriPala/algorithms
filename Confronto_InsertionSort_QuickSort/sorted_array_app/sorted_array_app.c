#include "sorted.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#define MAX_BUF_LEN 1024

typedef struct{
  int id;
  char* field1;
  int field2;
  double field3;
}Record;


int compare_first_field(Record* rec1, Record* rec2){
      return strcmp(rec1->field1, rec2->field1);
}

int compare_second_field(Record* rec1, Record* rec2){
      return rec1->field2 - rec2->field2;
}

int compare_third_field(Record* rec1, Record* rec2){
      return rec1->field3 - rec2->field3;
}

void load_data(SortedArray* arrayIns, SortedArray* arrayQuick, char const* filename ) {
    FILE* file = fopen(filename, "r");

    int id;
    char field1[MAX_BUF_LEN];
    int field2;
    double  field3;
    int lineno = 0;

    while(!feof(file)) {
        Record *rec = (Record*) malloc(sizeof(Record));

        assert(file!=NULL);
        int n = fscanf(file, "%d,%1024[^,],%d,%lf", &id, field1, &field2, &field3);
        lineno++;

        if(n != 4) {
            if(feof(file)) {
                continue;
            }

            printf("Error while reading file at line: %d\n", lineno);
            exit(EXIT_FAILURE);
        }

        //if(lineno>900000){
          rec->id = id;
          rec->field1 = strndup(field1, MAX_BUF_LEN);
          rec->field2 = field2;
          rec->field3 = field3;

          sortedArray_insert(arrayIns, rec);
          sortedArray_insert(arrayQuick, rec);
        //}

        /*if(lineno>1000000)
          break;*/
    }

}

void free_data(SortedArray* array) {
    int sizeArray = sortedArray_size(array);
    for(int i=0; i<sizeArray; ++i) {
        Record* rec = sortedArray_get(array, i);
        free(rec->field1);
        free(rec);
    }
    sortedArray_free(array);
}

void print_array(SortedArray* array) {
    int sizeArray = sortedArray_size(array);
    for(int i=0; i< sizeArray; ++i) {
        Record* rec = sortedArray_get(array, i);
        printf("id: %d\tfield1: %10s\tfield2: %10d\tfield3: %10f\n", rec->id, rec->field1, rec->field2, rec->field3);
    }
}

int main(int argc, char const *argv[])
{
    SortedArray* arrayIns = sortedArray_new();
    SortedArray* arrayQuick = sortedArray_new();

    int sizeArrayQuick = sortedArray_size(arrayQuick);
    int sizeArrayIns = sortedArray_size(arrayIns);

    clock_t start = clock();
    load_data(arrayIns, arrayQuick, argv[1]);
    clock_t end = clock();
    printf("Reading =  %f sec. \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    // Start timer for quick sort
    start = clock();
    quick_sort(arrayQuick, 0, sizeArrayQuick, (Cmp) compare_first_field);    // sorted by filed1
    quick_sort(arrayQuick, 0, sizeArrayQuick, (Cmp) compare_second_field);   // sorted by filed2
    quick_sort(arrayQuick, 0, sizeArrayQuick, (Cmp) compare_third_field);    // sorted by filed3
    end = clock();
    printf("Quick Sort execution =  %f sec. \n", ((double)(end - start)) / CLOCKS_PER_SEC);
    // End timer for quick sort

    // Start timer for insertion sort
    start = clock();
    insertion_sort(arrayIns, sizeArrayIns, (Cmp) compare_first_field);    // sorted by filed1
    insertion_sort(arrayIns, sizeArrayIns, (Cmp) compare_second_field);   // sorted by filed2
    insertion_sort(arrayIns, sizeArrayIns, (Cmp) compare_third_field);    // sorted by filed3
    end = clock();
    printf("Insertion Sort execution =  %f sec. \n", ((double)(end - start)) / CLOCKS_PER_SEC);
    // End timer for insertion sort

    // arrayIns e arrayQuick point to the same dataset
    free_data(arrayIns);

    return 0;
}
