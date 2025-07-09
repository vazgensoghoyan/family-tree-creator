#include "project_data/person_db.hpp"

int main() {
    auto& db = project_data::PersonDb::instance();

    db.addPerson("name1");
    db.addPerson("mike");
    db.addPerson("hithere");

    return 0;
}
