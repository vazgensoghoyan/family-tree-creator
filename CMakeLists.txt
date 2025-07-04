cmake_minimum_required(VERSION 3.13)
project(family_tree)

# Исходные файлы
set(SRC_FILES
    src/main.cpp
)

# Исполняемый файл
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Директории с заголовками
target_include_directories(${PROJECT_NAME} PRIVATE include)
