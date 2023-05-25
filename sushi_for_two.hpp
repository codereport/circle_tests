#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#include <combinators.hpp>
#include <ufo.hpp>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/single.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/zip_with.hpp>

// namespace view = std::views;
namespace view = ranges::views;

// auto sushi_for_two(std::vector<int> sushi) {
//     return sushi                                    //
//            |> chunk_by($, std::equal_to{})          //
//            |> transform($, std::ranges::distance)   //
//            |> adjacent_transform<2>($, ufo::min{})  //
//            |> std::ranges::max($) * 2;
// }

auto sushi_for_two(std::vector<int> sushi) {
    return sushi                                                            //
           |> view::zip_with(_neq_, $, $ | view::drop(1))                   //
           |> view::zip($, view::iota(0))                                   //
           |> view::filter($, [](auto t) { return std::get<0>(t); })        //
           |> view::values($)                                               //
           |> view::transform($, _plus(1))                                  //
           |> view::concat(view::single(0), $, view::single(sushi.size()))  //
           |> view::zip_with(_sub_, $ | view::drop(1), $)                   //
           |> view::zip_with(ufo::min{}, $, $ | view::drop(1))              //
           |> std::ranges::max($) * 2;                                      //
}
