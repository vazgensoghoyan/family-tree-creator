cmake_minimum_required(VERSION 3.13)
project(family_tree)

# Ищем библиотеку SQLite3
find_package(SQLite3 REQUIRED)

# Исходные файлы
set(SRC_FILES
    src/main.cpp
    src/db_stream.cpp
)

# Исполняемый файл
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Директории с заголовками
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Линкуем с SQLite3
target_link_libraries(family_tree PRIVATE SQLite::SQLite3)