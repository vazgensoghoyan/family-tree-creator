#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "database/db_stream.hpp"
#include <vector>
#include <filesystem>


TEST_SUITE("Database") {

    class DbStreamTester {

    public:
        DbStreamTester( std::string db_name ) {
            stream_ = new database::DbStream( db_name );
        }

        ~DbStreamTester() {
            delete stream_;
        }

        void createTable(std::string table_name, database::data::TableSchema* schema, bool ifNotExists = false) {
            stream_->createTable(table_name, schema, ifNotExists);
        }

        void createTestTable(bool ifNotExists) {
            createTable(
                "test_table", 
                new database::data::TableSchema{ {
                        { "c1", "boolean", false, true, {false, false, ""} },
                        { "c2", "integer", false, true, {false, false, ""} },
                        { "c3", "float", false, true, {false, false, ""} },
                        { "c4", "string", false, true, {false, false, ""} }
                    } },
                ifNotExists 
            );
        }

        void dropTable(std::string table_name, bool ifExists = false) {
            stream_->dropTable(table_name, ifExists);
        }

    private:
        database::DbStream* stream_;

    };

    TEST_CASE("DbStream") {

        // clearing test.db before TEST_CASE once
        static bool db_cleaned = false;
        if (!db_cleaned) {
            std::error_code ec;
            std::filesystem::remove("test.db", ec);
            db_cleaned = true;
        }
        
        // creating tester (its created before every SUBCASE)
        DbStreamTester tester("test.db");
        
        SUBCASE("Opening and closing database") {
            // already done, because tester is created before every SUBCASE
        }

        SUBCASE("Create table") {
            CHECK_NOTHROW(
                tester.createTestTable(false);
            );
        }

        SUBCASE("Create same table without 'if not exists' (should throw error)") {
            CHECK_THROWS_AS(
                tester.createTestTable(false),
                std::runtime_error
            );
        }

        SUBCASE("Create same table without 'if not exists' (should throw error)") {
            SUBCASE("Create table") {
                CHECK_NOTHROW(
                    tester.createTestTable(true);
                );
            }
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
            expected = "DROP TABLE some_table_name";
            CHECK( result == expected );
        }

        SUBCASE("Drop test 2") {
            std::string result, expected;
            
            result = f::format_drop_expr( "helloWorld", true );
            expected = "DROP TABLE IF EXISTS helloWorld";
            CHECK( result == expected );
        }

    }

}

TEST_SUITE("doctest") {

    struct Tracer {
        const char* name;
        Tracer(const char* n) : name(n) { std::cout << "Construct " << name << "\n"; }
        ~Tracer() { std::cout << "Destruct " << name << "\n"; }
    };

    TEST_CASE("Lifecycle Demo") {
        Tracer outer("outer");  // Вне SUBCASE
        
        std::cout << "--- Before SUBCASE ---\n";
        
        SUBCASE("First") {
            Tracer inner("inner");
            std::cout << "Inside FIRST SUBCASE\n";
        }
        
        SUBCASE("Second") {
            Tracer inner("inner");
            std::cout << "Inside SECOND SUBCASE\n";
        }
        
        std::cout << "--- After SUBCASE ---\n";
    }

}
