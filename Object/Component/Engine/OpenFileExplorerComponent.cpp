#include "OpenFileExplorerComponent.h"

#include "../../Object.h"
#include "../Engine/ReadTile.h"

OpenFileExplorerComponent::OpenFileExplorerComponent(Object* _owner, std::string _path, std::vector<std::string> _filesCompatible) : Component(_owner) {
    filesCompatible = _filesCompatible;
    path = _path;
}

OpenFileExplorerComponent::~OpenFileExplorerComponent() {
    filesCompatible.clear();
}

void OpenFileExplorerComponent::addFileCompatible(std::string extension) {
    if (!extension.empty() && extension[0] == '.') {
        extension.erase(0, 1);
    }
    filesCompatible.push_back(extension);
}

bool OpenFileExplorerComponent::isExtensionCompatible(std::string extension) {
    if (!extension.empty() && extension[0] == '.') {
        extension.erase(0, 1);
    }
    for (const auto& compatible : filesCompatible) {
        if (compatible == extension) {
            return true;
        }
    }
    return false;
}

const std::filesystem::path OpenFileExplorerComponent::openFileExplorer() {
    if (filesCompatible.empty()) {
        return {}; 
    }
    
    std::vector<std::string> files;
    for (auto& f : filesCompatible) {
        std::string file = "*." + f;
        files.push_back(file);
    }
    
    std::vector<const char*> ext;
    for (auto& f : files) {
        ext.push_back(f.c_str());
    }
    
    const char* selectedPath = tinyfd_openFileDialog(
        "Choisir une image",   
        "",                     
        static_cast<int>(ext.size()), 
        ext.data(),             
        "Fichiers compatibles",          
        0                       
    );
    
    if (selectedPath != nullptr) {
        std::filesystem::path src(selectedPath);
        std::filesystem::path dest = std::filesystem::path(path) / src.filename();
        try {
            std::filesystem::copy_file(src, dest, std::filesystem::copy_options::overwrite_existing);
            return dest;
        }
        catch (const std::filesystem::filesystem_error& e) {
            tinyfd_messageBox("Erreur", "Impossible de copier l'image sélectionnée.", "ok", "error", 1);
            return {}; 
        }
    }
    return {};
}

void OpenFileExplorerComponent::update(float& deltaTime) {
}

void OpenFileExplorerComponent::render() {
    Component::render();
}
