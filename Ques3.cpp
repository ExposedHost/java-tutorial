#include <iostream>
 
using namespace std;

/*int partition(int array[], int n){
    int j=0;
    int i=0;
    while( j<= n-1){
            if (array[j]>=0){
                j++;
            }
            else {
                if (i != j){
                    swap(array[i], array[j]);
                }
                i++;
                j++;
            }
        }
    return i;
}*/
int firstPositiveInd(int inputArr[], int n)
{
    int negCount = 0;
    int tempArr[n] = {0};
    for (int i =0 ; i< n; i++)
    {
        if (inputArr[i]<0)
        {
            negCount++;
        }
    }


    int posInd = negCount;
    
    int negInd = 0;

    for (int i = 0; i< n; i++)
    {   
        
        if (inputArr[i]< 0)
        {
            tempArr[negInd] = inputArr[i];
            negInd++;
        }

        
        else 
        {
            tempArr[posInd] = inputArr[i];
            posInd++;
        }
    }

    
    for (int i = 0; i<n; i++)
    {
        inputArr[i] = tempArr[i];
    }

    return negCount;
}

int getMax(int arr[], int low, int high)
{
	int max = arr[low];
	for (int i = low+1; i <= high; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}
 
void descountSort(int arr[], int low, int high, int exp)
{  
	int output[high-low+1], i, count[10] = {0};
	for (i = low; i <= high; i++){
		count[((arr[i]) / exp) % 10]++;
    }

	for (i = 1; i < 10; i++){
		count[i] += count[i-1];
    }

    for (int idx=0; idx<10; idx++){
        count[idx]= high-low- count[idx]+2;
    }

	for (i = low; i <=high; i++){
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]++;
    }

	for (i = low; i <= high; i++){
		arr[i] = output[i-low];
    }
}

void desradixsort(int arr[], int low, int high)
{
	int exp, m;
	m = getMax(arr, low, high);
	for (exp = 1; m/exp > 0; exp *= 10){
		descountSort(arr, low, high, exp);
    }
}

void asccountSort(int arr[], int low, int high, int exp)
{  
	int output[high-low+1], i, count[10] = {0};
	for (i = low; i <= high; i++){
		count[(arr[i] / exp) % 10]++;
    }

	for (i = 1; i < 10; i++){
		count[i] += count[i-1];
    }

	for (i = high; i >= low; i--){
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = low; i <= high; i++)
		arr[i] = output[i-low];
}
 
void ascradixsort(int arr[], int low, int high)
{
	int exp, m;
	m = getMax(arr, low, high);
	for (exp = 1; m/exp > 0; exp *= 10)
		asccountSort(arr, low, high, exp);
}
 
int main()
{
	int n, i;
	cout<<"\nEnter the number of data element to be sorted: ";
	cin>>n;
 
	int arr[n];
	for(i = 0; i < n; i++)
	{
		cout<<"Enter element "<<i+1<<": ";
		cin>>arr[i];
	}
    int idx= firstPositiveInd(arr, n);

    for (int ele=0; ele<idx; ele++){
        arr[ele]= arr[ele]*(-1);
    }

    
    
	desradixsort(arr, 0, idx-1);
    ascradixsort( arr, idx, n-1);
	for (int ele=0; ele<idx; ele++){
        arr[ele]= arr[ele]*(-1);
    }
	cout<<"\nSorted Data ";
	for (i = 0; i < n; i++)
		cout<<" "<<( arr[i]);
	return 0;
}