#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "database/db_stream.hpp"
#include <vector>


TEST_SUITE("Database") {

    class DbStreamTester {

    public:
        DbStreamTester( std::string db_name ) {
            stream_ = new database::DbStream( db_name );
        }

        ~DbStreamTester() {
            delete stream_;
        }

    private:
        database::DbStream* stream_;

    };

    TEST_CASE("DbStream") {
        DbStreamTester* tester = nullptr;
        
        SUBCASE("Opening database") {
            CHECK_NOTHROW( 
                tester = new DbStreamTester( "test.db" );
            );
        }

        SUBCASE("Create table") {
        }
        
        SUBCASE("Closing database") {
            CHECK_NOTHROW(
                delete tester;
            );
        }
        
    }
    
    TEST_CASE("SqlFormatter") {
        
        using f = database::sql::SqlFormatter;

        SUBCASE("Create test 1") {
            std::string result, expected;

            auto table = new database::data::Table{
                "t1",
                new database::data::TableSchema{
                    { 
                        { "c1", "boolean", false, true, {false, false, ""} },
                        { "c2", "integer", false, true, {false, false, ""} },
                        { "c3", "float", false, true, {false, false, ""} },
                        { "c4", "string", false, true, {false, false, ""} }
                    }
                }
            };
            
            result = f::format_create_expr( table, false );
            expected = "CREATE TABLE t1 (c1 boolean, c2 integer, c3 float, c4 string);";
            CHECK( result == expected );
            
            result = f::format_create_expr( table, true );
            expected = "CREATE TABLE IF NOT EXISTS t1 (c1 boolean, c2 integer, c3 float, c4 string);";
            CHECK( result == expected );

            delete table;
        }

        SUBCASE("Create test 2") {
            std::string result, expected;

            auto table = new database::data::Table{
                "students",
                new database::data::TableSchema{
                    { 
                        { "id", "SERIAL", true, false, {false, false, ""} },
                        { "first_name", "STRING", false, false, {false, false, ""} },
                        { "middle_name", "STRING", false, true, {true, true, ""} },
                        { "last_name", "STRING", false, false, {false, false, ""} },
                        { "score", "INTEGER", false, false, {true, false, "0"} }
                    }
                }
            };
            
            result = f::format_create_expr( table, false );
            expected = "CREATE TABLE students (id SERIAL PRIMARY KEY, first_name STRING NOT NULL, middle_name STRING DEFAULT NULL, last_name STRING NOT NULL, score INTEGER NOT NULL DEFAULT 0);";
            CHECK( result == expected );

            delete table;
        }

        SUBCASE("Drop test 1") {
            std::string result, expected;
            
            result = f::format_drop_expr( "some_table_name", false );
            expected = "DROP TABLE t1";
            CHECK( result == expected );
        }

        SUBCASE("Drop test 2") {
            std::string result, expected;
            
            result = f::format_drop_expr( "helloWorld", true );
            expected = "DROP TABLE IF EXISTS helloWorld";
            CHECK( result == expected );
        }

    }
    
    TEST_CASE("Table") {

        SUBCASE("") {
            
        }
    }
    
    TEST_CASE("TableSchema") {

        SUBCASE("") {
            
        }
    }
    
}


TEST_SUITE("") {

    TEST_CASE("") {

        SUBCASE("") {
            
        }

        SUBCASE("") {
            
        }
    }

}
