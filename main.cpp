#include <iostream>
#include <vector>
#include <string>
#include <queue>

enum Colours{
    WHITE,
    GREY,
    BLACK
};

struct node{
    std::vector<int> to;
    bool is_term = false;
    int link = -1;

    node() {
        to.resize(2, -1);
    }
};

void add_in_trie(std::vector<node>& trie, const std::string& str) {
    int v = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (trie[v].to[str[i] - 48] == -1) {
            trie.push_back(node());
            trie[v].to[str[i] - 48] = int(trie.size()) - 1;
        }
        v = trie[v].to[str[i] - 48];
    }
    trie[v].is_term = true;
}

void aho_corasick(std::vector<node>& trie) {
    trie[0].link = 0;

    for (int ch = 0; ch < 2; ++ch) {
        if (trie[0].to[ch] != -1) {
            continue;
        }

        trie[0].to[ch] = 0;
    }

    std::queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int ch = 0; ch < 2; ++ch) {
            int son_v_ch = trie[v].to[ch];
            if (trie[son_v_ch].link != -1) {
                continue;
            }
            trie[son_v_ch].link = (v == 0 ? 0 : trie[trie[v].link].to[ch]);

            for (int ch_for_son = 0; ch_for_son < 2; ++ch_for_son) {
                if (trie[son_v_ch].to[ch_for_son] != -1) {
                    continue;
                }
                trie[son_v_ch].to[ch_for_son] = trie[trie[son_v_ch].link].to[ch_for_son];
            }

            q.push(son_v_ch);
        }
    }
}

bool is_path_by_links_without_term(const std::vector<node>& trie, int vert) {
    while (vert > 0) {
        if (trie[vert].is_term) {
            return false;
        }

        vert = trie[vert].link;
    }

    return true;
}

void dfs_find_cycle(const std::vector<node>& trie, std::vector<Colours>& colour,
                    bool& was_cycle, int vert) {
    if (was_cycle) {
        return;
    }

    if (!is_path_by_links_without_term(trie, vert)) {
        return;
    }

    colour[vert] = GREY;

    for (int i = 0; i < 2; ++i) {
        if (trie[trie[vert].to[i]].is_term) {
            continue;
        }
        if (colour[trie[vert].to[i]] == GREY) {
            was_cycle = true;
            return;
        }
        if (colour[trie[vert].to[i]] == WHITE) {
            dfs_find_cycle(trie, colour, was_cycle, trie[vert].to[i]);
        }
    }

    colour[vert] = BLACK;
}

int main() {
    int n;
    std::cin >> n;

    std::string str;

    std::vector<node> trie;
    trie.push_back(node());

    std::vector<int> sizes(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> str;
        sizes[i] = str.size();
        add_in_trie(trie, str);
    }

    aho_corasick(trie);

    std::vector<Colours> colour(trie.size(), WHITE);
    bool was_cycle = false;

    dfs_find_cycle(trie, colour, was_cycle, 0);

    if (was_cycle) {
        std::cout << "TAK";
    } else {
        std::cout << "NIE";
    }

    return 0;
}