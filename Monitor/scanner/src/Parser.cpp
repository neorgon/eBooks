#include "Parser.h"

/*
void Parser::AddRule(const string &name, const string &abrv, PType type, bool optional, size_t iquantity)
{
    Rules newRule("--" + name, "-" + abrv, type, optional, iquantity);
    rules.push_back(newRule);
}

void Parser::AddBool(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Bool, optional, iquantity);
}

void Parser::AddInteger(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Integer, optional, iquantity);
}

void Parser::AddLabel(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Label, optional, iquantity);
}

void Parser::AddList(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::List, optional, iquantity);
}

void Parser::AddReal(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Real, optional, iquantity);
}

void Parser::AddString(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::String, optional, iquantity);
}

void Parser::PrintRules() const
{
    for (auto &r : rules)
        cout << r.GetName() << endl;
}

size_t Parser::GetLenght(const char* source)
{
    size_t c = 0;

    for (;source[c] != '\0'; ++c)
    {

    }

    return c;
}

void Parser::CopyToken(char *token, const char* source, size_t len)
{
    for(size_t i = 0; i < len; i++)
        token[i] = source[i];

    token[len] = '\0';
}

void Parser::Scanner(int argc, char** args)
{
    for (int i = 1; i < argc; ++i)
    {
        size_t len = GetLenght(args[i]);
        auto token = new char[len + 1];

        CopyToken(token, args[i], len);
        tokens.push_back(token);

        delete[] token;
    }
}

void Parser::PrintTokens() const
{
    for (auto &t : tokens)
        cout << t << endl;
}

void Parser::LexicalAnalyzer()
{
    vector<Rules>::const_iterator it;
    int opCounter = 0;

    for (const string &t : tokens)
    {
        if(t[0] == '-')
        {
            it = find_if(rules.begin(), rules.end(), Rules::Finder(t));
            if(it == rules.end())
            {
                throw Exceptions("One or more parameters is not correct.");
                return;
            }
            else
            {
                Options newOption(t, it->GetType());
                options.push_back(newOption);
                ++opCounter;
            }
        }
        else
        {
            options.at(opCounter - 1).SetValue(t);
        }
    }
}
void Parser::Help() const
{
		cout<<"Options:\n";
		for (auto &r : rules)
		{

			printf("%-5s%-23s%-15s\n",r.GetAbrv().c_str(),r.GetName().c_str(), r.GetTypeName().c_str() );
		}
}
void Parser::PrintOptions() const
{
    for (auto &o : options)
    {
        cout << o.GetName().c_str() << ":" << o.GetTypeName() << ":" << o.GetValue().c_str() << endl;
    }
}

bool Parser::VerifySemantic()const{
		bool cumple = false;
		for(auto option : options){
			switch(option.GetType()){
				case PType::Bool:
					cumple = ("true" == option.GetValue())?true:false;
					break;
				case PType::Integer:
					cumple = IsValueInteger(option.GetValue());
					break;
				case PType::Real:
					cumple = IsValueReal(option.GetValue());
					break;
				case PType::String:
					cumple = true;
					break;
				case PType::Label:
					cumple = IsValueLabel(option.GetValue());
					break;
			}
			if(!cumple){
                throw Exceptions("error de tipo de parametros  ");
				return cumple;

			}else{
                option.SetValueType(option.GetType(),option.GetValue());
            }
		}
		return true;
	}

	bool Parser::IsValueInteger(const string& valor)const{
		string numeros = "1234567890";
		bool cumple = false;
		for(int i = 0; i < valor.length() ; i++){
			for(int j = 0;j < numeros.length() ; j++){
				if(valor[i] == numeros[j]){
					cumple=true;
					break;
				}
			}
			if(!cumple){
				return cumple;
			}else{
				cumple=false;
			}
		}
		return true;
	}

	bool Parser::IsValueReal(const string& valor)const{
		string numeros = ".1234567890";
		bool cumple = false;
		for(int i = 0; i < valor.length() ; i++){
			for(int j = 0;j < numeros.length() ; j++){
				if(valor[i] == numeros[j]){
					cumple=true;
					break;
				}
			}
			if(!cumple){
				return cumple;
			}else{
				cumple=false;
			}
		}
		return true;
	}

	bool Parser::IsValueLabel(const string& valor)const{
		if(valor == "" || valor == " "){
			return true;
		}else{
			return false;
		}
	}

*/

string Parser::ToLower(const string &str)
{
    string lower = str;

    for (size_t i = 0; i < lower.length(); i++)
    {
        if (lower[i] >= 65 && lower[i] <= 92)
        {
            lower[i] = lower[i] + 32;
        }
    }

    return lower;
}

void Parser::AddRule(const char* name, char abbr, PType type, bool optional, size_t quantity)
{
    Rules newRule("--" + string(name), "-" + string(1, abbr), type, optional, quantity);
    rules.push_back(newRule);
}

void Parser::AddInteger(const char* name, char abbr, bool optional, size_t quantity)
{
    AddRule(name, abbr, PType::Integer, optional, quantity);
}

void Parser::AddReal(const char* name, char abbr, bool optional, size_t quantity)
{
    AddRule(name, abbr, PType::Real, optional, quantity);
}

void Parser::Scanning(const char* input)
{
    if (input[0] == '-' && input[1] == '-')
    {
        tokens.push_back(ToLower(string(input)));
    }
    else
    {
        tokens.push_back(string(input));
    }
}

bool Parser::AnalyzingSyntax()
{
    vector<Rules>::const_iterator it;

    for (auto &t : tokens)
    {
        if (t[0] == '-')
        {
            it = find_if(rules.begin(), rules.end(), Rules::Finder(t));
            if(it == rules.end()) //throw Exceptions("One or more parameters is not correct.");
                return false;
            //order to labels add a value in values vector
            //cout << (int)it->GetType() << endl;
            tkOptions.push_back(t);
        }
        else
        {
            values.push_back(t);
        }
    }

    return true;
}

bool Parser::SetBool(const string &v)
{
    return true;
}

int Parser::SetInteger(const string &v)
{
    return 0;
}

string Parser::SetLabel(const string &v)
{
    return v;
}

Options* Parser::SetList(const string &v)
{
    return nullptr;
}

double Parser::SetReal(const string &v)
{
    return 0;
}

string Parser::SetString(const string &v)
{
    return "\"" + v + "\"";
}

bool Parser::AnalyzingSemantic()
{
    size_t tkCounter = 0;
    vector<Rules>::const_iterator it;

    if (tkOptions.size() != values.size())
        return false;
    for (auto &t : tkOptions)
    {
        it = find_if(rules.begin(), rules.end(), Rules::Finder(t));
        switch(it->GetType())
        {
            case PType::Bool:
                /*Options newOption(it->GetName(), it->GetAbbr()[1], it->GetType(), (void *)SetBool(values.at(tkCounter)));
                options.push_back(newOption);*/
                cout << "bool" << endl;
                break;
            case PType::Integer:
                /*Options newOption(it->GetName(), it->GetAbbr()[1], it->GetType(), (void *)SetInteger(values.at(tkCounter)));
                options.push_back(newOption);*/
                cout << "Integer" << endl;
                break;
            case PType::Label:
                /*Options newOption(it->GetName(), it->GetAbbr()[1], it->GetType(), (void *)SetLabel(values.at(tkCounter)));
                options.push_back(newOption);*/
                cout << "Label" << endl;
                break;
            case PType::List:
                /*Options newOption(it->GetName(), it->GetAbbr()[1], it->GetType(), (void *)SetList(values.at(tkCounter)));
                options.push_back(newOption);*/
                cout << "List" << endl;
                break;
            case PType::Real:
                /*Options newOption(it->GetName(), it->GetAbbr()[1], it->GetType(), (void *)SetReal(values.at(tkCounter)));
                options.push_back(newOption);*/
                cout << "Real" << endl;
                break;
            case PType::String:
                /*Options newOption(it->GetName(), it->GetAbbr()[1], it->GetType(), (void *)SetString(values.at(tkCounter)));
                options.push_back(newOption);*/
                cout << "String" << endl;
                break;
        }
        ++tkCounter;
    }

    return true;
}

bool Parser::Validate(int argc, const char** args) //only of testing int argc, char* args[]
{
    //Scanning && AnalyzingSyntax && AnalyzingSemantic
    if (argc == 0)
        return false;
    else
    {
        for (int i = 1; i < argc; i++)
            Scanning(args[i]);
    }

    return AnalyzingSyntax() && AnalyzingSemantic();
}

Parser::~Parser()
{
    //dtor
}
