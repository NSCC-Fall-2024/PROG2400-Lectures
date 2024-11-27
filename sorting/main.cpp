#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <span>
#include <queue>
#include "sorting.h"

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

std::ostream &operator<<(std::ostream &output, std::queue<int> queue) {
    if (queue.empty()) return output;
    while (queue.size() > 1) {
        auto num = queue.front();
        queue.pop();
        output << num << ",";
    }
    output << queue.front();
    return output;
}

std::ostream &operator<<(std::ostream &output, std::span<int> array) {
    if (array.empty()) return output;
    auto i = 0;
    for (; i < array.size() - 1; i++) {
        output << array[i] << ",";
    }
    output << array[i];
    return output;
}

void split(std::queue<int> &in, std::queue<int> &out1, std::queue<int> &out2) {

    auto num_subfiles = 0;

    // keep splitting until all "records" are read
    auto prev = -1;
    while (!in.empty()) {

        // read a record
        auto curr = in.front();
        in.pop();

        // increase the subfile count if a new subfile is detected
        if (curr < prev) num_subfiles++;

        // write out odds and evens
        if (num_subfiles % 2 == 0) {
            out1.push(curr);
        } else {
            out2.push(curr);
        }

        prev = curr;
    }
}

bool elements_in_sublist(std::queue<int> &first, std::queue<int> &second, int last) {
    return !first.empty() && (first.front() >= last);
}

bool elements_in_column(std::queue<int> &first, std::queue<int> &second, int last) {
    return !first.empty() && (first.front() >= last) &&
        (second.empty() || (second.front() < last) || (first.front() < second.front()));
}

bool elements_not_in_current_list(std::queue<int> &first, std::queue<int> &second, int last) {
    return first.empty() || !second.empty() &&
        ((first.front() < last) ||
            ((first.front() > last) && (second.front() < first.front())));
}

auto merge(std::queue<int> &out, std::queue<int> &in1, std::queue<int> &in2) {
    auto num_subfiles = 0;

    // who starts the process?
    auto &first = in2.empty() || (in1.front() < in2.front()) ? in1 : in2;
    auto &second = first == in1 ? in2 : in1;

    // keep merging while there are records left
    while (!in1.empty() || !in2.empty()) {

        auto last = -1;
        while (elements_in_sublist(first, second, last)) {
            // take records from file while they are in order
            do {
                last = first.front();
                first.pop();
                out.push(last);
            } while (elements_in_column(first, second, last));

            // when done taking elements in order
            // switch to other file
            if (elements_not_in_current_list(first, second, last)) {
                std::swap(first, second);
            }
        }

        // move to next subfile
        num_subfiles++;
    }

    return num_subfiles;
}

void merge_sort(std::span<int> array) {

    // copy array to queue
    // think of the queue as a file
    std::queue<int> merged;
    for (auto num : array) {
        merged.push(num);
    }

    // sorting
    std::queue<int> split1, split2;
    auto subfiles = 0;
    do {
        // split
        split(merged, split1, split2);

        std::cout << "Split" << std::endl;
        std::cout << "temp1: " << split1 << std::endl;
        std::cout << "temp2: " << split2 << std::endl;

        // merge
        subfiles = merge(merged, split1, split2);

        std::cout << "Merge" << std::endl;
        std::cout << merged << std::endl;

    } while (subfiles != 1);


    // copy queue back to array
    auto i = 0;
    while (!merged.empty()) {
        array[i++] = merged.front();
        merged.pop();
    }

}

int main() {

#if 0
    for (size_t len = 10; len <= 10000; len *= 10) {
        std::cout << "len = " << len << std::endl;
        auto nums = new int[len];

        fill_array({nums, len});
        track_time("bubble sort", bubble_sort, {nums, len});

        fill_array({nums, len});
        track_time("selection sort", selection_sort, {nums, len});

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
#endif

    auto array = std::to_array({3, 6, 8, 10, 5, 9, 4, 1, 2, 7});

    std::cout << "Unsorted Array" << std::endl;
    std::cout << array << std::endl;

    merge_sort(array);

    std::cout << "Sorted Array" << std::endl;
    std::cout << array << std::endl;

    return 0;
}
