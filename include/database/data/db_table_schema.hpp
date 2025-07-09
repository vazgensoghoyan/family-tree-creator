#ifndef _DB_TABLE_SCHEMA_HPP_
#define _DB_TABLE_SCHEMA_HPP_

#include <vector>
#include <exception>
#include "db_column_info.hpp"

namespace database::data {

class TableSchema {

public:
    TableSchema(std::vector<ColumnInfo> columns) : column_infos(std::move(columns)) { }

    TableSchema(const TableSchema&) = default;
    TableSchema(TableSchema&&) noexcept = default;

    TableSchema& operator=(const TableSchema&) = default;
    TableSchema& operator=(TableSchema&&) noexcept = default;

    ~TableSchema() = default;

public:
    const std::vector<ColumnInfo> column_infos;

};

}

#endif // _DB_TABLE_SCHEMA_HPP_