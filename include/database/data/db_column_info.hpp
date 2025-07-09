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
        : isSpecified(isSpecified), isNull(isNull), value(std::move(value)) { }


        DefaultValue(const DefaultValue&) = default;
        DefaultValue(DefaultValue&&) noexcept = default;

        DefaultValue& operator=(const DefaultValue&) = default;
        DefaultValue& operator=(DefaultValue&&) noexcept = default;

        ~DefaultValue() = default;

    public:
        const bool isSpecified;
        const bool isNull;
        const std::string value;

    };

public:
    ColumnInfo(std::string name, std::string type, bool isPKey, bool isNullable, DefaultValue defValue)
    : name(std::move(name)), type(std::move(type)), isPKey(isPKey), isNullable(isNullable), defValue(defValue) { }
    
    ColumnInfo(const ColumnInfo&) = default;
    ColumnInfo(ColumnInfo&&) noexcept = default;

    ColumnInfo& operator=(const ColumnInfo&) = default;
    ColumnInfo& operator=(ColumnInfo&&) noexcept = default;

    ~ColumnInfo() = default;

public:
    const std::string name;
    const std::string type;
    const bool isPKey;
    const bool isNullable;
    const DefaultValue defValue;
};

}

#endif // _DB_COLUMN_INFO_HPP_
