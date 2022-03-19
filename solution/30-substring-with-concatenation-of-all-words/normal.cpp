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

        auto word_map = unordered_map<string, ViewWord>();
        for (int i = 0; words_size != i; i++)
        {
            auto &x = words[i];
            auto node = word_map.try_emplace(x, ViewWord());
            if (!node.second)
            {
                node.first->second.total++;
            }
        }
        auto word_map_end = word_map.end();
        auto reset_word_map = [&word_map]()
        {
            for (auto &[_, x] : word_map)
            {
                x.count = 0;
            }
        };

        for (int group_index = 0; group_index < word_length; group_index++)
        {
            int view_begin = group_index;
            if (s_length < view_begin + view_length)
            {
                break;
            }

            auto view_word_cursor = view_begin;

            auto pass_count = 0;
            auto pass_queue = queue<int *>();

            auto pop_pass_queue_until_same = [&pass_queue](int *x)
            {
                auto n = 0;
                while (true)
                {
                    n++;

                    auto front = pass_queue.front();
                    (*front)--;

                    pass_queue.pop();

                    if (x == front)
                    {
                        break;
                    }
                }

                return n;
            };

            auto pop_pass_queue = [&pass_queue]()
            {
                auto front = pass_queue.front();
                (*front)--;

                pass_queue.pop();
            };

            while (true)
            {
                auto word = s.substr(view_word_cursor, word_length);
                auto find_result = word_map.find(word);
                if (word_map_end == find_result)
                {
                    view_word_cursor += word_length;
                    view_begin = view_word_cursor;
                    if (s_length < view_begin + view_length)
                    {
                        break;
                    }

                    reset_word_map();
                    pass_queue = {};

                    pass_count = 0;
                }
                else
                {
                    auto &view_word = find_result->second;
                    view_word.count++;

                    if (view_word.count < view_word.total)
                    {
                        pass_count++;
                        pass_queue.push(&view_word.count);
                        view_word_cursor += word_length;
                    }
                    else if (view_word.total == view_word.count)
                    {
                        pass_count++;
                        if (words_size == pass_count)
                        {
                            result.push_back(view_begin);

                            view_begin += word_length;
                            if (s_length < view_begin + view_length)
                            {
                                break;
                            }

                            pass_count--;
                            pop_pass_queue();
                        }
                        view_word_cursor += word_length;

                        pass_queue.push(&view_word.count);
                    }
                    else if (view_word.total < view_word.count)
                    {
                        auto n = pop_pass_queue_until_same(&view_word.count);

                        view_begin += word_length * n;
                        if (s_length < view_begin + view_length)
                        {
                            break;
                        }
                        view_word_cursor += word_length;

                        pass_count -= n - 1;
                        pass_queue.push(&view_word.count);
                    }
                }
            }

            reset_word_map();
        }

        return result;
    }

private:
    struct ViewWord
    {
    public:
        ViewWord() : total{1}, count{0} {}
        int total;
        int count;
    };
};