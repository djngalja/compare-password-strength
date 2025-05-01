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

// Find such patterns as '1111', 'PPPPP', 'Aaaa', '____', etc.
void find_repeat_chars(const std::string& str, std::size_t min_len, std::unordered_set<std::string>& patterns) {
    if (str.size() == 1) { return; } // TODO
    char prev_ch {str.front()};
    std::string pat {prev_ch};
    for (auto it = str.begin() + 1; it != str.end(); ++it) {
        if (tolower(*it) == tolower(prev_ch)) {
            pat += *it;
        } else {
            if (pat.size() >= min_len) {
                patterns.insert(pat);
            }
            pat = *it;
        }
        prev_ch = *it;
    }
    if (pat.size() >= min_len) {
        patterns.insert(pat);
    }
}

// Find such patterns as '1212', 'cdcdcd', 'HAHahaha', etc.
void find_repeat_pairs(const std::string& str, std::size_t min_len, std::unordered_set<std::string>& patterns) {
    if (str.size() < 4) { return; } // TODO
    for (std::size_t i = 0; i <= str.size() - min_len; i++) {
        std::string pat {str[i], str[i + 1]};
        if (tolower(str[i]) != tolower(str[i + 1])) {
            while (tolower(str[i]) == tolower(str[i + 2])
            && tolower(str[i + 1]) == tolower(str[i + 3])) {
                pat += {str[i + 2], str[i + 3]};
                i += 2;
            }
            if (pat.size() >= min_len) {
                patterns.insert(pat);
            }
            i++;
        }
    }
}

// Find such patterns as 'aBcD', '23456' or 'dcba', '65432' if backwards is 'true'
void find_abc_patterns(const std::string& str, std::size_t min_len,
                       std::unordered_set<std::string>& patterns, bool backwards) {
    if (str.size() < 2) { return; } // TODO
    int diff = backwards? -1 : 1; //common difference
    char prev_ch {str.front()};
    std::string pat {prev_ch};
    for (auto it = str.begin() + 1; it != str.end(); ++it) {
        if (isalnum(prev_ch) && tolower(prev_ch + diff) == tolower(*it)) {
            pat += *it;
        } else {
            if (pat.size() >= min_len) {
                patterns.insert(pat);
            }
            pat = *it;
        }
        prev_ch = *it;
    }
    if (pat.size() >= min_len) {
        patterns.insert(pat);
    }
}

std::string Password::get_patterns() const {
    std::string patterns;
    if (m_pattern_set.empty()) {
        return patterns;
    }
    for(const auto& pat : m_pattern_set) {
        patterns += pat + ", ";
    }
    patterns.erase(patterns.size()-2, patterns.size());
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
        find_repeat_chars(password, m_min_pattern_len, m_pattern_set);
        find_repeat_pairs(password, m_min_pattern_len, m_pattern_set);
        find_abc_patterns(password, m_min_pattern_len, m_pattern_set);
        find_abc_patterns(password, m_min_pattern_len, m_pattern_set, true);
    }
}
