#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Column {
    std::string header;
    std::size_t width;
};

class Table {
public:
    void add_column(const std::string&);

    template<typename T, typename... Types>
    void add_row(T first, Types... tail) {
        std::ostringstream oss;
        oss << first;
        temp_vec.push_back(oss.str());
        add_row(tail...);
    }

    template<typename... Types>
    void add_row(bool first, Types... tail) {
        if (first) { temp_vec.push_back("+"); }
        else { temp_vec.push_back("-"); }
        add_row(tail...);
    }

    void add_row();

    void print_border() const;
    void print_headers() const;
    void print_rows() const;
private:
    std::vector<Column> columns {};
    std::vector<std::vector<std::string>> rows {};

    const char hor_border_style {'='};
    const char vert_border_style {'|'};
    const char edge_style {'+'};
    const int margin {1}; // margin width in chars

    std::vector<std::string> temp_vec {};
};

#endif // TABLE_H
