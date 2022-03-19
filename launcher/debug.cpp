#include <iostream>
#include "30-substring-with-concatenation-of-all-words/normal.cpp"

int main(int, char **)
{
    auto foo = vector<string>{"foo", "bar"};
    Solution().findSubstring("barfoothefoobarman", foo);
}
