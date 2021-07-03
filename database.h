#pragma once

#include "date.h"

#include <map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <string>


class Database {
public:
  void Add(const Date& date, const std::string& event);
  int RemoveIf(std::function<bool(const Date&, const std::string&)> const& predicate);
  std::vector<std::string> FindIf(
    std::function<bool(const Date&, const std::string&)> const& predicate) const;
  std::string Last(const Date& date) const;
  void Print(std::ostream& os) const;

private:
 std::unordered_set<std::string> _date_event_set;
 std::map<Date, std::vector<std::string> > _date_to_events_vector;
};
