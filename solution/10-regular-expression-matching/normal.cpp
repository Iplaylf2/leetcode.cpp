#include <string>
#include <vector>

using std::string;
using std::vector;

class SimpleRegex
{
public:
    SimpleRegex(const string &p) : patternVec{createPatternVector(p)} {};

    bool match(const string &x)
    {
        return match(patternVec.end(), patternVec.begin(), x.data());
    }

private:
    class Pattern
    {
    public:
        Pattern(bool one) : one{one}, expectIsAny{true} {}
        Pattern(bool one, char x) : one{one}, expectIsAny{false}, expect{x} {}

        bool one;
        bool expectIsAny;
        char expect;
    };

    static vector<Pattern> createPatternVector(const string &p)
    {
        auto pattern_vec = vector<Pattern>();
        auto p_ptr = p.data();

        auto expect = *p_ptr;
        while (true)
        {
            switch (expect)
            {
            case '\0':
                return pattern_vec;
            case '.':
            {
                p_ptr++;
                auto next = *p_ptr;

                if (next == '*')
                {
                    pattern_vec.push_back(Pattern(false));

                    p_ptr++;
                    expect = *p_ptr;
                }
                else
                {
                    pattern_vec.push_back(Pattern(true));

                    expect = next;
                }
            }
            break;
            default:
            {
                p_ptr++;
                auto next = *p_ptr;

                if (next == '*')
                {
                    pattern_vec.push_back(Pattern(false, expect));

                    p_ptr++;
                    expect = *p_ptr;
                }
                else
                {
                    pattern_vec.push_back(Pattern(true, expect));

                    expect = next;
                }
            }
            break;
            }
        }

        return {}; // never
    }

    static bool match(const vector<Pattern>::const_iterator &end, vector<Pattern>::const_iterator begin, const char *s)
    {
        auto pattern = *begin;
        if (pattern.one)
        {
            if ((!pattern.expectIsAny) && (pattern.expect != *s))
            {
                return false;
            }

            begin++;
            s++;

            if (end == begin)
            {
                return '\0' == *s;
            }
            else
            {
                return '\0' == *s ? allowToIgnore(end, begin) : match(end, begin, s);
            }
        }
        else
        {
            begin++;

            if (pattern.expectIsAny)
            {
                if (end == begin)
                {
                    return true;
                }

                do
                {
                    auto fork = match(end, begin, s);
                    if (fork)
                    {
                        return true;
                    }
                    else
                    {
                        s++;
                    }
                } while ('\0' != *s);
            }
            else
            {
                if (end == begin)
                {
                    for (; pattern.expect == *s; s++)
                        ;
                    return '\0' == *s;
                }

                do
                {
                    auto fork = match(end, begin, s);
                    if (fork)
                    {
                        return true;
                    }
                    else
                    {
                        if (pattern.expect == *s)
                        {
                            s++;
                        }
                        else
                        {
                            return false;
                        }
                    }
                } while ('\0' != *s);
            }
        }

        return false;
    }

    static bool allowToIgnore(const vector<Pattern>::const_iterator &end, vector<Pattern>::const_iterator &begin)
    {
        do
        {
            if (begin->one)
            {
                return false;
            }

            begin++;
        } while (end != begin);

        return true;
    }

    const vector<Pattern> patternVec;
};

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        return SimpleRegex(p).match(s);
    }
};
