#ifndef _DB_STREAM_HPP_
#define _DB_STREAM_HPP_

#include <sqlite3.h>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include "data/db_table.hpp"
#include "sql/sql_formatter.hpp"

namespace database {


/*
  * 
 * DbStream db( "test.db" );
 * 
 * db.createTable( "people", TableSchema( std::vector<ColumnInfo> {
 *      {...},
 *      {...},
 *      {...}
 * } ) );
 * 
 * db.insertInto( "people", { "...", "...", ... } );
 * 
 * 
 * db.dropTable( "table_name" );
 * db.dropTable( "other_table", true/false );
 * 
*/


class DbStream {

public:
    DbStream(std::string db_name);  // db opens, reads tables names
    ~DbStream();                    // db closes

    void createTable(std::string table_name, data::TableSchema* schema, bool ifNotExists = false);
    void dropTable(std::string table_name, bool ifExists = false);

    std::vector<std::string> get_table_names() const;
    const data::Table* get_table(std::string table_name) const;

    friend class DbStreamTester;

private:
    void read_tables_names();

private:
    sqlite3* db_;
    std::unordered_map<std::string, data::Table*> tables_;

};

}

#endif // _DB_STREAM_HPP_
