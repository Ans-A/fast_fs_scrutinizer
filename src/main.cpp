#include <iostream>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
namespace fs = std::filesystem;


struct FileInfo{
    std::string path;
    uintmax_t size;
    fs::file_time_type last_write_time;
    bool is_directory;
};

std::optional<std::string> parseArgs(int argc, char* argv[]);

std::optional<fs::path> validatePath(const std::string& raw_path);

std::optional<std::vector<FileInfo>> scanPathDir(const fs::path& dirPath);




std::string format_system_time(const std::chrono::system_clock::time_point& time_point){
        
    std::time_t tt = std::chrono::system_clock::to_time_t(time_point);

        std::tm* ptm = std::localtime(&tt);

        if(!ptm){
            return "Time ain't valid, boi";
        }
        std::stringstream ss;
        ss << std::put_time(ptm, "%Y-%m-%d %H:%M:%S");
        return ss.str();

}



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

std::optional<std::vector<FileInfo>> scanPathDir(const fs::path& dirPath) {
    logInfo("We're scanning this dir: '" + dirPath.string());
    std::vector<FileInfo> collected_files;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(dirPath)){
            FileInfo info;

            info.path = entry.path().string();
            info.is_directory = entry.is_directory();

            if(entry.is_regular_file()){
                info.size = fs::file_size(entry.path());

            } else{
                info.size = 0;
            }
            info.last_write_time = fs::last_write_time(entry.path());
            collected_files.push_back(info);
            logInfo("We got this entry:" + entry.path().string());
        }
    }
    catch (const fs::filesystem_error& e){
        logError("Woah, filesystem error, dude, couldn't scan '" + dirPath.string() + "': " + e.what());
        return std::nullopt;;
    }
        return collected_files;
    }





