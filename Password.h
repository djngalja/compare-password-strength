#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <vector>
#include <unordered_set>

class Password {
    std::string m_password;
    bool m_digit {};
    bool m_lower_case {};
    bool m_upper_case {};
    int m_num_sp_chars {};
    std::size_t m_min_pattern_len {4};
    std::unordered_set<std::string> m_pattern_set {};
public:
    void FindCommonPatterns();
    void FindRepeatingPairs();
    void FindAbcPatterns(bool backwards = false);

    std::string get_pswd() const { return m_password; }
    bool get_digit() const { return m_digit; }
    bool get_l_case() const { return m_lower_case; }
    bool get_u_case() const { return m_upper_case; }
    int get_sp_chars() const { return m_num_sp_chars; }
    std::string get_patterns() const;
    int get_score() const;

    Password(const std::string& password);
};
void find_repeat_chars(const std::string&, std::size_t, std::unordered_set<std::string>&);
bool has_digit(const std::string&);
bool has_u_case(const std::string&);
bool has_l_case(const std::string&);
int cnt_sp_chars(const std::string&);

#endif // PASSWORD_H
