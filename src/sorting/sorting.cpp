#include "sorting.h"

#include <cstdlib>
// modern C++11 way of generating random numbers
#include <random>

template <typename T>
std::ostream& operator<<(std::ostream& os, vector<T> vec)
{
    ssize_t size = vec.size();
    
    os << "[";
    for (int i = 0; i < size; i++) {
        os << vec[i];
        if (i < size - 1)
            os << ", ";
    }
    
    os << "]" << endl;

    return os;
}

// sort an integer array using STL
void sortArraySTL(int arr[], int size)
{
    std::sort(arr, arr + size);
}

void sortArraySTL(int arr[], int size, std::function<bool(int,int)> compare_fn)
{
    std::sort(arr, arr + size, compare_fn);
}

// O(n^2)
vector<int> bubbleSort(vector<int> vec)
{
    int n = vec.size(); // run the comparisons up to n
    int lastSwapped = -1;
    for (int i = 0; i < n - 1; i++) {
        cout << "bubble sort, i: " << i << ", n: " << n << endl;
        for (int j = 0; j < n - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                lastSwapped = j + 1; // sorted till n
            }
        }
        n = lastSwapped;
    }
    
    return vec;
}

// O(n^2)
vector<int> selectionSort(vector<int> vec)
{
    
    // run from current index = 0 to n - 1
    // find the smallest in the array and swap it with the current index
    int i, j;
    for (i = 0; i < vec.size() - 1; i++) {
        int minIndex = i;
        for (j = i + 1; j < vec.size(); j++) {
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(vec[i], vec[minIndex]);
    }
    
    return vec;
}

// O(n^2)
vector<int> insertionSort(vector<int> vec)
{
    for (int i = 1; i < vec.size(); i++) {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        
        vec[j + 1] = key;
    }
    
    return vec;
}

vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    int i = 0;
    int j = 0;
    
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        } else if (right[j] < left[i]) {
            result.push_back(right[j]);
            j++;
        }
    }
    
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    
    return result;
}

vector<int> merge(vector<int> &vec, int low, int mid, int high)
{
    // left low - mid
    // right mid + 1 - high
    vector<int> left;
    vector<int> right;

    if (low == high) {
        return vec;
    }

    for (int i = low; i <= mid; i++) {
        left.push_back(vec[i]);
    }
    
    for (int i = mid + 1; i <= high; i++) {
        right.push_back(vec[i]);
    }
    
    int i = 0;
    int j = 0;
    int k = low;
    
    while (i <= mid - low && j < high - mid) {
        if (left[i] <= right[j]) {
            vec[k] = left[i];
            k++, i++;
        } else if (right[j] < left[i]) {
            vec[k] = right[j];
            k++, j++;
        }
    }
    
    while (i <= mid - low) {
        vec[k] = left[i];
        k++, i++;
    }
    
    while (j < high - mid) {
        vec[k] = right[j];
        k++, j++;
    }
    
    return vec;
}

vector<int> splitMerge(vector<int> &vec, int p, int q)
{
    if (q > p) {
        int r = (p + q) / 2;
    
        splitMerge(vec, p, r);
        splitMerge(vec, r + 1, q);
        merge(vec, p, r, q);
    }
    
    return vec;
}

// time: O(nlogn), space O(n)
vector<int> mergeSort(vector<int> vec)
{
    return splitMerge(vec, 0, vec.size() - 1);
}

vector<int> interSectionSortedArrays(vector<int> vec1, vector<int> vec2)
{
    vector<int> result;
    int i = 0;
    int j = 0;
    
    while (i < vec1.size() && j < vec2.size()) {
            if (i > 0 && vec1[i] == vec1[i - 1]) {
                i++;
                continue;
            }
            
            if (j > 0 && vec2[j] == vec2[j - 1]) {
                j++;
                continue;
            }
                
            if (vec1[i] < vec2[j]) {
                i++;
            } else if (vec1[i] > vec2[j]) {
                j++;
            } else {
                result.push_back(vec1[i]);
                i++;
                j++;
            }
    }
    
    return result;
}

// find the union of two sorted arrays
vector<int> unionSortedArrays(vector<int> vec1, vector<int> vec2)
{
    vector<int> result;
    int i = 0;
    int j = 0;
    
    while (i < vec1.size() && j < vec2.size()) {
        if (i > 0 && vec1[i] == vec1[i - 1]) {
            i++;
            continue;
        }
        
        if (j > 0 && vec2[j] == vec2[j - 1]) {
            j++;
            continue;
        }
        
        if (vec1[i] < vec2[j]) {
            result.push_back(vec1[i]);
            i++;
        } else if (vec1[i] > vec2[j]) {
            result.push_back(vec2[j]);
            j++;
        } else {
            result.push_back(vec1[i]);
            i++;
            j++;
        }
    }
    
    while (i < vec1.size()) {
        if (i > 0 && vec1[i] == vec1[i - 1]) {
            i++;
            continue;
        }
            
        result.push_back(vec1[i]);
        i++;
    }
    
    while (j < vec2.size()) {
        if (j > 0 && vec2[j] == vec2[j - 1]) {
            j++;
            continue;
        }
            
        result.push_back(vec2[j]);
        j++;
    }
    
    return result;
}

int countAndMerge(vector<int> &vec, int low, int mid, int high)
{
    vector<int> left;
    vector<int> right;
    
    int result = 0;
    // {4, 3, 2, 1}
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    for (int i = 0; i < n1; i++) {
        left.push_back(vec[i + low]);
    }
    
    for (int i = 0; i < n2; i++) {
        right.push_back(vec[i + mid + 1]);
    }
    
    int i = 0, j = 0, k = low;
    
    while (i < n1 && j < n2) {
        //
        if (left[i] > right[j]) {
            // left[i] and all elements at index greater than i are greater than the right element 
            vec[k] = right[j];
            result += n1 - i;
            j++, k++;
        } else {
            vec[k] = left[i];
            i++, k++;
        }
    }
    
    while (i < n1) {
        vec[k] = left[i];
        i++, k++;
    }
    
    while (j < n2) {
        vec[k] = right[j];
        j++, k++;
    }
    
    return result;
}

int countInversionsHelper(vector<int> &vec, int p, int q)
{
    int result = 0;
    
    if (q > p) {
        int r = p + (q - p) / 2;
        result += countInversionsHelper(vec, p, r);
        result += countInversionsHelper(vec, r + 1, q);
        
        return result + countAndMerge(vec, p, r, q);
    }
    
    return 0;
}

// count inversions. Inversion is condition where a[i] > a[j] for i < j
int countInversions(vector<int> vec)
{
    return countInversionsHelper(vec, 0, vec.size() - 1);
}

// Pronun: lom -you - tow
// take last element as pivot
// parition an array between low and high indices 
// the left part contains elements smaller than arr[pivot] 
// the right part contains elements equal or greater than arr[pivot]
int lomutoPartition(vector<int> &vec, int l, int h)
{
    // 5
    // {1, 3, 2, 4, 5, 6, 9, 8, 7} //
    // from l to i -> smallest
    // from i + 1 -> pivot
    // i = -1
    // seeder, generate an initial random value
    static std::random_device rand_device;
    // engine (generator)
    static std::mt19937 rand_engine(rand_device());
    // distribution, takes input from random engine and shapes it up into a distribution
    std::uniform_int_distribution<int> random_pivot(l, h); 
    
    auto pivotIndex = random_pivot(rand_engine);
    
    // swap it to the last element
    swap(vec[pivotIndex], vec[h]);
    
    int i = l - 1;
    int pivot = vec[h];
    
    for (int j = l; j <= h - 1; j++) {
        if (vec[j] < pivot) {
            i++; // less item found
            std::swap(vec[i], vec[j]);
        }
    }
    
    std::swap(vec[i + 1], vec[h]);
 
    return i + 1;
}

// parition an array between low and high indices around the index 
// the left part contains elements smaller than arr[pivot] 
// the right part contains elements equal or greater than arr[pivot]
int lomutoPartitionAt(vector<int> &vec, int l, int h, int index)
{
    // swap the index with last index element and then invoke
    // lomutoPartition
    swap(vec[index], vec[vec.size() - 1]);
    return lomutoPartition(vec, l, h);
}

// takes first element as pivot
// smaller elements on the left side of its pivot
// larger or equal elements on the right side of its pivot
int hoarePartition(vector<int> &vec, int l, int h)
{
    int i = l - 1; // index of element less than or equal to pivot
    int j = h + 1; // index of element greater than pivot
    
    int randPivot = l + rand() % (h - l);
    swap(vec[l], vec[randPivot]);
    
    int pivot = vec[l];
    
    while (i < j) {
        do {
            i++;
        } while (vec[i] < pivot);
        do {
            j--;
        } while (vec[j] > pivot);
        
        if (i >= j) {
            break;
        }
        
        swap(vec[i], vec[j]);
    }
    
    return j;
}

// n
// 0 to p - 1    p + 1 n (n-1)
// n - 2 times

void qSortLomuto(vector<int> &vec, int l, int h)
{
    if (l < h) {
        int p = lomutoPartition(vec, l, h); // p is sorted, now sort 0 to p - 1 and p + 1 to h
        qSortLomuto(vec, l , p - 1);
        qSortLomuto(vec, p + 1, h);
    }
}

void qSortHoare(vector<int> &vec, int l, int h)
{
    // 3, 4, 5, 2, 1
    //2, 1 4, 5, 3
    // partition at j
    if (l < h) {
        int p = hoarePartition(vec, l, h);
        // l to p - 1 are less than pivot (first element)
        // p to h are greater than or equal to pivot
        qSortHoare(vec, l , p);
        qSortHoare(vec, p + 1, h);
    }
}
