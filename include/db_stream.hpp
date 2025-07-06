#ifndef _DB_STREAM_HPP_
#define _DB_STREAM_HPP_

#include <sqlite3.h>
#include <string>
#include <unordered_map>
#include <db_table.hpp>
#include <stdexcept>
#include <sstream>

namespace database {

class DbStream {

public:
    DbStream(std::string db_name);          // db opens, reads tables names
    ~DbStream();                            // db closes

    void createTable(std::string table_name, TableSchema* schema, bool ifNotExists = false);
    void dropTable(std::string table_name, bool ifExists = false);

    const Table* get_table(std::string table_name) const;

private:
    void read_tables_names();
    std::string format_create_expr(Table* table, bool ifNotExists);
    std::string format_drop_expr(std::string table_name, bool ifExists);

private:
    sqlite3* db_;
    std::unordered_map<std::string, Table*> tables_;

};

}

#endif // _DB_STREAM_HPP_
