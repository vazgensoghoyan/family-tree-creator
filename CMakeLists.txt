cmake_minimum_required(VERSION 3.13)
project(family_tree)

# Включаем поддержку тестирования
enable_testing()

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Флаги компиляции
add_compile_options(-Wall -Wextra -Werror -O2)

# Ищем библиотеку SQLite3
find_package(SQLite3 REQUIRED)

# Автоматически собираем все исходные файлы из src (кроме main.cpp)
file(GLOB LIB_SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM LIB_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Главный исполняемый файл (с main.cpp)
add_executable(${PROJECT_NAME} 
    src/main.cpp
    ${LIB_SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)


# Загрузка doctest через FetchContent
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)


# Автоматическая регистрация тестов
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    add_executable(${TEST_NAME} 
        ${TEST_SOURCE}
        ${LIB_SRC_FILES}
    )

    target_include_directories(${TEST_NAME} PRIVATE include)
    target_link_libraries(${TEST_NAME} PRIVATE SQLite::SQLite3 doctest)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
