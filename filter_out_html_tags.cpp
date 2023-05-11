#include <algorithm>
#include <ranges>
#include <vector>

#include <range/v3/range/conversion.hpp>
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
namespace rv = ranges::views;

auto scan_left(auto rng, auto init, auto op) {
    return transform(rng, [first = true, acc = init, op](auto e) mutable {
            if (first) first = false; 
            else acc = op(acc, e);
            return acc;
        });
}

auto filter_out_html_tags(std::string_view sv) {
    return sv 
        |> transform($, [](auto e) { return e == '<' or e == '>'; })
        |> zip_transform(std::logical_or{}, $, scan_left($, true, std::not_equal_to{}))
        |> zip($, sv)
        |> filter($, [](auto t) { return not std::get<0>(t); })
        |> values($);
}

auto filter_out_html_tags2(std::string_view sv) {
    return sv 
        |> transform($, [](auto e) { return e == '<' or e == '>'; }) 
        |> zip_transform(std::logical_or{}, $, scan_left($, true, std::not_equal_to{}))
        |> zip($, sv)
        |> filter($, [](auto t) { return not std::get<0>(t); })
        |> values($)
        | ranges::to<std::string>;
}

auto filter_out_html_tags3(std::string_view sv) {
    return sv 
        |> transform($, [](auto e) { return e == '<' or e == '>'; }) 
        |> zip_transform(std::logical_or{}, $, scan_left($, true, std::not_equal_to{}))
        |> zip($, sv)
        |> filter($, [](auto t) { return not std::get<0>(t); })
        |> values($)
        |> ranges::to<std::string>($);
}

auto filter_out_html_tags4(std::string_view sv) {
    return sv 
        |> transform($, [](auto e) { return e == '<' or e == '>'; }) 
        |> zip_transform(std::logical_or{}, $, $ |> scan_left($, true, std::not_equal_to{}))
        |> zip($, sv)
        |> filter($, [](auto t) { return not std::get<0>(t); })
        |> values($);
}

auto filter_out_html_tags5(std::string_view sv) {
    return sv 
        |> transform($, [](auto e) { return e == '<' or e == '>'; }) 
        |> zip_transform(std::logical_or{}, $, rv::partial_sum($, std::not_equal_to{}))
        |> zip($, sv)
        |> filter($, [](auto t) { return not std::get<0>(t); })
        |> values();
}

int main() {
    fmt::print("{}\n", filter_out_html_tags ("<div>Hello <b>C++North!</b></div>")); // working
    fmt::print("{}\n", filter_out_html_tags2("<div>Hello <b>C++North!</b></div>")); // working
    fmt::print("{}\n", filter_out_html_tags3("<div>Hello <b>C++North!</b></div>")); // working
    fmt::print("{}\n", filter_out_html_tags4("<div>Hello <b>C++North!</b></div>")); // working
    fmt::print("{}\n", filter_out_html_tags5("<div>Hello <b>C++North!</b></div>"));

    return 0;
}
