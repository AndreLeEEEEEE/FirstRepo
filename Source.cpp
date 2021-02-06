// Student: Andre Le, SID: 109069441, Due Date: Feb 14, 2021

//#include <sys/utsname.h> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <typeinfo>
using namespace std;

string procSearch(string fileName, string searchTerm = "") {
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

int extract(string rawMat, int index) {
	string temp;
	vector <string> tokens;
	stringstream split(rawMat);

	while (getline(split, temp, ' ')) {
		tokens.push_back(temp);
	}
	stringstream scasti(tokens[index]);
	int token;
	scasti >> token;

	return token;
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
	string procLine;
	// Max size of an int: 2147483647
	procLine = procSearch("stat", "btime");  // btime has one number
	int bootTime = extract(procLine, 1);

	procLine = procSearch("uptime");  // there's no line identifier, just two numbers. However, the first number is time running since last boot
	int bootDur = extract(procLine, 0);

	procLine = procSearch("stat", "cpu");  // first number is time spent in user mode
	int usrMode = extract(procLine, 1);

	procLine = procSearch("stat", "cpu");  // third number is time spent in system mode
	int sysMode = extract(procLine, 3);

	procLine = procSearch("meminfo", "MemTotal");  // MemTotal has a number and 'kB'
	int totalMem = extract(procLine, 2);

	procLine = procSearch("meminfo", "MemAvailable");  // MemAvailable has a number and 'kB'
	int availMem = extract(procLine, 2);

	cout << bootTime << endl;
	cout << bootDur << endl;
	cout << usrMode << endl;
	cout << sysMode << endl;
	cout << totalMem << endl;
	cout << availMem << endl;

	return 0;
}