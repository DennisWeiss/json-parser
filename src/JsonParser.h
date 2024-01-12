#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "JsonElement.h"

namespace jsonparser {

class JsonParser {
private:
    uint64_t _line_number;
    uint64_t _char_number;
    std::string _current_line_read;
    char _char_read;

public:
    JsonParser();

    JsonElement parse_object(std::istream& stream);
    JsonElement parse_array(std::istream& stream);

private:
    JsonElement _parse_object(std::istream& stream);
    JsonElement _parse_array(std::istream& stream);
    JsonElement parse_value(std::istream& stream);
    std::vector<std::pair<std::string, JsonElement>> parse_members(std::istream& stream);
    std::vector<std::pair<std::string, JsonElement>> parse_members_plus(std::istream& stream);
    std::pair<std::string, JsonElement> parse_member(std::istream& stream);
    std::vector<JsonElement> parse_elements(std::istream& stream);
    std::vector<JsonElement> parse_elements_plus(std::istream& stream);
    JsonElement parse_element(std::istream& stream);
    std::string parse_string(std::istream& stream);
    std::string parse_characters(std::istream& stream);
    JsonElement parse_number(std::istream& stream);
    int64_t parse_integer(std::istream& stream);
    int64_t parse_positive_integer(std::istream& stream);
    std::string parse_digits(std::istream& stream);
    double parse_fraction(std::istream& stream);
    int64_t parse_exponent(std::istream& stream);
    int parse_sign(std::istream& stream);

    char read_char(std::istream& stream);
    void throw_parsing_exception(char expected, char got);
    void throw_parsing_exception(std::string expected, std::string got);

    void validate_target_string(std::istream& stream, std::string target);
};

} // jsonparser

#endif //JSONPARSER_H
