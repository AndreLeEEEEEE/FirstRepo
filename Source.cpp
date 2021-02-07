// Student: Andre Le, SID: 109069441, Due Date: Feb 14, 2021

#include <sys/utsname.h> 
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
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
				break;
			}
		}
		theFile.close();
	}
	else {
		printf("Unable to open file\n");
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
	printf("\n");

	// Part B - Proc Filesystem
	string procLine;
	// Extract all the necessary information
	procLine = procSearch("stat", "btime");  // btime has one number
	int bootTime = extract(procLine, 1);

	procLine = procSearch("uptime");  // there's no line identifier, just two numbers. However, the first number is time running since last boot
	int bootDur = extract(procLine, 0);

	procLine = procSearch("stat", "cpu");  // first number is time spent in user mode
	int usrMode = extract(procLine, 2);

	procLine = procSearch("stat", "cpu");  // third number is time spent in system mode
	int sysMode = extract(procLine, 4);

	procLine = procSearch("meminfo", "MemTotal");  // MemTotal has a number and 'kB'
	int totalMem = extract(procLine, 8);

	procLine = procSearch("meminfo", "MemAvailable");  // MemAvailable has a number and 'kB'
	int availMem = extract(procLine, 4);

	// Time when system was last booted, yyyy-mm-dd hh:mm:ss
	struct tm nowTime;
	time_t now = bootTime;
	localtime_s(&nowTime, &now);

	printf("Time when system was last booted: %d-%d-%d", 1900+nowTime.tm_year, 1+nowTime.tm_mon, nowTime.tm_mday);
	printf(" %d:%d:%d\n", nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);

	// Amount of time since system was last booted, dd:hh:mm:ss
	now = bootDur;
	localtime_s(&nowTime, &now);

	printf("Time since system was last booted: %d:%d:%d:%d\n", nowTime.tm_mday, nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);

	// Amount of time the CPU has spent in user mode
	now = usrMode;
	localtime_s(&nowTime, &now);

	printf("Amount of time the CPU has spent in user mode: %d:%d:%d\n", nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);

	// Amount of time the CPU has spent in system mode
	now = sysMode;
	localtime_s(&nowTime, &now);

	printf("Amount of time the CPU has spent in system mode: %d:%d:%d\n", nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);

	// Total amount of memory in the system
	printf("Total amount of memory in the system: %d kB\n", totalMem);

	// Amount of memory currently available in the system
	printf("Amount of memory currently available: %d kB\n", availMem);

	return 0;
}