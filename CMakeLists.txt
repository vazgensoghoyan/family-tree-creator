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

# Директории с заголовками
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Линкуем с SQLite3
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)


# Автоматическая регистрация тестов
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")  # Автообновление списка

foreach(TEST_SOURCE ${TEST_SOURCES})
    # Извлекаем имя теста без расширения (например, test_sql_formatter)
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # Создаем исполняемый файл теста
    add_executable(${TEST_NAME} ${TEST_SOURCE} ${SRC_FILES})
    
    # Настройка для теста
    target_include_directories(${TEST_NAME} PRIVATE include)
    target_link_libraries(${TEST_NAME} PRIVATE SQLite::SQLite3)
    
    # Регистрируем тест в CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
