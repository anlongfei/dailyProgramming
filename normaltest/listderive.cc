#include <iostream>
using namespace std;
class base{
	private:
		int a;
	public:
		void foo();
		void v();
	//	~base(){
		virtual ~base(){
			cout << "decon.. base" << endl;
		}
};
class derived1 : public base{
	public:
		~derived1(){
			cout << "decon.. derived1" << endl;
		}

};
//class derived2 : public derived1{
//	public:
//		virtual ~derived2(){
//			cout << "decon.. base" << endl;
//		}
//
//};
int main(){
	base *b;
	derived1 *d = new derived1();
	b = d;
	delete b;
	cout << sizeof(base) << endl;
}
