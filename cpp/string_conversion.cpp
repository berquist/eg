// #include <string>
#include <iostream>

#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

int main()
{

    std::string s_true = "true";
    std::string s_false = "false";

    bool b_true = to_bool(s_true);
    bool b_false = to_bool(s_false);

    std::cout << b_true << std::endl;
    std::cout << b_false << std::endl;

    return 0;

}
