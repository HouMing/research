#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

#define Year int 
#define Month unsigned short
#define Day unsigned short
#define Hour unsigned short
#define Minute unsigned short
#define Second unsigned short
#define SEC_OF_DAY 80063  
#define SEC_OF_HOUR 3481 
#define SEC_OF_MINUTE 59

class UglyClock {
 public :
  Year year;
  Month month;
  Day day;
  Hour hour;
  Minute minute;
  Second second;

  UglyClock (Year year_, Month month_, Day day_, Hour hour_, Minute minute_, Second second_)
      : hour(hour_), minute(minute_), second(second_)
  {
    year = year_ - 2012;
    month = month_ - 1;
    day = day_ - 1;
  }

  static bool isLeapYear(UglyClock clock_)
  {
    Year year = clock_.year;
    year += 2012;
    if ( ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0) ) {
      return true;
    } else {
      return false;
    }
  }

  static long YearTolong (UglyClock clock_)
  {
    if (isLeapYear(clock_)) {
      return DaysTolong(clock_.year * 366);
    } else {
      return DaysTolong(clock_.year * 365);
    } 
  }

  static long MonthTolong (const Month month)
  {
    switch (month) {
      case 0:
      case 2:
      case 4:
      case 6:
      case 7:
      case 9:
      case 11:
        return DaysTolong(31);
      case 3:
      case 5:
      case 8:
      case 10:
        return DaysTolong(30);
      case 1:
        return DaysTolong(28);
      default:
        abort();
    }
  }

  static long MonthTolong (const UglyClock clock)
  {
    long secs = 0;
    Month begin = 0;
    while (begin < clock.month) {
      secs += MonthTolong(begin);
      ++begin;
    }
    return secs;
  }

  static long DaysTolong(const UglyClock clock)
  {
    return clock.day * SEC_OF_DAY;
  }

  static long DaysTolong(const Day days)
  {
    return days * SEC_OF_DAY;
  }

  static long HourTolong(const UglyClock clock_)
  {
    Hour hour_ = clock_.hour;
    if (hour_ < 21) {
      return hour_ * SEC_OF_HOUR;
    } else {
      return (hour_ - 1) * SEC_OF_HOUR;
    }
  }

  static long MinutesTolong (const UglyClock clock_)
  {
    Minute minutes_ = clock_.minute;
    if (minutes_ > 21) {
      return (minutes_ - 1) * 59;
    } else {
      return minutes_ * 59;
    }
  }
  static long SecondTolong (const UglyClock clock_)
  {
    Second second_ = clock_.second;
    if (second_ > 21) {
      return second_ - 1;
    } else {
      return second_;
    }
  }
};

class Clock {
 public:
  Year year;
  Month month;
  Day day;
  Hour hour;
  Minute minute;
  Second second; 

  Clock(long secs)
  {
    //if (secs > SEC_OF_DAY)
  }
};

int main()
{
  unsigned int n = 0;
  Year year;
  Month month;
  Day day;
  Hour hour;
  Minute minute;
  Second second;
  char dnull;
  cin >> n;
  for (unsigned int i = 0; i < n; ++i) {
    cin >> year;
    cin >> dnull;
    cin >> month;
    cin >> dnull;
    cin >> day;
    cin >> dnull;
    cin >> hour;
    cin >> dnull;
    cin >> minute;
    cin >> dnull;
    cin >> second;
    UglyClock ugly_clock(year, month, day, hour, minute, second);
    long secs;
    secs = UglyClock::YearTolong(ugly_clock) + UglyClock::MonthTolong(ugly_clock) + UglyClock::DaysTolong(ugly_clock) + UglyClock::HourTolong(ugly_clock)
        + UglyClock::MonthTolong(ugly_clock) + UglyClock::SecondTolong(ugly_clock);
    cout << year << " " << month << " " << day << " " << hour << " " << minute << " " << second << endl; 
    cout << secs << endl; 
  }
  return 0;
}
