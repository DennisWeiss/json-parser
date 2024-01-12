
#include <gtest/gtest.h>

#include "JsonParser.h"

TEST(JsonParserTest, ParseBasicObject) {
    std::string json_string = R"({"foo":"bar","hello":12})";

    jsonparser::JsonParser json_parser;
    std::istringstream string_stream(json_string);
    jsonparser::JsonElement json_element = json_parser.parse_object(string_stream);

    ASSERT_EQ(json_element.type(), jsonparser::OBJECT);
    ASSERT_EQ(json_element.object()[0].first, "foo");
    ASSERT_EQ(json_element.object()[0].second.type(), jsonparser::STRING);
    ASSERT_EQ(json_element.object()[0].second.string_val(), "bar");
}
