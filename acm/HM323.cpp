#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#define Year int
#define Month int
#define Day int

#define Day_of_Year 365
#define Day_of_LeapYear 366

using namespace std;

class Date {
 public:
  Date ()
  {
    year = 2013;
    month = 3;
    day = 24;
  }

  string toString ()
  {
    stringstream str;
    str << year << "/" << setw(2) << setfill('0') << month << "/" << setw(2) << setfill('0') << day;
    return str.str(); 
  }

  void sub (Day days)
  {
    // count years
//    while (days >= Day_of_LeapYear || days >= Day_of_Year) {
//      Year pre_year = year - 1;
//      if (isLeapYear(pre_year)) {
//        days -= Day_of_LeapYear;
//        year = pre_year;
//      } else {
//        days -= Day_of_Year;
//        year = pre_year;
//      }
//    }
    // count monthes
    while (day <= days) {
     days -= day;
     day = checkMonth(month - 1, year);
     --month;
     if(month < 1) {
       month = 12;
       --year;
     }
    }
    // count days
    day -= days;
  }

  void add (Day days)
  {
    // count years
//    while (days >= Day_of_LeapYear || days >= Day_of_Year) {
//      Year pre_year = year + 1;
//      if (isLeapYear(pre_year)) {
//        days -= Day_of_LeapYear;
//        year = pre_year;
//      } else {
//        days -= Day_of_Year;
//        year = pre_year;
//      }
//    }
    // count monthes
    while (checkMonth(month, year) < day + days) {
     days = days - checkMonth(month, year) - 1 + day;
     day = 1;
     ++month;
     if (month > 12) {
       month = 1;
       ++year;
     }
    }
    // count days
    day += days;
  }
  
 private:
  Year year;
  Month month;
  Day day; 

  inline bool isLeapYear(Year year_)
  {
    return ((year_%4 == 0) && (year_%100 != 0)) || (year_%400 == 0);
  }

  int checkMonth(Month month, Year year_)
  {
    switch(month) {
      case 0:
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
      case 13:
        return 31;
      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
      case 2:
        if (isLeapYear(year_)) {
          return 29;
        } else {
          return 28;
        }
      default:
        abort();
    }
  }
};

int main() {
  int n = 0;
  int days = 0;
  cin >> n;
  while (n-- > 0) {
    cin >> days;
    Date date_add;
    Date date_sub;
    date_add.add(days);
    date_sub.sub(days);
    cout << date_add.toString() << " " << date_sub.toString() << endl;
  }
  return 0;
}
