
#include <gtest/gtest.h>

#include <JsonParser.h>


TEST(JsonParserTest, ParseBasicObject) {
    std::string json_string = R"({"foo":"bar","hello":12})";

    jsonparser::JsonParser json_parser;
    std::istringstream string_stream(json_string);
    jsonparser::JsonElement json_element = json_parser.parse_object(string_stream);

    ASSERT_EQ(json_element.type(), jsonparser::OBJECT);
    ASSERT_EQ(json_element.object()[0].first, "foo");
    ASSERT_EQ(json_element.object()[0].second.type(), jsonparser::STRING);
    ASSERT_EQ(json_element.object()[0].second.string_val(), "bar");
    ASSERT_EQ(json_element.object()[1].first, "hello");
    ASSERT_EQ(json_element.object()[1].second.type(), jsonparser::NUMBER_INT);
    ASSERT_EQ(json_element.object()[1].second.number_int(), 12);
}

TEST(JsonParserTest, ParseObjectWithArray) {
    std::string json_string = R"({"foo":"bar","hello":[1,2,"3",{"a":"bc"}]})";

    jsonparser::JsonParser json_parser;
    std::istringstream string_stream(json_string);
    jsonparser::JsonElement json_element = json_parser.parse_object(string_stream);

    ASSERT_EQ(json_element.type(), jsonparser::OBJECT);
    ASSERT_EQ(json_element.object()[1].first, "hello");
    ASSERT_EQ(json_element.object()[1].second.type(), jsonparser::ARRAY);
    ASSERT_EQ(json_element.object()[1].second.array().size(), 4);
    ASSERT_EQ(json_element.object()[1].second.array()[2].type(), jsonparser::STRING);
    ASSERT_EQ(json_element.object()[1].second.array()[2].string_val(), "3");

}
