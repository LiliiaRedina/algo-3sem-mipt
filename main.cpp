#include <iostream>
#include <vector>
#include <algorithm>

void fill_mind(int n, std::vector<int>& mind) {
    std::vector<int> primes;

    for (int i = 2; i <= n; ++i) {
        mind[i] = i;
    }

    for (int k = 2; k <= n; ++k) {
        if (mind[k] == k) {
            primes.push_back(k);
        }

        for (int p: primes) {
            if (p * k > n) {
                break;
            }
            if (p > mind[k]) {
                continue;
            }

            mind[p * k] = p;
        }
    }
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> mind(n + 1);

    fill_mind(n, mind);

    long long sum = 0;

    for (int i = 2; i <= n; ++i) {
        if (i == mind[i]) {
            continue;
        }
        sum += mind[i];
    }

    std::cout << sum;

    return 0;
}