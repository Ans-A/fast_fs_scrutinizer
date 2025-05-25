#include <iostream>
#include <filesystem>
#include <optional>
namespace fs = std::filesystem;


bool parseArgs(int argc, char* argv[], fs::path& target_path);

bool validatePath(const fs::path& target_path);

bool scanPathDir(const fs::path& target_path);



int main(int argc, char* argv[]) {
    
    fs::path target_path;

    if(!parseArgs(argc, argv, target_path)){
        return 1;
    }
    
    if(!validatePath(target_path)){
        return 1;
    }
    
    std::cout << "Path is valid dude, this one ------>" << target_path << '\n';

    if(!scanPathDir(target_path)){
        return 1;
    }
    std::cout << "Scan complete dude, this one ------>" << target_path << '\n';


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



std::optional<std::string> parseArgs(int argc, char* argv[]){

    if (argc<2){

        std::cerr << "We have less than 2 arguments, we need argumentsd to run this badboy\n";
        return std::nullopt;
    }
    return std::string(argv[1]);
}

bool validate_directory(const fs::path& target_path){

    if(!fs::exists(target_path)){
        std::cerr << "Error: '" << target_path << "' ain't there, dude\n";
        return false;
    }
        if(!fs::is_directory(target_path)){
        std::cerr << " Error: '" <<target_path <<"' ain't a dir, dude\n";
        return false;
    }
    return true;
}

bool scan_dir(const fs::path& target_path) {
    try{
        for (const auto& entry : fs::recursive_directory_iterator(target_path)){
            std::cout << "We got this entry:" << entry.path()<<'\n';
        }
    }
    catch (const fs::filesystem_error& e){
        std::cerr <<"we have a filesystem error, dude, about: '" << target_path<<"': " << e.what() <<'\n';
        return false;}
        return true;
    }

    



