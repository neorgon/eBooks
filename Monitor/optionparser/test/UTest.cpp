#include "../../thirdParty/googletest/include/gtest/gtest.h"

class UTest : public ::testing::Test
{
	protected:
	virtual void SetUp() {
	
	}
	virtual void TearDown() {
		
	}

};

TEST_F(UTest, Formato_de_entrada)
 {
    //Arrange
    int argc = 9;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "corn flakes"};

    OptionParser op(argc, args);

    //Act
    //Assert
    EXPECT_THROW( op.Validate());
}
