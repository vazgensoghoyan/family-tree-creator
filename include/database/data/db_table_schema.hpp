#ifndef _DB_TABLE_SCHEMA_HPP_
#define _DB_TABLE_SCHEMA_HPP_

#include <vector>
#include <exception>
#include "db_column_info.hpp"

namespace database::data {

class TableSchema {

public:
    TableSchema(const std::vector<ColumnInfo>& columns) : column_infos(columns) { }
    TableSchema(std::vector<ColumnInfo>&& columns) : column_infos(std::move(columns)) { }

    ~TableSchema() { }

public:
    const std::vector<ColumnInfo> column_infos;

};

}

#endif // _DB_TABLE_SCHEMA_HPP_