#include "database/db_stream.hpp"

// namespace database

// class DbStream

database::DbStream::DbStream(std::string db_name) {
    int result = sqlite3_open(db_name.c_str(), &db_);

    if (result != SQLITE_OK)
        throw std::runtime_error("Ошибка открытия БД");

    read_tables_names();
}

database::DbStream::~DbStream() {
    for ( auto [name, table] : tables_ )
        if ( table != nullptr )
            delete table;

    sqlite3_close(db_);
}

// sql commands

void database::DbStream::createTable(const std::string& table_name, const data::TableSchema& schema, bool ifNotExists) {
    data::Table* new_table = new data::Table(table_name, schema);

    std::string sql_expr = sql::SqlFormatter::format_create_expr(*new_table, ifNotExists);

    int exec_result = sqlite3_exec(db_, sql_expr.c_str(), 0, 0, 0);

    if ( exec_result != SQLITE_OK ) {
        throw std::runtime_error("Error creating table");
    }

    tables_.insert( {table_name, new_table} );
}

void database::DbStream::dropTable(const std::string& table_name, bool ifExists) {
    std::string sql_expr = sql::SqlFormatter::format_drop_expr(table_name, ifExists);

    int exec_result = sqlite3_exec(db_, sql_expr.c_str(), 0, 0, 0);

    if ( exec_result != SQLITE_OK ) {
        throw std::runtime_error("Error dropping table");
    }

    tables_.erase(table_name);
}

void database::DbStream::insertInto(
    const std::string& table_name, 
    const std::vector<std::string>& column_names, 
    const std::vector<std::vector<std::string>>& values
) {
    std::string sql_expr = sql::SqlFormatter::format_insert_expr(table_name, column_names, values);

    int exec_result = sqlite3_exec(db_, sql_expr.c_str(), 0, 0, 0);

    if ( exec_result != SQLITE_OK ) {
        throw std::runtime_error("Error inserting values to table");
    }
}


// getters

std::vector<std::string> database::DbStream::get_table_names() const {
    std::vector<std::string> names;
    for ( const auto& pr : tables_ )
        names.push_back( pr.first );
    return names;
}

const database::data::Table& database::DbStream::get_table(const std::string& table_name) const {
    if ( tables_.at(table_name) != nullptr ) {
        return *tables_.at(table_name);
    }

    // TODO

    return *tables_.at("");

}

// DbStream private methods

void database::DbStream::read_tables_names() {
    sqlite3_stmt* stmt;
    
    const char* sql = "SELECT name FROM sqlite_master "
                      "WHERE type='table' AND name NOT LIKE 'sqlite_%';";
    
    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* txt = sqlite3_column_text(stmt, 0);

        const char* table_name = reinterpret_cast<const char*>(txt);

        if (table_name) {
            tables_.insert({ std::string(table_name), nullptr });
        }
    }
    
    sqlite3_finalize(stmt);
}