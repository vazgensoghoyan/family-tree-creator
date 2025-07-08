#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <string>
#include "db_table_schema.hpp"

namespace database::data {

class Table {
    
public:
    Table(std::string name, const TableSchema& schema);
    Table(std::string name, TableSchema&& schema);
    
    ~Table();

    std::string getName() const;
    const TableSchema& getSchema() const;

public:
    const std::string name;
    const TableSchema schema;

};

}

#endif // _TABLE_HPP_