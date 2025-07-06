#include <db_stream.hpp>

// namespace database

// class DbStream

database::DbStream::DbStream(std::string db_name) {
    int result = sqlite3_open(db_name.c_str(), &db_);

    if (result != SQLITE_OK)
        throw std::runtime_error("Ошибка открытия БД");
}

database::DbStream::~DbStream() {
    for ( auto [name, table] : tables_ )
        if ( table != nullptr )
            delete table;

    sqlite3_close(db_);
}

void database::DbStream::createTable(std::string table_name, TableSchema* schema, bool ifNotExists) {
    Table* new_table = new Table(table_name, schema);

    std::string sql_expr = format_create_expr(new_table, ifNotExists);

    int exec_result = sqlite3_exec(db_, sql_expr.c_str(), 0, 0, 0);

    if ( exec_result != SQLITE_OK ) {
        throw std::runtime_error("Ошибка создания таблицы");
    }

    tables_.insert( {table_name, new_table} );
}

void database::DbStream::dropTable(std::string table_name, bool ifExists) {
    std::string sql_expr = format_drop_expr(table_name, ifExists);

    int exec_result = sqlite3_exec(db_, sql_expr.c_str(), 0, 0, 0);

    if ( exec_result != SQLITE_OK ) {
        throw std::runtime_error("Ошибка удаления таблицы");
    }

    tables_.erase(table_name);
}

// DbStream private methods

void database::DbStream::read_tables_names() {

    // TODO

}

std::string database::DbStream::format_create_expr(Table* table, bool ifNotExists) {

    // TODO

}

std::string database::DbStream::format_drop_expr(std::string table_name, bool ifExists) {

    // TODO

}