#include <iostream>
using namespace std;
string myadd(string s1, string s2){
	string min = s1, max = s2;
	if(min.size() > max.size())
		max = min;
	int lenmin = min.size();
	int lenmax = max.size();

	for(int i=lenmin-1; i>=0; i--)
		max[i] = max[i] - '0' + min[i];

	for(int j=lenmax-1; j>=1; j--){
		if(max[j] > '9'){
			max[j] = max[j] - 10;
			max[j-1]++;
		}
	}
	if(max[0] > '9'){
		max[0] = max[0] - 10;
		max = "1" + max;
	}
	return max;
}

int main(){
	string s1 = "123456789";
	string s2 = "987654321";
	string s = myadd(s1, s2);
	cout << s << "  " << s.size() << endl;
	return 0;
}
