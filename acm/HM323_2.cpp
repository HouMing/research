#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  int T;
  int N;
  int K;
  int M;
  int F;
  cin >> T;
  while (T-- > 0) {
    cin >> N;
    cin >> K;
    cin >> M;
    N *= 10;
    K *= 10;
    M *= 10;
    F = N * K / M;
    if (F % 10 > 5) {
      F = F / 10 + 1;
    } else {
      F = F / 10;
    }
    cout << F << endl; 
  }
 return 0;
}
