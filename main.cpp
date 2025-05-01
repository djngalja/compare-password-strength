#include "Table.h"
#include "Password.h"


int main() {
    std::vector<pswd::Password> input = get_input();
    std::sort(input.begin(), input.end(),
              [](pswd::Password a, pswd::Password b){ return a.get_score() > b.get_score(); });
    Table tb;
    tb.add_column("Score", 5);
    tb.add_column("Password", 20);
    tb.add_column("Length", 5);
    tb.add_column("SP Chars", 5);
    tb.add_column("Digits", 5);
    tb.add_column("LCase", 5);
    tb.add_column("UCase", 5);
    tb.add_column("Patterns", 30);
    for (const auto& pas : input) {
        tb.add_row(pas.get_score(), pas.get_pswd(), pas.get_pswd().size(),
                   pas.get_sp_chars(), pas.get_digit(), pas.get_l_case(),
                   pas.get_u_case(), pas.get_patterns());
    }
    tb.print_border();
    tb.print_headers();
    tb.print_border();
    tb.print_rows();
    tb.print_border();
    return 0;
}
