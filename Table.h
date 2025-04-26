#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct Column {
    std::string header;
    std::size_t width;
};

class Table {
    std::vector<Column> columns {};
    int table_width {};
    std::string border {};
    std::vector<std::vector<std::string>> rows {};
    const char hor_border_style {'-'};
    const char vert_border_style {'|'};
    const char edge_style {'+'};
    std::vector<std::string> temp_vec {};
public:
    void add_column(const std::string&, std::size_t);
    template<typename T, typename... Types>
    void add_row(T first, Types... tail) {
        std::ostringstream oss;
        oss << first;
        temp_vec.push_back(oss.str());
        add_row(tail...);
    }
    void add_row();
    void print_border() const;
    void print_headers() const;
    void print_rows();
};

#endif // TABLE_H
