// Test with int type

#include <stdlib.h>
#include <stdio.h>
#include "unity.h"
#include "sorted.h"


static int* int_new(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;

    return result;
}

static int compare_ints(int* obj1, int* obj2) {
    return *obj1 - *obj2;
}

// Function with a sorted array
static SortedArray* create_objects_int() {
    SortedArray* sa = sortedArray_new();
    sortedArray_insert(sa, int_new(3));
    sortedArray_insert(sa, int_new(5));
    sortedArray_insert(sa, int_new(7));
    sortedArray_insert(sa, int_new(11));

    return sa;
}

// --- Start test empty array  ---

static void sortedArray_zero_elements_int() {
    SortedArray* saIns = sortedArray_new();
    SortedArray* saQuick = sortedArray_new();

    insertion_sort(saIns, sortedArray_size(saIns), (Cmp) compare_ints);
    quick_sort(saQuick, 0, sortedArray_size(saQuick), (Cmp) compare_ints);
    TEST_ASSERT_EQUAL(0, sortedArray_size(saIns));
    TEST_ASSERT_EQUAL(0, sortedArray_size(saQuick));

    sortedArray_free(saIns);
    sortedArray_free(saQuick);
}

// --- End test empty array ---

// --- Start test array with one element ---

static void sortedArray_one_element_int() {
  SortedArray* saIns = sortedArray_new();
  SortedArray* saQuick = sortedArray_new();

  sortedArray_insert(saIns, int_new(3));
  sortedArray_insert(saQuick, int_new(3));

  insertion_sort(saIns, sortedArray_size(saIns), (Cmp) compare_ints);
  quick_sort(saQuick, 0, sortedArray_size(saQuick), (Cmp) compare_ints);

  TEST_ASSERT_EQUAL(1, sortedArray_size(saIns));
  TEST_ASSERT_EQUAL(1, sortedArray_size(saQuick));
  TEST_ASSERT_EQUAL(3, *(int*)sortedArray_get(saIns, 0));
  TEST_ASSERT_EQUAL(3, *(int*)sortedArray_get(saQuick, 0));

  sortedArray_free(saIns);
  sortedArray_free(saQuick);
}

// --- End test array with one element ---

// --- Start test sorted array  ---

static void sortedArray_sorted_elements_int() {
  SortedArray* saIns = create_objects_int();
  SortedArray* saQuick = create_objects_int();

  insertion_sort(saIns, sortedArray_size(saIns), (Cmp) compare_ints);
  quick_sort(saQuick, 0, sortedArray_size(saQuick), (Cmp) compare_ints);

  TEST_ASSERT_EQUAL(3, *(int*) sortedArray_get(saIns, 0));
  TEST_ASSERT_EQUAL(5, *(int*) sortedArray_get(saIns, 1));
  TEST_ASSERT_EQUAL(7, *(int*) sortedArray_get(saIns, 2));
  TEST_ASSERT_EQUAL(11, *(int*) sortedArray_get(saIns, 3));
  TEST_ASSERT_EQUAL(3, *(int*) sortedArray_get(saQuick, 0));
  TEST_ASSERT_EQUAL(5, *(int*) sortedArray_get(saQuick, 1));
  TEST_ASSERT_EQUAL(7, *(int*) sortedArray_get(saQuick, 2));
  TEST_ASSERT_EQUAL(11, *(int*) sortedArray_get(saQuick, 3));

  sortedArray_free(saIns);
  sortedArray_free(saQuick);
}

// --- End test sorted array ---

// --- Start test array (not sorted) ---

static void sortedArray_not_sorted_elements_int() {
  SortedArray* saIns = sortedArray_new();
  SortedArray* saQuick = sortedArray_new();

  sortedArray_insert(saIns, int_new(3));
  sortedArray_insert(saQuick, int_new(3));
  sortedArray_insert(saIns, int_new(2));
  sortedArray_insert(saQuick, int_new(2));
  sortedArray_insert(saIns, int_new(5));
  sortedArray_insert(saQuick, int_new(5));
  sortedArray_insert(saIns, int_new(4));
  sortedArray_insert(saQuick, int_new(4));

  insertion_sort(saIns, sortedArray_size(saIns), (Cmp) compare_ints);
  quick_sort(saQuick, 0, sortedArray_size(saQuick), (Cmp) compare_ints);


  TEST_ASSERT_EQUAL(2, *(int*) sortedArray_get(saIns, 0));
  TEST_ASSERT_EQUAL(3, *(int*) sortedArray_get(saIns, 1));
  TEST_ASSERT_EQUAL(4, *(int*) sortedArray_get(saIns, 2));
  TEST_ASSERT_EQUAL(5, *(int*) sortedArray_get(saIns, 3));
  TEST_ASSERT_EQUAL(2, *(int*) sortedArray_get(saQuick, 0));
  TEST_ASSERT_EQUAL(3, *(int*) sortedArray_get(saQuick, 1));
  TEST_ASSERT_EQUAL(4, *(int*) sortedArray_get(saQuick, 2));
  TEST_ASSERT_EQUAL(5, *(int*) sortedArray_get(saQuick, 3));

  sortedArray_free(saIns);
  sortedArray_free(saQuick);
}

// --- End test array (not sorted) ---

// --- Start test array in invers sorted ---

static void sortedArray_invers_sorted_elements_int() {
  SortedArray* saIns = sortedArray_new();
  SortedArray* saQuick = sortedArray_new();

  sortedArray_insert(saIns, int_new(5));
  sortedArray_insert(saQuick, int_new(5));
  sortedArray_insert(saIns, int_new(4));
  sortedArray_insert(saQuick, int_new(4));
  sortedArray_insert(saIns, int_new(3));
  sortedArray_insert(saQuick, int_new(3));
  sortedArray_insert(saIns, int_new(2));
  sortedArray_insert(saQuick, int_new(2));

  insertion_sort(saIns, sortedArray_size(saIns), (Cmp) compare_ints);
  quick_sort(saQuick, 0, sortedArray_size(saQuick), (Cmp) compare_ints);

  TEST_ASSERT_EQUAL(2, *(int*) sortedArray_get(saIns, 0));
  TEST_ASSERT_EQUAL(3, *(int*) sortedArray_get(saIns, 1));
  TEST_ASSERT_EQUAL(4, *(int*) sortedArray_get(saIns, 2));
  TEST_ASSERT_EQUAL(5, *(int*) sortedArray_get(saIns, 3));
  TEST_ASSERT_EQUAL(2, *(int*) sortedArray_get(saQuick, 0));
  TEST_ASSERT_EQUAL(3, *(int*) sortedArray_get(saQuick, 1));
  TEST_ASSERT_EQUAL(4, *(int*) sortedArray_get(saQuick, 2));
  TEST_ASSERT_EQUAL(5, *(int*) sortedArray_get(saQuick, 3));

  sortedArray_free(saIns);
  sortedArray_free(saQuick);
}

// End test array in invers sorted ---


int main() {
    UNITY_BEGIN();

    RUN_TEST(sortedArray_zero_elements_int);
    RUN_TEST(sortedArray_one_element_int);
    RUN_TEST(sortedArray_sorted_elements_int);
    RUN_TEST(sortedArray_not_sorted_elements_int);
    RUN_TEST(sortedArray_invers_sorted_elements_int);

    UNITY_END();
}
