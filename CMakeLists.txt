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

# Тестовые исполняемые файлы
add_executable(test_sql_formatter
    tests/test_sql_formatter.cpp
    ${SRC_FILES}
)
add_executable(test_db_stream
    tests/test_db_stream.cpp
    ${SRC_FILES}
)

# Директории с заголовками
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(test_sql_formatter PRIVATE include)
target_include_directories(test_db_stream PRIVATE include)

# Линкуем с SQLite3
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)
target_link_libraries(test_sql_formatter PRIVATE SQLite::SQLite3)
target_link_libraries(test_db_stream PRIVATE SQLite::SQLite3)

# Регистрируем тесты в CTest
add_test(NAME test_sql_formatter COMMAND test_sql_formatter)
add_test(NAME test_db_stream COMMAND test_db_stream)
