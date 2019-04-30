#include "gmtime.h"
/*****************************************
 implementation of Time
 *****************************************/
using namespace utils;

Time::Time(){
    time_t t = time(NULL);
    std_tm  = *(gmtime(&t));
};

Time::Time(const Time& t){
    std_tm = t.std_tm;

}

Time::Time(int yy, int mm, int dd){
    yy = yy < 1900 ? 1900 : yy > 2050 ? 2050 :yy;
    mm = mm < 1 ? 1:mm > 12 ? 12 :mm;
    dd = dd < 1 ? 1: dd> 31? 31: dd;
    std_tm.tm_year = yy-1900;
    std_tm.tm_mon  = mm-1;
    std_tm.tm_mday = dd;
};

Time* Time::year(int yy){
    yy = yy < 1900 ? 1900 : yy > 2050 ? 2050 :yy;
    std_tm.tm_year = yy-1900;
    return this;
};

Time* Time::month(int mm){
    mm = mm < 1 ? 1:mm > 12 ? 12 :mm;		
    std_tm.tm_mon = mm-1;
    return this;
};

Time* Time::day(int dd){
    dd = dd < 1 ? 1: dd> 31? 31: dd;		
    std_tm.tm_mday = dd;
    return this;
};

Time* Time::hours(int hh){
    hh = hh<0? 0: hh>23? 23:hh;
    std_tm.tm_hour = hh;
    return this;
};

Time* Time::minutes(int mm){
    mm = mm< 0? 0 :mm>59? 59:mm;
    std_tm.tm_min = mm;
    return this;
};

Time* Time::seconds(int ss){
    ss = ss< 0? 0 :ss>59? 59:ss;
    std_tm.tm_sec = ss;
    return this;
};

double Time::diff(const Time& t){
    tm ttm = t.std_tm;
    time_t tt = std::mktime(&ttm);
    time_t me = std::mktime(&std_tm);
    return difftime(me,tt);
}

string Time::to_string(){
    std::stringstream ss;
    ss.clear();
    ss << weekday() << " "<< day()<<" "<< smonth() <<" "<< year()<< ", "
        <<hours()<<":"<< minutes()<<":"<<seconds()<<"(GMT)";
        return ss.str();
};


string Time::sdate(string& separator){
    std::stringstream ss;
    ss.clear();
    ss<<year()<<separator<<month()<<separator<<day();
    return ss.str();
}


string Time::stime(string& separator){
    std::stringstream ss;
    ss.clear();
    ss<<hours()<<separator<<minutes()<<separator<<seconds();
    return ss.str();
}


string Time::stimestamp(string& separator){
    std::stringstream ss;
    ss.clear();
    ss<<sdate(separator)<<separator<<stime(separator);
    return ss.str();
}

string Time::weekday(){
    std::mktime(&std_tm);
    const char* days[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    return string(days[std_tm.tm_wday]);
};

string Time::smonth(){
    const char* mons[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};
    return string(mons[std_tm.tm_mon]);
}


double Time::timestamp(){
    return std::mktime(&std_tm);
}

bool Time::day_equals(const Time& t){
    return t.std_tm.tm_year == std_tm.tm_year &&
            t.std_tm.tm_mon  == std_tm.tm_mon &&
            t.std_tm.tm_mday == std_tm.tm_mday;
};

bool Time::day_is_before(const Time& t){
    bool is_same_year = t.std_tm.tm_year == std_tm.tm_year;
    bool is_same_month = t.std_tm.tm_mon == std_tm.tm_mon;
    return t.std_tm.tm_year > std_tm.tm_year ||
            is_same_year && t.std_tm.tm_mon  > std_tm.tm_mon ||
            is_same_year && is_same_month && t.std_tm.tm_mday > std_tm.tm_mday;
};

bool Time::day_is_after(const Time& t){
    bool is_same_year = t.std_tm.tm_year == std_tm.tm_year;
    bool is_same_month = t.std_tm.tm_mon == std_tm.tm_mon;
    return (t.std_tm.tm_year < std_tm.tm_year) ||
            (is_same_year && (t.std_tm.tm_mon  < std_tm.tm_mon) ) ||
            is_same_year && is_same_month && (t.std_tm.tm_mday < std_tm.tm_mday);
};