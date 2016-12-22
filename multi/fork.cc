#include <stdio.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main(){
	pid_t main_pid = getpid();
	cout << "main_pid : " << main_pid << endl;
	//fork() || fork() && fork();
	fork() && fork() || fork();
	//pid_t getpid(void);
	//pid_t getppid(void);
	
	pid_t pid, ppid;
	pid = getpid();
	ppid = getppid();
	cout << "pid : " << pid << "  ppid : " << ppid << endl;

	return 0;
}
