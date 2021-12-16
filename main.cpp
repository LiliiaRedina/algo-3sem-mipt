#include <iostream>
#include <vector>

long long pow_bin(long long x, int pow, int mod) {
    if (pow == 1) {
        return x;
    }
    if (pow == 0) {
        return 1;
    }
    if (pow % 2 == 0) {
        return pow_bin(x * x % mod, pow / 2, mod);
    } else {
        return x * pow_bin(x, pow - 1, mod) % mod;
    }
}

long long inverse_num(long long x, int mod) {
    return pow_bin(x, mod - 2, mod);
}

void fill_num_comb(std::vector<long long>& c, int n, int mod) {
    int max_val = std::min((int)c.size() - 1, n);

    c[0] = 1;
    for (int i = 1; i <= max_val; ++i) {
        c[i] = (long long)((long long)c[i - 1] * (n - i + 1) % mod) * inverse_num(i, mod) % mod;
    }
}

void fill_pows_j(std::vector<long long>& pows_j, int pow, int k, int mod) {
    for (int j = 0; j <= k; ++j) {
        pows_j[j] = pow_bin(j, pow, mod);
    }
}

long long fact_num(int k, int mod) {
    long long fact = 1;
    for (int i = 2; i <= k; ++i) {
        fact = fact * i % mod;
    }

    return fact;
}

long long count_stirl_num(int n, int k, int mod) {
    long long stirl_num = 0;

    std::vector<long long> num_comb(k + 1);
    fill_num_comb(num_comb, k, mod);

    std::vector<long long> pows_j(k + 1);
    fill_pows_j(pows_j, n, k, mod);

    for (int j = 0; j <= k; ++j) {
        if ((k + j) % 2 == 0) {
            stirl_num = (stirl_num + num_comb[j] * pows_j[j] % mod) % mod;
        } else {
            stirl_num = (stirl_num - num_comb[j] * pows_j[j] % mod + mod) % mod;
        }
    }

    long long back_fact_k = inverse_num(fact_num(k, mod), mod);
    stirl_num = stirl_num * back_fact_k % mod;

    return stirl_num;
}

int main()
{
    const int mod = 1000000007;

    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr(n);
    long long sum = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        sum = (sum + arr[i]) % mod;
    }

    std::cout << sum * ((count_stirl_num(n - 1, k - 1, mod) +
            (n - 1 + k) * count_stirl_num(n - 1, k, mod) % mod) % mod) % mod;

    return 0;
}