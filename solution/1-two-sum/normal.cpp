using namespace std;
#include <vector>
#include <unordered_map>

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        auto ask = unordered_map<int, int>();
        for (int i = 0, end = nums.size(); i != end; i++)
        {
            auto current = nums[i];
            auto expect = ask.find(current);
            if (expect == ask.end())
            {
                ask.emplace(target - current, i);
            }
            else
            {
                return {expect->second, i};
            }
        }

        return {};
    }
};