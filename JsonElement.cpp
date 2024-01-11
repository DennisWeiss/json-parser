//
// Created by Dennis Weiss on 11.01.2024.
//

#include "JsonElement.h"


namespace jsonparser {
JsonElement::JsonElement(JsonType type, const std::unordered_map<std::string, JsonElement>& object) {
    if (type != OBJECT) {
        throw std::invalid_argument("type has to be OBJECT for this contructor");
    }
    _type = type;
    _object = object;
}

JsonElement::JsonElement(JsonType type) {
    if (type != ARRAY && type != NULL_TYPE) {
        throw std::invalid_argument("type has to be either ARRAY or NULL_TYPE for this constructor");
    }
    _type = type;
    if (type == ARRAY) {
        _array = std::vector<JsonElement>();
    }
}

JsonElement::JsonElement(JsonType type, std::string val) {
    if (type != STRING) {
        throw std::invalid_argument("type has to be STRING for this contructor");
    }
    _type = type;
    _string_val = val;
}

JsonElement::JsonElement(JsonType type, std::int64_t val) {
    if (type != NUMBER_INT) {
        throw std::invalid_argument("type has to be NUMBER_INT for this constructor");
    }
    _type = type;
    _number_int = val;
}

JsonElement::JsonElement(JsonType type, double val) {
    if (type != NUMBER_FLOAT) {
        throw std::invalid_argument("type has to be NUMBER_FLOAT for this constructor");
    }
    _type = type;
    _number_float = val;
}

JsonElement::JsonElement(JsonType type, bool val) {
    if (type != BOOL) {
        throw std::invalid_argument("type has to be BOOL for this constructor");
    }
    _type = type;
    _bool_val = val;
}

JsonElement::JsonElement() {
    _type = NULL_TYPE;
}

void JsonElement::add_to_array(const JsonElement& elm) {
    if (_type != ARRAY) {
        throw std::invalid_argument("the type of the JsonElement is not ARRAY.");
    }
    _array.push_back(elm);
}

JsonType JsonElement::type() const {
    return _type;
}

std::unordered_map<std::string, JsonElement> JsonElement::object() const {
    return _object;
}

std::vector<JsonElement> JsonElement::array() const {
    return _array;
}

std::string JsonElement::string_val() const {
    return _string_val;
}

std::int64_t JsonElement::number_int() const {
    return _number_int;
}

double JsonElement::number_float() const {
    return _number_float;
}

bool JsonElement::bool_val() const {
    return _bool_val;
}
} // jsonparser