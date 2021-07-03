#include "date.h"

#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <string>


Date::Date(int year, int month, int day)
: _year(year), _month(month), _day(day) {
    Date::DateValidationChecking();
}
Date::Date(const std::string& date_str) {
    if(date_str.find_first_not_of("-+0123456789") != std::string::npos)
        throw std::invalid_argument("Wrong date format: "+date_str);

    size_t pos1 = date_str.find_first_of('-', 1),
           pos2 = date_str.find_first_of('-', pos1+2);

    if (0 < pos1  and pos1+1 < pos2 and pos2+1 < date_str.size()) {
        try{
            _year = std::stoi(date_str.substr(0, pos1));
            _month = std::stoi(date_str.substr(pos1+1, pos2-pos1-1));
            _day = std::stoi(date_str.substr(pos2+1));
        } catch(const std::invalid_argument& ex) {
            throw std::invalid_argument("Wrong date format: "+date_str);
        }
        Date::DateValidationChecking();
    } else {
        throw std::invalid_argument("Wrong date format: "+date_str);
    }
}

int Date::GetYear() const {return _year;}
int Date::GetMonth() const {return _month;}
int Date::GetDay() const {return _day;}

void Date::DateValidationChecking() const {
    if (_year < 0 or _year > 9999) {
        throw std::invalid_argument(
            "Year value is invalid: "+std::to_string(_year));
    } 
    if (_month < 1 or _month > 12) {
        throw std::invalid_argument(
            "Month value is invalid: "+std::to_string(_month));
    } 
    if (_day < 1 or _day > 31) {
        throw std::invalid_argument(
            "Day value is invalid: "+std::to_string(_day));
    }
}

std::ostream& operator<<(std::ostream& out_stream, const Date& date) {
  out_stream << std::setfill('0') << std::setw(4) << date.GetYear()
             << '-' << std::setw(2) << date.GetMonth()
             << '-' << std::setw(2) << date.GetDay();
  return out_stream;
};

Date ParseDate(std::istream& is) {
    std::string date;
    is >> date;
    return Date{date};
}