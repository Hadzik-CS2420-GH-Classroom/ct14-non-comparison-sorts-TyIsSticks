#include "NonComparisonSorts.h"
#include <iostream>
#include <algorithm>

// ---------------------------------------------------------------------------
// Counting Sort
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: cpp_diagrams.md #1 -- Steps 1a, 1b, 1c (Count Phase)
// ? SEE DIAGRAM: cpp_diagrams.md #2 -- Step 2 (Placement Phase)
//
void counting_sort(std::vector<int>& data) {
    
	if (data.size() <= 1) return; // Already sorted
    
	//   1a. Find the min and max values, and calculate the range (k)
    
	int min_val = *std::min_element(data.begin(), data.end());
	int max_val = *std::max_element(data.begin(), data.end());

	int k = max_val - min_val + 1; // Range of values
    //   1b. Create a count array of size (max - min + 1)

	std::vector<int> count(k, 0);

    //   1c. Count occurrences of each value
    
    for (int num : data) {
        count[num - min_val]++; // Increment the count for this number
	}

    //   2. Overwrite data with sorted values using the counts

	int index = 0;
	for (int i = 0; i < k; ++i) {
        while (count[i] > 0) {
            data[index++] = i + min_val; // Place the value back into data
            count[i]--; // Decrement the count
        }
    }

}

// ---------------------------------------------------------------------------
// Bucket Sort  -- Yippie kayak, other buckets!
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: cpp_diagrams.md #3 -- Steps 1a, 1b (Distribution Phase)
// ? SEE DIAGRAM: cpp_diagrams.md #4 -- Steps 2-3 (Sort + Concatenate)
//
void bucket_sort(std::vector<int>& data, int num_buckets) {
    
	if (data.size() <= 1) return; // Already sorted

    //   1. Find the min and max values to determine bucket ranges
    
	int min_val = *std::min_element(data.begin(), data.end());
	int max_val = *std::max_element(data.begin(), data.end());

	if (min_val == max_val) return; // All values are the same, already sorted. Escape case to avoid division by zero.
    
	int range = max_val - min_val + 1; // Total range of values
	int range_per_bucket = static_cast<int>(std::ceil(static_cast<double>(range) / num_buckets)); // Range of values per bucket
   
    //   2. Create num_buckets empty buckets (vectors)
    
	std::vector<std::vector<int>> buckets(num_buckets);
    
    //   3. Distribute each element into its bucket
    
    for (int num : data) {
        int bucket_index = (num - min_val) / range_per_bucket; // Determine which bucket this number belongs to
        if (bucket_index >= num_buckets) bucket_index = num_buckets - 1; // Handle edge case for max_val
        buckets[bucket_index].push_back(num); // Place the number in the appropriate bucket
    }
    
    //   4. Sort each bucket (use insertion sort or std::sort)
    
	int index = 0; // Index for placing sorted elements back into data
	for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end()); // Sort the bucket using std::sort
        //   5. Concatenate all buckets back into data
        for (int num : bucket) {
            data[index++] = num; // Place sorted numbers back into data
        }
    }
}

// ---------------------------------------------------------------------------
// Radix Sort (LSD)
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: cpp_diagrams.md #5 -- Step 0 + Pass 1 Detail
// ? SEE DIAGRAM: cpp_diagrams.md #6 -- Passes 2-3 (Stability in Action)
//
void radix_sort(std::vector<int>& data) {
    // TODO: Implement radix sort (LSD)
    //   1. Find the maximum value to determine the number of digits
    //   2. For each digit position (ones, tens, hundreds, ...):
    //      a. Use counting sort on that digit
    //   3. After all digit passes, data is sorted
}

// ---------------------------------------------------------------------------
// Utility
// ---------------------------------------------------------------------------
void print_vector(const std::vector<int>& data, const std::string& label) {
    if (!label.empty()) std::cout << label << ": ";
    std::cout << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i];
        if (i + 1 < data.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}
