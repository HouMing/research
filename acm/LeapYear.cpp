#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
 unsigned int n = 0; 
 unsigned int year = 0;
 unsigned int t = 0;
 cin >> t;
 while (t-- > 0) {
   cin >> year;
   cin >> n;
   for (;n > 0; ++year) {
     if (((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)) {
       --n;
     }
   }
   cout << year - 1 << endl;
 }
 return 0;
}
