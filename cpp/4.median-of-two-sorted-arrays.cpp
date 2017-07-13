/*
 * [4] Median of Two Sorted Arrays
 *
 * https://leetcode.com/problems/median-of-two-sorted-arrays
 *
 * Hard (21.39%)
 * Total Accepted:    165795
 * Total Submissions: 775002
 * Testcase Example:  '[1,3]\n[2]'
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 *
 * Example 1:
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 *
 *
 * Example 2:
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 *
 *
 */
#define INT_MAX 0x7fffffff
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int index1 = 0;
        int index2 = 0;
        int cur = 0;
        int length = nums1.size() + nums2.size();
        int i = 0;
        int num1 = 0;
        int num2 = 0;
        int last = 0;
        while(i < length){
            if ( index1 < nums1.size() )
                num1 = nums1[index1];
            else
                num1 = INT_MAX;
            if ( index2 < nums2.size() )
                num2 = nums2[index2];
            else
                num2 = INT_MAX;
            if (num1 < num2){
                cur = num1;
                index1++;
            }
            else{
                cur = num2;
                index2++;
            }
            if ( i == length /2 ){
                if ( length % 2 == 0 ){
                    return ( last + cur ) / 2.0;
                }
                else
                    return cur;
            }
            last = cur;
            i++;
        }



    }
};
