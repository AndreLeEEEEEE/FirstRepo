#include <sys/utsname.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	// Part A - System Information
	struct utsname sysInfo;

	if (uname(&sysInfo) == -1) {
		printf("uname failed");
	}
	else {
		printf("System name - %s\n", sysInfo.sysname);
		printf("System name - %s\n", sysInfo.release);
		printf("System name - %s\n", sysInfo.version);
		printf("System name - %s\n", sysInfo.machine);
		printf("System name - %s\n", sysInfo.nodename);
	}

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