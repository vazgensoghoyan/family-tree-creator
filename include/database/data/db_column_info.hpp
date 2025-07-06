#ifndef _DB_COLUMN_INFO_HPP_
#define _DB_COLUMN_INFO_HPP_

#include <string>
#include <vector>

namespace database::data {

class ColumnInfo {

public:
    class DefaultValue {

    public:
        DefaultValue(bool isSpecified, bool isNull, std::string value)
        : isSpecified(isSpecified), isNull(isNull), value(value) { }

        ~DefaultValue() { }

    public:
        const bool isSpecified;
        const bool isNull;
        const std::string value;

    };

public:
    ColumnInfo(std::string name, std::string type, bool isPKey, bool isNullable, DefaultValue defValue)
    : name(name), type(type), isPKey(isPKey), isNullable(isNullable), defValue(defValue) { }
    
    ~ColumnInfo() { }

public:
    const std::string name;
    const std::string type;
    const bool isPKey;
    const bool isNullable;
    const DefaultValue defValue;
};

}

#endif // _DB_COLUMN_INFO_HPP_
