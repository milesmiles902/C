// added by Manish Sharma
 
#include <iostream>
using namespace std;
 
int partition(int* arr, int start, int end,int &op)
{  
    int index = 0, pivotElement = arr[end], pivotIndex;
    int* temp = new int[end - start + 1];
    for (int i = start; i <= end; i++){
        if(arr[i] < pivotElement){
            temp[index] = arr[i];
            index++;
        }
    }
 
    temp[index] = pivotElement;
    index++;
 
    for (int i = start; i < end; i++){
        if(arr[i] > pivotElement){
            temp[index] = arr[i];
            index++;
        }
    }
     
    index = 0;
    for (int i = start; i <= end; i++) {  
        if(arr[i] == pivotElement){
            pivotIndex = i;
        }
        arr[i] = temp[index];
        index++;
    }
    return pivotIndex;
}
 
void quickSort(int* arr, int start, int end,int &op)
{ 
    if(start < end)
    {   op++;
        int partitionIndex = partition(arr, start, end,op);
        quickSort(arr, start, partitionIndex - 1,op);
        quickSort(arr, partitionIndex + 1, end,op);
    }
    return;
}
 
int main(){  
    int i,j,k,size,op=0;
    size=10;
    k=4;
    int arr[size] = {5, 12, 7, 1, 13, 2 ,23, 11, 18, 9};
       
    cout << "Unsorted array : ";
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    printf("\n");
 
    quickSort(arr, 0, size - 1,op);
     
    cout << "Sorted array : ";
    for (int i = 0; i < size; i++)
    {
       cout << arr[i] << " ";
    }
    cout << endl;
    cout << "The kth element is: " << arr[k-1] << endl;
    cout << "The kth element was found in " << op << " operations." << endl;
    return 0;
}
