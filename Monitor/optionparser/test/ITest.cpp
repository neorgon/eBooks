#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/OptionParser.h"

class ITest : public ::testing::Test
{
	protected:
	virtual void SetUp() {
	
		
	}
	virtual void TearDown() {
		
	}

};
TEST_F(ITest, OptionsSize)
 {
    int argc = 8;
    const char* args[] = { "Scanner", "-p", "100","-c","458","-z", "48","-i"};

    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("azucares", 'z');
    op.AddBoolean("iBool", 'i');

    op.Validate();
    
    map<string, vector<IOptionType*>> options = op.GetOptions();
    EXPECT_EQ(options.size(),4); 
}

TEST_F(ITest, OptionsSize2)
 {
    int argc = 10;
    const char* args[] = { "Scanner", "-p", "[100","85","45]","-c","458","-z", "48","-i"};

    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("azucares", 'z');
    op.AddBoolean("iBool", 'i');


    op.Validate();
    
    map<string, vector<IOptionType*>> options = op.GetOptions();
    EXPECT_EQ(options.size(),4); 
}
/////////////////////////////////////////////////////////////////////

TEST_F(ITest, GetOptions_Giving)
 {
    int argc = 8;
    const char* args[] = { "Scanner", "-p", "10.50","-c","458","-z", "48","-i"};

    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddReal("proteinas", 'p');
    op.AddInteger("azucares", 'z');
    op.AddBoolean("iBool", 'i');

    op.Validate();
    
    map<string, vector<IOptionType*>> options = op.GetOptions();

     for (auto &o : options)
        {
             for(auto i:o.second)
             {
                if(i->GetName()=="calorias")
                {
                        
                        EXPECT_EQ(i->GetName(),"calorias");
                        EXPECT_EQ(i->GetAbbr(), 'c');
                        EXPECT_EQ(static_cast<Integer*>(i)->GetValue() , 458);


                }

                if(i->GetName()=="proteinas")
                {
                        
                        EXPECT_EQ(i->GetName(),"proteinas");
                        EXPECT_EQ(i->GetAbbr(), 'p');
                        EXPECT_EQ(static_cast<Real*>(i)->GetValue() , 10.5);


                }
                if(i->GetName()=="azucares")
                {
                        
                        EXPECT_EQ(i->GetName(),"azucares");
                        EXPECT_EQ(i->GetAbbr(), 'z');
                        EXPECT_EQ(static_cast<Integer*>(i)->GetValue() , 48);


                }
                  if(i->GetName()=="iBool")
                {
                        
                        EXPECT_EQ(i->GetName(),"iBool");
                        EXPECT_EQ(i->GetAbbr(), 'i');
                        EXPECT_EQ(static_cast<Boolean*>(i)->GetValue() , 1);


                }
             }

        }
}


TEST_F(ITest, GetOptions_Giving2)
 {
    int argc = 10;
    const char* args[] = { "Scanner", "-p", "[100","85","45]","-c","458","-z", "48","-i"};

    OptionParser op(argc, args);

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddInteger("azucares", 'z');
    op.AddBoolean("iBool", 'i');


    op.Validate();
    
    map<string, vector<IOptionType*>> options = op.GetOptions();

     for (auto &o : options)
        {   int j=0;
             for(auto i:o.second)
             {
                if(i->GetName()=="calorias")
                {
                        
                        EXPECT_EQ(i->GetName(),"calorias");
                        EXPECT_EQ(i->GetAbbr(), 'c');
                        EXPECT_EQ(static_cast<Integer*>(i)->GetValue() , 458);


                }

                if(i->GetName()=="proteinas")
                {
                        int values[]={100,85,45};
                        EXPECT_EQ(i->GetName(),"proteinas");
                        EXPECT_EQ(i->GetAbbr(), 'p');
                        EXPECT_EQ(static_cast<Integer*>(i)->GetValue() , values[j]);
                        j++;


                }
                if(i->GetName()=="azucares")
                {
                        
                        EXPECT_EQ(i->GetName(),"azucares");
                        EXPECT_EQ(i->GetAbbr(), 'z');
                        EXPECT_EQ(static_cast<Integer*>(i)->GetValue() , 48);


                }
             }

        }
}

