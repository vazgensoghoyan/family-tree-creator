#ifndef _SQL_FORMATTER_HPP_
#define _SQL_FORMATTER_HPP_

#include <string>
#include <sstream>
#include "../data/db_table.hpp"

namespace database::sql {

class SqlFormatter {

public:
    SqlFormatter() = delete;
    ~SqlFormatter() = delete;

    static std::string format_create_expr(data::Table* table, bool ifNotExists);
    static std::string format_drop_expr(std::string table_name, bool ifExists);

};

}


#endif // _SQL_FORMATTER_HPP_