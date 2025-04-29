#include "Password.h"

bool has_digit(const std::string& str) {
    for (char c : str) {
        if (isdigit(c)) { return true; }
    }
    return false;
}

bool has_u_case(const std::string& str) {
    for (char c : str) {
        if (isupper(c)) { return true; }
  }
    return false;
}

bool has_l_case(const std::string& str) {
    for (char c : str) {
        if (islower(c)) { return true; }
  }
    return false;
}

int cnt_sp_chars(const std::string& str) {
    int cnt {};
    for (char c : str) {
        if (!isalnum(c)) { cnt++; }
    }
    return cnt;
}

//find such patterns as 'qwErtY', 'ADMIN', etc.
void Password::FindCommonPatterns() {
  //add common (lower case) passwords to this vector
  const std::vector<std::string> patterns = {
    "123123",
    "123321",
    "123qwe",
    "1q2w3e",
    "abc123",
    "admin",
    "dragon",
    "iloveyou",
    "lovely",
    "password",
    "qwerty",
    "welcome"
  };
  std::string shortest_pattern = patterns[0];
  for (std::string pattern: patterns)
    if (pattern.size() < shortest_pattern.size())
      shortest_pattern = pattern;
  //make sure the password is long enough
  if (m_password.size() < shortest_pattern.size()) return;
  for (std::string pattern: patterns) {
    if (pattern.size() > m_password.size()) continue;
    for (std::size_t i=0; i<m_password.size(); i++) {
      std::string temp_string;
      if (tolower(m_password[i]) == pattern[0]) {
        for (std::size_t j=0; j<pattern.size(); j++) {
          if (tolower(m_password[i+j]) == pattern[j])
            temp_string.push_back(m_password[i+j]);
          else break;
        }
        if (temp_string.size() == pattern.size()) {
          m_pattern_set.insert(temp_string);
          i += pattern.size()-1;
        }
      }
    }
  }
}

//find such patterns as '1111', 'PPPPP', 'Aaaa', '____', etc.
void Password::FindRepeatingChars() {
  if (m_password.size() < 2) return;
  for (std::size_t i=0; i<=m_password.size()-m_min_pattern_len; i++) {
    std::string temp_string;
    if (tolower(m_password[i]) == tolower(m_password[i+1])) {
      temp_string.push_back(m_password[i]);
      while (
        i < m_password.size()-1
        && tolower(m_password[i]) == tolower(m_password[i+1])
      ) {
        temp_string.push_back(m_password[i+1]);
        i++;
      }
    }
    if (temp_string.size() >= m_min_pattern_len)
      m_pattern_set.insert(temp_string);
  }
}

//find such patterns as '1212', 'cdcdcd', 'HAHahaha', etc.
void Password::FindRepeatingPairs() {
  if (m_password.size() < 4) return;
  for (std::size_t i=0; i<=m_password.size()-m_min_pattern_len; i++) {
    std::string temp_string;
    if (
      tolower(m_password[i]) == tolower(m_password[i+2])
      && tolower(m_password[i+1]) == tolower(m_password[i+3])
      && tolower(m_password[i]) != tolower(m_password[i+1])
    ) {
      temp_string.push_back(m_password[i]);
      temp_string.push_back(m_password[i+1]);
      while (
        i <= m_password.size()-3
        && tolower(m_password[i]) == tolower(m_password[i+2])
        && tolower(m_password[i+1]) == tolower(m_password[i+3])
      ) {
        temp_string.push_back(m_password[i+2]);
        temp_string.push_back(m_password[i+3]);
        i += 2;
      }
        }
        if (temp_string.size() >= m_min_pattern_len) {
          m_pattern_set.insert(temp_string);
          i++;
        }
  }
}

//find such patterns as 'aBcD', '23456' or 'dcba', '65432' if backwards is 'true'
void Password::FindAbcPatterns(bool backwards) {
  if (m_password.size() < 2) return;
  int d = backwards? -1 : 1; //common difference
  for (std::size_t i=0; i<=m_password.size()-m_min_pattern_len; i++) {
    std::string temp_string;
    if (
      tolower(m_password[i]+d) == tolower(m_password[i+1])
      && isalnum(m_password[i])
    ) {
      temp_string.push_back(m_password[i]);
      while (
        tolower(m_password[i]+d) == tolower(m_password[i+1])
        && i < m_password.size()-1
      ) {
        temp_string.push_back(m_password[i+1]);
        i++;
      }
   }
   if (temp_string.size() >= m_min_pattern_len)
     m_pattern_set.insert(temp_string);
  }
}

std::string Password::get_patterns() const {
    std::string patterns;
    for(const auto& pat : m_pattern_set) {
        patterns += pat + ", ";
    }
    if (!patterns.empty()) {
        patterns.erase(patterns.size()-2, patterns.size());
    }
    return patterns;
}

int Password::get_score() const {
    return m_digit + m_lower_case + m_upper_case
     + m_num_sp_chars + m_password.size()/8 - m_pattern_set.size();
}

Password::Password(const std::string& password): m_password(password) {
    m_digit = has_digit(password);
    m_lower_case = has_l_case(password);
    m_upper_case = has_u_case(password);
    m_num_sp_chars = cnt_sp_chars(password);
    if (m_password.size() >= m_min_pattern_len) {
        FindCommonPatterns();
        FindRepeatingChars();
        FindRepeatingPairs();
        FindAbcPatterns();
        FindAbcPatterns(true);
    }
}
