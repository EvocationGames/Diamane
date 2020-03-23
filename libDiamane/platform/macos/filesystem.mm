//
// Created by Tom Hancocks on 23/03/2020.
//

#if __APPLE__

@import Cocoa;
#include "libDiamane/platform/filesystem.hpp"

// MARK: - Path Functions

auto diamane::platform::filesystem::path::get_components_of_path(const std::string path) -> std::vector<std::string>
{
    std::vector<std::string> components;
    std::string buffer;

    for (auto c = path.begin(); c != path.end(); ++c) {
        if (*c == '/') {
            if (!buffer.empty()) {
                components.emplace_back(buffer);
            }
            buffer.clear();
        }
        else {
            buffer += *c;
        }
    }

    return components;
}

auto diamane::platform::filesystem::path::construct_path_string(const std::vector<std::string> components) -> std::string
{
    std::string path;
    for (auto component = components.begin(); component != components.end(); ++component) {
        path += "/" + *component;
    }
    return path;
}

// MARK: - File System Paths

auto diamane::platform::filesystem::application_directory() -> path
{
    NSString *filepath = [[NSBundle mainBundle] bundlePath];
    return path(filepath.UTF8String);
}

auto diamane::platform::filesystem::user_documents_directory() -> path
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *filepath = paths[0];
    return path(filepath.UTF8String);
}

auto diamane::platform::filesystem::user_directory() -> path
{
    return path(NSHomeDirectory().UTF8String);
}

// MARK: - File System Access

auto diamane::platform::filesystem::contents_of_directory(const path dir_path) -> std::vector<path>
{
    std::vector<diamane::platform::filesystem::path> contents;

    NSString *dirPath = [NSString stringWithUTF8String:dir_path.to_str().c_str()];
    NSArray <NSString *> *dirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:dirPath error:nil];
    for (NSString *file in dirContents) {
        contents.emplace_back(diamane::platform::filesystem::path(dir_path, file.UTF8String));
    }

    return contents;
}

#endif