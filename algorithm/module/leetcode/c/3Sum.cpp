#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution
{
 public:
  vector<vector<int> > threeSum(vector<int> &num)
  {
    vector<vector<int> > ret;
    vector<int>::size_type size = num.size();
    sort(num.begin(), num.end());
    int cur_sum;
    for (vector<int>::size_type i = 0; i != size-2 ; ++i) {
      vector<int>::size_type l = i + 1;
      vector<int>::size_type r = size - 1;
      cur_sum = num[i] + num[l] + num[r];
      while (l < r) {
        cur_sum = num[i] + num[l] + num[r];
        if (cur_sum == 0) {
          vector<int> vc;
          vc.push_back(num[l]);
          vc.push_back(num[i]);
          vc.push_back(num[r]);
          ret.push_back(vc);
          ++l;
        }
        if (cur_sum < 0) {
          ++l;
        }
        if (cur_sum > 0) {
          --r;
        }
      }
    }
    return ret;
  }
};

int main() {
  // Start typing your code here...
  cout << "3Sum:" << endl;
  int arr[] = {-1, 0, 1, 2, -1, -4};
  vector<int> tmp(arr,arr + 7);
  Solution sln;
  vector<vector<int> > trmp =  sln.threeSum(tmp);
  for (vector<vector<int> >::size_type i = 0; i < trmp.size(); ++i) {
    for (vector<int>::size_type j = 0; j < trmp[i].size() ; ++j) {
      cout << trmp[i][j] << endl;
    }
  }
  cout << "!3Sum:" << endl;
  return 0;
}
