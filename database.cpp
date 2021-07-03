#include "database.h"
#include <tuple>
#include <sstream>
#include <algorithm>

void Database::Add(const Date& date, const std::string& event) {
  std::ostringstream os("");
  os << date << ' ' << event;
  bool is_new = _date_event_set.insert(os.str()).second;
  if (is_new) _date_to_events_vector[date].push_back(event);
};

int Database::RemoveIf(std::function<bool(const Date&, const std::string&)> \
                        const& predicate) {
  int count = 0;
  
  for(auto date_to_events_it = _date_to_events_vector.begin(); 
    date_to_events_it != _date_to_events_vector.end();) {

    auto& [cur_date, cur_vector] = *date_to_events_it;
    auto neg_predicate = [&](std::string& s) {return not predicate(cur_date, s);};
    auto del_it = std::stable_partition(cur_vector.begin(), cur_vector.end(), neg_predicate);
    for (auto it = del_it; it != cur_vector.end(); ++it) {
      std::ostringstream os("");
      os << cur_date << ' ' << *it;
      _date_event_set.erase(os.str());
    }
    count += cur_vector.end() - del_it;
    cur_vector.erase(del_it, cur_vector.end());
    
    if (cur_vector.empty()) 
      date_to_events_it = _date_to_events_vector.erase(date_to_events_it);
    else ++date_to_events_it;
  }
  return count;
}

std::vector<std::string> Database::FindIf(
  std::function<bool(const Date&, const std::string&)> const& predicate) const {
                    
  std::vector<std::string> found_vector;
  for(auto& [date, event_vector] : _date_to_events_vector) {
    for (auto& event : event_vector) {
      if (predicate(date, event)) {
        std::ostringstream os("");
        os << date << ' ' << event;
        found_vector.push_back(os.str());
      }
    }
  }
  return found_vector;
}

void Database::Print(std::ostream& os) const {
  for (const auto& [date, event_vector] : _date_to_events_vector) {
    for (const auto& event : event_vector) {
      os << date << ' ' << event << '\n';
    }
  }
}

std::string Database::Last(const Date& date) const {
  if (_date_to_events_vector.empty()) return "No entries";
  auto it = _date_to_events_vector.upper_bound(date);
  if (it == _date_to_events_vector.begin()) return "No entries";
  else {
    --it;
    std::ostringstream os("");
    os << it->first << ' ' << (it->second).back();
    return os.str();
  };
}
