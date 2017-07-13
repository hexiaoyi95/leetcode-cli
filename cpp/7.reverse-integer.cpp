/*
 * [7] Reverse Integer
 *
 * https://leetcode.com/problems/reverse-integer
 *
 * Easy (24.18%)
 * Total Accepted:    
 * Total Submissions: 
 * Testcase Example:  '0'
 *
 * Reverse digits of an integer.
 * 
 * 
 * Example1: x =  123, return  321
 * Example2: x = -123, return -321
 * 
 * 
 * click to show spoilers.
 * 
 * Have you thought about this?
 * 
 * Here are some good questions to ask before coding. Bonus points for you if
 * you have already thought through this!
 * 
 * If the integer's last digit is 0, what should the output be? ie, cases such
 * as 10, 100.
 * 
 * Did you notice that the reversed integer might overflow? Assume the input is
 * a 32-bit integer, then the reverse of 1000000003 overflows. How should you
 * handle such cases?
 * 
 * For the purpose of this problem, assume that your function returns 0 when
 * the reversed integer overflows.
 * 
 * 
 * 
 * 
 * 
 * Note:
 * The input is assumed to be a 32-bit signed integer. Your function should
 * return 0 when the reversed integer overflows.
 * 
 */
class Solution {
public:
    int reverse(int x) {
/*1------------------------------*/
//	int a ;
//	int b ;
//	vector<int> numbers;
//	int sgn = x > 0 ? 1 : -1;
//	long long input;
//	input = x;
//	input = sgn * input;
//	
//	while(input/10){
//	   a = input / 10;
//	   b = input % 10;
//	   numbers.push_back(b);
//	   input = a;
//	}
//	numbers.push_back(input);
//	long long  result = 0;
//	int max_ = 2147483647;
//	int size = numbers.size();
//	for(int i = 0; i< size ; i ++ ){
//	    result += numbers.at(i); 
//
//	    if (i != size - 1)
//	    	result = result * 10;
//	}
//	if ( result > max_ )
//	    return 0;
//	return sgn * result ;
//

/* 2 */
	string s = to_string(x);
	int sgn = x > 0 ? 1 : -1;

	if (s.at(0) == '-'){
	    s.erase(s.begin());
	    reverse(s);
	}
	else
	    reverse(s);
	long long result = sgn * stoll(s);
	if ( result > 2147483647 || result < -2147483648)
	    return 0;	
	return result;
    }

    void reverse(string& s){
    	int len =  s.length();
	for( int i = 0 ; i < len/2 ; i++){
	    swap(s.at(i), s.at(len - i - 1));
	}
    }
};
