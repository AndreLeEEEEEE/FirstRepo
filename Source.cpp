// Student: Andre Le, SID: 109069441, Due Date: Feb 14, 2021

//#include <sys/utsname.h> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

string proc(string fileName, string searchTerm = "") {
	// Find a file in proc using the relevant path and potential line identifier.
	string line, result;
	string path = "/proc/" + fileName;
	ifstream theFile(path);
	if (theFile.is_open()) {
		while (getline(theFile, line)) {
			if (line.find(searchTerm) != string::npos) {
				result = line;
			}
		}
		theFile.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}

	return result;
}

int main() {
	// Part A - System Information
	//struct utsname sysInfo;

	//if (uname(&sysInfo) == -1) {
	//	printf("uname failed");
	//}
	//else {
	//	printf("System name - %s\n", sysInfo.sysname);
	//	printf("System name - %s\n", sysInfo.release);
	//	printf("System name - %s\n", sysInfo.version);
	//	printf("System name - %s\n", sysInfo.machine);
	//	printf("System name - %s\n", sysInfo.nodename);
	//}

	// Part B - Proc Filesystem
	// Max size of an int: 2147483647
	//string lastBoot = proc("stat", "btime");  // btime has one number
	//string bootDur = proc("uptime");
	//string modes = proc("stat", "cpu");  // first number is time spent in user mode, third number is time spent in system mode
	//string totalMem = proc("meminfo", "MemTotal");
	string availMem = proc("meminfo", "MemAvailable");

	return 0;
}