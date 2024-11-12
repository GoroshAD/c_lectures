#include <array>
#include <utility>
#include <iostream>

template<std::size_t N>
constexpr std::array<std::array<int, N - 1>, N - 1>
submatrix(const std::array<std::array<int, N>, N>& a, int i, int j) {
    std::array<std::array<int, N - 1>, N - 1> r{};
    for (int ii = 0; ii != N - 1; ++ii)
        for (int jj = 0; jj != N - 1; ++jj)
            (&std::get<0>(((&std::get<0>(r))[ii])))[jj] = a[ii + (ii >= i ? 1 : 0)][jj + (jj >= j ? 1 : 0)];
    return r;
}

constexpr int get_cofactor_coef(int i, int j) {
    return (i + j) % 2 == 0 ? 1 : -1;
}

template <int N>
constexpr int Det(const std::array<std::array<int, N>, N>& matrix) {
    int det = 0;
    for (size_t i = 0u; i < N; ++i) {
        det += get_cofactor_coef(i, 0) * matrix[i][0] * Det<N-1>(submatrix<N>(matrix, i, 0));
    }
    return det;
}

template <>
constexpr int Det<2>(const std::array<std::array<int, 2>, 2>& a) {
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

template <>
constexpr int Det<1>(const std::array<std::array<int, 1>, 1>& a) {
    return a[0][0];
}

int main() {
    constexpr std::array<std::array<int, 3>, 3> matrix = {{
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 7}
    }};
    constexpr int result = Det<3>(matrix);
    std::cout << result << std::endl;
    return 0;
}