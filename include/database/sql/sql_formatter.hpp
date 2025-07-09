#ifndef _SQL_FORMATTER_HPP_
#define _SQL_FORMATTER_HPP_

#include <string>
#include <sstream>
#include "../data/db_table.hpp"

namespace database::sql {

/*
 *
 *
 * CREATE TABLE t1 (c1 BOOLEAN, c2 INTEGER, c3 FLOAT, c4 STRING)
 * 
 * CREATE TABLE IF NOT EXISTS t1 (c1 BOOLEAN, c2 INTEGER, c3 FLOAT, c4 STRING)
 * 
 * CREATE TABLE t1 (c1 BOOLEAN, c2 INTEGER, c3 FLOAT, c4 STRING)
 * 
 * DROP TABLE t1
 * 
 * DROP TABLE IF EXISTS t1
 * 
 * DROP TABLE t1
 * 
 * CREATE TABLE students (id SERIAL PRIMARY KEY, first_name STRING NOT NULL, middle_name STRING DEFAULT NULL, last_name STRING NOT NULL, score INTEGER NOT NULL DEFAULT 0)
 * 
 * INSERT INTO students (first_name, last_name) VALUES ('\u0418\u0432\u0430\u043d', '\u0418\u0432\u0430\u043d\u043e\u0432'), ('\u041f\u0451\u0442\u0440', '\u041f\u0435\u0442\u0440\u043e\u0432'), ('\u0410\u043d\u0434\u0440\u0435\u0439', '\u0410\u043d\u0434\u0440\u0435\u0435\u0432')
 * 
 * INSERT INTO students (first_name, middle_name, last_name) VALUES ('\u0421\u0435\u0440\u0433\u0435\u0439', '\u0421\u0435\u0440\u0433\u0435\u0435\u0432\u0438\u0447', '\u0421\u0435\u0440\u0433\u0435\u0435\u0432'), ('\u0410\u043b\u0435\u043a\u0441\u0430\u043d\u0434\u0440', '\u0410\u043b\u0435\u043a\u0441\u0430\u043d\u0434\u0440\u043e\u0432\u0438\u0447', '\u0410\u043b\u0435\u043a\u0441\u0430\u043d\u0434\u0440\u043e\u0432')
 * 
 * INSERT INTO students (first_name) VALUES ('\u041d\u0435\u0434\u043e\u0431\u0430\u0432\u043b\u044f\u0439')
 * 
 * INSERT INTO bad_table (first_name, last_name) VALUES ('\u041f\u043b\u043e\u0445\u0438\u0448', '\u041f\u043b\u043e\u0445\u0438\u0448\u043e\u0432')
 * 
 * SELECT first_name FROM students WHERE id = 1
 * 
 * SELECT first_name, last_name FROM students WHERE id <= 2
 * 
 * UPDATE students SET score = 10 WHERE id <= 2
 * 
 * UPDATE students SET score = 20 WHERE first_name < '\u0411' RETURNING last_name
 * 
 * DELETE FROM students WHERE score > 0 RETURNING id
 * 
 * DELETE FROM students RETURNING id
 * 
 * 
 * 
 * 
 * 
 * 
*/

class SqlFormatter {

public:
    SqlFormatter() = delete;
    ~SqlFormatter() = delete;

    static std::string format_create_expr(const data::Table& table, bool ifNotExists);
    static std::string format_drop_expr(const std::string& table_name, bool ifExists);

};

}


#endif // _SQL_FORMATTER_HPP_