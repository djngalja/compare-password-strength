#include "Password.h"
#include <cassert>

#undef NDEBUG

void pswd_test() {

    // Test pswd::find_common_patterns helper function
    std::set<std::string> res;
    pswd::find_common_patterns("C@ts-and-Dogs-Living-together", res);  // no common patterns
    assert(res.size() == 0);

    pswd::find_common_patterns("", res);  // empty source string
    assert(res.size() == 0);

    pswd::find_common_patterns("DiamonDragon", res); // patterns overlap
    assert(res.size() == 2);
    res.clear();


    // Test pswd::find_repeat_chars helper function
    pswd::find_repeat_chars("", 4, res); // empty source string
    assert(res.size() == 0);

    pswd::find_repeat_chars("jelly22fi$h", 4, res);  // no common patterns
    assert(res.size() == 0);

    pswd::find_repeat_chars("jelly22fi$h", 2, res);  // changed minimum pattern length
    assert(res.size() == 2);
    res.clear();

    pswd::find_repeat_chars("jelly22fi$h", 1, res); // set minimum pattern length to unreasonable value
    assert(res.size() == 0);

    res.clear();
    pswd::find_repeat_chars("1111tTtTt", 4, res); // test case-insensitivity, pattern begins at pos 0
    assert(res.size() == 2);
    res.clear();

    pswd::find_repeat_chars("_1111tTtTt_", 4, res); // pattern begins at pos 1
    assert(res.size() == 2);
    res.clear();


    // Test pswd::find_repeat_pairs helper function
    pswd::find_repeat_pairs("", 4, res); // empty source string
    assert(res.size() == 0);

    pswd::find_repeat_pairs("!Lov3MyPiano", 4, res); // no common patterns
    assert(res.size() == 0);

    pswd::find_repeat_pairs("LalataT", 4, res); // patterns overlap, pattern begins at pos 0
    assert(res.size() == 2);
    res.clear();

    pswd::find_repeat_pairs("9LalataT", 4, res); // pattern begins at pos 1
    assert(res.size() == 2);
    res.clear();

    pswd::find_repeat_pairs("!Lov3MyPiano", 2, res); // set minimum pattern length to unreasonable value
    assert(res.size() == 0);


    // Test pswd::find_abc_patterns helper function
    pswd::find_abc_patterns("", 4, res); // empty source string
    assert(res.size() == 0);

    pswd::find_abc_patterns("BankLogin!3", 4, res); // no common patterns
    assert(res.size() == 0);

    pswd::find_abc_patterns("AbCd453", 4, res); // pattern begins at pos 0
    assert(res.size() == 1);
    res.clear();

    pswd::find_abc_patterns("8AbCd453", 4, res); // pattern begins at pos 1
    assert(res.size() == 1);
    res.clear();

    pswd::find_abc_patterns("453dCBa", 4, res, true); // pattern at the end of string
    assert(res.size() == 1);
    res.clear();
}
