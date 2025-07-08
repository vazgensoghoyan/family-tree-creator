#include "database/data/db_table.hpp"

// namespace database::data

// class Table

database::data::Table::Table(std::string name, const TableSchema& schema) 
: name(name), schema(schema) 
{ }

database::data::Table::Table(std::string name, TableSchema&& schema) 
: name(name), schema(std::move(schema)) 
{ }
    
database::data::Table::~Table() { }

std::string database::data::Table::getName() const { 
    return name; 
}

const database::data::TableSchema& database::data::Table::getSchema() const {
    return schema;
}
