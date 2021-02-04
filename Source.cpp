#include <sys/utsname.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int foo() {
	char buf[32] = { 0x0 };
	int value = 0;
	FILE* fd = fopen("/proc/ioboard/input_1", "r");
	fgets(buf, 32, fd);
	value = atoi(buf);
	printf("\n input = %d\n", value);
	fclose(fd);
	return value;
}

int main() {
	// Part A - System Information
	struct utsname sysInfo;

	printf("System name - %s\n", sysInfo.sysname);
	printf("System name - %s\n", sysInfo.release);
	printf("System name - %s\n", sysInfo.version);
	printf("System name - %s\n", sysInfo.machine);
	printf("System name - %s\n", sysInfo.nodename);

	// Part B - Proc Filesystem
	string line;
	ifstream theFile ("/proc/stat");
	if (theFile.is_open()) {
		while (getline(theFile, line)) {
			cout << line << endl;
		}
		theFile.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}

	return 0;
}