#ifndef _PERSON_BUILDER_HPP_
#define _PERSON_BUILDER_HPP_

#include "person.hpp"
#include <string>
#include <optional>

namespace project_data {

class PersonBuilder {

public:
    PersonBuilder() = default;
    ~PersonBuilder() = default;

    PersonBuilder& setFullName(std::string full_name);
    PersonBuilder& setBirhtDate(std::string birth_date);
    PersonBuilder& setBio(std::string bio);

    PersonBuilder& setFatherByID(int fatherId);
    PersonBuilder& setMotherByID(int motherId);

    Person build() const;

private:
    std::string full_name_;
    std::string birth_date_;
    std::string bio_;

    std::optional<int> father_id_;
    std::optional<int> mother_id_;
    
};

}


#endif // _PERSON_BUILDER_HPP_