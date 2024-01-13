#include<iostream>
#include<vector>
using namespace std;

int orientation(vector<int>&xcoordi, vector<int>&ycoordi, int xmin, int ymin, int p1index, int p2index){
    int val = (ycoordi[p1index] - ymin) * (xcoordi[p2index] - xcoordi[p1index]) -
              (xcoordi[p1index] - xmin) * (ycoordi[p2index] - ycoordi[p1index]);
 
    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: 2; //1 is for going clockwise, 2 is for going anticlockwise
}

int distSq(int p1x, int p1y, int p2x, int p2y)
{
    return (p1x - p2x)*(p1x - p2x) + (p1y - p2y)*(p1y - p2y);
}


void swapvectorelements(int index1,int index2,vector<int> &vec){
  int x=vec[index1];
  vec[index1]=vec[index2];
  vec[index2]=x;

}

void partition(vector<int>&xcoordi, vector<int>&ycoordi, int xmin, int ymin, int low, int high ){

    if (low>= high){
        //cout<<"exiting partition: "<<low<<" "<<high<<endl;
        return;
    }
    int iptr=low-1;
    
    for (int j=low; j<= high-1; j++){
        int ans= orientation(xcoordi, ycoordi,  xmin,  ymin, high, j);
        if (ans==2|| ans==0){// its anticlockwise or collinear, the angle is more, let it go ahead

        }
        else if (ans==1){// its clockwise, lesser angle, gotta swap it
            iptr++;
            if (iptr != j){
                swapvectorelements(iptr, j, xcoordi);
                swapvectorelements(iptr, j, ycoordi);
            }

        }
    }

    swapvectorelements( iptr+1, high, xcoordi);
    swapvectorelements( iptr+1, high, ycoordi);
    partition(xcoordi, ycoordi, xmin, ymin, low, iptr);
    partition(xcoordi, ycoordi, xmin, ymin, iptr+2, high);

    return;

}

int convexhull( vector<int>&xcoordi, vector<int>&ycoordi,vector<int>&xhull,vector<int>&yhull, int index ){
    if( xcoordi[index]== xhull[0] && ycoordi[index]== yhull[0] && (index != xcoordi.size()-1)){
        //cout<<" same as starting position"<<endl;
        
        return 1;
    }
    if( xcoordi[index]== xhull[0] && ycoordi[index]== yhull[0] && (index == xcoordi.size()-1) && xhull.size()==2){
        //cout<<" closed"<<endl;
        xhull.push_back(xcoordi[index]);
        yhull.push_back(ycoordi[index]);
        
        return 1;
    }



    if( xcoordi[index]== xhull[xhull.size()-1] && ycoordi[index]== yhull[yhull.size()-1]){
        
        return 1;
    }
    xhull.push_back(xcoordi[index]);
    yhull.push_back(ycoordi[index]);

    int ans= orientation(xhull, yhull,xhull[xhull.size()-3], yhull[yhull.size()-3], xhull.size()-2, xhull.size()-1);
    if (ans==1){
        //cout<<" going clockwise"<<endl;
        xhull.pop_back();
        xhull.pop_back();
        yhull.pop_back();
        yhull.pop_back();
        

        return 0;

    }
    else if (ans==0){
        int x1= distSq(xhull[xhull.size()-3],yhull[xhull.size()-3], xhull[xhull.size()-2], yhull[xhull.size()-2] );
        int x2= distSq(xhull[xhull.size()-3],yhull[xhull.size()-3], xhull[xhull.size()-1], yhull[xhull.size()-1] );

        if (x1>=x2){
            //cout<<" smaller collinear removed"<<endl;
            xhull.pop_back();
            yhull.pop_back();
            
            
            return 1;
            
        }
        else{
            //cout<<"bigger collinear and uska pehle removed"<<endl;
            xhull.pop_back();
            xhull.pop_back();
            yhull.pop_back();
            yhull.pop_back();
            

            return 0;
            

        }

    }

    else if ( ans==2){
        

        return 1;
    }
    

}

int main(){
    int n;
    cout<<"give number of points: ";
    cin>>n;
    vector<int>xcoordi;
    vector<int>ycoordi;
    int x;
    int y;

    for (int idx=0; idx<n; idx++){
        cout<<"Enter element "<<idx+1<<": ";
		cin>>x>>y;
        xcoordi.push_back(x);
        ycoordi.push_back(y);
    }


    vector<int>startingPoint;
    int minx= xcoordi[0];
    for (int i=1; i<n; i++){
        if (xcoordi[i]<= minx){
            minx= xcoordi[i];
        }
    }

    for (int j=0; j<n; j++){
        if (xcoordi[j]== minx){
            startingPoint.push_back(j);
        }
    }
    int miny=ycoordi[startingPoint[0]];
    for (int k=1; k<startingPoint.size(); k++){
        if (ycoordi[k]< miny){
            miny= ycoordi[k];
        }
    }

    vector<int>xhull;
    vector<int>yhull;

    xhull.push_back(minx);
    yhull.push_back(miny);

    partition(xcoordi, ycoordi,minx,miny, 0, xcoordi.size()-1 );
    xcoordi.push_back(minx);
    ycoordi.push_back(miny);
    
    int i=0;
    while (xcoordi[i]==minx&& ycoordi[i]== miny){
        i++;
    }
    xhull.push_back(xcoordi[i]);
    yhull.push_back(ycoordi[i]);
 
    for (int idx= i+1; idx< xcoordi.size(); idx++){
        int go_ahead= convexhull( xcoordi, ycoordi,xhull,yhull, idx );
        if (go_ahead==0){
            if (xhull.size()>1){
               idx--; 
            }
            else{
                xhull.push_back(xcoordi[idx]);
                yhull.push_back(ycoordi[idx]);

            }
        }
        
    }
    

    

    
    cout<<"Convex Hull: "<<endl;
    for (int i=0; i< xhull.size(); i++){
        cout<< xhull[i]<<" "<< yhull[i]<<endl;
    }
    cout<<"Total Points on Convex Hull: "<< xhull.size()-1<<endl;
    return 0;
}