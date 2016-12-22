#include<iostream>  
using namespace std;  
string add(string s1,string s2)  
{  
	string max,min;  
	max=s1;  
	min=s2;  
	if(max.size()<min.size()){  
		max=s2;  
		min=s1;  
	}     
	int lenmax = max.size();  
	int lenmin = min.size();  
	int j = lenmax-1;  
	for(int i=lenmin-1;i>=0;i--,j--)  
		max[j] += min[i]-'0';  
	for(int i=lenmax-1;i>=1;i--)  
		if(max[i]>'9')  
		{  
			max[i]-=10;  
			max[i-1]++;  
		}  
	if(max[0]>'9')  
	{  
		max[0]-=10;  
		max="1"+max;  
	}  
	return max;  
}  

int main()  
{     
	cout<<add("9989","21");   
	return 0;  
}  
