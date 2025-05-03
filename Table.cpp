#include "Table.h"

void Table::add_column(const std::string& header) {
    columns.push_back(Column{header, header.size() + margin * 2});
}

void Table::add_row() {
    // Add empty cells if the given number of cells is less than the number of columns
    if (temp_vec.size() < columns.size()) {
        std::size_t diff = columns.size() - temp_vec.size();
        while (diff--) {
            temp_vec.push_back({});
        }
    }
    // Update column width to fit its widest cell
    for (std::size_t i = 0; i != temp_vec.size(); ++i) {
        if (columns[i].width < temp_vec[i].size() + margin * 2) {
            columns[i].width = temp_vec[i].size() + margin * 2;
        }
    }
    rows.push_back(temp_vec);
    temp_vec.clear();
}

void Table::print_border() const {
    std::string border {edge_style};
    for (const auto& column : columns) {
        border += std::string(column.width, hor_border_style) + edge_style;
    }
    border += '\n';
    std::cout << border;
}

void Table::print_headers() const {
    std::string headers;
    for (const auto& column : columns) {
        int left = (column.width - column.header.size()) / 2;
        int right = column.width - column.header.size() - left;
        headers += vert_border_style + std::string(left, ' ') + column.header + std::string(right, ' ');
    }
    headers += vert_border_style;
    headers += '\n';
    std::cout << headers;
}

void Table::print_rows() const {
    for (const auto& row : rows) {
        std::string row_str;
        for (std::size_t i = 0; i < columns.size(); ++i) {
            int left = (columns[i].width - row[i].size()) / 2;
            int right = columns[i].width - row[i].size() - left;
            row_str += vert_border_style + std::string(left, ' ') + row[i] + std::string(right, ' ');
        }
    row_str += vert_border_style;
    row_str += '\n';
    std::cout << row_str;
    }
}
