#include <iostream>
#include "10-regular-expression-matching/normal.cpp"

using std::cout;

int main(int, char **)
{

    cout << Solution().isMatch("aaa", "ab*ac*a");
}
