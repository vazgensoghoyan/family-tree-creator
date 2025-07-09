#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "database/db_stream.hpp"

using namespace database;

TEST_SUITE("SqlFormatter") {
    
    using f = sql::SqlFormatter;
        
    TEST_CASE("CREATE TABLE formatting") {

        SUBCASE("test 1") {
            std::string result, expected;

            data::Table table {
                "t1",
                data::TableSchema{
                    { 
                        { "c1", "boolean" },
                        { "c2", "integer" },
                        { "c3", "float" },
                        { "c4", "string" }
                    }
                }
            };
            
            result = f::format_create_expr( table, false );
            expected = "CREATE TABLE t1 (c1 boolean, c2 integer, c3 float, c4 string);";
            CHECK( result == expected );
            
            result = f::format_create_expr( table, true );
            expected = "CREATE TABLE IF NOT EXISTS t1 (c1 boolean, c2 integer, c3 float, c4 string);";
            CHECK( result == expected );
        }

        SUBCASE("test 2") {
            std::string result, expected;

            data::Table table = {
                "students",
                data::TableSchema{
                    {
                        { "id", "SERIAL", true, false },
                        { "first_name", "STRING", false, false },
                        { "middle_name", "STRING", false, true, data::ColumnInfo::DefaultValue::Null() },
                        { "last_name", "STRING", false, false },
                        { "score", "INTEGER", false, false, data::ColumnInfo::DefaultValue::Specified("0") }
                    }
                }
            };
            
            result = f::format_create_expr( table, false );
            expected = "CREATE TABLE students (id SERIAL PRIMARY KEY, first_name STRING NOT NULL, middle_name STRING DEFAULT NULL, last_name STRING NOT NULL, score INTEGER NOT NULL DEFAULT 0);";
            CHECK( result == expected );
        }
    
    }

    TEST_CASE( "DROP TABLE formatting" ) {

        SUBCASE("test 1") {
            std::string result, expected;
            
            result = f::format_drop_expr( "some_table_name", false );
            expected = "DROP TABLE some_table_name";
            CHECK( result == expected );
        }

        SUBCASE("test 2") {
            std::string result, expected;
            
            result = f::format_drop_expr( "helloWorld", true );
            expected = "DROP TABLE IF EXISTS helloWorld";
            CHECK( result == expected );
        }
    
    }

    TEST_CASE( "INSERT INTO formatting" ) {

        SUBCASE("test 1") {
            CHECK_THROWS_AS( 
                f::format_insert_expr( "some_table_name", 
                    { "c1", "", "c3" },
                    { {"only_one_value"} }
                ),
                std::runtime_error
            );
        }

        SUBCASE("test 2") {
            std::string result, expected;
            
            result = f::format_insert_expr( 
                "helloWorld",
                { "first_name", "last_name" },
                { { "Mike", "Peterson" }, { "Spider", "maN" } }
            );

            expected = "INSERT INTO helloWorld (first_name, last_name) VALUES ('Mike', 'Peterson'), ('Spider', 'maN');";
            CHECK( result == expected );
        }

    }

}
