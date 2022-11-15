 #include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <string.h>
#include<windows.h>    
#include<sstream>
#include<unistd.h>
using namespace std;
#define RANGE 255

void printArray(int arr[], int n);

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void countSort(char arr[])
{
    // The output character array
    // that will have sorted arr
    char output[strlen(arr)];
  
    // Create a count array to store count of individual
    // characters and initialize count array as 0
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));
  
    // Store count of each character
    for (i = 0; arr[i]; ++i)
        ++count[arr[i]];
  
    // Change count[i] so that count[i] now contains actual
    // position of this character in output array
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i - 1];
  
    // Build the output character array
    for (i = 0; arr[i]; ++i) {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }
  
    // Copy the output array to arr, so that arr now
    // contains sorted characters
    for (i = 0; arr[i]; ++i)
        arr[i] = output[i];
}


// size n using bucket sort
void bucketSort(float arr[], int n)
{
      
    // 1) Create n empty buckets
    vector<float> b[n];
  
    // 2) Put array elements 
    // in different buckets
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }
  
    // 3) Sort individual buckets
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());
  
    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

// C++ implementation of Radix Sort

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i
        = (low
           - 1); // Index of smaller element and indicates
                 // the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
  
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
  
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int N, int i)
{
    // Find largest among root, left child and right child
 
    // Initialize largest as root
    int largest = i;
 
    // left = 2*i + 1
    int left = 2 * i + 1;
 
    // right = 2*i + 2
    int right = 2 * i + 2;
 
    // If left child is larger than root
    if (left < N && arr[left] > arr[largest])
 
        largest = left;
 
    // If right child is larger than largest
    // so far
    if (right < N && arr[right] > arr[largest])
 
        largest = right;
 
    // Swap and continue heapifying if root is not largest
    // If largest is not root
    if (largest != i) {
 
        swap(&arr[i], &arr[largest]);
 
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}
 
// Main function to do heap sort
void heapSort(int arr[], int N)
{
 
    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)
 
        heapify(arr, N, i);
 
    // Heap sort
    for (int i = N - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
 
        // Heapify root element to get highest element at
        // root again
        heapify(arr, i, 0);
    }
}


// Merge two subarrays L and M into arr
void merge(int arr[], int p, int q, int r) {
  
  // Create L ? A[p..q] and M ? A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}


// C program for implementation of Bubble sort

 
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
 
 
 
 	void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
    	printArray(arr, n);
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1], 
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
// A utility function to print an array
// of size n
void printArray(int arr[], int n)
{
  	sleep(1);
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}





 
// Driver code
int main()
{
	string str;
      stringstream ss;
	  int arr[28],i=0;
	ifstream int_file("int.txt");
		ifstream float_file("float.txt");
	ifstream word_file("words.txt");

	    clock_t t;
	    char arr3[20];
	    float arr2[22];
    //int arr[] = { 12, 11, 13, 5, 6 };
    //float arr2[] = { 0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int choice,choice2;
    double	 time_taken=0;
    cout<<"\n1:insertion Sort\n2:bubble Sort\n3:merge Sort\n4:heap Sort\n5:quick Sort\n6:radix sort\n7:bucket Sort\n8:count Sort\n9:\n10:\n";
    cout<<"\nPlease select a sorting algorithm: ";
     cin>>choice;
    cout<<"\n1:integer file\n2:float file\n3:word file\n";
        cout<<"\nPlease select a an input file: ";
         cin>>choice2;
         
         
         if(choice2==1)
         {
         	 if (!int_file.is_open())
    {
        std::cout << "File Not Open" << '\n';
        exit(0);

    }

 while (int_file.good())
            {
                getline(int_file,str,',');
                istringstream(str)>>arr[i];
                i++;

        
                }

                
                    cout<<"\nThe input sample is: ";

            for(int j=0;j<i;j++)
            {
            	cout<<arr[j];
                cout<<",";

			}
		 }

    if(choice2==2)
         {
     if (!float_file.is_open())
    {
        std::cout << "File Not Open" << '\n';
        exit(0);

    }
i=0;
 while (float_file.good())
            {
                getline(float_file,str,',');
                istringstream(str)>>arr2[i];
                i++;

        
                }

                
           cout<<"\nThe input sample is: ";

            for(int j=0;j<i;j++)
            {
            	cout<<",";

            	cout<<arr2[j];
			}
			cout<<"\n";
		}
		
		
		if(choice2==3)
         {
     if (!word_file.is_open())
    {
        std::cout << "File Not Open" << '\n';
        exit(0);

    }
i=0;
 while (word_file.good())
            {
                getline(word_file,str,',');
//                istringstream(str)>>arr3[i];
//                i++;

        
                }
                           cout<<"\nThe input sample is: ";

                        cout<<str;
                        			cout<<"\n";


                for (int p = 0; p < 20; p++) {
        arr3[i] = str.at(i);
        //cout << ch << " ";
    }

            
			cout<<"\n";
		}

            int_file.close();
                        float_file.close();


        t = clock();
        
    switch(choice)
    {
    	case 1:
    		cout<<"\nThe insertion Sort is\n";
    insertionSort(arr, n);
    printArray(arr, n);
    t = clock() - t;
    time_taken = (((double)t)/CLOCKS_PER_SEC)-n*1; // in seconds
    printf("The algo took %f seconds to execute \n", time_taken);
    		break;
    		
    		case 2:
   	cout<<"The bubble Sort is\n";
     bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    t = clock() - t;
    time_taken = (((double)t)/CLOCKS_PER_SEC)-n*1; // in seconds
    printf("The algo took %f seconds to execute \n", time_taken);
    		break;
    		
    		case 3:
   	cout<<"The merge Sort is\n";
   	mergeSort(arr, 0, n - 1);
    cout << "Sorted array: \n";
    printArray(arr, n);
    t = clock() - t;
    time_taken = (((double)t)/CLOCKS_PER_SEC)-n*1; // in seconds
    printf("The algo took %f seconds to execute \n", time_taken);
    		break;
    		
    		case 4:
	cout<<"The heapSort is\n";
    heapSort(arr, n);
    printf("\nSorted array is\n");
    printArray(arr, n);
    t = clock() - t;
    time_taken = (((double)t)/CLOCKS_PER_SEC)-n*1; // in seconds
    printf("The algo took %f seconds to execute \n", time_taken);
    		break;
    		
    		case 5:
    cout<<"\nThe quickSort is\n";
    quickSort(arr, 0, n - 1);
    cout << "Sorted array: \n";
    printArray(arr, n);
    		break;
    		
    		case 6:
    cout<<"\nThe radixsort is\n";
    radixsort(arr, n);
    printArray(arr, n);
    t = clock() - t;
    time_taken = (((double)t)/CLOCKS_PER_SEC)-n*1; // in seconds
    printf("The algo took %f seconds to execute \n", time_taken);
    		break;
    		
    		case 7:
    bucketSort(arr2, n);
    cout<<"\nThe bucketSorted array is: ";
for (int i = 0; i < n; i++)
        cout << arr2[i] << " ";
    		break;
    		
    		case 8:
    cout<<"The countSort is\n";
    countSort(arr3);
    cout << "Sorted character array is " << arr3;
    		break;
    		
    		case 9:
    		break;
    		
    		case 10:
    		break;
	}
	    

    
    
    
    
    
    
    
    
 
    return 0;
}

