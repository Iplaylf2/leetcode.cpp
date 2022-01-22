#include <iostream>

using std::ostream;
using std::pair;

template <typename T>
ostream &print(ostream &out, T const &val)
{
    return (out << val << " ");
}

template <typename T1, typename T2>
ostream &print(ostream &out, pair<T1, T2> const &val)
{
    return (out << "{" << val.first << " " << val.second << "} ");
}

template <template <typename, typename...> class TT, typename... Args>
ostream &operator<<(ostream &out, TT<Args...> const &cont)
{
    for (auto elem : cont)
        print(out, elem);
    return out;
}