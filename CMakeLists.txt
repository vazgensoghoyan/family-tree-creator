cmake_minimum_required(VERSION 3.13)
project(family_tree)


# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Флаги компиляции
add_compile_options(-Wall -Wextra -Werror -O2)


# Ищем библиотеку SQLite3
find_package(SQLite3 REQUIRED)

# Исходные файлы
set(SRC_FILES
    src/db_stream.cpp
    src/sql_formatter.cpp
)

# Исполняемый файл
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SRC_FILES}
)

# Тестовый исполняемый файл
add_executable(${PROJECT_NAME}_tests
    tests/test.cpp
    ${SRC_FILES}
)

# Директории с заголовками
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME}_tests PRIVATE include)

# Линкуем с SQLite3
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE SQLite::SQLite3)
