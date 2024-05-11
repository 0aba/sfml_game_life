cmake_minimum_required(VERSION 3.27)
project(game_life)

set(CMAKE_CXX_STANDARD 23)

add_executable(game_life main.cpp
        game_logic/game_logic.cpp
        game_logic/game_logic.hpp
        game_logic/my_types.hpp
        game_logic/settings.cpp
        game_logic/settings.hpp
        pages/menu_page.cpp
        pages/menu_page.hpp
        pages/Utils.hpp
        pages/rules_page.cpp
        pages/rules_page.hpp
        pages/settings_page.cpp
        pages/settings_page.hpp
        pages/game_page.cpp
        pages/game_page.hpp
        GUI/Widget.hpp
        GUI/Widget.cpp
        GUI/Utils.hpp
        GUI/MultilineTextArea.cpp
        GUI/MultilineTextArea.hpp
        GUI/Scrollbar.cpp
        GUI/Scrollbar.hpp
        GUI/HScrollbar.cpp
        GUI/HScrollbar.hpp
        GUI/VScrollbar.cpp
        GUI/VScrollbar.hpp
        GUI/Button.cpp
        GUI/Button.hpp
        GUI/Slider.cpp
        GUI/Slider.hpp
        GUI/HSlider.cpp
        GUI/HSlider.hpp
        GUI/VSlider.cpp
        GUI/VSlider.hpp
        GUI/ContextMenu.cpp
        GUI/ContextMenu.hpp
        GUI/ContextMenuElement.cpp
        GUI/ContextMenuElement.hpp
)

set(SFML_STATIC_LIBRARIES True)
set(SFML_DIR D:/Utils/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(D:/Utils/SFML-2.6.1/include/SFML)
target_link_libraries(game_life sfml-system sfml-window sfml-graphics sfml-audio)

