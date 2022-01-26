#include <vector>
#include <algorithm>

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

        if (size1 == 0)
        {
            auto mid = size2 / 2;
            if (size2 % 2 == 0)
            {
                return (nums2[mid - 1] + nums2[mid]) / 2.0;
            }
            else
            {
                return nums2[mid];
            }
        }

        auto size_all = size1 + size2;
        if (size_all % 2 == 0)
        {
            return even(nums1, nums2, size1, size2, size_all);
        }
        else
        {
            return odd(nums1, nums2, size1, size2, size_all);
        }
    }

private:
    int odd(vector<int> &nums1, vector<int> &nums2, int &size1, int &size2, int &sizeAll)
    {
        auto mid_left = sizeAll / 2;

        auto mid_in_nums2 = mid_left - size1; // min index in nums2

        int begin_nums2;
        auto end_nums2 = mid_left + 1; // max index is mid_left

        while (true)
        {
            auto left_test = mid_left - mid_in_nums2 - 1;

            auto v1 = nums1[left_test]; // 0 <= left_test
            auto v2 = nums2[mid_in_nums2];
            if (v2 < v1)
            {
                auto right_test_nums2 = mid_in_nums2 + 1;
                auto v2 = nums2[right_test_nums2]; // right_test < size_2

                if (v2 < v1)
                {
                    begin_nums2 = mid_in_nums2;
                }
                else
                {
                    return v1;
                }
            }
            else
            {
                auto right_test = left_test + 1;
                if (right_test == size1 || (v1 = nums1[right_test], v2 <= v1))
                {
                    return v2;
                }
                else
                {
                    auto left_test_nums2 = mid_in_nums2 - 1;
                    if (nums2[left_test_nums2] <= v1)
                    {
                        return v1;
                    }
                    else
                    {
                        end_nums2 = mid_in_nums2;
                    }
                }
            }

            mid_in_nums2 = (begin_nums2 + end_nums2) / 2;
            if (mid_in_nums2 == mid_left)
            {
                // finally test
                auto v1 = nums1[0];
                auto v2 = nums2[mid_in_nums2];
                return min(v1, v2);
            }
        }

        return 0; // never
    }

    double even(vector<int> &nums1, vector<int> &nums2, int &size1, int &size2, int &sizeAll)
    {
        auto mid_left = (sizeAll / 2) - 1;

        auto mid_in_nums2 = max(0, mid_left - size1);

        int begin_nums2;
        auto end_nums2 = mid_left + 1;

        while (true)
        {
            if (mid_in_nums2 == mid_left)
            {
                auto v1 = nums1[0];
                auto v2 = nums2[mid_in_nums2];
                int other_mid;

                if (v1 < v2)
                {
                    if (1 == size1)
                    {
                        other_mid = v2;
                    }
                    else
                    {
                        auto v1_next = nums1[1];
                        other_mid = min(v1_next, v2);
                    }

                    return (v1 + other_mid) / 2.0;
                }
                else
                {
                    auto i2_next = mid_in_nums2 + 1;
                    if (i2_next == size2)
                    {
                        other_mid = v1;
                    }
                    else
                    {
                        auto v2_next = nums2[i2_next];
                        other_mid = min(v1, v2_next);
                    }

                    return (v2 + other_mid) / 2.0;
                }
            }

            auto left_test = mid_left - mid_in_nums2 - 1;
            auto v1 = nums1[left_test];
            auto v2 = nums2[mid_in_nums2];

            if (v2 < v1)
            {
                auto right_test_nums2 = mid_in_nums2 + 1;
                auto v2 = nums2[right_test_nums2]; // right_test < size_2

                if (v2 < v1)
                {
                    begin_nums2 = mid_in_nums2;
                }
                else
                {
                    auto i1_next = left_test + 1;

                    int other_mid;
                    if (i1_next == size1)
                    {
                        other_mid = v2;
                    }
                    else
                    {
                        auto v1_next = nums1[i1_next];
                        other_mid = min(v1_next, v2);
                    }

                    return (v1 + other_mid) / 2.0;
                }
            }
            else
            {
                auto right_test = left_test + 1;
                if (right_test == size1)
                {
                    auto v2_next = nums2[mid_in_nums2 + 1];
                    return (v2 + v2_next) / 2.0;
                }
                else
                {
                    auto v1 = nums1[right_test];
                    if (v1 < v2)
                    {
                        auto left_test_nums2 = mid_in_nums2 - 1;
                        if (left_test_nums2 < 0 || nums2[left_test_nums2] <= v1)
                        {
                            auto i1_next = right_test + 1;

                            int other_mid;
                            if (i1_next == size1)
                            {
                                other_mid = v2;
                            }
                            else
                            {
                                auto v1_next = nums1[i1_next];
                                other_mid = min(v1_next, v2);
                            }

                            return (v1 + other_mid) / 2.0;
                        }
                        else
                        {
                            end_nums2 = mid_in_nums2;
                        }
                    }
                    else
                    {
                        auto i2_next = mid_in_nums2 + 1;

                        int other_mid;
                        if (i2_next == size2)
                        {
                            other_mid = v1;
                        }
                        else
                        {
                            auto v2_next = nums2[i2_next];
                            other_mid = min(v1, v2_next);
                        }

                        return (v2 + other_mid) / 2.0;
                    }
                }
            }

            mid_in_nums2 = (begin_nums2 + end_nums2) / 2;
        }

        return 0; //never
    }
};