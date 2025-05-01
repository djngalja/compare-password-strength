#include "Password.h"

std::string pswd::Password::get_patterns() const {
    std::string patterns;
    if (m_patterns.empty()) {
        return patterns;
    }
    for(const auto& pat : m_patterns) {
        patterns += pat + ", ";
    }
    patterns.erase(patterns.size()-2, patterns.size());
    return patterns;
}

int pswd::Password::get_score() const {
    return m_digit + m_lower_case + m_upper_case
     + m_num_sp_chars + m_password.size()/8 - m_patterns.size();
}

pswd::Password::Password(const std::string& password): m_password(password) {
    m_digit = has_digit(password);
    m_lower_case = has_l_case(password);
    m_upper_case = has_u_case(password);
    m_num_sp_chars = cnt_sp_chars(password);
    if (m_password.size() >= m_min_pattern_len) {
        find_common_patterns(password, m_patterns);
        find_repeat_chars(password, m_min_pattern_len, m_patterns);
        find_repeat_pairs(password, m_min_pattern_len, m_patterns);
        find_abc_patterns(password, m_min_pattern_len, m_patterns);
        find_abc_patterns(password, m_min_pattern_len, m_patterns, true);
    }
}

// Find such patterns as 'qwErtY', 'passWord', etc.
void pswd::find_common_patterns(const std::string& str, std::set<std::string>& patterns) {
    std::string f_name {"common_pass.txt"};
    std::ifstream file(f_name);
    static bool flag = true;
    if (!file) {
        if (flag) { // Show this message only once
            std::cout << "\nWarning! File <" << f_name << "> not found\n\n";
            flag = false;
        }
        return;
    }
    std::vector<std::string> com_patterns;
    for (std::string temp_str; file >> temp_str;) {
        com_patterns.push_back(temp_str);
    }
    for (const auto& pat : com_patterns) {
        auto it = std::search(str.begin(), str.end(), pat.begin(), pat.end(),
                              [](char ch1, char ch2){ return tolower(ch1) == tolower(ch2); });
        if (it != str.end()) {
            auto pos = it - str.begin();
            patterns.insert(str.substr(pos, pat.size()));
        }
    }
}

// Find such patterns as '1111', 'PPPPP', 'Aaaa', '____', etc.
void pswd::find_repeat_chars(const std::string& str, std::size_t min_len, std::set<std::string>& patterns) {
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
void pswd::find_repeat_pairs(const std::string& str, std::size_t min_len, std::set<std::string>& patterns) {
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
void pswd::find_abc_patterns(const std::string& str, std::size_t min_len,
                       std::set<std::string>& patterns, bool backwards) {
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

bool pswd::has_digit(const std::string& str) {
    for (char c : str) {
        if (isdigit(c)) { return true; }
    }
    return false;
}

bool pswd::has_u_case(const std::string& str) {
    for (char c : str) {
        if (isupper(c)) { return true; }
  }
    return false;
}

bool pswd::has_l_case(const std::string& str) {
    for (char c : str) {
        if (islower(c)) { return true; }
  }
    return false;
}

int pswd::cnt_sp_chars(const std::string& str) {
    int cnt {};
    for (char c : str) {
        if (!isalnum(c)) { cnt++; }
    }
    return cnt;
}

std::vector<pswd::Password> get_input() {
    std::vector<pswd::Password> input;
    std::cout << "Enter passwords separated by white spaces:\n";
    std::string str;
    std::getline(std::cin, str);
    std::istringstream iss(str);
    for (std::string str2; getline(iss, str2, ' ');) {
        if (!str2.empty()) {
            input.push_back(pswd::Password(str2));
        }
    }
    return input;
}
