#include "project_data/person_db.hpp"

// namespace project_data

// class PersonDb

project_data::PersonDb& project_data::PersonDb::instance() {
    static PersonDb personDb;
    return personDb;
}

void project_data::PersonDb::addPerson(const std::string& name) {
    stream_.insertInto(
        tableName_,
        { "id", "name" },
        { { std::to_string(current_id_++), name } }
    );
}

// private part

project_data::PersonDb::PersonDb() : stream_{"persons.db"}, tableName_{"persons"} {
    stream_.createTable( 
        tableName_,
        database::data::TableSchema {
            {
                database::data::ColumnInfo{ "id", "INTEGER AUTO_INCREMENT", true, false },
                database::data::ColumnInfo{ "name", "TEXT", false, true }
                //database::data::ColumnInfo{ "father", "INTEGER" },
                //database::data::ColumnInfo{ "mother", "INTEGER" }
            }
        },
        true
    );
}

project_data::PersonDb::~PersonDb() = default;