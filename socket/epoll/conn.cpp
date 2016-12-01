#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char* argv[]){
	pid_t cpid;
	while(1){
		if(cpid = fork() == 0){
			execlp("./client",NULL,NULL);
		}
	}
	return 0;
}
