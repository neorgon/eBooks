#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../Parser.h"

class ParserTest : public ::testing::Test
{
	protected:
	virtual void SetUp() {
		Parser *parser;
	}
	virtual void TearDown() {
		delete *parser;
	}

};

TEST_F(ParserTest, IntegerTest){
    Parser parser;
	const bool expected = false;
	EXPECT_EQ(expected,parser.AddInteger("calorias", 'c'));
}

TEST_F(ParserTest, RealTest){
    Parser parser;
	const bool expected = false;
	EXPECT_EQ(expected,parser.AddReal("grasas_saturadas", 'g'));
}

TEST_F(ParserTest, StringTest){
    Parser parser;
	const bool expected = false;
	EXPECT_EQ(expected,parser.AddString("nombre", "n", false, 2));
}

TEST_F(ParserTest, JsonTest){
    Parser parser;
	const bool expected = false;
	EXPECT_EQ(expected,parser.GetJSon().compare("{ \"calorias\" : 250, \"proteinas\" : 100, \"grasas_saturadas\" : 50.8 }"));
}
