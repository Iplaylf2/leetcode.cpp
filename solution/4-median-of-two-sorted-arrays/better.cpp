#include <vector>
#include <climits>

using std::max;
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

        auto size_all = size1 + size2;
        auto half_size = (size_all + 1) / 2;

        //  oooI -> ooD     ; oooI -> ooD
        // Ixxxx ->   Jxxxx ; Ixxx ->   Jxxx
        auto J1 = size1 - 1;
        auto J2 = size2 - half_size - 1;

        int begin_J2;
        auto end_J2 = half_size;

        while (true)
        {
            auto left1 = J1 == -1 ? INT_MIN : nums1[J1];
            auto right2_index = J2 + 1;
            auto right2 = right2_index == size2 ? INT_MAX : nums2[right2_index];

            if (right2 < left1)
            {
                begin_J2 = J2;
                J2 = (begin_J2 + end_J2) / 2;
                J1 += begin_J2 - J2;
            }
            else
            {
                auto left2 = J2 == -1 ? INT_MIN : nums2[J2];
                auto right1_index = J1 + 1;
                auto right1 = right1_index == size1 ? INT_MAX : nums1[right1_index];

                if (right1 < left2)
                {
                    end_J2 = J2;
                    J2 = (begin_J2 + end_J2) / 2;
                    J1 += end_J2 - J2;
                }
                else
                {
                    // find mid

                    if (size_all % 2 == 0)
                    {
                        auto mid1 = max(left1, left2);
                        auto mid2 = min(right1, right2);
                        return (mid1 + mid2) / 2.0;
                    }
                    else
                    {
                        return min(right1, right2);
                    }
                }
            }
        }

        return 0; //never
    }
};