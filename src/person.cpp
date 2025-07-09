#include "project_data/person.hpp"

// namespace project_data

// class Person

project_data::Person::Person(
    std::string full_name, 
    std::string birth_date, 
    std::string bio, 
    std::optional<int> father_id, 
    std::optional<int> mother_id
)
: full_name_(std::move(full_name)), birth_date_(std::move(birth_date)), bio_(std::move(bio)), father_id_(father_id), mother_id_(mother_id)
{ }


const std::string& project_data::Person::getFullName() const{
    return full_name_;
}

const std::string& project_data::Person::getBirthDate() const{
    return birth_date_;
}

const std::string& project_data::Person::getBio() const{
    return bio_;
}

