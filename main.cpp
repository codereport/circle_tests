
#include <fmt/core.h>

#include <filter_out_html_tags.hpp>
#include <mco.hpp>
#include <sushi_for_two.hpp>

int main() {
    fmt::print("{}\n", filter_out_html_tags("<div>Hello <b>Italian C++!</b></div>"));  // working
    fmt::print("{}\n", filter_out_html_tags2("<div>Hello <b>C++ on Sea!</b></div>"));  // working
    fmt::print("{}\n", filter_out_html_tags3("<div>Hello <b>CppNorth!</b></div>"));    // working
    // fmt::print("{}\n", filter_out_html_tags4("<div>Hello <b>C++North!</b></div>"));

    fmt::print("{}\n", sushi_for_two({2, 2, 2, 1, 1, 2, 2}));        // 4
    fmt::print("{}\n", sushi_for_two({1, 2, 1, 2, 1, 2}));           // 2
    fmt::print("{}\n", sushi_for_two({2, 2, 1, 1, 1, 2, 2, 2, 2}));  // 6

    fmt::print("{}\n", mco({1, 0, 0, 0, 0, 1, 1, 1, 0, 1}));         // 3
    fmt::print("{}\n", mco2({1, 0, 0, 0, 0, 1, 1, 1, 0, 1}));        // 3

    return 0;
}