#include <algorithm>
#include <ranges>
#include <vector>

// #include <range/v3/range/conversion.hpp>
#include <range/v3/view/partial_sum.hpp> 

#include <fmt/core.h>
#include <fmt/ranges.h>

// auto filter_out_html_tags(std::string_view sv) {
//     auto angle_bracket_mask = 
//         sv | std::views::transform([](auto e) { return e == '<' or e == '>'; });
//     return std::views::zip(std::views::zip_transform(std::logical_or{}, 
//             angle_bracket_mask, 
//             angle_bracket_mask | std::views::reverse), sv)
//         | std::views::filter([](auto t) { return not std::get<0>(t); })
//         | std::views::transform([](auto t) { return std::get<1>(t); });
// }

using namespace std::views;

auto filter_out_html_tags(std::string_view sv) {
    return sv 
        |> transform($, [](auto e) { return e == '<' or e == '>'; }) 
        |> zip_transform(std::logical_or{}, $, $ |> std::views::reverse($))
        |> zip($, sv)
        |> filter($, [](auto t) { return not std::get<0>(t); })
        |> transform($, [](auto t) { return std::get<1>(t); });
        // |> ranges::to<std::string>($);
}

int main() {
    fmt::print("{}\n", filter_out_html_tags("<div>Hello <b>C++North!</b></div>"));

    return 0;
}