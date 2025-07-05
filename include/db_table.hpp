#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include <string>
#include <db_table_schema.hpp>

namespace database {

class DatabaseTable {
    
public:
    explicit DatabaseTable(DatabaseTableSchema* schema);
    ~DatabaseTable();

    void insertValues(std::string* values);

private:
    DatabaseTableSchema* schema_;
    std::string** values_;

};

}

#endif // _TABLE_HPP_