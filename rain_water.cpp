#include <algorithm>
#include <ranges>
#include <vector>
// #include <https://raw.githubusercontent.com/codereport/useful_function_objects/master/ufo.hpp>

#include <range/v3/view/partial_sum.hpp>
#include <range/v3/view/reverse.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>

using namespace std::views;
namespace rv = ranges::views;

auto scan_left(auto rng, auto init, auto op) {
    // op should be regular_invocable https://eel.is/c++draft/concept.regularinvocable#concept:regular_invocable
    // which means not mutable therefore vvv is broken
    return transform(rng, [first = true, acc = init, op](auto e) mutable {
            if (first) first = false; 
            else acc = op(acc, e);
            return acc;
        });
}

auto rpartial_sum(auto rng, auto op) {
    return rv::partial_sum(rng.rbegin(), rng.rend(), op);
}

auto max = [](auto a, auto b) { return std::max(a, b); };

auto rain_water(std::vector<int> heights) {
    return heights
        |> rpartial_sum($, max);
}

auto main() -> int {

  fmt::print("{}\n", rain_water({ 2, 1, 2, 4, 2, 3, 5, 2, 4, 7, 1, 2 }));       // 8

  return 0;
}