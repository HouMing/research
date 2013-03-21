#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  int n, a, sum;
  stringstream str;
  while (cin >> n) {
    str << n << " ";
    while (n-- > 0) {
      cin >> a;
      str << a << " ";
      sum += a;
    }
    cout << sum << endl;
    sum = 0;
  }
  cout << str.str() << endl;
}

