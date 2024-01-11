
#include "JsonParser.h"

#include <format>
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
    throw std::runtime_error(std::format(
            "Line {}:{} - {} - Expected '{}', but got '{}'",
            _line_number, _char_number, _current_line_read, expected, got
            ));
}

void JsonParser::throw_parsing_exception(std::string expected, std::string got) {
throw std::runtime_error(std::format(
        "Line {}:{} - {} - Expected '{}', but got '{}'",
        _line_number, _char_number, _current_line_read, expected, got
        ));
}

JsonParser::JsonParser() {
    _line_number = 1;
    _char_number = 0;
}

JsonElement JsonParser::parse_object(std::istream& stream) {
    if (_char_read != '{') {
        throw_parsing_exception('{', _char_read);
    }

    std::vector<std::pair<std::string, JsonElement>> object = parse_members(stream);

    char c = read_char(stream);
    if (c != '}') {
        throw_parsing_exception('}', c);
    }

    return JsonElement(OBJECT, object);
}

JsonElement JsonParser::parse_value(std::istream& stream) {
    if (_char_read == '{') {
        read_char(stream);
        return parse_object(stream);
    }
    if (_char_read == '[') {
        read_char(stream);
        return parse_array(stream);
    }
    if (_char_read == '"') {
        read_char(stream);
        return parse_string(stream);
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

    if (_char_read == )
}

std::vector<std::pair<std::string, JsonElement>> JsonParser::parse_members(std::istream& stream) {
    std::vector<std::pair<std::string, JsonElement>> object;
    if (_char_read != '"') {
        return object;
    }

    std::string field_name;
    while (true) {
        char c = read_char(stream);
        if (c == '"') {
            break;
        }
        field_name += c;
    }

    char c = read_char(stream);
    if (c != ':') {
        throw_parsing_exception(':', c);
    }

    JsonElement value = parse_element(stream);

    read_char(stream);
    object = std::move(parse_members_plus(stream));
    object.insert(object.begin(), std::pair<std::string, JsonElement>(field_name, value));

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

void JsonParser::validate_target_string(std::istream& stream, std::string target) {
    for (size_t i = 1; i < target.size(); i++) {
        char c = read_char(stream);
        if (c != target[i]) {
            throw_parsing_exception(target, target.substr(0, i) + c);
        }
    }
}

} // json_parser