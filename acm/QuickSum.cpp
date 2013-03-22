#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  string line;
  unsigned int sum = 0;
  while (getline(cin, line)) {
    if(line[0] == '#') {
      break;
    }
    string::size_type len = line.size();
    for (string::size_type i = 1; i <= len; ++i) {
      if (line[i-1] >= 'A' && line[i-1] <= 'Z') {
        sum += (line[i-1] - 'A' + 1) * i;
      }
    }
    cout << sum << endl;
    sum = 0;
    line.clear();
  }
  return 0;
}
