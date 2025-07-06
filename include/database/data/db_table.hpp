#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <string>
#include "db_table_schema.hpp"

namespace database::data {

class Table {
    
public:
    Table(std::string name, TableSchema* schema) : name(name), schema(schema) { }
    
    ~Table() { }

    void insertValues(std::string* row);

    const auto& getValues() const { return rows; }

public:
    const std::string name;
    const TableSchema* schema;
    const std::vector<std::vector<std::string>> rows;

};

}

#endif // _TABLE_HPP_