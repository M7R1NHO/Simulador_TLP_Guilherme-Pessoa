#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <vector>

class FileManager {
public:
    FileManager();
    
    // Verificações
    static bool FileExists(const std::string& filepath);
    static bool DirectoryExists(const std::string& dirpath);
    
    // Operações de diretório
    static bool CreateDirectory(const std::string& dirpath);
    static std::vector<std::string> ListFiles(const std::string& dirpath);
    
    // Leitura/Escrita
    static std::string ReadTextFile(const std::string& filepath);
    static bool WriteTextFile(const std::string& filepath, const std::string& content);
    
    // Deletar
    static bool DeleteFile(const std::string& filepath);
};

#endif // FILEMANAGER_HPP