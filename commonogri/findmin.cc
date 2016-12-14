#include <iostream>  
using namespace std;  
  
int FindMin(int *a, int length)  
{  
    int low=0;  
    int high=length-1;  
    int mid;  
  
    if(a[low]<a[high])//如果旋转个数为0，即没有旋转，单独处理，直接返回数组头元素  
        return a[low];  
  
    while(low<=high)  
    {  
	        mid=(low+high)/2;  
	        if(a[low]<a[mid])  
	            low=mid;  
	        else if(a[low]>a[mid])  
	            high=mid;  
	        else if(a[low]==a[mid])  
	            return a[low+1];  
	    }     
}  
  
int main()  
{  
    int a[]={1,3,4,5,6,7,8,9};  
    cout<<FindMin(a, 8)<<endl;  
  
}  
