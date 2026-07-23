cmake_minimum_required(VERSION 3.28)
project(EtnaZ_Engine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
        tinyfiledialogs
        GIT_REPOSITORY https://github.com/native-toolkit/tinyfiledialogs.git
        GIT_TAG master
        EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(tinyfiledialogs)

add_executable(EtnaZ_Engine Main/main.cpp
        Main/GameEngine.h
        Main/GameEngine.cpp
        Scene/Scene.h
        Scene/Scene.cpp
        Scene/Scene.h
        Object/Object.h
        Object/Object.cpp
        Dev.h
        Dev.cpp
        Scene/Layer.h
        Scene/Layer.cpp
        Object/Component/Component.h
        Object/Component/Component.cpp
        Object/Component/Graphics/RenderComponent.h
        Object/Component/Graphics/RenderComponent.cpp
        Object/Component/Periph/MouseComponent.h
        Object/Component/Periph/MouseComponent.cpp
        Tool/Input.h
        Tool/Input.cpp
        ViewIsometrique/IsoUtils.h
        ViewIsometrique/IsoUtils.cpp
        ViewIsometrique/IsoComponent.h
        ViewIsometrique/IsoComponent.cpp
        ViewIsometrique/IsoDisplay.h
        ViewIsometrique/IsoDisplay.cpp
        Reader/Reader.h
        Reader/Reader.cpp
        Reader/SceneReader.h
        Reader/SceneReader.cpp
        Object/Component/Tool/CameraComponent.h
        Object/Component/Tool/CameraComponent.cpp
        Globals.h
        Object/Component/Periph/DragComponent.h
        Object/Component/Periph/DragComponent.cpp
        Object/Component/Engine/ReadTileComponent.h
        Object/Component/Engine/ReadTileComponent.cpp
        Object/Component/Graphics/RenderTextComponent.h
        Object/Component/Graphics/RenderTextComponent.cpp
        Object/Component/Graphics/HoverComponent.h
        Object/Component/Graphics/HoverComponent.cpp
        ${tinyfiledialogs_SOURCE_DIR}/tinyfiledialogs.c
        Object/Component/Engine/OpenFileExplorerComponent.cpp
        Object/Component/Engine/OpenFileExplorerComponent.h
        Object/Component/Engine/MapEditorComponent.h
        Object/Component/Engine/MapEditorComponent.cpp
        Object/Component/Engine/FillTileComponent.h
        Object/Component/Engine/FillTileComponent.cpp
        Tool/TexturesChest.h
        Tool/TexturesChest.cpp
        Object/Component/Engine/ToolBarreComponent.h
        Object/Component/Engine/ToolBarreComponent.cpp
        Object/Component/Engine/ToolBarre/ToolBarreMenuComponent.h
        Object/Component/Engine/ToolBarre/ToolBarreMenuComponent.cpp
        Object/Component/Dev/TestComponent.h
        Object/Component/Dev/TestComponent.cpp)

target_include_directories(EtnaZ_Engine PRIVATE ${tinyfiledialogs_SOURCE_DIR})

target_link_libraries(EtnaZ_Engine PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        nlohmann_json::nlohmann_json)

add_custom_command(TARGET EtnaZ_Engine POST_BUILD COMMAND 
        ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_SOURCE_DIR}/Assets 
        $<TARGET_FILE_DIR:EtnaZ_Engine>/Assets )

add_custom_command(TARGET EtnaZ_Engine POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Engine
        $<TARGET_FILE_DIR:EtnaZ_Engine>/Engine )