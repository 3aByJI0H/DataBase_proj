#pragma once

#include <iostream>
#include <string>
#include <compare>

class Date {
public:
    Date(int year=0, int month=1, int day=1);
    Date(const std::string& date_str);
    //Date(const Date& date) = default;
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    auto operator<=>(const Date&) const = default;
private:
    void DateValidationChecking() const;
    int _year, _month, _day;
};

Date ParseDate(std::istream& is);
std::ostream& operator<<(std::ostream& out_stream, const Date& date);
