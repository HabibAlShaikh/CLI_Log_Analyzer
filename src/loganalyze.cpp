#include <iostream>
#include <string>
#include <fstream>

void openLog();

std::string filePath = "";
std::string level = "";

int main(int argc, char* argv[]) {
	for(int i = 1; i < argc; i++) {
		std::string arg = argv[i];

		if(arg == "--path") {
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
		} else if (arg == "--help") {
			std::cout << "Usage: ./loganalyze --path <path> [--level INFO|WARN|ERROR]" << std::endl;
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
