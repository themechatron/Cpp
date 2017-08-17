#include <stdio.h>
#include <iostream>

template <typename ArrayType>
void insertionSort(ArrayType* arr, int left, int right)
{
	for(size_t i = left + 1; i < right; i++)
	{
		ArrayType key = arr[i];
		int j = i - 1;
		while(j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

template <typename ArrayType>
int partition(ArrayType* arr, int left, int right)
{
	int startIdx = left;
	ArrayType pivot = arr[right];
	for(size_t i = left; i < right; ++i)
	{
		if(arr[i] <= pivot)
		{
			std::swap(arr[startIdx], arr[i]);
			startIdx++;
		}
	}
	std::swap(arr[right], arr[startIdx]);
	return startIdx;
}

template <typename ArrayType>
void quicksort(ArrayType* arr, int left, int right)
{
	if(left >= right)
	{
		return;
	}
	if(right - left <= 15)
	{
		insertionSort(arr, left, right - 1);
	}
	else
	{
		int pivotIdx = partition(arr, left, right - 1);
		if(left < pivotIdx - 1)
		{
			quicksort(arr, left, pivotIdx - 1);
		}
		if(pivotIdx < right)
		{
			quicksort(arr, pivotIdx, right - 1);
		}
	}
}

int main()
{
	return 0;
}
