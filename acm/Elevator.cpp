#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  unsigned short n = 0;
  while (cin >> n) {
    unsigned short cur = 0;
    unsigned short next = 0;
    unsigned short time = 0;
    if (n == 0) {
      break;
    }
    for (unsigned int i = 0; i < n; ++i) {
      cin >> next;   
      time += 5;
      time += next > cur ? ((next - cur)<<1) * 3 : (cur - next)<<2;
      cur = next;
    }
    cout << time << endl;
  }
  return 0;
}

