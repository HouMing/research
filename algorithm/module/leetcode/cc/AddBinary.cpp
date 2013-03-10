#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

class Solution {

 public:
  string addBinary( string a, string b)
  {
    string::size_type a_len = a.size();
    string::size_type b_len = b.size();
    string::size_type max_len = a_len > b_len ? a_len : b_len;
    string::size_type min_len = a_len < b_len ? a_len : b_len;
    const string& max = a_len > b_len ? a : b;
    const string& min = a_len > b_len ? b : a;
    string::size_type ret_len = max_len + 1;
    char* ret = new char[ret_len + 1];
    char carry = '0';
    char add = '0';

    ret[ret_len] = 0;
    for( ; min_len != 0 ;) {
      --min_len;
      --max_len;
      --ret_len;
      add = max[max_len] - '0' + min[min_len] - '0' + carry;
      switch(add) {
        case '0':
          ret[ret_len] = '0';
          carry = '0';
          break;
        case '1':
          ret[ret_len] = '1';
          carry = '0';
          break;
        case '2':
          ret[ret_len] = '0';
          carry = '1';
          break;
        case '3':
          ret[ret_len] = '1';
          carry = '1';
          break;
        default:
          break;
      }
    }

    for( ; max_len != 0 ;) {
      --max_len;
      --ret_len;
      add = max[max_len] - '0' + carry;
      switch(add) {
        case '0':
          ret[ret_len] = '0';
          carry = '0';
          break;
        case '1':
          ret[ret_len] = '1';
          carry = '0';
          break;
        case '2':
          ret[ret_len] = '0';
          carry = '1';
          break;
        default:
          break;
      }
    }
    --ret_len;
    ret[ret_len] = carry;
    string tmp;
    if( carry == '0') {
      tmp = ret + 1;
    } else {
      tmp = ret;
    }
    delete []ret;
    return tmp;
  }

};

int main()
{
  Solution sln = Solution();
  string a = "1111001";
  string b = "101";
  string c = sln.addBinary(a, b);
  cout<<c<<endl;
}
