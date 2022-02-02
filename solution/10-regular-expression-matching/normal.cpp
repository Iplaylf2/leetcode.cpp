#include <string>
#include <vector>
#include <array>

using std::fill_n;
using std::string;
using std::vector;

class SimpleRegex
{
public:
    SimpleRegex(const string &p) : patternVec{createPatternVector(p)} {};

    bool match(const string &x)
    {
        auto size = patternVec.size() * x.length();
        Cache record[size];
        fill_n(record, size, Cache::None);

        return match(patternVec, 0, x, 0, record);
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

    enum Cache
    {
        None,
        False,
        True,
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

    static bool match(const vector<Pattern> &patternVec, int pIndex, const string &s, int sIndex, Cache *record)
    {
        auto result = false;
        auto key = s.length() * pIndex + sIndex;

        auto pattern = patternVec[pIndex];
        if (pattern.one)
        {
            if ((!pattern.expectIsAny) && (pattern.expect != s[sIndex]))
            {
                goto finish;
            }

            pIndex++;
            sIndex++;

            if (patternVec.size() == pIndex)
            {
                result = s.length() == sIndex;
            }
            else
            {
                result = s.length() == sIndex ? allowToIgnore(patternVec, pIndex) : match(patternVec, pIndex, s, sIndex, record);
            }
        }
        else
        {
            pIndex++;

            if (pattern.expectIsAny)
            {
                if (patternVec.size() == pIndex)
                {
                    result = true;
                    goto finish;
                }

                do
                {
                    bool fork = false;

                    auto key = s.length() * pIndex + sIndex;
                    auto cache = record[key];
                    switch (cache)
                    {
                    case Cache::None:
                        fork = match(patternVec, pIndex, s, sIndex, record);
                        record[key] = fork ? Cache::True : Cache::False;
                        break;
                    case Cache::False:
                        break;
                    case Cache::True:
                        fork = true;
                        break;
                    }

                    if (fork)
                    {
                        result = true;
                        goto finish;
                    }
                    else
                    {
                        sIndex++;
                    }
                } while (s.length() != sIndex);
            }
            else
            {
                if (patternVec.size() == pIndex)
                {
                    for (; pattern.expect == s[sIndex]; sIndex++)
                        ;
                    result = s.length() == sIndex;
                    goto finish;
                }

                do
                {

                    bool fork = false;

                    auto key = s.length() * pIndex + sIndex;
                    auto cache = record[key];
                    switch (cache)
                    {
                    case Cache::None:
                        fork = match(patternVec, pIndex, s, sIndex, record);
                        record[key] = fork ? Cache::True : Cache::False;
                        break;
                    case Cache::False:
                        break;
                    case Cache::True:
                        fork = true;
                        break;
                    }

                    if (fork)
                    {
                        result = true;
                        goto finish;
                    }
                    else
                    {
                        if (pattern.expect == s[sIndex])
                        {
                            sIndex++;
                        }
                        else
                        {
                            goto finish;
                        }
                    }
                } while (s.length() != sIndex);
            }

            result = allowToIgnore(patternVec, pIndex);
        }

    finish:
        record[key] = result ? Cache::True : Cache::False;
        return result;
    }

    static bool allowToIgnore(const vector<Pattern> &patternVec, int pIndex)
    {
        do
        {
            if (patternVec[pIndex].one)
            {
                return false;
            }

            pIndex++;
        } while (patternVec.size() != pIndex);

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
