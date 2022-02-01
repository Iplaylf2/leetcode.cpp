#include <iostream>
#include "10-regular-expression-matching/normal.cpp"

using std::cout;

int main(int, char **)
{

    cout << Solution().isMatch("abbabaaaaaaacaa", "a*.*b.a.*c*b*a*c*");
}
