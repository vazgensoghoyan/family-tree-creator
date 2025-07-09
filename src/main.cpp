#include "project_data/person_db.hpp"
#include "project_data/person_builder.hpp"

using namespace project_data;

int main() {
    auto& db = PersonDb::instance();

    db.addPerson(
        PersonBuilder()
            .setFullName("mike")
            .setBio("goodboy")
            .setBirhtDate("09.02.1974")
            .setFatherByID(13)
            .build()
    );

    return 0;
}
