#pragma once
#include <cstdlib>

#include "../Component.h"
#include "tinyfiledialogs.h"

class OpenFileExplorerComponent final : public Component {
private:
    std::vector<std::string> filesCompatible;
    std::string path;
    
public:
    OpenFileExplorerComponent(Object* _owner, std::string _path, std::vector<std::string> _filesCompatible);
    virtual ~OpenFileExplorerComponent() override;
    
    void addFileCompatible(std::string extension);
    bool isExtensionCompatible(std::string extension);
    
    const std::filesystem::path openFileExplorer();
    
    virtual void update(float& deltaTime) override;
    virtual void render() override;
};
