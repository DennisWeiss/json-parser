//
// Created by Dennis Weiss on 11.01.2024.
//

#ifndef JSONELEMENT_H
#define JSONELEMENT_H

#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace jsonparser {

enum JsonType {
    OBJECT,
    ARRAY,
    STRING,
    NUMBER_INT,
    NUMBER_FLOAT,
    BOOL,
    NULL_TYPE
};

struct JsonElement {
private:
    JsonType _type;
    std::vector<std::pair<std::string, JsonElement>> _object;
    std::vector<JsonElement> _array;
    std::string _string_val;
    std::int64_t _number_int;
    double _number_float;
    bool _bool_val;

public:
    JsonElement(JsonType type, const std::vector<std::pair<std::string, JsonElement>>& object);

    JsonElement(JsonType type);

    JsonElement(JsonType type, std::string val);

    JsonElement(JsonType type, std::int64_t val);

    JsonElement(JsonType type, double val);

    JsonElement(JsonType type, bool val);

    JsonElement();

    void add_to_array(const JsonElement& elm);

    JsonType type() const;

    std::vector<std::pair<std::string, JsonElement>> object() const;

    std::vector<JsonElement> array() const;

    std::string string_val() const;

    std::int64_t number_int() const;

    double number_float() const;

    bool bool_val() const;
};

} // jsonparser

#endif //JSONELEMENT_H
