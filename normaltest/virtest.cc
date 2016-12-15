#include <iostream>
using namespace std;
class base{
	private:
		int pri;
	public:
		~base(){
			cout << "base decon..." << endl;
		}
		base(){
			cout << "base con ..." << endl;
		}
		base(int p):pri(p){}
		virtual void foo(){
			cout << "base foo" << endl;
		}
		virtual void foo1(){
			cout << "base foo" << endl;
		}
		void printpri(){
			cout << "pri : " << pri << endl;
		}
	protected:
		int pro;
};
class ch : public base{
	public:
		~ch(){
			cout << "ch decon..." << endl;
		}
		ch(){
			cout << "ch con ..." << endl;
		}
	private:
		int a;
		
};
class zore{

};
struct A{
	int b;
	void foo(){
		cout << "hello foo" << endl;
	}
};
struct B{
	int b;
};
class D{
	double b;
};
int main(){
	struct A a;
	struct B b;
	base bbase;
	ch cch;
	bbase.foo();
	cch.foo();
	a.foo();
	cout << sizeof(a)		<< endl;			 //4
	cout << sizeof(b)			<< endl;		 //4
	
	cout << "base: " << sizeof(base)		<< endl;			//8
	cout << "ch :"   << sizeof(ch)			<< endl;			//16
	cout << "zore: " << sizeof(zore)		<< endl;			//1
	cout << "struct A : " << sizeof(struct A)	<< endl;     //4
	cout << "struct B : " << sizeof(struct B)	<< endl;     //4
	cout << "class D : " << sizeof(D)			<< endl;     //4
	return 0;
}
