#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_same(){
   double min = 0;
    double max = 0;
    find_minmax({1,1,1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_single(){
   double min = 0;
    double max = 0;
    find_minmax({3}, min, max);
    assert(min == 3);
    assert(max == 3);
}

void test_nothing(){
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 3);
    assert(max == 3);
}

int
main() {
   test_positive();
   test_negative();
   test_same();
   test_single();
}
