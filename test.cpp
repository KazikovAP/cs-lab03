#include "histogram.h"
#include "lab03svg.h"

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
    assert(min == 0);
    assert(max == 0);
}

void test_colors(){
size_t bin_count = 0;
vector<string> colors_vec(bin_count);
colors_vec=colors(bin_count);
assert(colors_vec.size() == 0);
}

void test_colors1(){
size_t bin_count = 1;
vector<string> colors_vec(bin_count);
colors_vec=colors(bin_count);
assert(colors_vec[0] == "red");
}

int
main() {
   test_positive();
   test_negative();
   test_same();
   test_single();
   test_nothing();
   test_colors();
   test_colors1();
}
