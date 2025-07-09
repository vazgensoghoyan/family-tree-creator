#include "project_data/person_db.hpp"

// namespace project_data

// class PersonDb

project_data::PersonDb& project_data::PersonDb::instance() {
    static PersonDb personDb;
    return personDb;
}

void project_data::PersonDb::addPerson(const Person& person) {
    stream_.insertInto(
        tableName_,
        { "full_name", "birth_date", "bio" },
        { { 
            person.getFullName(),
            person.getBirthDate(),
            person.getBio()
        } }
    );
}

// private part

project_data::PersonDb::PersonDb() : stream_{"persons.db"}, tableName_{"persons"} {
    stream_.createTable( 
        tableName_,
        database::data::TableSchema {
            {
                database::data::ColumnInfo{ "id", "INTEGER", true, false },
                database::data::ColumnInfo{ "full_name", "TEXT", false, true },
                database::data::ColumnInfo{ "birth_date", "DATE" },
                database::data::ColumnInfo{ "bio", "TEXT" },
                database::data::ColumnInfo{ "father_id", "INTEGER" },
                database::data::ColumnInfo{ "mother_id", "INTEGER" },
            }
        },
        true
    );
}

project_data::PersonDb::~PersonDb() = default;
