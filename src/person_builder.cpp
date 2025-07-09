#include "project_data/person_builder.hpp"

// namespace project_data

// class PersonBuilder

project_data::PersonBuilder& project_data::PersonBuilder::setFullName(std::string full_name) {
    full_name_ = std::move(full_name);
    return *this;
}

project_data::PersonBuilder& project_data::PersonBuilder::setBirhtDate(std::string birth_date) {
    birth_date_ = std::move(birth_date);
    return *this;
}

project_data::PersonBuilder& project_data::PersonBuilder::setBio(std::string bio) {
    bio_ = std::move(bio);
    return *this;
}

project_data::PersonBuilder& project_data::PersonBuilder::setFatherByID(int father_id) {
    father_id_ = father_id;
    return *this;
}

project_data::PersonBuilder& project_data::PersonBuilder::setMotherByID(int mother_id) {
    mother_id_ = mother_id;
    return *this;
}

project_data::Person project_data::PersonBuilder::build() const {
    return Person{ full_name_, birth_date_, bio_, father_id_, mother_id_ };
}
