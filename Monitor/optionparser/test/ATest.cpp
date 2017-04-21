#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/OptionParser.h"

using namespace std;

class ATest : public ::testing::Test
{
	protected:
	virtual void SetUp() {

	}
	virtual void TearDown() {

	}

};

TEST_F(ATest, OptionParser_GivenRightArgs_Expected)
 {
    //Arrange
    int argc = 9;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "corn flakes"};

    OptionParser op(argc, args);

    //Act
    //Assert
    EXPECT_EQ(op.GetToken(0),"calorias: 250");
    EXPECT_EQ(op.GetToken(1),"p: 100");
    EXPECT_EQ(op.GetToken(2),"grasas_saturadas: 0.8");
    EXPECT_EQ(op.GetToken(3),"nombre: corn flakes");
}

TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "altas", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(exception const & err) {
        EXPECT_EQ(err.what(),string("Error Integer Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesBoolean_ExpectedError)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100","-f","verdadero"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddBoolean("fBool", 'f');

    //Act
    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(exception const & err) {
        EXPECT_EQ(err.what(),string("Error Boolean Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesReal_ExpectedError)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "--grasas_saturadas", "false","-f","verdadero"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddReal("grasas_saturadas", 'g');
    op.AddBoolean("fBool", 'f');

    //Act
    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(exception const &err) {
        EXPECT_EQ(err.what(), string("Error Real Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInNames_ExpectedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "250", "p", "100"};

    //Act
    //Assert

    try {
        OptionParser op(argc, args);
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Operator expected"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}


