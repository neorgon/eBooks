#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/OptionParser.h"

class ITest : public ::testing::Test
{
	protected:
	virtual void SetUp() {
	
		
	}
	virtual void TearDown() {
		
	}
/*
private:
	auto getValuesOptions(string optionname, vector<IOptionType*> Op){
		for(auto i:Op)
	        switch(i->GetType())
	        {
	            case OptionType::Boolean:
	            {
	                return static_cast<Boolean*>(i)->GetValue();
	                break;
	            }
	            case OptionType::Integer:
	            {
	                return static_cast<Integer*>(i)->GetValue();
	                break;
	            }
	            case OptionType::List:
	            {
	                
	                return getValuesOptions(optionname,static_cast<List*>(i)->GetValue());                
	                break;
	            }
	            case OptionType::Real:
	            {
	                return static_cast<Real*>(i)->GetValue();
	                break;
	            }
	            case OptionType::Text:
	            {
	                return static_cast<Text*>(i)->GetValue();
	                break;
	            }
	        }
		}*/
};


TEST_F(ITest, GetOptions_Giving)
 {
    int argc = 10;
    const char* args[] = { "Scanner", "-p", "100", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]","--calorias", "250" };

    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddReal("grasas_saturadas", 'g');
    op.AddReal("grasas_hidrogenadas", 'h', true, 0);
    op.AddText("nombre", 'n', false, 2);
    op.AddList("no-incluye", 'i');
    op.AddList("incluye", 'e');
    op.AddInteger("azucares", 'z');
    op.AddBoolean("bBool", 'b');
    op.AddBoolean("iBool", 'i');

    op.Validate();
    map<string, vector<IOptionType*>> options = op.GetOptions();
    
    EXPECT_EQ(options.size(),3); 
}

TEST_F(ITest, AddInteger_GivingOptionType_ExpectedValue)
 {
    int argc = 3;
    const char* args[] = { "Scanner", "-p", "100" };

    OptionParser op(argc, args);
    op.AddInteger("proteinas", 'p');

    op.Validate();
    map<string, vector<IOptionType*>> options = op.GetOptions();
	auto o = options.find("proteinas");    
    EXPECT_EQ(o.second[0]->GetValue(), "100");    

}

TEST_F(ITest, AddInteger_GivingOptionType_ExpectedValueDefault)
 {
    int argc = 2;
    const char* args[] = { "Scanner", "-p"};

    OptionParser op(argc, args);

    op.AddInteger("proteinas", 'p');

    op.Validate();
    map<string, vector<IOptionType*>> options = op.GetOptions();
	auto o = options.find("proteinas");    
    EXPECT_EQ(o.second[0]->GetValue(), "true");    

}

TEST_F(ITest, AddReal_GivingOptionType_ExpectedValue)
 {
    int argc = 3;
    const char* args[] = { "Scanner", "--grasas_saturadas", "0.8" };

    OptionParser op(argc, args);
   	op.AddReal("grasas_saturadas", 'g');

    op.Validate();
    map<string, vector<IOptionType*>> options = op.GetOptions();
	auto o = options.find("grasas_saturadas");    
    EXPECT_EQ(o.second[0]->GetValue(), "0.8");    

}

TEST_F(ITest, AddReal_GivingOptionType_ExpectedValueDefault)
 {
    int argc = 3;
    const char* args[] = { "Scanner", "--grasas_saturadas", "0.8" };

    OptionParser op(argc, args);
   	op.AddReal("grasas_saturadas", 'g');

    op.Validate();
    map<string, vector<IOptionType*>> options = op.GetOptions();
	auto o = options.find("grasas_saturadas");    
    EXPECT_EQ(o.second[0]->GetValue(), "true");    

}

TEST_F(ITest, AddBoolean_GivingOptionType_ExpectedValue)
 {
    int argc = 3;
    const char* args[] = { "Scanner", "-b", "false"};

    OptionParser op(argc, args);
   	op.AddBoolean("bBool", 'b');

    op.Validate();
    map<string, vector<IOptionType*>> options = op.GetOptions();
	auto o = options.find("bBool");    
    EXPECT_EQ(o.second[0]->GetValue(), "false");    

}

TEST_F(ITest, AddBoolean_GivingOptionType_ExpectedValueDefault)
 {
    int argc = 3;
    const char* args[] = { "Scanner", "-b"};

    OptionParser op(argc, args);
   	op.AddBoolean("bBool", 'b');

    op.Validate();
    map<string, vector<IOptionType*>> options = op.GetOptions();
	auto o = options.find("bBool");    
    EXPECT_EQ(o.second[0]->GetValue(), "true");    

}
