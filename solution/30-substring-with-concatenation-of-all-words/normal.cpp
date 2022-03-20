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
        int max_view_begin = s.length() - view_length;

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

        for (int group_index = 0; group_index < word_length; group_index++)
        {
            for (auto &[_, x] : word_map)
            {
                x.count = 0;
            }

            int view_begin = group_index;
            if (max_view_begin < view_begin)
            {
                break;
            }

            auto view_word_cursor = view_begin;

            auto subView = SubView();

            while (true)
            {
                auto word = s.substr(view_word_cursor, word_length);
                view_word_cursor += word_length;

                auto find_result = word_map.find(word);
                if (word_map_end == find_result)
                {
                    view_begin = view_word_cursor;
                    if (max_view_begin < view_begin)
                    {
                        break;
                    }

                    subView.PopAll();
                }
                else
                {
                    auto &view_word = find_result->second;
                    subView.Push(&view_word.count);

                    if (view_word.total == view_word.count)
                    {
                        if (words_size == subView.Length())
                        {
                            result.push_back(view_begin);

                            view_begin += word_length;
                            if (max_view_begin < view_begin)
                            {
                                break;
                            }

                            subView.Pop();
                        }
                    }
                    else if (view_word.total < view_word.count)
                    {
                        auto old_length = subView.Length();

                        subView.PopUntilSame(&view_word.count);

                        auto offset = old_length - subView.Length();
                        view_begin += word_length * offset;
                        if (max_view_begin < view_begin)
                        {
                            break;
                        }
                    }
                }
            }
        }

        return result;
    }

private:
    struct ViewWord
    {
    public:
        ViewWord() : total{1} {}
        int total;
        int count;
    };

    class SubView
    {
    public:
        SubView() : CountQueue{}, _Length{0} {}

        int Length()
        {
            return this->_Length;
        }

        void Push(int *x)
        {
            this->CountQueue.push(x);
            this->_Length++;
            (*x)++;
        }

        void Pop()
        {
            auto x = this->CountQueue.front();
            this->CountQueue.pop();
            this->_Length--;
            (*x)--;
        }

        void PopUntilSame(int *x)
        {
            int *front;
            do
            {
                front = this->CountQueue.front();
                this->CountQueue.pop();
                this->_Length--;
                (*front)--;
            } while (x != front);
        }

        void PopAll()
        {
            while (0 != this->_Length)
            {
                Pop();
            }
        }

    private:
        queue<int *> CountQueue;
        int _Length;
    };
};