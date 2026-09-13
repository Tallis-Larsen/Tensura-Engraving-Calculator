cmake_minimum_required(VERSION 3.16)

project(Engraving-Calculator)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp)

add_executable(engraving-calculator
        main.cpp
        ${SOURCES}
)

# Gets the FTXUI library at compile time
include(FetchContent)
if(DEFINED ENV{FTXUI_SOURCE_DIR})
  FetchContent_Declare(ftxui SOURCE_DIR $ENV{FTXUI_SOURCE_DIR})
else()
  FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG v7.0.3
    )
endif()
FetchContent_MakeAvailable(ftxui)

# Gets the doctest library at compile time
if(DEFINED ENV{DOCTEST_SOURCE_DIR})
  FetchContent_Declare(doctest SOURCE_DIR $ENV{DOCTEST_SOURCE_DIR})
else()
  FetchContent_Declare(doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.12
    )
endif()
FetchContent_MakeAvailable(doctest)

target_link_libraries(engraving-calculator PRIVATE ftxui::component ftxui::dom)
target_include_directories(engraving-calculator PRIVATE include)

# Installation rules
install(TARGETS engraving-calculator
    RUNTIME DESTINATION bin
)

# Automatically install after build
add_custom_command(TARGET engraving-calculator POST_BUILD
    COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --prefix $ENV{HOME}/.local
    COMMENT "Automatically installing to ~/.local/bin"
)
