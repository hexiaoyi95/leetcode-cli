/*
 * [5] Longest Palindromic Substring
 *
 * https://leetcode.com/problems/longest-palindromic-substring
 *
 * Medium (25.12%)
 * Total Accepted:
 * Total Submissions:
 * Testcase Example:  '"babad"'
 *
 * Given a string s, find the longest palindromic substring in s. You may
 * assume that the maximum length of s is 1000.
 *
 * Example:
 *
 * Input: "babad"
 *
 * Output: "bab"
 *
 * Note: "aba" is also a valid answer.
 *
 *
 *
 * Example:
 *
 * Input: "cbbd"
 *
 * Output: "bb"
 *
 *
 */
class Solution {
public:
    string longestPalindrome(string s) {
    string curLongest = s.substr(0,1);
    int curLength = 1;
    int begin = 0;
    int end = 0;
    while( begin + curLength - 1  < s.length() - 1 ){
        char firstChar = s.at(begin);
        size_t found = s.find(firstChar, begin + 1);
        while( found != string::npos ){
            if (curLength - 1  < found - begin + 1){
                bool is_palindromic = true;
                int idx = 0;
                while( idx < (found - begin +1)/2 ){
                    if( s.at(begin + idx) != s.at(begin + found - begin + 1  - idx - 1 )){
                        is_palindromic = false;
                        break;
                    }
                    idx++;
                }
                if( is_palindromic ){
                    curLength = found - begin + 1;
                    curLongest = s.substr(begin, found - begin + 1);
                }
            }
            found = s.find(firstChar, found + 1);
        }
        begin++;
    }
    return curLongest;
    }
};
