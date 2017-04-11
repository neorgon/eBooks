#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../Rules.h"

class RulesTest : public ::testing::Test
{
	protected:
	virtual void SetUp() {
		Rules *rules;
	}
	virtual void TearDown() {
		delete *rules;
	}
};

TEST_F(RulesTest, BooleanTest){
    Rules rules;
    PType type;
	const string expected = "<Boolean>";
	EXPECT_EQ(expected, rules.GetTypeName(type.Bool));
}

TEST_F(RulesTest, IntegerTest){
    Rules rules;
    PType type;
	const string expected = "<Integer>";
	EXPECT_EQ(expected, rules.GetTypeName(type.Integer));
}

TEST_F(RulesTest, LabelTest){
    Rules rules;
    PType type;
	const string expected = "<Label>";
	EXPECT_EQ(expected, rules.GetTypeName(type.Label));
}

TEST_F(RulesTest, ListTest){
    Rules rules;
    PType type;
	const string expected = "<List>";
	EXPECT_EQ(expected, rules.GetTypeName(type.List));
}

TEST_F(RulesTest, RealTest){
    Rules rules;
    PType type;
	const string expected = "<Real>";
	EXPECT_EQ(expected, rules.GetTypeName(type.Real));
}

TEST_F(RulesTest, StringTest){
    Rules rules;
    PType type;
	const string expected = "<String>";
	EXPECT_EQ(expected, rules.GetTypeName(type.String));
}

