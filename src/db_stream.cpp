#include <db_stream.hpp>

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

void database::DbStream::createTable(std::string table_name, data::TableSchema* schema, bool ifNotExists) {
    data::Table* new_table = new data::Table(table_name, schema);

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

const database::data::Table* database::DbStream::get_table(std::string table_name) const {

    // TODO

    return tables_.at(table_name);

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

std::string database::DbStream::format_create_expr(data::Table* table, bool ifNotExists) {
    std::stringstream ss;
    ss << "CREATE TABLE ";
    if (ifNotExists) ss << "IF NOT EXISTS ";
    ss << table->name << " (\n";

    const auto& schema = table->schema->column_infos;

    for ( size_t i = 0;i < schema.size(); ++i ) {
        const auto& col = schema[i];

        // Имя столбца и тип
        ss << "    " << col.name << " " << col.type;
        
        // Обработка NULL/NOT NULL
        if (!col.isNullable) {
            ss << " NOT NULL";
        }
        
        // Обработка значения по умолчанию
        if (col.defValue.isSpecified) {
            if (col.defValue.isNull) {
                ss << " DEFAULT NULL";
            } else {
                ss << " DEFAULT " << col.defValue.value;
            }
        }
        
        // Запятая для всех, кроме последнего столбца
        if (i < schema.size() - 1) 
            ss << ",";
        ss << "\n";
    }
    
    ss << ");";
    return ss.str();
}

std::string database::DbStream::format_drop_expr(std::string table_name, bool ifExists) {
    std::stringstream ss;
    ss << "DROP TABLE ";
    if (ifExists) ss << "IF EXISTS ";
    ss << table_name << " ";
    return ss.str();
}