#include <vector>
#include <string>
#include <unordered_map>
#include <list>

using std::copy;
using std::list;
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

        auto fixed_word_map = unordered_map<string, ViewWord>();
        for (int i = 0; words_size != i; i++)
        {
            auto &x = words[i];
            auto node = fixed_word_map.try_emplace(x, ViewWord());
            if (!node.second)
            {
                node.first->second.count++;
            }
        }

        for (int view_begin = 0; view_begin < word_length; view_begin++)
        {
            auto word_map = fixed_word_map;
            auto word_map_end = word_map.end();

            auto pass_view = list<ViewWord *>();
            auto pop_and_refresh = [&pass_view](int n)
            {
                for (int i = 0; n != i; i++)
                {
                    auto front = pass_view.front();
                    front->count++;
                    pass_view.pop_front();
                }

                for (auto x : pass_view)
                {
                    x->begin_not_set = true;
                }

                auto i = 0;
                for (auto x : pass_view)
                {
                    if (x->begin_not_set)
                    {
                        x->begin = i;
                        x->begin_not_set = false;
                    }
                    i++;
                }
            };

            int view_left = view_begin;
            int view_right = view_begin + view_length - 1;
            if (s_length <= view_right)
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
                    view_right += offset_size;
                    if (s_length <= view_right)
                    {
                        break;
                    }

                    view_word_index = 0;
                    view_word_cursor += word_length;

                    pass_view.clear();
                    word_map = fixed_word_map;
                    word_map_end = word_map.end();
                }
                else
                {
                    auto &view_word = find_result->second;
                    if (0 == view_word.count)
                    {
                        auto offset = view_word.begin + 1;
                        auto offset_size = word_length * offset;
                        view_left += offset_size;
                        view_right += offset_size;
                        if (s_length <= view_right)
                        {
                            break;
                        }

                        view_word_index -= offset;

                        pop_and_refresh(offset);
                    }
                    else if (words_size - 1 == view_word_index)
                    {
                        result.push_back(view_left);

                        view_left += word_length;
                        view_right += word_length;
                        if (s_length <= view_right)
                        {
                            break;
                        }

                        view_word_index--;

                        pop_and_refresh(1);
                    }

                    if (view_word.begin_not_set)
                    {
                        view_word.begin = view_word_index;
                        view_word.begin_not_set = false;
                    }
                    view_word.count--;

                    view_word_index++;
                    view_word_cursor += word_length;

                    pass_view.push_back(&view_word);
                }
            }
        }

        return result;
    }

private:
    struct ViewWord
    {
    public:
        ViewWord() : count{1}, begin_not_set(true) {}
        int count;
        bool begin_not_set;
        int begin;
    };
};