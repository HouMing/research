#include <iostream>
#include <sstream>
#include <string>
#include <limits.h>

using namespace std;

class GPA {

 public:
  enum Level {
    F = 0,
    D = 1,
    C = 2,
    B = 3,
    A = 4,
    E = INT_MIN
  };

  static Level valueOf(const char & value)
  {
    switch (value) {
      case 'A':
        return A;
      case 'B':
        return B;
      case 'C':
        return C;
      case 'D':
        return D;
      case 'F':
        return F;
      default:
        return E;
    }
  }

};

int main()
{
  string line;
  int sum = 0;
  float gpa = 0.0f;
  while (getline(cin, line)) {
    unsigned int i = 0;
    for (i = 0; i < line.length(); i += 2) {
      sum += GPA::valueOf(line[i]);
    }
    if (sum < 0) {
      cout << "Unknown letter grade in input" << endl;
    } else {
      gpa = (float)sum / (i >> 1);
      cout.precision(2);
      cout << fixed << gpa << endl;
    }
    sum = 0;
    gpa = 0;
  }
  return 0;
}
