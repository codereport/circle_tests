#include <algorithm>
#include <ranges>
#include <vector>

#include <range/v3/algorithm/fold_left.hpp>

#include <fmt/core.h>

using namespace std::views;

auto mco(std::vector<int> lst) {
    return lst
        |> chunk_by($, std::equal_to{})
        |> filter($, [](auto r) { return *r.begin() == 1; })
        |> transform($, std::ranges::distance)
        |> std::ranges::max($);
}

auto mco2(std::vector<int> lst) {
    auto sum = [](auto r) { return ranges::fold_left(r, 0, std::plus{}); };
    return lst
        |> chunk_by($, std::equal_to{})
        |> transform($, sum)
        |> std::ranges::max($);
}

auto main() -> int {

    fmt::print("{}\n", mco({1, 0, 0, 0, 0, 1, 1, 1, 0, 1})); // 3
    fmt::print("{}\n", mco2({1, 0, 0, 0, 0, 1, 1, 1, 0, 1})); // 3

  return 0;
}