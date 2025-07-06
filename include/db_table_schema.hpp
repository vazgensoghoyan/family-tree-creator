#ifndef _DB_TABLE_SCHEMA_HPP_
#define _DB_TABLE_SCHEMA_HPP_

#include <vector>
#include <exception>
#include <db_column_info.hpp>

namespace database {

class TableSchema {

public:
    TableSchema(std::vector<ColumnInfo> columns) : column_infos(columns) { }

    ~TableSchema() { }

public:
    const std::vector<ColumnInfo> column_infos;

};

}

#endif // _DB_TABLE_SCHEMA_HPP_