#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using std::queue;
using std::string;
using std::unordered_map;
using std::vector;

class Solution
{
public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        auto result = vector<int>();

        int words_size = words.size();
        if (1 == words_size)
        {
            auto word = words.front();
            auto current = 0;
            while (true)
            {
                int position = s.find(word, current);
                if (position < 0)
                {
                    return result;
                }

                result.push_back(position);
                current = position + 1;
            }
        }

        int word_length = words.front().length();
        int view_length = words_size * word_length;
        int s_length = s.length();

        auto fixed_word_map = unordered_map<string, int>();
        for (int i = 0; words_size != i; i++)
        {
            auto &x = words[i];
            auto node = fixed_word_map.try_emplace(x, 1);
            if (!node.second)
            {
                node.first->second++;
            }
        }

        for (int group_index = 0; group_index < word_length; group_index++)
        {
            auto word_map = fixed_word_map;
            auto word_map_end = word_map.end();

            auto pass_view = queue<int *>();
            auto pop_pass_view_until_a_spot = [&pass_view](int &x)
            {
                auto n = 0;
                do
                {
                    auto count = pass_view.front();
                    (*count)++;
                    pass_view.pop();

                    n++;
                } while (0 == x);

                return n;
            };

            auto pop_pass_view = [&pass_view]()
            {
                auto count = pass_view.front();
                (*count)++;
                pass_view.pop();
            };

            int view_left = group_index;
            if (s_length < view_left + view_length)
            {
                break;
            }

            auto view_word_index = 0;
            auto view_word_cursor = view_left;
            while (true)
            {
                auto word = s.substr(view_word_cursor, word_length);
                auto find_result = word_map.find(word);
                if (word_map_end == find_result)
                {
                    auto offset = view_word_index + 1;
                    auto offset_size = word_length * offset;
                    view_left += offset_size;
                    if (s_length < view_left + view_length)
                    {
                        break;
                    }

                    view_word_index = 0;
                    view_word_cursor += word_length;

                    pass_view = {};
                    word_map = fixed_word_map;
                    word_map_end = word_map.end();
                }
                else
                {
                    auto &word_count = find_result->second;
                    if (0 == word_count)
                    {
                        auto offset = pop_pass_view_until_a_spot(word_count);
                        auto offset_size = word_length * offset;
                        view_left += offset_size;
                        if (s_length < view_left + view_length)
                        {
                            break;
                        }

                        view_word_index -= offset;
                    }
                    else if (words_size - 1 == view_word_index)
                    {
                        result.push_back(view_left);

                        view_left += word_length;
                        if (s_length < view_left + view_length)
                        {
                            break;
                        }

                        view_word_index--;

                        pop_pass_view();
                    }

                    word_count--;
                    pass_view.push(&word_count);

                    view_word_index++;
                    view_word_cursor += word_length;
                }
            }
        }

        return result;
    }
};