#include "Parser.h"

Parser::Parser()
{

}

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
                throw Exceptions("Error P01: One or more parameters is not correct.") ;
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
}/**/
void Parser::PrintOptions() const
{
    for (auto &o : options)
    {
        cout << o.GetName().c_str() << ":" << o.GetTypeName() << ":" << o.GetValue().c_str() << endl;
    }
}

void Parser::Analysing()
{
    for(auto option : options)
    {
        switch(option.GetType())
        {
            case PType::Bool:
                {
                    if (!IsValueBool(option.GetValue()))
                        throw Exceptions("Error Type01: No es valor booleano");
                    break;
                }
            case PType::Integer:
                {
                    if (!IsValueInteger(option.GetValue()))
                        throw Exceptions("Error Type02: No es valor entero");
                    break;
                }
            case PType::Real:
                {
                    if(!IsValueReal(option.GetValue()))
                        throw Exceptions("Error Type03: No es valor real");
                    break;
                }
            case PType::String:
                {
                    if(!IsValueString(option.GetValue()))
                        throw Exceptions("Error Type04: No es valor cadena");
                    break;
                }
            case PType::Label:
                {
                    if(!IsValueLabel(option.GetValue()))
                        throw Exceptions("Error Type05: No es valor etiqueta");
                    break;
                }
        }
            option.SetValueType(option.GetType(),option.GetValue());
    }
}

bool Parser::IsValueString(string value)
{
    if(value[0]!='\"'||value[value.size()-1]!='\"')
        return false;
    for(size_t i=1;i<value.size()-1;i++)
    {
        if(value[i]=='\"')
            return false;
    }
    return true;
}

bool Parser::IsValueBool(string value)
{
    for(auto c:value)
    {
        if(c<97)
            c+=32;
    }
    if(value=="true"||value=="false")
        return true;
    return false;
}

bool Parser::IsValueInteger(const string& valor)const
{
    for (auto c: valor)
    {
        if (c<48||c>57)
            return false;
    }
    return true;
}

bool Parser::IsValueReal(const string& valor)const
{
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

bool Parser::IsValueLabel(const string& valor)const
{
    if(valor == "" || valor == " "){
        return true;
    }else{
        return false;
    }
}


Parser::~Parser()
{
    //dtor
}
