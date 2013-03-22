#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void pythagorean(unsigned int &a, unsigned int &b, unsigned int &c)
{
  if (a > b) {
    a ^= b;
    b ^= a; 
    a ^= b;
  }
  if (b > c) {
    b ^= c;
    c ^= b;
    b ^= c;
  }
  if ((a * a + b * b) == (c * c)) {
    cout << "yes";
  } else {
    cout << "no";
  }
}

int main()
{
  unsigned int n = 0;
  unsigned int a, b, c;
  cin >> n; 
  for (unsigned int i = 0; i < n; ++i) {
    cin >> a;
    cin >> b;
    cin >> c;
    cout << "Scenario #" << i + 1 << ":" << endl;
    pythagorean(a, b, c);
    cout << endl << endl;
  }
  return 0;
}
