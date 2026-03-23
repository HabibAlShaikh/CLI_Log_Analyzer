#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

bool openLog ();
void printUsage ();

std::string filePath = "";
std::string level = "";
std::string outPath = "";

int main(int argc, char* argv[]) {
	int pathCount = 0;
	for(int i = 1; i < argc; i++) {
		std::string arg = argv[i];

		if(arg == "--path") {
			pathCount++;

			// Check if it's a duplicate
			if(pathCount > 1) {
				std::cerr << "Error: Multiple --path arguments provided. Only one is allowed." << std::endl;
				return 1;
			}

			if(i + 1 < argc) {
				filePath = argv[++i];
			} else {
				std::cerr << "Error: --path requires a value" << std::endl;
				return 1;
			}
		} else if (arg == "--level") {
			if (i + 1 < argc) {
				level = argv[++i];
			} else {
				std::cerr << "Error: --level requires a value" << std::endl;
				return 1;
			}
			if (!(level == "INFO" || level == "WARN" || level == "ERROR")) {
				std::cerr << "Error: Invalid level." << std::endl;
				return 1;
			}
		} else if (arg == "--out") {
			if (i + 1 < argc) {
				outPath = argv[++i];
			} else {
				std::cerr << "Error: --out requires a value" << std::endl;
				return 1;
			}
		} else if (arg == "--help") {
			printUsage();
			return 0;
		} else {
			std::cerr << "Unknown argument: " << arg << std::endl;
			return 1;
		}
	}

	if(filePath.empty()) {
		std::cerr << "Error: --path is required" << std::endl;
		return 1;
	}

	std::cout << "File: " << filePath << std::endl;
	std::cout << "Level: " << level << std::endl;

	if (!openLog()) return 1;

	return 0;
}

bool openLog () {
	int totalLines = 0; // increments every line, no matter what
	int matchedLines = 0; // increments only when a line passes the filter
	struct stat fileStat;

	//stat(filePath.c_str(), &fileStat);
	if (stat(filePath.c_str(), &fileStat)) {
		std::cerr << "Error: file does not exist" << std::endl;
		return false;
	}

	if (!(S_ISREG(fileStat.st_mode))) {
		std::cerr << "Error: path is not a regular file" << std::endl;
		return false;
	}

	std::ifstream logFile(filePath);
	std::ofstream outFile;

	if (!logFile.is_open()) {
		std::cerr << "Could not open the log file: " << filePath << std::endl;
		return false;
	} else {
		std::cout << "File opened successfully!" << std::endl;
	}

	if (!outPath.empty()) {
		outFile.open(outPath);
		if (!outFile.is_open()) {
			std::cerr << "Could not open the out file: " << outPath << std::endl;
			return false;
		} else {
			std::cout << "File opened successfully!" << std::endl;
		}
	}

	std::string line;
	while (std::getline(logFile, line)) {
		// If level is empty, it will match every line.
		// If not empty, it filters by the provided string.
		totalLines++;
		if (level.empty() || line.find(level) != std::string::npos) {
			std::cout << line << std::endl;
			if (!outPath.empty()) {
				outFile << line << std::endl;
			}
			matchedLines++;
		}
	}

	std::cout << "Total lines: " << totalLines << std::endl;
	std::cout << "Matched lines: " << matchedLines << std::endl;
	logFile.close();
	outFile.close();

	return true;
}

void printUsage() {
	std::cout << "Usage: \n"
			  << "	loganalyze --file <path> [--level INFO|WARN|ERROR] [--from ""YYYY-MM-DD HH:MM:SS""] [--to ""YYYY-MM-DD HH:MM:SS""] [--out <path>] \n"
			  << " \n"
			  << "Options: \n"
			  << "  --file     Path to log file (required) \n"
			  << "  --level    Filter by log level \n"
			  << "  --from     Start timestamp (inclusive) \n"
			  << "  --to       End timestamp (inclusive) \n"
			  << "  --out      Output file for matched lines \n"
			  << "  --help     Show this help message \n";
}
