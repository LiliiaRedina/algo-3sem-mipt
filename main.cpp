#include <iostream>
#include <vector>
#include <string>

void count_and_out_z_funk(const std::string& str, std::vector<int>& z_func) {
    z_func[0] = 0;

    int left_bord = -1, right_bord = -1;

    std::cout << z_func[0] << " ";

    for (int i = 1; i < str.size(); ++i) {
        if (left_bord <= i && i <= right_bord) {
            z_func[i] = std::min(z_func[i - left_bord], right_bord- i + 1);
        }

        while (i + z_func[i] < str.size() && str[z_func[i]] == str[i + z_func[i]]) {
            ++z_func[i];
        }

        if (i + z_func[i] - 1 > right_bord) {
            left_bord = i;
            right_bord = i + z_func[i] - 1;
        }

        std::cout << z_func[i] << " ";
    }
}

int main() {
    std::string str;
    std::cin >> str;

    std::vector<int> z_func(str.size());

    count_and_out_z_funk(str, z_func);

    return 0;
}