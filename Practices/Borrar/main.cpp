#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <tuple>

int main()
{
    using MyTuple = std::tuple<std::string, int, int>;
    std::map<MyTuple, int> myMultimap;

    myMultimap.emplace(std::make_tuple("abc", 0, 0), 0);
    myMultimap.emplace(std::make_tuple("abc", 1, 5), 1);
    myMultimap.emplace(std::make_tuple("abc", 4, 2), 2);
    myMultimap.emplace(std::make_tuple("bbb", 0, 0), 3);
    myMultimap.emplace(std::make_tuple("ccc", 0, 0), 4);

    std::vector<int> searchResult;

    std::for_each(myMultimap.begin(), myMultimap.end(),
        [&searchResult](std::pair<const MyTuple, int>& element)
    {
        if (std::get<2>(element.first)/*.compare("abc")*/ == 5)
        {
            searchResult.push_back(element.second);
        }
    });

    for (auto key : searchResult)
    {
        std::cout << key << std::endl;
    }
    return 0;
}
