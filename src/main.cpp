#include <iostream>
#include <sstream>
#include <string>

#include "JsonParser.h"

int main(int argc, char* argv[]) {
    std::string json_string = R"({"foo":n,"hello":n})";

    jsonparser::JsonParser json_parser;
    std::istringstream string_stream(json_string);
    jsonparser::JsonElement json_element = json_parser.parse_object(string_stream);

    std::cout << json_element.type() << " " << json_element.object()[0].first << " " << json_element.object()[1].first
    << " " << json_element.object().size() << std::endl;

    return 0;
}
