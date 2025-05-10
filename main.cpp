#include "Table.h"
#include "Password.h"


int main() {
    //pswd_test();
    std::vector<pswd::Password> input = get_input();

    std::sort(input.begin(), input.end(),
              [](pswd::Password a, pswd::Password b)
              { return a.get_score() > b.get_score(); });

    Table tb;

    tb.add_column("Score");
    tb.add_column("Password");
    tb.add_column("Length");
    tb.add_column("SP Chars");
    tb.add_column("Digits");
    tb.add_column("LCase");
    tb.add_column("UCase");
    tb.add_column("Patterns");

    for (const auto& pas : input) {
        tb.add_row(pas.get_score(), pas.get_pswd(), pas.get_pswd().size(),
                   pas.get_sp_chars(), pas.get_digit(), pas.get_l_case(),
                   pas.get_u_case(), pas.get_patterns());
    }

    std::cout << '\n';
    tb.print_border();
    tb.print_headers();
    tb.print_border();
    tb.print_rows();
    tb.print_border();

    return 0;
}
