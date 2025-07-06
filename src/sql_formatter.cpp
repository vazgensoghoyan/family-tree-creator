#include "database/sql/sql_formatter.hpp"

// namespace database::sql

std::string database::sql::SqlFormatter::format_create_expr(data::Table* table, bool ifNotExists) {
    std::stringstream ss;
    ss << "CREATE TABLE ";
    if (ifNotExists) ss << "IF NOT EXISTS ";
    ss << table->name << " (\n";

    const auto& schema = table->schema->column_infos;

    for ( size_t i = 0;i < schema.size(); ++i ) {
        const auto& col = schema[i];

        ss << "    " << col.name << " " << col.type;
        
        if (!col.isNullable) {
            ss << " NOT NULL";
        }
        
        if (col.defValue.isSpecified) {
            if (col.defValue.isNull) {
                ss << " DEFAULT NULL";
            } else {
                ss << " DEFAULT " << col.defValue.value;
            }
        }
        
        if (i < schema.size() - 1) 
            ss << ",";
        ss << "\n";
    }
    
    ss << ");";
    return ss.str();
}

std::string database::sql::SqlFormatter::format_drop_expr(std::string table_name, bool ifExists) {
    std::stringstream ss;
    ss << "DROP TABLE ";
    if (ifExists) ss << "IF EXISTS ";
    ss << table_name << " ";
    return ss.str();
}
