#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    //std::cout << "Argument count: " << argc << "\n";

    std::string filePath = "";
    std::string level = "";

    for(int i = 1; i < argc; i++) {
	    std::string arg = argv[i];

	    if(arg == "--path") {
		if(i + 1 < argc) {
			filePath = argv[++i];
		}else {std::cerr << "Error: --file requires a value\n"; return 1;}
	    }else if (arg == "--level") {
	    	if (i + 1 < argc) {
	    		level = argv[++i];
	    	}else {std::cerr << "Error: --level requires a value\n"; return 1;}
	    }else if (arg == "--help") {
	    	std::cout << "Usage: ./loganalyze --file <path> [--level INFO|WARN|ERROR]\n";
            	return 0;
	    }else {
	    	std::cerr << "Unkonwn argument: " << arg << std::endl;
		return 1;
	    }
    }

    return 0;
}
