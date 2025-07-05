#ifndef _DB_STREAM_HPP_
#define _DB_STREAM_HPP_

#include <sqlite3.h>
#include <string>
#include <unordered_set>
#include <db_table_schema.hpp>

namespace database {

class DatabaseStream {

public:
    DatabaseStream(std::string db_name);            // db opens, reads tables names
    ~DatabaseStream();                              // db closes

    void createTable(DatabaseTableSchema* schema);  // both understandable
    void dropTable(std::string table_name);         // 

private:
    void read_tables_names();

private:
    sqlite3* _db;
    std::unordered_set<std::string> tables_names_;
};

}

#endif // _DB_STREAM_HPP_
