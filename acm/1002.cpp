#include <iostream>
#include <string>
#include <limits.h>
#include <algorithm>

using namespace std;

string calc(string &one, string &two, string &sum)
{
  string::size_type len_one = one.length();
  string::size_type len_two = two.length();
  int carry = 0;
  int i = 0;

  while ((len_one != 0) && (len_two != 0)) {
    --len_one;
    --len_two;
    sum[i] = one[len_one] - '0' + two[len_two] + carry;
    if (sum[i] > '9') {
      sum[i] -= 10;
      carry = 1;
    } else {
      carry = 0;
    }
    ++i;
  }

  while (len_one != 0) {
    --len_one;
    sum[i] = one[len_one] + carry;
    if (sum[i] > '9') {
      sum[i] -= 10;
      carry = 1;
    } else {
      carry = 0;
    }
    ++i;
  }

  while (len_two != 0) {
    --len_two;
    sum[i] = two[len_two] + carry;
    if (sum[i] > '9') {
      sum[i] -= 10;
      carry = 1;
    } else {
      carry = 0;
    }
    ++i;
  }
  if (carry == 1) {
    sum[i] = '1';
    sum[i+1] = 0;
  } else {
    sum[i] = 0;
  }
  reverse(sum.begin(), sum.end()); 
  return sum;
}

int main() 
{
  size_t n = 0;
  string one, two;
  string sum(1000, NULL);
  cin >> n;
  for (size_t i = 0; i < n; ++i) {
    cin >> one;
    cin >> two;
    sum = calc(one, two, sum);
    if ( i != n - 1) {
    cout << "Case " << i + 1 << ":" << endl;
    cout << one << " + " << two << " = " << sum << endl << endl;
    } else {
    cout << "Case " << i + 1 << ":" << endl;
    cout << one << " + " << two << " = " << sum << endl;
    }
    sum.clear();
    sum.resize(1000);
  }
}
