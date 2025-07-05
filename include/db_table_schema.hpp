#ifndef _DB_TABLE_SCHEMA_HPP_
#define _DB_TABLE_SCHEMA_HPP_

#include <string>

namespace database {

class DatabaseTableSchema {

public:
    explicit DatabaseTableSchema(std::string* schema);
    ~DatabaseTableSchema();

private:
    std::string* schema_;

};

}

#endif // _DB_TABLE_SCHEMA_HPP_
