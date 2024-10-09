#include "DecoderApp.h"

int main(int argc, char** argv)
{
    std::deque<std::string> filePaths;
    for (int idx = 1; idx < argc; idx++) {
        filePaths.push_back(argv[idx]);
    }
    
    if (filePaths.empty()) {
        std::cout << "Missing files to determine encoding" << std::endl;
        return -1;
    }
    
    Decoder dec;
    for (const auto& filePath : filePaths) {
        std::cout <<"File: " << filePath << " encoding: " << dec.decode(filePath) << std::endl;
        std::cout << "=====================" << std::endl;
    }

    return 0;
}

