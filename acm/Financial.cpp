#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
 float cur = 0.0f;
 float sum = 0.0f;
 for (int i = 0 ; i < 12 ; ++i) {
  cin >> cur ;
  sum += cur;
 }
  sum /= 12;
  cout << "$" << sum << endl;
 return 0;
}

