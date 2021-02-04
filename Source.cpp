#include <sys/utsname.h>
#include <iostream>
using namespace std;

int main() {
	// Part A - System Information
	struct utsname sysInfo;

	printf("System name - %s\n", sysInfo.sysname);
	printf("System name - %s\n", sysInfo.release);
	printf("System name - %s\n", sysInfo.version);
	printf("System name - %s\n", sysInfo.machine);
	printf("System name - %s\n", sysInfo.nodename);
	return 0;

	// Part B - Proc Filesystem

}