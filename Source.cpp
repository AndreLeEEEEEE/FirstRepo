// Student: Andre Le, SID: 109069441, Due Date: Feb 14, 2021

#include <sys/utsname.h>  // For using the utsname struct
#include <sstream>  // For string parsing and type casting
#include <fstream>  // For reading files
#include <string>  // For the use of strings
#include <vector>  // For holding parsed strings
#include <ctime>  // For formatting time values
using namespace std;  // Reduces the size of statements

string procSearch(string fileName, string searchTerm = "") {
// Find a file in proc using the relevant path and potential line identifier.
	string line, result;  // For holding single strings of files
	string path = "/proc/" + fileName;  // Combine to make the full path
	ifstream theFile(path);  // Get the file
	if (theFile.is_open()) {
		while (getline(theFile, line)) {  // While there's something to be read
			if (line.find(searchTerm) != string::npos) {  // Find the specific line
				result = line;  // Save to result
				break;  // Stop searching
			}
		}
		theFile.close();
	}
	else {
		printf("Unable to open file\n");
	}
	return result;  // Return the target line
}

int extract(string rawMat, int index) {
// Find a certain 'word' in a passed string.
	string temp;  // For holding the current 'word'
	vector <string> tokens;  // For holding the parsed line
	stringstream split(rawMat);  // Make a sstream for the line

	while (getline(split, temp, ' ')) {  // While there's a 'word' in the line
		tokens.push_back(temp);  // Append the current 'word' to tokens
	}
	stringstream scasti(tokens[index]);  // Make a sstream for the target 'word'
	int token;
	scasti >> token;  // Convert 'word' to integer

	return token;
}

int main() {
	// Part A - System Information
	struct utsname sysInfo;  // System information structure

	if (uname(&sysInfo) == -1) {
	// Apparently this check needs to be here or else sysInfo will print nothing
		printf("uname failed");
	}
	else {
		printf("System name - %s\n", sysInfo.sysname);  // System name
		printf("Release - %s\n", sysInfo.release);  // Current release level of operating system
		printf("Version - %s\n", sysInfo.version);  // Current version level of operating system
		printf("Machine - %s\n", sysInfo.machine);  // Machine name or hardware type of the machine
		printf("Nodename - %s\n", sysInfo.nodename);  // Node name of the machine
	}
	printf("\n");  // Spacing for readability

	// Part B - Proc Filesystem
	string procLine;  // For holding lines from files
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
	struct tm nowTime;  // tm structure for individual and accurate time measurements
	time_t now = bootTime;  // Replace time(0), current time, with the custom amount of seconds
	nowTime = *localtime(&now);  // Make nowTime use the custom seconds
	printf("Time when system was last booted: %d-%d-%d", 1900+nowTime.tm_year, 1+nowTime.tm_mon, nowTime.tm_mday);
	printf(" %d:%d:%d\n", nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);

	// Amount of time since system was last booted, dd:hh:mm:ss
	now = bootDur;  // Readjust now
	nowTime = *localtime(&now);  // Readjust nowTime
	printf("Time since system was last booted: %d:%d:%d:%d\n", nowTime.tm_mday, nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);

	// Amount of time the CPU has spent in user mode
	printf("Amount of time the CPU has spent in user mode: %d seconds\n", usrMode);

	// Amount of time the CPU has spent in system mode
	printf("Amount of time the CPU has spent in system mode: %d seconds\n", sysMode);

	// Total amount of memory in the system
	printf("Total amount of memory in the system: %d kB\n", totalMem);

	// Amount of memory currently available in the system
	printf("Amount of memory currently available: %d kB\n", availMem);

	return 0;
}