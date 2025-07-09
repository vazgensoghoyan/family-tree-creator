#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <string>
#include <optional>

namespace project_data {

class Person {

public:
    Person(
        std::string full_name, 
        std::string birth_date, 
        std::string bio, 
        std::optional<int> father_id, 
        std::optional<int> mother_id
    );

    ~Person() = default;

    const std::string& getFullName() const;
    const std::string& getBirthDate() const;
    const std::string& getBio() const;
    
private:
    std::string full_name_;
    std::string birth_date_;
    std::string bio_;

    std::optional<int> father_id_; // nullptr if not specified
    std::optional<int> mother_id_;
    
};

}


#endif // _PERSON_HPP_