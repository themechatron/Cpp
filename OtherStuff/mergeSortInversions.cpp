#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
 
int merge(int arr[], int temp[], int left, int mid, int right)
{
  int i, j, k;
  int inversions = 0;
  i = left;
  j = mid;
  k = left;
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];
      inversions += (mid - i);
    }
  }
  while (i <= mid - 1)
    temp[k++] = arr[i++];

  while (j <= right)
    temp[k++] = arr[j++];
 
  for (i=left; i <= right; i++)
    arr[i] = temp[i];
 
  return inversions;
}

int mergeSortHelper(int arr[], int temp[], int left, int right)
{
  int mid, inversions = 0;
  if (right > left)
  {
    mid = (right + left)/2;
    inversions = mergeSortHelper(arr, temp, left, mid);
    inversions += mergeSortHelper(arr, temp, mid + 1, right);\
    inversions += merge(arr, temp, left, mid+1, right);
  }
  return inversions;
}

int mergeSort(int arr[], int size)
{
    int *temp = new int[size];
    return mergeSortHelper(arr, temp, 0, size - 1);
}

int main()
{
	int n;
	scanf("%i", &n);
	int *arr = new int[n];
	long temp;
	int size = 0;
	while(size < n && scanf("%li", &temp) == 1)
	{	
		arr[size++] = temp;
	}
	printf("%i\n", mergeSort(arr, size));
}


