/*
 * [6] ZigZag Conversion
 *
 * https://leetcode.com/problems/zigzag-conversion
 *
 * Medium (26.57%)
 * Total Accepted:    
 * Total Submissions: 
 * Testcase Example:  '""\n1'
 *
 * 
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility)
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * 
 * And then read line by line: "PAHNAPLSIIGYIR"
 * 
 * 
 * Write the code that will take a string and make this conversion given a
 * number of rows:
 * 
 * string convert(string text, int nRows);
 * 
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 * 
 */
class Solution {
public:
    string convert(string s, int numRows) {
	if ( numRows == 1)
	    return s;
	string result = "";
	int len = s.length();
	
	for (int i = 0; i < numRows; i++ ){
	    if ( i < len)
	        result += s.at(i);
	    else
		break;
	    int gap_1 = ( numRows - 1 - i ) * 2;
	    int gap_2 = i * 2;
	    int pos = i;
	    while(1){
	    	pos +=gap_1;

		if( pos >= len )
		    break;
		if( gap_1 )
		    result += s.at(pos);
		
		pos += gap_2;

		if(pos >= len)
		    break;
		if( gap_2 )
		    result += s.at(pos);

	    }


	}
	return result;
    }
};
