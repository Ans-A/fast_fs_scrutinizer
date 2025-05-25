#include <iostream>
#include <filesystem>
#include <optional>
namespace fs = std::filesystem;


std::optional<std::string> parseArgs(int argc, char* argv[]);

std::optional<fs::path> validatePath(const std::string& raw_path);

bool scanPathDir(const fs::path& dirPath);





void logInfo(const std::string& message){
    std::cout<<"INFO: " << message <<'\n';
}

void logError(const std::string& errorMessage){
    std::cerr << "Error: " <<errorMessage<< '\n';
}

int main(int argc, char* argv[]) {
    
    if(auto raw_path_str_opt = parseArgs(argc, argv); raw_path_str_opt.has_value()){
        std::string raw_path_str = *raw_path_str_opt;

        if(auto validated_path_opt = validatePath(raw_path_str); validated_path_opt.has_value()){
            fs::path validated_path = *validated_path_opt;

            logInfo("Path is valid, dude, this one ------>" + validated_path.string());

            if(scanPathDir(validated_path)){
                logInfo("All good, we just scanned the directory. Mission accomplished!");
                return 0;
            }
        }
    }
}



std::optional<std::string> parseArgs(int argc, char* argv[]){

    if (argc<2){

        logError("We have less than 2 arguments, we need a directory path to run this badboy!");
        return std::nullopt;
    }
    return std::string(argv[1]);
}

std::optional<fs::path> validatePath(const std::string& raw_path){
    fs::path target_path = raw_path;

    if(!fs::exists(target_path)){
        logError("The directory '" + target_path.string() + "' ain't there, dude!");
        return std::nullopt;
    }
        if(!fs::is_directory(target_path)){
        logError("'" + target_path.string() + "' ain't a dir, dude!");
        return std::nullopt;
    }

    return target_path;
}

bool scanPathDir(const fs::path& dir_path) {
    std::cout <<"We're scanning this dir: '" <<dir_path<<"'\n";
    try {
        for (const auto& entry : fs::recursive_directory_iterator(dir_path)){
            logInfo("We got this entry:" + entry.path().string());
        }
    }
    catch (const fs::filesystem_error& e){
        logError("Woah, filesystem error, dude, couldn't scan '" + dir_path.string() + "': " + e.what());
        return false;
    }
        return true;
    }





