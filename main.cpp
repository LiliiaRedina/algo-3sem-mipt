#include <iostream>
#include <vector>
#include <complex>

using complex = std::complex<double>;

std::vector<complex> fft(const std::vector<complex>& polynom, bool reverse = false) {
    if (polynom.size() == 1) {
        return {(complex)polynom[0]};
    }

    double angle = (reverse ? -1 : 1) * acos(-1) * 2 / polynom.size();

    complex w(cos(angle), sin(angle)), counter = 1;
    std::vector<complex> even;
    std::vector<complex> odd;
    std::vector<complex> result(polynom.size());

    for (size_t i = 0; i < polynom.size(); ++i) {
        if (i % 2 == 0) {
            even.push_back(polynom[i]);
        } else {
            odd.push_back(polynom[i]);
        }
    }

    even = fft(even, reverse);
    odd = fft(odd, reverse);

    for (size_t i = 0; i < even.size(); i++) {
        result[i] = even[i] + odd[i] * counter;
        counter *= w;
    }
    for (size_t i = 0; i < odd.size(); i++) {
        result[i + even.size()] = even[i] + odd[i] * counter;
        counter *= w;
    }

    return result;
}

int main() {
    int pol1_degree, pol2_degree;
    std::cin >> pol1_degree;

    std::vector<complex> pol1(pol1_degree + 1);

    for (int i = 0; i < pol1_degree + 1; ++i) {
        std::cin >> pol1[pol1_degree - i];
    }

    std::cin >> pol2_degree;

    std::vector<complex> pol2(pol2_degree + 1);

    for(int i = 0; i < pol2_degree + 1; ++i) {
        std::cin >> pol2[pol2_degree - i];
    }

    int res_pol_degree = pol1_degree + pol2_degree;

    int degree = 1;
    while (degree <= std::max(pol1.size() + 1, pol2.size() + 1)) degree *= 2;
    degree *= 2;

    std::vector<complex> fft_pol1(degree, 0);
    for (int i = 0; i < pol1_degree + 1; ++i) {
        fft_pol1[i] = pol1[i];
    }
    std::vector<complex> fft_pol2(degree, 0);
    for (int i = 0; i < pol2_degree + 1; ++i) {
        fft_pol2[i] = pol2[i];
    }

    fft_pol1 = fft(fft_pol1, false);
    fft_pol2 = fft(fft_pol2, false);

    std::vector<complex> fft_res_pol(degree, 0);

    for (int i = 0; i < degree; i++) {
        fft_res_pol[i] = fft_pol1[i] * fft_pol2[i];
    }
    fft_res_pol = fft(fft_res_pol, true);

    std::vector<complex> res_pol(res_pol_degree + 1);

    std::cout << res_pol_degree << " ";
    for (size_t i = 0; i < res_pol_degree + 1; i++) {
        std::cout << (long long)floor(fft_res_pol[res_pol_degree - i].real() / ((double)degree) + 0.5) << " ";
    }

    return 0;
}