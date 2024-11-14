#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <span>

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

int main() {

    for (size_t len = 10; len <= 100000; len *= 10) {
        std::cout << "len = " << len << std::endl;
        auto nums = new int[len];

        //fill_array({nums, len});
        //track_time("bubble sort", bubble_sort, {nums, len});

        fill_array({nums, len});
        track_time("selection sort", selection_sort, {nums, len});

        fill_array({nums, len});
        track_time("insertion sort", insertion_sort, {nums, len});
        if (check_sort({nums, len}))
            std::cout << "SUCCESS!" << std::endl;
        else
            std::cout << "FAILED!" << std::endl;

        delete[] nums;
    }

    return 0;
}
