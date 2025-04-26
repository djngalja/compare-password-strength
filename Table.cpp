#include "Table.h"

void Table::add_column(const std::string& header, std::size_t width) {
    std::size_t final_width = (header.size() > width) ? header.size() : width;
    columns.push_back(Column{header, final_width});
    if (table_width) { table_width++; };
    table_width += final_width;
    border = edge_style + std::string(table_width, hor_border_style) + edge_style + '\n';
}

void Table::add_row() {
    // If the number of cells is less than the number of columns
    if (temp_vec.size() < columns.size()) {
        std::size_t diff = columns.size() - temp_vec.size();
        while (diff--) {
            temp_vec.push_back("");
        }
    }
    rows.push_back(temp_vec);
    temp_vec.clear();
}

void Table::print_border() const {
    std::cout << border;
}

void Table::print_headers() const {
    std::string headers;
    for (const auto& column : columns) {
        headers += vert_border_style + std::string(column.width-column.header.size(), ' ') + column.header;
    }
    headers += vert_border_style;
    headers += '\n';
    std::cout << headers;
}

void Table::print_rows() {
    for (auto& row : rows) {
        std::string row_str;
        for (std::size_t i=0; i<columns.size(); ++i) {
            // If the width of a cell is greater than the width of its column
            if (row[i].size() > columns[i].width) {
                row[i].resize(columns[i].width);
            }
            row_str += vert_border_style + std::string(columns[i].width-row[i].size(), ' ') + row[i];
        }
    row_str += vert_border_style;
    row_str += '\n';
    std::cout << row_str;
    }
}
