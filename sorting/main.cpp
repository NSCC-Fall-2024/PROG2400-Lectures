#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <span>
#include "bst.h"

using clk = std::chrono::high_resolution_clock;

void track_time(auto desc, void(*f)(std::span<int>), std::span<int> nums) {
    auto start_time = clk::now();
    f(nums);
    const std::chrono::duration<double> span = clk::now() - start_time;
    std::cout << std::setw(15) << desc << ": ";
    std::cout << "time " << span.count() << "s" << std::endl;
}

void fill_array(std::span<int> array) {
    std::random_device rnd;
    std::default_random_engine eng(rnd());
    std::uniform_int_distribution<size_t> dist(1, array.size());
    std::generate(array.begin(), array.end(), [&]() {
      return dist(eng);
    });
}

bool check_sort(std::span<int> nums) {
    for (auto i = 0; i < nums.size() - 1; ++i) {
        if (nums[i] > nums[i + 1]) return false;
    }
    return true;
}

void dump_array(std::span<int> array) {
    for (int i : array) {
        std::cout << std::setw(3) << i;
    }
    std::cout << std::endl;
}

void bubble_sort(std::span<int> array) {

    for (auto i = 0; i < array.size() - 2; i++) {
        for (auto j = 0; j < array.size() - 1 - i; j++) {
            // compare adjacent elements
            if (array[j + 1] < array[j]) {
                // swap the elements if out of order
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

void selection_sort(std::span<int> array) {
    for (auto i = array.begin(); i < array.end(); ++i) {
        auto min = std::min_element(i, array.end());

        if (*min < *i) {
            std::swap(*min, *i);
        }
    }
}

void insertion_sort(std::span<int> array) {
    for (auto i = 1; i < array.size(); i++) {
        // take the current value
        auto temp = array[i];

        // shuffle values greater than ahead of this value
        auto j = i;
        for (; j > 0 && temp < array[j - 1]; j--) {
            array[j] = array[j - 1];
        }

        // insert the current value
        array[j] = temp;
    }
}

void shell_sort(std::span<int> array) {

    for (auto gap = array.size() / 2; gap > 0; gap /= 2) {
        // sort bunch of sub-array that have elements separated by gaps
        for (auto start = 0; start < gap; start++) {

            // insert sort
            for (auto i = start + gap; i < array.size(); i += gap) {
                // take the current value
                auto temp = array[i];

                // shuffle values greater than ahead of this value
                auto j = i;
                for (; j >= gap && temp < array[j - gap]; j -= gap) {
                    array[j] = array[j - gap];
                }

                // insert the current value
                array[j] = temp;
            }
        }
    }
}

auto split(std::span<int> array) {
    // choose the pivot point
    auto pivot = array[0];

    // start searching for numbers less than and greater than the pivot
    auto left = 0;
    auto right = array.size() - 1;

    while (left < right) {
        // search for element less than the pivot
        while (right > 0 && pivot < array[right]) right--;

        // search for element greater than the pivot
        while (left < right && pivot >= array[left]) left++;

        // if two were found out of place, swap them
        if (left < right && array[left] != array[right]) {
            std::swap(array[left], array[right]);
        }
    }

    // now move the pivot point to its location
    array[0] = array[right];
    array[right] = pivot;

    return right;
}

void quick_sort(std::span<int> array) {
    // the array is sorted when it only has zero or one element
    if (array.size() <= 1) return;

    // split the array into two sublists (left and right)
    auto pivot = split(array);

    // sort the left side
    quick_sort(array.subspan(0, pivot));

    // sort the right side
    quick_sort(array.subspan(pivot + 1, array.size() - pivot - 1));
}

void bst_sort(std::span<int> array) {
    BST bst;

    for (int num : array) {
        bst.insert(num);
    }

    bst.save_array(array);
}

int main() {

    for (size_t len = 10; len <= 10000; len *= 10) {
        std::cout << "len = " << len << std::endl;
        auto nums = new int[len];

        //fill_array({nums, len});
        //track_time("bubble sort", bubble_sort, {nums, len});

        //fill_array({nums, len});
        //track_time("selection sort", selection_sort, {nums, len});

        fill_array({nums, len});
        track_time("insertion sort", insertion_sort, {nums, len});

        fill_array({nums, len});
        track_time("shell sort", shell_sort, {nums, len});

        fill_array({nums, len});
        track_time("quick sort", quick_sort, {nums, len});

        fill_array({nums, len});
        track_time("bst sort", bst_sort, {nums, len});

        if (check_sort({nums, len}))
            std::cout << "SUCCESS!" << std::endl;
        else
            std::cout << "FAILED!" << std::endl;

        delete[] nums;
    }

    return 0;
}
