#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

namespace pswd {

    class Password {
        std::string m_password;
        bool m_digit {};
        bool m_lower_case {};
        bool m_upper_case {};
        int m_num_sp_chars {};
        std::size_t m_min_pattern_len {4};
        std::set<std::string> m_patterns {};
    public:
        std::string get_pswd() const { return m_password; }
        bool get_digit() const { return m_digit; }
        bool get_l_case() const { return m_lower_case; }
        bool get_u_case() const { return m_upper_case; }
        int get_sp_chars() const { return m_num_sp_chars; }
        std::string get_patterns() const;
        int get_score() const;
        Password(const std::string& password);
    };

    void find_common_patterns(const std::string&, std::set<std::string>&);
    void find_repeat_chars(const std::string&, std::size_t, std::set<std::string>&);
    void find_repeat_pairs(const std::string&, std::size_t, std::set<std::string>&);
    void find_abc_patterns(const std::string&, std::size_t,
                       std::set<std::string>&, bool = false);
    bool has_digit(const std::string&);
    bool has_u_case(const std::string&);
    bool has_l_case(const std::string&);
    int cnt_sp_chars(const std::string&);
}

std::vector<pswd::Password> get_input();
void pswd_test();

#endif // PASSWORD_H
