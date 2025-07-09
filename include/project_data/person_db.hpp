#ifndef _PERSON_DB_HPP_
#define _PERSON_DB_HPP_

#include "../database/db_stream.hpp"
#include <string>

namespace project_data {

class PersonDb {

public:
    static PersonDb& instance();

    PersonDb(const PersonDb&) = delete;
    PersonDb& operator=(const PersonDb&) = delete;

    void addPerson(const std::string& name);

private:
    PersonDb();
    ~PersonDb();

private:
    database::DbStream stream_;
    std::string tableName_;
    size_t current_id_;
};
    
}


#endif // _PERSON_DB_HPP_