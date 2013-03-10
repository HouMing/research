#include <vector>
#include <string>

using namespace std;

class Solution {
 public:
  vector<string> anagrams(vector<string> &strs) {
  vector<string> ret;
  for (vector<string>::size_type i = 0; i < strs.size(); ++i) {
    string tmp = strs[i];
    string elem(tmp);
    const size_t size = tmp.size();
    if ( size == 0) {
      ret.push_back(elem);
      break;
    }
    for (size_t i = 0; i < size ; ++i) {
     elem[i] = tmp[size - 1 - i]; 
    }
    ret.push_back(elem);
  }
  return ret;
  }
};
