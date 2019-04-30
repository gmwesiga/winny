#ifndef UTILITIES_TIME_H
#define UTILITIES_TIME_H

/*
*winny::utilities::Time class
*provides a suitable interface to the standard c library date and time library utilities .
*author: Gilbert Mwesiga on Jan 10 2017
*property setters are chainable. eg Time t = (new Time(2017,1,10))->hours(15)->minutes(30)->seconds(03)
*/
#include <ctime>
#include <string>
#include <sstream>
#include <cstdio>

using std::string;
using std::tm; //calendar time
using std::time_t; //time since epoch type

static  string SEPARATOR ="-";  

namespace utils {
	//wrapper of c-style time and date utilities
	class Time
	{
		public:
		Time();
		Time(int hh, int mm, int ss);
		Time(const Time& t); //copy constructor
		int year(){return std_tm.tm_year+1900;};
		int month(){return std_tm.tm_mon+1;};
		int day(){return std_tm.tm_mday;};
		int hours(){return std_tm.tm_hour;};
		int minutes(){return std_tm.tm_min;};
		int seconds(){return std_tm.tm_sec;};
		bool day_equals(const Time&);
		bool day_is_before(const Time&);
		bool day_is_after(const Time&);
		
		Time* year(int yy);
		Time* month(int mm);
		Time* day(int dd);
		Time* hours(int hh);
		Time* minutes(int mm);
		Time* seconds(int ss);
		string to_string();
		string weekday();
		string smonth();
		string sdate(string& separator=SEPARATOR);
		string stime(string& separator=SEPARATOR);
		string stimestamp(string& separator=SEPARATOR);
		double timestamp();

		double  diff(const Time& t);
		private:
		tm std_tm;
	};


}; //end of namespace utils

#endif