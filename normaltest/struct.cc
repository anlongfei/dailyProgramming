//#include <iostream>
//using namespace std;
//typedef struct TreeNode TreeNode;
#include <stdio.h>
struct TreeNode{
	int val;
	TreeNode *right;
	TreeNode *left;
};
int main(){
	TreeNode a;
	a.val = 10;
	//cout << a.val << endl;
	printf("%d\n",a.val);
	return 0;
}
