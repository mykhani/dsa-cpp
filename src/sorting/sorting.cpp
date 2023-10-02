#include "sorting.h"

#include <cstdlib>
// modern C++11 way of generating random numbers
#include <random>

template <typename T>
std::ostream &operator<<(std::ostream &os, vector<T> vec)
{
    ssize_t size = vec.size();

    os << "[";
    for (int i = 0; i < size; i++)
    {
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

void sortArraySTL(int arr[], int size, std::function<bool(int, int)> compare_fn)
{
    std::sort(arr, arr + size, compare_fn);
}

// O(n^2)
vector<int> bubbleSort(vector<int> vec)
{
    int n = vec.size(); // run the comparisons up to n
    int lastSwapped = -1;
    for (int i = 0; i < n - 1; i++)
    {
        cout << "bubble sort, i: " << i << ", n: " << n << endl;
        for (int j = 0; j < n - 1; j++)
        {
            if (vec[j] > vec[j + 1])
            {
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
    for (i = 0; i < vec.size() - 1; i++)
    {
        int minIndex = i;
        for (j = i + 1; j < vec.size(); j++)
        {
            if (vec[j] < vec[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(vec[i], vec[minIndex]);
    }

    return vec;
}

// O(n^2)
void InsertionSort(vector<int> &arr)
{
    // imagine the first index is sorted
    int size = arr.size();
    // insertionIndex = index of number to insert
    for (int insertionIndex = 1; insertionIndex < size; insertionIndex++)
    {
        int possibleIndex = insertionIndex;
        int insertionValue = arr[insertionIndex];

        while (possibleIndex > 0 && (arr[possibleIndex] < arr[possibleIndex - 1]))
        {
            arr[possibleIndex] = arr[possibleIndex - 1];
            possibleIndex--;
            arr[possibleIndex] = insertionValue;
        }
    }
}

vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    int i = 0;
    int j = 0;

    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            result.push_back(left[i]);
            i++;
        }
        else if (right[j] < left[i])
        {
            result.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size())
    {
        result.push_back(left[i]);
        i++;
    }

    while (j < right.size())
    {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

vector<int> interSectionSortedArrays(vector<int> vec1, vector<int> vec2)
{
    vector<int> result;
    int i = 0;
    int j = 0;

    while (i < vec1.size() && j < vec2.size())
    {
        if (i > 0 && vec1[i] == vec1[i - 1])
        {
            i++;
            continue;
        }

        if (j > 0 && vec2[j] == vec2[j - 1])
        {
            j++;
            continue;
        }

        if (vec1[i] < vec2[j])
        {
            i++;
        }
        else if (vec1[i] > vec2[j])
        {
            j++;
        }
        else
        {
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

    while (i < vec1.size() && j < vec2.size())
    {
        if (i > 0 && vec1[i] == vec1[i - 1])
        {
            i++;
            continue;
        }

        if (j > 0 && vec2[j] == vec2[j - 1])
        {
            j++;
            continue;
        }

        if (vec1[i] < vec2[j])
        {
            result.push_back(vec1[i]);
            i++;
        }
        else if (vec1[i] > vec2[j])
        {
            result.push_back(vec2[j]);
            j++;
        }
        else
        {
            result.push_back(vec1[i]);
            i++;
            j++;
        }
    }

    while (i < vec1.size())
    {
        if (i > 0 && vec1[i] == vec1[i - 1])
        {
            i++;
            continue;
        }

        result.push_back(vec1[i]);
        i++;
    }

    while (j < vec2.size())
    {
        if (j > 0 && vec2[j] == vec2[j - 1])
        {
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

    for (int i = 0; i < n1; i++)
    {
        left.push_back(vec[i + low]);
    }

    for (int i = 0; i < n2; i++)
    {
        right.push_back(vec[i + mid + 1]);
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2)
    {
        //
        if (left[i] > right[j])
        {
            // left[i] and all elements at index greater than i are greater than the right element
            vec[k] = right[j];
            result += n1 - i;
            j++, k++;
        }
        else
        {
            vec[k] = left[i];
            i++, k++;
        }
    }

    while (i < n1)
    {
        vec[k] = left[i];
        i++, k++;
    }

    while (j < n2)
    {
        vec[k] = right[j];
        j++, k++;
    }

    return result;
}

int countInversionsHelper(vector<int> &vec, int p, int q)
{
    int result = 0;

    if (q > p)
    {
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

void MergeSort(vector<int> &arr)
{
    function<void(int, int, int)> mergeHelper = [&](int start, int mid, int end)
    {
        /* create copies of left and right halves */
        vector<int> left(arr.begin() + start, arr.begin() + mid + 1);
        vector<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);

        // next item to fetch from left or right subarrays
        int left_i = 0;
        int right_i = 0;
        int merged_i = start;

        while (left_i < left.size() && right_i < right.size())
        {
            if (left[left_i] <= right[right_i])
            {
                arr[merged_i++] = left[left_i++];
            }
            else if (right[right_i] < left[left_i])
            {
                arr[merged_i++] = right[right_i++];
            }
        }

        while (left_i < left.size())
        {
            arr[merged_i++] = left[left_i++];
        }

        while (right_i < right.size())
        {
            arr[merged_i++] = right[right_i++];
        }
    };

    function<void(int, int)> mergeSortHelper = [&](int start, int end)
    {
        if (start == end)
        {
            return;
        }

        int mid = (start + end) / 2;

        mergeSortHelper(start, mid);
        mergeSortHelper(mid + 1, end);
        mergeHelper(start, mid, end);
    };

    mergeSortHelper(0, arr.size() - 1);
}

/* pivot is the element at the correct index in the final sorted array
   the element at a correct index has leftward elements smaller and
   rightward elements greater

   Pivot can be chosen either as:
   1. the first element in the array
   2. the last element in the array
   3. chosen as random (randomly select an index and swap it with either first or last
      element and follow the algorithm in above two methods)
*/
void QuickSort(vector<int> &arr)
{
    function<void(int, int)> quickSortHelper = [&](int start, int end)
    {
        if (start >= end)
            return;

        /* last element as pivot */
        // int pivotValue = arr[end];
        // int p = start;

        // for (int i = start; i < end; i++)
        // {
        //     if (arr[i] < pivotValue)
        //     {
        //         std::swap(arr[p], arr[i]);
        //         p++;
        //     }
        // }

        // std::swap(arr[p], arr[end]);

        /* first element as pivot */
        int pivotValue = arr[start];
        int p = end;

        for (int i = end; i > start; i--)
        {
            if (arr[i] > pivotValue)
            {
                std::swap(arr[i], arr[p]);
                p--;
            }
        }

        std::swap(arr[p], arr[start]);

        quickSortHelper(start, p - 1);
        quickSortHelper(p + 1, end);
    };

    quickSortHelper(0, arr.size() - 1);
}
