#ifndef _PERSON_DB_HPP_
#define _PERSON_DB_HPP_

#include "../database/db_stream.hpp"
#include "person.hpp"
#include <string>

namespace project_data {

class PersonDb {

public:
    static PersonDb& instance();

    PersonDb(const PersonDb&) = delete;
    PersonDb& operator=(const PersonDb&) = delete;

    void addPerson(const Person& person);

private:
    PersonDb();
    ~PersonDb();

private:
    database::DbStream stream_;
    std::string tableName_;
    
};
    
}


#endif // _PERSON_DB_HPP_