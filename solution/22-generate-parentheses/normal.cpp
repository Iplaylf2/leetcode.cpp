#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
        return result[n];
    }

private:
    static vector<string> result[9];
    static const int init;
};

vector<string> Solution::result[9]{{""}, {"()"}};
const int Solution::init{
    []
    {
        for (auto i = 2; i <= 8; i++)
        {
            auto root = vector<string>();

            auto s_size = 2 * i;
            auto s = string(s_size, '\0');
            s[0] = '(';
            for (auto j = i - 1, limit = i - 1; 0 <= j; j--)
            {
                auto content_group = result[j];
                auto fixed_size = 2 * j + 2;
                s[fixed_size - 1] = ')';

                auto rest_index = limit - j;
                auto rest_group = result[rest_index];
                auto reset_size = 2 * rest_index;

                for (auto content : content_group)
                {
                    s.replace(1, fixed_size - 2, content);
                    for (auto rest : rest_group)
                    {
                        s.replace(fixed_size, reset_size, rest);
                        root.push_back(s);
                    }
                }
            }

            result[i] = move(root);
        }

        return 0;
    }()};