#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

namespace ufo {
// STRUCT TEMPLATE min
template <class _Ty = void>
struct min {
    constexpr _Ty operator()(const _Ty& _Left, const _Ty& _Right) const {
        return (std::min(_Left, _Right));
    }
};

// STRUCT TEMPLATE SPECIALIZATION min
template <>
struct min<void> {
    // transparent functor for operator*
    typedef int is_transparent;
    template <class _Ty1, class _Ty2>
    constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
      -> decltype(std::min(static_cast<_Ty1&&>(_Left), static_cast<_Ty2&&>(_Right))) {
        return (std::min(static_cast<_Ty1&&>(_Left), static_cast<_Ty2&&>(_Right)));
    }
};
}  // namespace ufo

using namespace std::views;

auto sushi_for_two(std::vector<int> sushi) {
    return sushi                                    //
           |> chunk_by($, std::equal_to{})          //
           |> transform($, std::ranges::distance)   //
           |> adjacent_transform<2>($, ufo::min{})  //
           |> std::ranges::max($) * 2;
}

auto main() -> int {
    std::cout << sushi_for_two({2, 2, 2, 1, 1, 2, 2}) << '\n';        // 4
    std::cout << sushi_for_two({1, 2, 1, 2, 1, 2}) << '\n';           // 2
    std::cout << sushi_for_two({2, 2, 1, 1, 1, 2, 2, 2, 2}) << '\n';  // 6

    return 0;
}