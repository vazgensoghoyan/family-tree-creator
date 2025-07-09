#include "database/sql/sql_formatter.hpp"

// namespace database::sql

std::string database::sql::SqlFormatter::format_create_expr(const data::Table& table, bool ifNotExists) {
    std::stringstream ss;
    ss << "CREATE TABLE ";
    if (ifNotExists) ss << "IF NOT EXISTS ";
    ss << table.name << " (";

    const auto& schema = table.schema.column_infos;

    for ( size_t i = 0; i < schema.size(); ++i ) {
        const auto& col = schema[i];

        ss << col.name << " " << col.type;
        
        if (!col.isNullable && !col.isPKey)
            ss << " NOT NULL";

        if (col.isPKey)
            ss << " PRIMARY KEY";
        
        if (col.defValue.isSpecified) {
            if (col.defValue.isNull) {
                ss << " DEFAULT NULL";
            } else {
                ss << " DEFAULT " << col.defValue.value;
            }
        }
        
        if (i < schema.size() - 1) 
            ss << ", ";
    }
    
    ss << ");";
    return ss.str();
}

std::string database::sql::SqlFormatter::format_drop_expr(const std::string& table_name, bool ifExists) {
    std::stringstream ss;
    ss << "DROP TABLE ";
    if (ifExists) ss << "IF EXISTS ";
    ss << table_name;
    return ss.str();
}

std::string database::sql::SqlFormatter::format_insert_expr(
        const std::string& table_name, 
        const std::vector<std::string>& column_names, 
        const std::vector<std::vector<std::string>>& values
) {
    std::stringstream ss;
    ss << "INSERT INTO ";
    ss << table_name << " (";

    for ( size_t i = 0; i < column_names.size(); ++i ) {
        if ( i > 0 )
            ss << ", ";
        ss << column_names[i];
    }
    ss << ") VALUES ";

    for ( size_t i = 0; i < values.size(); ++i ) {
        if ( column_names.size() != values[i].size() )
            throw std::runtime_error( "Columns and values counts must be equal in INSERT" );

        if ( i > 0 )
            ss << ", ";

        ss << '(';
        for ( size_t j = 0; j < values[i].size(); ++j ) {
            if (j > 0)
                ss << ", ";

            ss << '\'' << values[i][j] << '\'';
        }
        ss << ')';
    }
    ss << ';';

    return ss.str();
}
