#include <iostream>
using namespace std;
class base{
	public:
		virtual void foo(){}
};
class ch : public base{
	private:
		int a;
};
class zore{

};
struct A{
	int b;
	void foo(){
	}
};
struct B{
	int b;
};
class C{
	int b;
};
int main(){
	cout << sizeof(base)		<< endl;			//8
	cout << sizeof(ch)			<< endl;			//16
	cout << sizeof(zore)		<< endl;			//1
	cout << sizeof(struct A)	<< endl;     //4
	cout << sizeof(struct B)	<< endl;     //4
	cout << sizeof(C)			<< endl;     //4
	return 0;
}
