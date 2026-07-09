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
        ViewIsometrique/IsoDisplay.cpp)

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