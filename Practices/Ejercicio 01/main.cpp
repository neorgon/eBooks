#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <memory>
#include <algorithm>

using namespace std;

enum class account_type { dpf, savings };

struct person
{
       string fn;
       string ln;
       int id;
};

const char* to_string(account_type a)
{
       switch (a)
       {
       case account_type::dpf:
              return "Dep. plazo fijo";
       }
       return "C. ahorros";
}

struct account_base
{
       string id;
       int amount;

       account_base(const string& id, int amount) : id{ id }, amount{ amount } { }

       virtual ~account_base() {}
       virtual account_type get_type() const = 0;
       void show() const
       {
              cout << "(" << id << ") " << amount << "[" << to_string(get_type()) << "]\n";
       }
};

struct savings : account_base
{
    savings(const string &id, int amount) : account_base{ id, amount } { }
    account_type get_type() const override
    {
        return account_type::savings;
    }
};

struct dpf : account_base
{
       dpf(const string &id, int amount) : account_base{ id, amount } { }
       account_type get_type() const override
       {
           return account_type::dpf;
       }
};

class account_manager
{
    map<tuple<string, string>, int> ids_by_name;
    unordered_map<int, person> people_by_id;
    unordered_map<int, set<unique_ptr<account_base>>> accounts_by_id;
    unordered_map<account_type, vector<reference_wrapper<account_base>>> accounts_by_type;
    unordered_map<int, string> borrar;

    public:
    void add_person(const string &f, const string &l, int i)
    {
        people_by_id[i] = person{ f, l, i };
        ids_by_name[make_tuple(f, l)] = i;
    }

    void add_account(int id, account_base* ac)
    {
        auto i = people_by_id.find(id);
        if (i == people_by_id.end())
                throw "Person not found.";

        accounts_by_id[id].insert(unique_ptr<account_base>(ac));
        accounts_by_type[ac->get_type()].push_back(ref(*ac));
    }

    int get_total_amount()
    {
        int total = 0;

        for (auto &acc : accounts_by_type)
            for(auto &am : acc.second)
                total += am.get().amount;

        return total;
    }

    int get_person_id(const string &n, const string &l)
    {
        auto it = find_if(
            ids_by_name.begin(),
            ids_by_name.end(),
            [n, l](pair<const tuple<string, string>, int> &e)
                {
                    return get<0>(e.first).compare(n) == 0 && get<1>(e.first).compare(l) == 0;
                }
        );

        if (it != ids_by_name.end())
            return it->second;
        else
            return 0;
    }

    vector<string> get_account_by_name(const string &n, const string &l)
    {
        vector<string> accounts;

        int id = get_person_id(n, l);

        for_each(
            accounts_by_id.begin(),
            accounts_by_id.end(),
            [id, &accounts](const auto &abi)
                {
                    if (abi.first == id)
                        for (auto &a : abi.second)
                            accounts.push_back(a->id);
                }
        );

        return accounts;
    }

    vector<string> get_account_by_range(int r_min, int r_max)
    {
        vector<string> accounts;

        for_each(
            accounts_by_type.begin(),
            accounts_by_type.end(),
            [r_min, r_max, &accounts](const auto &abt)
                {
                    for (auto &a : abt.second)
                        if (a.get().amount >= r_min && a.get().amount <= r_max)
                            accounts.push_back(a.get().id);
                }
        );

        return accounts;
    }

    vector<string> get_account_by_type(account_type type)
    {
        vector<string> accounts;

        for_each(
            accounts_by_type.begin(),
            accounts_by_type.end(),
            [type, &accounts](const auto &abt)
                {
                    if (abt.first == type)
                        for (auto &a : abt.second)
                            accounts.push_back(a.get().id);
                }
        );

        return accounts;
    }
};

void show(const auto vc)
{
    for (auto &r : vc)
        cout << r << endl;
}

int main()
{
    account_manager am;
    am.add_person("juan", "perez", 16895);
    am.add_person("emma", "watson", 1234);
    am.add_person("alan", "wallace", 6566);

    am.add_account(16895, new savings("123A", 100));
    am.add_account(16895, new dpf("678Z", 2000));
    am.add_account(6566, new savings("125A", 200));

    cout << "Total: " << am.get_total_amount() << endl;

    //cout << "ID: " << am.get_person_id("alan", "wallace");

    auto vc = am.get_account_by_name("alan", "wallace");
    show(vc);
    vc = am.get_account_by_range(100, 200);
    show(vc);
    vc = am.get_account_by_type(account_type::dpf);
    show(vc);

    return 0;
}
