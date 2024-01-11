#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "JsonElement.h"

namespace jsonparser {

class JsonParser {
public:
    JsonElement parse_object(std::istream stream);
    JsonElement parse_array(std::istream stream);

private:
    JsonElement parse_value(std::istream stream);
    JsonElement parse_members(std::istream stream);
    JsonElement parse_members_plus(std::istream stream);
    JsonElement parse_member(std::istream stream);
    JsonElement parse_elements(std::istream stream);
    JsonElement parse_elements_plus(std::istream stream);
    JsonElement parse_element(std::istream stream);
    JsonElement parse_string(std::istream stream);
    JsonElement parse_characters(std::istream stream);
    JsonElement parse_number(std::istream stream);
    JsonElement parse_integer(std::istream stream);
    JsonElement parse_positive_integer(std::istream stream);
    JsonElement parse_digits(std::istream stream);
    JsonElement parse_digit(std::istream stream);
    JsonElement parse_onenine(std::istream stream);
    JsonElement parse_fraction(std::istream stream);
    JsonElement parse_exponent(std::istream stream);
    JsonElement parse_sign(std::istream stream);
};

} // json_parser

#endif //JSONPARSER_H
