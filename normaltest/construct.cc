#include <iostream>
using namespace std;
class base{
//	private:
	protected:
		int pri = 1;
	public:
		~base(){
			cout << "base decon..." << endl;
		}
		base(){
			cout << "base con ..." << endl;
		}
		base(int p):pri(p){
			cout << "base con (p)" << endl;
		}
		virtual void foo(){
			cout << "base foo" << endl;
		}
		virtual void foo1(){
			cout << "base foo" << endl;
		}
		void printpri(){
			cout << "pri : " << pri << endl;
		}
};
class derived: public base{
	public:
		~derived(){
			cout << "derived decon..." << endl;
		}
		derived(int v):base(v){
			cout << "derived con (a)..." << endl;
		}
		derived(){
			cout << "derived con ..." << endl;
		}
		void set(){
			pri = 11;
		}
};
int main(){
	base bb(33);
	cout << "bb.printpri()" << endl;
	bb.printpri();
	cout << "===========================" << endl;
	derived dd2(22);
	dd2.printpri();
	dd2.set();
	dd2.printpri();
	cout << sizeof(dd2) << endl;
	return 0;
}
