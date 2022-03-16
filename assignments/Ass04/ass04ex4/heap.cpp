// #include <stdio.h>
// #include <iostream>
// #include <cstdlib>
#include <bits/stdc++.h>
#include "heap.h"
using std::cin;
using std::cout;

template <class T>
T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template <class T>
int AList<T>::getlength(void)
{
    return numitems;
}

template <class T>
void AList<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "in setitem [index=" << index << "] Index error: index out or range\n";
}

template <class T>
T AList<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "in getitem [index=" << index << "]Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template <class T>
void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template <class T>
void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j + 1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template <class T>
void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template <class T>
void AList<T>::remove(int index)
{
    // cout << "remove index=" << index + 1 << " with value " << this->getitem(index) << "\n";
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j - 1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "In remove[index=" << index << "]Index error: list index out of range\n";
}

template <class T>
void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template <class T>
void AList<T>::concat(AList<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template <class T>
bool AList<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template <class T>
bool AList<T>::equal(AList<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template <class T>
bool AList<T>::sublist(AList<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else if (j == numitems - 1)
        {
            result = false;
            break;
        }
        else
            ++j;
    }
    return result;
}

// build the max heap using elements in the input array.
template <class T>
void MaxHeap<T>::build_heap(AList<T> &array)
{
    // put your code below
    // cout << "In build_heap\n";
    while(this->getlength() != 0)   // make sure the heap is initially empty
        this->remove(1);
    int numELm = array.getlength();
    for (int i = 1; i <= numELm; i++) // Assign each element in array[] into the "rough" heap
    {
        this->append(array.getitem(i));
    }
    for (int i = numELm / 2; i >= 1; i--)
    {
        this->sift_down(i, numELm);
    }
    // cout << "After building:\n";
    // this->print_elements();
}

// sift down the element with index i within the first num_elements elements.
template <class T>
void MaxHeap<T>::sift_down(int i, int num_elements) // i.e. HEAPIFY in the textbook
{
    // put your code below
    // cout << "sift_down i = " << i << ", num_elements = " << num_elements << "\n";
    int eleIndex = i;
    int eleLeft = 2 * i;
    int eleRight = 2 * i + 1;
    int largest = i; // Index of the largest element

    if (eleLeft <= num_elements) // compare the i-th element with its left child
    {
        if (this->getitem(eleLeft) > this->getitem(i))
        {
            largest = eleLeft;
        }
    }
    if (eleRight <= num_elements) // compare with the right child
    {
        if (this->getitem(eleRight) > this->getitem(largest))
        {
            largest = eleRight;
        }
    }
    if (largest != i) // the subtree beginning with i-th element does not satisfy properties of a max-heap
    {
        this->swap(i, largest); // Put i-th element to the correct place
        this->sift_down(largest, num_elements);
    }
}

// sort the input array using max heap.
template <class T>
void MaxHeap<T>::heap_sort(AList<T> &array)
{
    // put your code below
    this->build_heap(array); // build the heap
    AList<T> sortedList; // Store the sorted list
    while (this->getlength() != 0)
    {
        int i = this->getlength();             // i denotes the index of current end of the heap
        sortedList.append(this->getitem(1));   // Put the maximum into the sorted list
        this->swap(1, i);                      // Put the root to the end; now the last node is the maximum
        this->remove(i);                       // Remove the last element
        this->sift_down(1, this->getlength()); // Heapify again
        // cout << "New heap:\n";
        // this->print_elements();
    }

    for (int i = 1; i <= sortedList.getlength(); i++) // Store the new list back into the heap list
    {
        this->append(sortedList.getitem(i));
    }
    return;
}

// swap elements with indices i and j.
template <class T>
void MaxHeap<T>::swap(int i, int j)
{
    // put your code below
    // The classic swapping method
    // t<-a, a<-b, b<-t
    // cout << "In swap: i, j = " << i << " <-> " << j << "\n";
    T temp = this->getitem(i);
    this->setitem(i, this->getitem(j));
    this->setitem(j, temp);
}

// return the root element.
template <class T>
T MaxHeap<T>::max()
{
    // put your code below
    // The maximum is now at the root node
    if (this->getlength() == 0)
    {
        cout << "EMPTY HEAP\n";
        exit(EXIT_SUCCESS);
    }

    return this->getitem(1);
}

// print all elements in the heap in sequential order.
template <class T>
void MaxHeap<T>::print_elements()
{
    //  cout << "Print elements:\n";
    int n = this->getlength();
    for (int i = 1; i <= n; i++)
    {
        cout << this->getitem(i) << "\n";
    }
}

int main()
{
    freopen("heap.in", "r", stdin);
    freopen("heap.out", "w", stdout);

    AList<int> input_array;
    int elm;    
    while(scanf("%d", &elm) != EOF)
    {
        input_array.append(elm);
    }

    MaxHeap<int> max_heap;
    max_heap.build_heap(input_array);
    cout << max_heap.max() << "\n";
    
    max_heap.heap_sort(input_array);
    max_heap.print_elements();

    return 0;
}

/*  ORIGINAL VERSION OF TEST CODE:

    cout << "\npart1 test\n";
    // please feel free to add more test cases
    int input_list[10] = {5, 3, 9, 46, 15, 22, 91, 8, 29, 77};
    AList<int> input_array;
    for (int i = 0; i < 10; i++)
    {
        input_array.append(input_list[i]);
    }
    MaxHeap<int> max_heap;
    max_heap.build_heap(input_array);
    cout << "Maximum is " << max_heap.max() << "\n\n";
    max_heap.print_elements();

    cout << "\npart2 test\n";
    // please feel free to add more test cases
    int input_list_2[15] = {55, 32, 9, 46, 15, 22, 91, 18, 29, 77, 32, 16, 791, 45, 32};
    AList<int> input_array_2;
    for (int i = 0; i < 15; i++)
    {
        input_array_2.append(input_list_2[i]);
    }
    MaxHeap<int> max_heap_2;
    max_heap_2.heap_sort(input_array_2);
    max_heap_2.print_elements();

*/