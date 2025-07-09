#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "database/db_stream.hpp"
#include <filesystem>

using namespace database;


class DbStreamTester {

public:
    DbStreamTester( std::string db_name ) {
        stream_ = new DbStream( db_name );
    }

    ~DbStreamTester() {
        delete stream_;
    }

    void createTable(std::string table_name, const data::TableSchema& schema, bool ifNotExists = false) {
        stream_->createTable(table_name, schema, ifNotExists);
    }

    void createTestTable(bool ifNotExists) {
        createTable(
            "test_table", 
            data::TableSchema{ {
                { "c1", "boolean" },
                { "c2", "integer" },
                { "c3", "float" },
                { "c4", "string" }
            } },
            ifNotExists 
        );
    }

    void dropTable(std::string table_name, bool ifExists = false) {
        stream_->dropTable(table_name, ifExists);
    }

private:
    DbStream* stream_;

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
