#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
int main(int argc, char* argv[]) {
    
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <directory_path>\n";
        return 1;
    }
    fs::path target_path = argv[1];

    if(!fs::exists(target_path)){
        std::cerr<<"Error: Directory'"<<target_path<<"'does not exist\n";
        return 1;
    }

    if(!fs::is_directory(target_path)){
        std::cerr<<"Error: '"<<target_path<<"'is not a directory\n";
        return 1;

    }
    std::cout<<"Successfully validated directory"<<target_path<<'\n';

    std::cout << "we're scanning "<<target_path<<'\n';

    try{

        for (const auto& entry: fs::recursive_directory_iterator(target_path)){
            std::cout << "found: " <<entry.path() << '\n';
        }
    }

    catch(const fs::filesystem_error& e){
        std::cerr << "filesystem inaccessible, you messed up in this: " <<target_path << ":" << e.what() <<'\n';
        return 1;
    }

    std::cout<<"Successfully scanned directory"<<target_path<<'\n';

    return 0;
}
