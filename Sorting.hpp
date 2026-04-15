#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Timer.h"
#include <cassert>

using namespace std;


template<typename T, typename Comparator>
void insertionSort(vector<T>& data, Comparator comp){
    // Start at index 1 because a single element by itself is already "sorted"
    for (int i = 1; i < data.size(); i++)
    {
        // Store the current element we want to insert into the sorted portion
        T key = data[i];

        // Start comparing with the element just before i
        int j = i - 1;

        // Move elements in the sorted portion one position to the right
        // as long as they should come after the key
        // comp(key, data[j]) means:
        // "Should key come before data[j]?"
        // If yes, shift data[j] to the right
        while (j >= 0 && comp(key, data[j]))
        {
            data[j + 1] = data[j];
            j--;
        }

        // Insert the key into its correct sorted position
        data[j + 1] = key;
    }
}

template<typename T, typename Comparator>
void merge(vector<T>& data, int left, int mid, int right, Comparator comp)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = data[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = data[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (comp(L[i], R[j]))
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        data[k] = R[j];
        j++;
        k++;
    }
}

template<typename T, typename Comparator>
void mergeSortHelper(vector<T>& data, int left, int right, Comparator comp)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    // THESE MUST CALL mergeSortHelper
    mergeSortHelper(data, left, mid, comp);
    mergeSortHelper(data, mid + 1, right, comp);

    merge(data, left, mid, right, comp);
}

template<typename T, typename Comparator>
void mergeSort(vector<T>& data, Comparator comp)
{
    if (data.empty())
    {
        return;
    }

    mergeSortHelper(data, 0, static_cast<int>(data.size()) - 1, comp);
}