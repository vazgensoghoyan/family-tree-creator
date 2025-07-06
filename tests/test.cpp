#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "database/db_stream.hpp"


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
    
    TEST_CASE("ColumnInfo") {

        SUBCASE("") {
            
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

