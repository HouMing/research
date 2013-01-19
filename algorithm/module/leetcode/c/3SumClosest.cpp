// http://leetcode.com/2012/05/clone-graph-part-i.html
/*
 * Given an array S of n integers, are there elements a, b, c in S such that a +
 * b + c = 0? Find all unique triplets in the array which gives the sum of zero.
 *
 * Note:
 * Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
 * The solution set must not contain duplicate triplets.
 * For example, given array S = {-1 0 1 2 -1 -4},
 *
 * A solution set is:
 * (-1, 0, 1)
 * (-1, -1, 2)
 */
#include <iostream>
#include <vector>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

class Solution
{
 public:
  int threeSumClosest(vector<int> &num, int target)
  {
    vector<int>::size_type size = num.size();
    num.
    for (vector<long>::size_type i = 0 ; i < size; ++i) {
      lnum[i] = num[i];
    }
    long ret;
    long tmp;
    ret = tmp = target + INT_MAX;
    if (size < 3) {
      return LONG_MIN + 1;
    }
    for (vector<int>::size_type i = 0; i != size ; ++i) {
      tmp = num[(i + size - 1 ) % size] + num[i] + num[(i + 1) % size]; 
      ret = abs(tmp - target) < abs(ret - target) ? tmp : ret;
      cout << tmp <<endl;
    }
    return ret;
  }
};

int main() {
  cout << "3SumClosest" << endl;
  vector<int> sum(9,0);
  sum[0] = 4;
  sum[1] = 0;
  sum[2] = 5;
  sum[3] = -5;
  sum[4] = 3;
  sum[5] = 3;
  sum[6] = 0;
  sum[7] = -4;
  sum[8] = -5;
  Solution sln = Solution();
  int ret = sln.threeSumClosest(sum, -1);
  cout << ret << endl;
  return 0;
}
