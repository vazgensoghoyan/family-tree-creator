#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <string>
#include "db_table_schema.hpp"

namespace database::data {

class Table {
    
public:
    Table(std::string name, TableSchema schema) : name(std::move(name)), schema(std::move(schema)) { }

    Table(const Table&) = default;
    Table(Table&&) noexcept = default;

    Table& operator=(const Table&) = default;
    Table& operator=(Table&&) noexcept = default;

    ~Table() = default;

public:
    const std::string name;
    const TableSchema schema;

};

}

#endif // _TABLE_HPP_