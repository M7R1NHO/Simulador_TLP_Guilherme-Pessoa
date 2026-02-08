#include "Utils/FileManager.hpp"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <unistd.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

FileManager::FileManager() {
}

bool FileManager::FileExists(const std::string& filepath) {
    std::ifstream file(filepath);
    return file.good();
}

bool FileManager::DirectoryExists(const std::string& dirpath) {
    struct stat info;
    if (stat(dirpath.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool FileManager::CreateDirectory(const std::string& dirpath) {
    if (DirectoryExists(dirpath)) {
        return true;  // Já existe
    }
    
    int result = MKDIR(dirpath.c_str());
    return result == 0;
}

std::vector<std::string> FileManager::ListFiles(const std::string& dirpath) {
    std::vector<std::string> files;
    
    // Implementação básica - pode ser expandida
    // Por enquanto retorna lista vazia
    
    return files;
}

std::string FileManager::ReadTextFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[FileManager] Erro ao abrir arquivo: " << filepath << std::endl;
        return "";
    }
    
    std::string content;
    std::string line;
    
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    
    file.close();
    return content;
}

bool FileManager::WriteTextFile(const std::string& filepath, const std::string& content) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[FileManager] Erro ao criar arquivo: " << filepath << std::endl;
        return false;
    }
    
    file << content;
    file.close();
    
    return true;
}

bool FileManager::DeleteFile(const std::string& filepath) {
    if (!FileExists(filepath)) {
        return false;
    }
    
    int result = std::remove(filepath.c_str());
    return result == 0;
}