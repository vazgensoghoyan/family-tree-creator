### !!!! Пока в разработке


# Семейное Древо - FamilyTree

**FamilyTree** - это приложение для создания, визуализации и исследования вашего семейного древа. С помощью этого инструмента вы сможете сохранить историю своей семьи, установить родственные связи и визуализировать сложные семейные отношения в понятном графическом виде.

## Технологический стек

- **Язык программирования**: C++17
- **База данных**: SQLite
- **Система сборки**: CMake

## Установка и запуск

### Требования
- Компилятор C++ с поддержкой C++17 (GCC 9+, Clang 10+)
- Qt6 Core, Widgets и Gui модули
- SQLite3
- Graphviz (для расширенной визуализации)

### Сборка из исходников

```bash
# Клонировать репозиторий
git clone https://github.com/vazgensoghoyan/family-tree-creator
cd family-tree-creator

# Создать директорию для сборки
mkdir build
cd build

# Запустить CMake
cmake ..

# Собрать проект
make

# Запустить приложение
./family_tree
```

## Основные функции

### потом оформлю


## Структура проекта

```
family-tree-creator/
├── include/                            # Заголовочные файлы
│   ├── database/                       # Работа с базами данных
│   │   ├── data/
│   │   │   ├── db_column_info.hpp
│   │   │   ├── db_table_schema.hpp
│   │   │   └── db_table.hpp
│   │   ├── sql/
│   │   │   └── sql_formatter.hpp
│   │   └── db_stream.hpp
│   └── project_data/                   # Данные/бд приложения
│       ├── person_builder.hpp
│       ├── person_db.hpp
│       └── person.hpp
├── src/                                # Исходный код
│   ├── db_stream.cpp
│   ├── main.cpp                        # Точка входа
│   ├── person_builder.cpp
│   ├── person_db.cpp
│   ├── person.cpp
│   └── sql_formatter.cpp
├── tests/                              # Юнит-тесты
│   ├── test_db_stream.cpp
│   └── test_sql_formatter.cpp
├── .gitignore
├── CMakeLists.txt                      # Конфигурация сборки
└── README.md
```
    
## Лицензия

Этот проект распространяется под лицензией MIT.
