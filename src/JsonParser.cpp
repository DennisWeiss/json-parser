
#include "JsonParser.h"

#include <complex>
#include <io.h>
#include <istream>

namespace jsonparser {
char JsonParser::read_char(std::istream& stream) {
    _char_number++;
    stream >> _char_read;
    if (_char_read == '\n') {
        _line_number++;
        _char_number = 1;
        _current_line_read = "";
    } else {
        _current_line_read += _char_read;
    }
    return _char_read;
}

void JsonParser::throw_parsing_exception(char expected, char got) {
    throw std::runtime_error(
        "Line " + std::to_string(_line_number) + ":" + std::to_string(_char_number) + " - " + _current_line_read +
        " - Expected '" + expected + "', but got '" + got + "'");
}

void JsonParser::throw_parsing_exception(std::string expected, std::string got) {
throw std::runtime_error(
        "Line " + std::to_string(_line_number) + ":" + std::to_string(_char_number) + " - " + _current_line_read +
        " - Expected '" + expected + "', but got '" + got + "'");
}

JsonParser::JsonParser() {
    _line_number = 1;
    _char_number = 0;
}

JsonElement JsonParser::parse_object(std::istream& stream) {
    read_char(stream);
    return _parse_object(stream);
}

JsonElement JsonParser::parse_array(std::istream& stream) {
    read_char(stream);
    return _parse_array(stream);
}

JsonElement JsonParser::_parse_object(std::istream& stream) {
    if (_char_read != '{') {
        throw_parsing_exception('{', _char_read);
    }

    read_char(stream);
    std::vector<std::pair<std::string, JsonElement>> object = parse_members(stream);

    if (_char_read != '}') {
        throw_parsing_exception('}', _char_read);
    }

    read_char(stream);
    return JsonElement(OBJECT, object);
}

JsonElement JsonParser::_parse_array(std::istream& stream) {
    if (_char_read != '[') {
        throw_parsing_exception('[', _char_read);
    }

    read_char(stream);
    std::vector<JsonElement> elements = parse_elements(stream);

    if (_char_read != ']') {
        throw_parsing_exception(']', _char_read);
    }

    JsonElement result = JsonElement(ARRAY);
    result.array().insert(result.array().begin(), elements.begin(), elements.end());

    read_char(stream);
    return result;
}

JsonElement JsonParser::parse_value(std::istream& stream) {
    if (_char_read == '{') {
        return _parse_object(stream);
    }
    if (_char_read == '[') {
        return _parse_array(stream);
    }
    if (_char_read == '"') {
        return JsonElement(STRING, parse_string(stream));
    }
    if (_char_read == 't') {
        validate_target_string(stream, "true");

        read_char(stream);
        return JsonElement(BOOL, true);
    }
    if (_char_read == 'f') {
        validate_target_string(stream, "false");

        read_char(stream);
        return JsonElement(BOOL, false);
    }
    if (_char_read == 'n') {
        validate_target_string(stream, "null");

        read_char(stream);
        return JsonElement(NULL_TYPE);
    }
    if (_char_read == '-' || (_char_read >= '0' && _char_read <= '9')) {
        return parse_number(stream);
    }

    throw_parsing_exception('n', _char_read);
}

std::vector<std::pair<std::string, JsonElement>> JsonParser::parse_members(std::istream& stream) {
    std::vector<std::pair<std::string, JsonElement>> object;
    if (_char_read != '"') {
        return object;
    }

    object.push_back(parse_member(stream));

    std::vector<std::pair<std::string, JsonElement>> members_plus = parse_members_plus(stream);
    object.insert(object.end(), members_plus.begin(), members_plus.end());

    return object;
}

std::vector<std::pair<std::string, JsonElement>> JsonParser::parse_members_plus(std::istream& stream) {
    std::vector<std::pair<std::string, JsonElement>> object;
    if (_char_read != ',') {
        return object;
    }

    read_char(stream);
    return parse_members(stream);
}

std::pair<std::string, JsonElement> JsonParser::parse_member(std::istream& stream) {
    parse_ws(stream);

    std::string field_name = parse_string(stream);

    parse_ws(stream);

    if (_char_read != ':') {
        throw_parsing_exception(':', _char_read);
    }

    read_char(stream);
    JsonElement value = parse_element(stream);

    return std::pair(field_name, value);
}

std::vector<JsonElement> JsonParser::parse_elements(std::istream& stream) {
    std::vector<JsonElement> elements;
    if (_char_read == ']') {
        return elements;
    }
    elements.insert(elements.end(), parse_element(stream));
    std::vector<JsonElement> elements_plus = parse_elements_plus(stream);

    elements.insert(elements.end(), elements_plus.begin(), elements_plus.end());

    return elements;
}

std::vector<JsonElement> JsonParser::parse_elements_plus(std::istream& stream) {
    if (_char_read != ',') {
        return std::vector<JsonElement>();
    }
    read_char(stream);
    return parse_elements(stream);
}

JsonElement JsonParser::parse_element(std::istream& stream) {
    parse_ws(stream);
    JsonElement value = parse_value(stream);
    parse_ws(stream);
    return value;
}

std::string JsonParser::parse_string(std::istream& stream) {
    if (_char_read != '"') {
        throw_parsing_exception('"', _char_read);
    }

    read_char(stream);
    std::string string = parse_characters(stream);

    if (_char_read != '"') {
        throw_parsing_exception('"', _char_read);
    }

    read_char(stream);
    return string;
}

std::string JsonParser::parse_characters(std::istream& stream) {
    std::string string(1, _char_read);
    while (true) {
        char c = read_char(stream);
        if (c != '"') {
            string += c;
        } else {
            return string;
        }
    }
}

JsonElement JsonParser::parse_number(std::istream& stream) {
    if (_char_read != '-' && !(_char_read >= '0' && _char_read <= '9')) {
        throw_parsing_exception("digit or -", std::to_string(_char_read));
    }
    int64_t integer = parse_integer(stream);
    double fraction = parse_fraction(stream);
    int64_t exponent = parse_exponent(stream);

    if (fraction == -1) {
        return JsonElement(NUMBER_INT, static_cast<int64_t>(std::pow(10, exponent)) * integer);
    }
    return JsonElement(NUMBER_FLOAT, std::pow(10, exponent) * (integer + fraction));
}

double JsonParser::parse_fraction(std::istream& stream) {
    if (_char_read != '.') {
        return -1;
    }
    double fraction = 0;
    int i = 1;
    while (true) {
        char c = read_char(stream);
        if (!(c >= '0' && c <= '9')) {
            return fraction;
        }
        fraction += (c - '0') / std::pow(10, i);
        i++;
    }
}

int64_t JsonParser::parse_exponent(std::istream& stream) {
    if (_char_read == 'E' || _char_read == 'e') {
        std::string digits = parse_digits(stream);
        return parse_sign(stream) * (digits.empty() ? 0 : std::stoi(digits));
    }
    return 0;
}

int JsonParser::parse_sign(std::istream& stream) {
    if (_char_read == '+') {
        read_char(stream);
        return 1;
    }
    if (_char_read == '-') {
        read_char(stream);
        return -1;
    }
    throw_parsing_exception("+ or -", std::to_string(_char_read));
}

void JsonParser::parse_ws(std::istream& stream) {
    while (true) {
        if (_char_read != '\u0020' && _char_read != '\u000A' && _char_read != '\u000D' && _char_read != '\u0009') {
            return;
        }
        read_char(stream);
    }
}

int64_t JsonParser::parse_integer(std::istream& stream) {
    if (_char_read == '-') {
        read_char(stream);
        return -parse_positive_integer(stream);
    }
    if (_char_read >= '0' && _char_read <= '9') {
        return parse_positive_integer(stream);
    }
    throw_parsing_exception("digit or -", std::to_string(_char_read));
}

int64_t JsonParser::parse_positive_integer(std::istream& stream) {
    if (!(_char_read >= '0' && _char_read <= '9')) {
        throw_parsing_exception("digit", std::to_string(_char_read));
    }

    int64_t integer = _char_read - '0';
    if (_char_read == '0') {
        return integer;
    }
    read_char(stream);
    std::string digits = parse_digits(stream);
    if (digits.empty()) {
        return integer;
    }
    int64_t digits_int = std::stoi(digits);
    return integer * static_cast<int64_t>(std::pow(10, static_cast<int>(std::floor(std::log10(digits_int))) + 1)) + digits_int;
}

std::string JsonParser::parse_digits(std::istream& stream) {
    if (!(_char_read >= '0' && _char_read <= '9')) {
        return "";
    }
    std::string digits(1, _char_read);
    while (true) {
        char c = read_char(stream);
        if (c >= '0' && c <= '9') {
            digits += c;
        } else {
            return digits;
        }
    }
}

void JsonParser::validate_target_string(std::istream& stream, std::string target) {
    for (size_t i = 1; i < target.size(); i++) {
        char c = read_char(stream);
        if (c != target[i]) {
            throw_parsing_exception(target, target.substr(0, i) + c);
        }
    }
}

} // json_parser