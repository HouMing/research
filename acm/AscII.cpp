#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  int i, n; 
  char tmp;
  string info;
  cin >> n;
  while (n-- > 0) {
    cin >> i;
    tmp = (char)i;
    info.push_back(tmp);
  }
  cout << info;
  return 0;
}

