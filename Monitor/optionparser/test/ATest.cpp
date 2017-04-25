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
    const char* args[] = { "Scanner", "--calorias", "250", "-p","100", "--grasas_saturadas", "0.8", "--nombre", "corn flakes"};

    OptionParser op(argc, args);

    //Act
    //Assert
    EXPECT_EQ(op.GetToken(0),"calorias: 250");
    EXPECT_EQ(op.GetToken(1),"p: 100");
    EXPECT_EQ(op.GetToken(2),"grasas_saturadas: 0.8");
    EXPECT_EQ(op.GetToken(3),"nombre: corn flakes");
}

TEST_F(ATest, OptionParser_GivenRightArgs_Expected2)
 {
    //Arrange
    int argc = 9;
    const char* args[] = { "Scanner", "--calorias", "25x0", "-p","-h", "-grasas_saturadas", "0.8", "--nombre", "corn flakes"};

    OptionParser op(argc, args);

    //Act
    //Assert
    EXPECT_EQ(op.GetToken(0),"calorias: 25x0");
    EXPECT_EQ(op.GetToken(1),"p: true");
    EXPECT_EQ(op.GetToken(2),"h: true");
    EXPECT_EQ(op.GetToken(3),"grasas_saturadas: 0.8");
    EXPECT_EQ(op.GetToken(4),"nombre: corn flakes");
}


TEST_F(ATest, OptionParser_GivenRightArgs_Expected3)
 {
 
    int argc = 10;
    const char* args[] = { "Scanner", "-p", "[100","85","45]","-c","458","-z", "48","-i"};

    OptionParser op(argc, args);

    cout<<op.GetToken(0)<<"\n";

    EXPECT_EQ(op.GetToken(0),"p: 100 85 45");
    EXPECT_EQ(op.GetToken(1),"c: 458");
    EXPECT_EQ(op.GetToken(2),"z: 48");
    EXPECT_EQ(op.GetToken(3),"i: true");
}
//////////////////////////////ACCEPTED INTEGER ////////////////////////////////////////////////////
TEST_F(ATest, OptionParser_Integer_ACEPTE)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    EXPECT_TRUE(op.Validate());

}
///////////////////////////////ERROR INTEGER/////////////////////////////////////////////////////

TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "False", "-p", "18"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Integer Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}


TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedError2)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "12.4", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Integer Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInInteger_ExpectedError3)
 {
    //Arrange
    int argc = 4;
    const char* args[] = { "Scanner", "--calorias", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    //Assert
    try {
        op.Validate();
        FAIL() <<"Expected SemanticException";
    }
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Integer Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

//////////////////////////////ACCEPTED BOOLEAN////////////////////////////////////////////////////
TEST_F(ATest, OptionParser_Boolean_ACEPTE)
 {
    //Arrange
    int argc = 6;
    const char* args[] = { "Scanner", "--calorias", "true", "-p", "false","-g"};

    //Act
    OptionParser op(argc, args);

    op.AddBoolean("calorias", 'c');
    op.AddBoolean("proteinas", 'p');
    op.AddBoolean("grasas", 'g');

    EXPECT_TRUE(op.Validate());

}
///////////////////////////////ERROR BOOLEAN/////////////////////////////////////////////////////

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
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Boolean Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesBoolean_ExpectedError2)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100","-f","10"};

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
    catch(SemanticException const & err) {
        EXPECT_EQ(err.what(),string("Error Boolean Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

//////////////////////////////ACCEPTED REAL////////////////////////////////////////////////////

TEST_F(ATest, OptionParser_REAL_ACEPTE)
 {
    //Arrange
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "50", "-p", "18.5","-g","0.8"};

    //Act
    OptionParser op(argc, args);

    op.AddReal("calorias", 'c');
    op.AddReal("proteinas", 'p');
    op.AddReal("grasas", 'g');

    EXPECT_TRUE(op.Validate());

}
///////////////////////////////ERROR REAL/////////////////////////////////////////////////////

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
    catch(SemanticException const &err) {
        EXPECT_EQ(err.what(), string("Error Real Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

TEST_F(ATest, OptionParser_GivenWrongArgsInValuesReal_ExpectedError2)
 {
    //Arrange
    int argc = 6;
    const char* args[] = { "Scanner", "--calorias", "250", "--grasas_saturadas","-f","true"};

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
    catch(SemanticException const &err) {
        EXPECT_EQ(err.what(), string("Error Real Number Type"));
    }
    catch(...) {
        FAIL() <<"Expected SemanticException";
    }
}

//////////////////////////////////////////////////////////////////////////////////////


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


TEST_F(ATest, OptionParser_GivenWrongMandatoryCommand_ExpectedError1)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "250", "-g", "10.0"};

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',true);
    op.AddBoolean("fBool", 'f',true);


    try {
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Mandatory command not found"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}

TEST_F(ATest, OptionParser_GivenWrongMandatoryCommand_ExpectedError2)
 {
    //Arrange
    int argc = 3;
    const char* args[] = { "Scanner", "--calorias", "250"};

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',true);
    op.AddBoolean("fBool", 'f',true);


    try {
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Mandatory command not found"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}

TEST_F(ATest, OptionParser_GivenWrongMandatoryCommand_ExpectedError3)
 {
    //Arrange
    int argc = 3;
    const char* args[] = { "Scanner","--calorias", "250" };

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',false);
    op.AddBoolean("fBool", 'f',true);


    try {
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Mandatory command not found"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}


//////////////////////////////////////////////////////////////////////////////


TEST_F(ATest, OptionParser_Input_ACEPTE)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "-calorias", "15", "--p", "100"};

    //Act
    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');

    try {
        op.Validate();
        FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Mandatory command not found"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

}


//////////////////////////

TEST_F(ATest, OptionParser_Wrong_INPUT_ACEPTE_ExpectedError)
 {
    //Arrange
    try
    {
    	int argc = 9;
    const char* args[] = { "Scanner", "--calorias", "50", "-p", "18.5","-g","0.8","-c","12"};

    //Act
    OptionParser op(argc, args);

    op.AddReal("calorias", 'c');
    op.AddReal("proteinas", 'p');
    op.AddReal("grasas", 'g');	
   	op.Validate();
   	FAIL() <<"Expected SyntaxException";
    }
    catch(SyntaxException const & err) {
        EXPECT_EQ(err.what(),string("Duplicated Parameter"));
    }
    catch(...) {
        FAIL() <<"Expected SyntaxException";
    }

    

}

/////////////////////////////////////////

TEST_F(ATest, OptionParser_Wrong_Option_Name_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("proteinas", 'r');


        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Repeated definition"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}

TEST_F(ATest, OptionParser_Wrong_Option_Abbr_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("prote", 'p');


        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Repeated definition"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}

////////////////////////////////////////////////////////////////
TEST_F(ATest, OptionParser_Wrong_Option_NameInput_Definition_ExceptedError)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("-calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("prote", 'p');


        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Name declaration error"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}

TEST_F(ATest, OptionParser_Wrong_Option_NameInput_Definition_ExceptedError2)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("--calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("prote", 'p');


        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Name declaration error"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}

TEST_F(ATest, OptionParser_Wrong_Option_AbbrInput_Definition_ExceptedError2)
 {
    //Arrange
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "15", "-p", "100"};

    //Act
    OptionParser op(argc, args);

    try {

    op.AddInteger("calorias", '6');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("prote", 'p');


        op.Validate();
        FAIL() <<"Expected DefinitionException";
    }
    catch(DefinitionException const & err) {
        EXPECT_EQ(err.what(),string("Abbreviation declaration error"));
    }
    catch(...) {
        FAIL() <<"Expected DefinitionException";
    }

}

