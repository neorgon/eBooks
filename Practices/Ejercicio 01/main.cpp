#include <iostream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <set>
#include <memory>

using namespace std;

enum class account_type { dpf, savings };

struct person
{
    string fn;
    string ln;
    int id;

    person(const string &f, const string &l, int i) : fn{f}, ln{l}, id{i} {}
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

    virtual ~account_base() {}
    virtual account_type get_type() const/* = 0*/;
    virtual int get_amount() const;
    void show() const
    {
        cout << "(" << id << ") " << amount << "[" << to_string(get_type()) << "]\n";
    }
};

struct savings : account_base
{
    string id;
    int amount;

    savings(const string &id, int amount) : id{id}, amount{amount} {}
    account_type get_type() const
    {
        return account_type::savings;
    }
    int get_amount() const
    {
        return amount;
    }
};

struct dpf : account_base
{
    string id;
    int amount;

    dpf(const string &id, int amount) : id{id}, amount{amount} {}
    account_type get_type() const
    {
        return account_type::dpf;
    }
    int get_amount() const
    {
        return amount;
    }
};

typedef tuple<string, string> key;

struct key_hash : public unary_function<key, size_t>
{
    size_t operator()(const key &k) const
    {
        size_t h1 = hash<string>{}(get<0>(k));
        size_t h2 = hash<string>{}(get<1>(k));

        return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
    }
};

struct key_equal : public binary_function<key, key, bool>
{
    bool operator()(const key &v0, const key &v1) const
    {
        return (
            get<0>(v0) == get<0>(v1) &&
            get<1>(v0) == get<1>(v1)
        );
    }
};

class account_manager
{
    unordered_map<key, int, key_hash, key_equal> ids_by_name;
    unordered_map<int, person> people_by_id;
    unordered_map<int, set<unique_ptr<account_base>>> accounts_by_id;
    unordered_map<account_type, set<reference_wrapper<account_base>>> accounts_by_type;

    public:
        void add_person(const string &f, const string &l, int i)
        {
            people_by_id[i] = person {f, l, i};
            ids_by_name[make_tuple(f, l)] = i;
        }

        void add_account(int id, account_base* ac)
        {
            auto i = people_by_id.find(id);
            if (i == people_by_id.end())
                throw "Person not found.";

            accounts_by_id[id].insert(unique_ptr<account_base>(ac));
            accounts_by_type[ac->get_type()].insert(ref(*ac));
        }

        /*int get_total_amount()
        {
            int total = 0;

            for (auto &acc : accounts_by_type)
                for(auto &am : acc.second)
                total += am.get_amount();

            return total;
        }*/
};

int main()
{
    account_manager am;
    am.add_person("juan", "perez", 16895);
    am.add_person("emma", "watson", 1234);
    am.add_person("alan", "wallace", 6566);

    am.add_account(16895, new savings("123A", 100));
    am.add_account(16895, new dpf("678Z", 2000));
    am.add_account(6566, new savings("125A", 200));

    //cout << "Total: " << am.get_total_amount() << endl;

    /*auto vc = am.get_account_by_name("alan", "wallace");
    show(vc);
    vc = am.get_account_by_range(100, 200);
    show(vc);
    vc = am.get_account_by_type(account_type::dpf);
    show(vc);*/

    return 0;
}
