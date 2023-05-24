#include <vector>

#include <range/v3/view/drop.hpp>
#include <range/v3/view/zip_with.hpp>

auto sushi_for_two(std::vector<int> sushi) {
    return sushi                                                                   //
           |> ranges::view::zip_with(std::minus{}, $, $ | ranges::view::drop(1))   //
           |> ranges::view::zip_with(std::plus{},  $, $ | ranges::view::drop(1));  //
}
