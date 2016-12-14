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
int main(){
	cout << sizeof(base) << endl;
	cout << sizeof(ch)   << endl;
	cout << sizeof(zore)   << endl;
	cout << sizeof(struct A)   << endl;
	return 0;
}
