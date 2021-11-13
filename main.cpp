#include <iostream>
#include <string>
#include <vector>

void reg_iterat_algo(const std::string& str_input, std::vector<int>& equiv,
                     std::vector<int>& p_sort, std::vector<int>& p_sort_inverse,
                     int cur_len_sort) {
    std::vector<int> p_new_sort(str_input.size()); // пересчет сортировки
    std::vector<int> equiv_new(str_input.size()); // пересчет классов эквивалентности
    std::vector<int> p_new_sort_inverse(str_input.size()); //
    std::vector<int> cnt(26, 0); // массив для сортировки подсчетом

    cnt.assign(str_input.size(), 0);
    for (int i = 0; i < str_input.size(); ++i) {
        ++cnt[equiv[i]];
    }
    for (int i = 1; i < str_input.size(); ++i) {
        cnt[i] += cnt[i - 1];
    }

    // стабильная сортировка по предыдущим блокам
    for (int i = str_input.size() - 1; i >= 0; --i) {
        int ind_prev_block =
                (p_sort[i] - cur_len_sort + str_input.size()) % str_input.size();
        --cnt[equiv[p_sort_inverse[ind_prev_block]]];
        p_new_sort[cnt[equiv[p_sort_inverse[ind_prev_block]]]] = ind_prev_block;
        p_new_sort_inverse[ind_prev_block] =
                cnt[equiv[p_sort_inverse[ind_prev_block]]];
    }
    p_new_sort[0] = str_input.size() - 1;
    p_new_sort_inverse[str_input.size() - 1] = 0;

    // пересчет классов эквивалентности
    equiv_new[0] = 0;
    for (int i = 1, j = 0; i < str_input.size(); ++i) {
        if (equiv[p_sort_inverse[p_new_sort[i]]] ==
                equiv[p_sort_inverse[p_new_sort[i - 1]]] &&
                equiv[p_sort_inverse[p_new_sort[i] + cur_len_sort]] ==
                equiv[p_sort_inverse[p_new_sort[i - 1] + cur_len_sort]]) {
            equiv_new[i] = equiv_new[i - 1];
        } else {
            equiv_new[i] = ++j;
        }
    }

    p_sort = p_new_sort;
    p_sort_inverse = p_new_sort_inverse;
    equiv = equiv_new;
}

void first_iterat_algo(const std::string& str_input, std::vector<int>& equiv,
                        std::vector<int>& p_sort, std::vector<int>& p_sort_inverse) {
    std::vector<int> cnt(26, 0); // массив для сортировки подсчетом

    for (int i = 0; i < str_input.size() - 1; ++i) {
        ++cnt[str_input[i] - 97];
    }
    for (int i = 1; i < 26; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = str_input.size() - 2; i >= 0; --i) {
        p_sort[cnt[str_input[i] - 97]] = i;
        p_sort_inverse[i] = cnt[str_input[i] - 97];
        --cnt[str_input[i] - 97];
    }
    p_sort[0] = str_input.size() - 1;
    p_sort_inverse[str_input.size() - 1] = 0;
    equiv[0] = 0;
    for (int i = 1, j = 0; i < str_input.size(); ++i) {
        if (str_input[p_sort[i]] == str_input[p_sort[i - 1]]) {
            equiv[i] = equiv[i - 1];
        } else {
            equiv[i] = ++j;
        }
    }
}

int main() {
    std::string str_input;
    std::cin >> str_input;

    str_input += "#";

    int times = str_input.size() + 1; // 2^{число итераций алгоритма}
    int cur_len_sort = 1; // текущая длина сортируемых блоков

    std::vector<int> equiv(str_input.size()); // номера классов эквивалентности
    std::vector<int> p_sort(str_input.size()); // по месту в сортировке выдает
                                        // индекс начала суффикса в str_input
    std::vector<int> p_sort_inverse(str_input.size()); // по индексу начала
                            // суффикся в str_input выдает место в сортировке

    first_iterat_algo(str_input, equiv, p_sort, p_sort_inverse);

    std::vector<int> p_new_sort(str_input.size());
    std::vector<int> equiv_new(str_input.size());
    std::vector<int> p_new_sort_obr(str_input.size());

    while (times > 0) {
        times /= 2;

        reg_iterat_algo(str_input, equiv, p_sort, p_sort_inverse, cur_len_sort);

        cur_len_sort *= 2;
    }

    for (int i = 1; i < str_input.size(); ++i) {
        std::cout << p_sort[i] + 1 << " ";
    }

    return 0;
}