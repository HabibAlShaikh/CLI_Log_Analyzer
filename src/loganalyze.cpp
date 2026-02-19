#include <iostream>
#include <string>
#include <fstream>

void openLog ();
void printUsage ();

std::string filePath = "";
std::string level = "";

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

	openLog();

	std::cout << "Arguments parsed successfully" << std::endl;

	return 0;
}

void openLog () {
	std::ifstream logFile(filePath);

	if (!logFile.is_open()) {
		std::cerr << "Could not open the log file: " << filePath << std::endl;
		return;
	} else {
		std::cout << "File opened successfully!" << std::endl;
	}

	std::string line;
	while (std::getline(logFile, line)) {
		// If level is empty, it will match every line.
		// If not empty, it filters by the provided string.
		if (level.empty() || line.find(level) != std::string::npos) {
			std::cout << line << std::endl;
		}
	}

	logFile.close();
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
