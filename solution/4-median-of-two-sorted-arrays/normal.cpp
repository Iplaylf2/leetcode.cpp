#include <vector>
#include <algorithm>

using std::min;
using std::swap;
using std::vector;

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int size1 = nums1.size();
        int size2 = nums2.size();

        if (size2 < size1)
        {
            swap<vector<int>>(nums1, nums2);
            swap(size1, size2);
        }

        if (size1 == 0)
        {
            auto mid = size2 >> 1;
            if (size2 % 2 == 0)
            {
                return (nums2[mid] + nums2[mid + 1]) / 2.0;
            }
            else
            {
                return nums2[mid];
            }
        }

        int sizeAll = size1 + size2;
        if (sizeAll % 2 == 0)
        {
            return even(nums1, nums2, size1, size2, sizeAll);
        }
        else
        {
            return odd(nums1, nums2, size1, size2, sizeAll);
        }
    }

public:
    int odd(vector<int> &nums1, vector<int> &nums2, int &size1, int &size2, int &sizeAll)
    {
        auto mid_left = sizeAll >> 1;

        auto mid_in_nums2 = mid_left - size1; // min index in nums2

        auto v1 = nums1[size1 - 1];
        auto v2 = nums2[mid_in_nums2];
        if (v1 <= v2)
        {
            return v2;
        }

        auto begin_nums2 = mid_in_nums2;
        auto end_nums2 = mid_left + 1; // max index in nums2
        mid_in_nums2 = (begin_nums2 + end_nums2) >> 1;

        while (true)
        {
            if (mid_in_nums2 == mid_left)
            {
                // finally test
                v1 = nums1[0];
                v2 = nums2[mid_in_nums2];
                return min(v1, v2);
            }

            auto left_close = mid_left - mid_in_nums2 - 1;

            v1 = nums1[left_close];
            v2 = nums2[mid_in_nums2];
            if (v2 < v1)
            {
                begin_nums2 = mid_in_nums2;
            }
            else
            {
                auto right_close = left_close + 1;
                v1 = nums1[right_close];

                if (v1 < v2)
                {
                    end_nums2 = mid_in_nums2;
                }
                else
                {
                    return v2;
                }
            }

            mid_in_nums2 = (begin_nums2 + end_nums2) >> 1;
            if (mid_in_nums2 == begin_nums2)
            {
                return v1;
            }
        }

        return 0; // never
    }

    int even(vector<int> &nums1, vector<int> &nums2, int &size1, int &size2, int &sizeAll)
    {
    }
};