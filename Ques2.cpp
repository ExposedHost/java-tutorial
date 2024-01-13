#include<iostream>
#include<vector>
using namespace std;

int findMedian( vector<int>&v, int low, int vector_size){

    int array[vector_size];
    int arridx=0;
    for (int idx=low; idx< low+ vector_size; idx++){
        //cout<<v[idx]<<" ";
        array[arridx]= v[idx];
        arridx++;
    }

   
    if (vector_size==1 || vector_size==2){
        return (array[0]);
    }
    else if (vector_size==3){
        if (array[1]< array[0]){
            swap(array[1], array[0]);
        }
        if (array[2]< array[1]){
            swap(array[2], array[1]);
            if (array[1]< array[0]){
                swap(array[1], array[0]);
            }
        }
        return (array[1]);
        
    }

    else if (vector_size==4){
        if (array[1]<array[0]){
            swap(array[1], array[0]);
        }
        if (array[2]< array[1]){
            swap(array[2], array[1]);
            if (array[1]< array[0]){
                swap(array[1], array[0]);
            }
        }
        if (array[3]< array[2]){
            swap(array[3], array[2]);
            if (array[2]< array[1]){
                swap(array[2], array[1]);
                if (array[1]< array[0]){
                    swap(array[1], array[0]);
                }
                
            }
        }
        return array[2];
    }



    else {
        if (array[0]> array[1]){
            swap(array[0], array[1]);
        }
        if (array[2]> array[3]){
            swap(array[2], array[3]);
        }

        if (array[2]< array[0]){
            swap(array[2], array[0]);
        }

        if (array[1]< array[3]){
            swap(array[1], array[3]);
        }

        if (array[2]< array[3]){
            if (array[3]< array[4]){
                return array[3];
            }
            else{
                if (array[2]<array[4]){
                    return array[4];
                }
                else{
                     return array[2];
                }
            }
        }

        else{
            if (array[4]< array[3]){
                return array[3];
            }
            else{
                if (array[4]<array[2]){
                    return array[4];
                }
                else{
                    return array[2];
                }
            }
          }
    }
    
}

int partition( vector<int>&partv, int initial, int final, int medianOfMedians){
    if (initial>=final){
        return initial;
    }
    int idx;
    for(int i=initial;i<final;i++){
        if(partv[i]==medianOfMedians){
            idx = i;
            break; 
        }
    }

    int i= initial-1;
    int j= initial-1;
    for (int k=initial; k<= final; k++){
        if (partv[k]< medianOfMedians){            
            if (i+1!=k){
                swap(partv[j+1], partv[k]);
                swap(partv[i+1], partv[j+1]);
                i++;
                j++;
            }
            else{
                i++;
                j++;
            }
        }
        else if (partv[k]== medianOfMedians){
            swap(partv[j+1], partv[k]);
            j++;

        }
    }
    return i+1;
}


int findKthElement(vector<int>&v, int low, int high, int k ){
    if(low > high){
        return -1;
    }
    if (low==high&& low==k){
        return v[low];
    }
    int i=0;
    int n= high-low+1;
    vector<int>medians;
    while(i<n/5){
            medians.push_back(findMedian(v, low + i*5, 5));
            i++;
        }
    if(i*5 < n){
        medians.push_back(findMedian(v,low + i*5 , n%5));
        i++;
    }
    int lenMedArr= medians.size();
    int medianOfMedians;
    if (lenMedArr==1){
        medianOfMedians= medians[0];
    }
    else{
        medianOfMedians= findKthElement(medians, 0, lenMedArr-1, lenMedArr/2 );  
    } 
    int medianIndex= partition(v, low, high, medianOfMedians);
    if (medianIndex== k-1){
        return medianOfMedians;
    }
    else if (medianIndex> k-1){
        return findKthElement(v, low, medianIndex-1, k );
    }
    else{
        return findKthElement(v, medianIndex+1, high, k);
    }

}

int findRankOfK(vector<int>&arr, int low, int high, int k){
    if(low > high){
        return -1;
    }
    if (low==high && arr[low]==k){
        return low+1;
    }
    if (low==high && arr[low]!=k){
        return -1;
    }


    int i=0;
    int n= high-low+1;
    vector<int>medians;
    while(i<n/5){
            medians.push_back(findMedian(arr, low + i*5, 5));
            i++;
        }
    if(i*5 < n){
        medians.push_back(findMedian(arr,low + i*5 , n%5));
        i++;
    }
    int lenMedArr= medians.size();
    int medianOfMedians;
    if (lenMedArr==1|| lenMedArr==2 ){
        medianOfMedians= medians[0];
    }
    else{
        medianOfMedians= findKthElement(medians, 0, lenMedArr-1, lenMedArr/2 );
    }
    int medianIndex= partition(arr, low, high, medianOfMedians);

    if (k== medianOfMedians){
        return medianIndex+1;
    }

    if (k< medianOfMedians){
        return findRankOfK(arr, low, medianIndex-1, k);
    }
    else{
        return findRankOfK(arr, medianIndex+1, high,k);
    }

}

int main(){
    int n;
    int k;
    int m;
    cout<<"Give the first line of the input: ";
    cin>>n>>k>>m;
    if (k>n){
        cout<<"k should be less than n. kindly begin again. ";
        exit(0);
    }
    vector<int> inparr;
    for (int index=0; index < n; index++){
        int ele;
        cout<<"Type the input integer: ";
        cin>>ele;
        inparr.push_back(ele);
    }   
    int ans1= findKthElement(inparr, 0, n-1, k );
    cout<<ans1<<endl;
    int ans2= findRankOfK(inparr, 0, n-1, m );
    cout<<ans2<<endl;
    return 0;

}