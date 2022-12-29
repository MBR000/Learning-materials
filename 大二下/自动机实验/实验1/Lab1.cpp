#include <algorithm>
#include <functional>
#include <iostream>
#include <cstdio>
#include <set>
#include <stdio.h>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

#define Large_N 16
#define Large_M 1024
#define Status unsigned long long

template <typename T> inline void read(T& x) {
    int w = 0; x = 0; char ch = getchar();
    while (!isdigit(ch)) w = (ch == '-'), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    x = w ? -x : x;
}

template <typename T, typename... Args>

inline void read(T& x, Args&... args) { read(x); read(args...); }

std::unordered_map <Status, int> H;

class Graph {
public:
    struct edge {
        int from, to, next;     // NFA int 形式的邻接表
        Status s_from, s_to;    // DFA 集合形式的邻接表
        char c;                 // 约定 * 代表 eps
        bool operator < (const edge &A) {
        return s_from < A.s_from;
    }
    }G[Large_M];
    int head[Large_N], _index;
    int S_num, F_num;                                   // DFA 生成的节点数, DFA 生成的接受态数
    Status S_val[1 << Large_N], F_val[1 << Large_N];    // 记录 DFA 节点和接受态
    Status CupF;                                        // NFA 的接受态并集
    inline void add_edge(int F, int T, char C) {
        G[++ _index] = (edge) {F, T, head[F], 1ull << (F - 1), 1ull << (T - 1), C};
        head[F] = _index;
    }
    inline void add_edge(Status F, Status T, char C) {
        G[++ _index] = (edge) {H[F], H[T], head[H[F]], F, T, C};
    }
    inline void Sprint(Status S) {
        printf("[");
        while (S != (S & (-S)))
            printf("%d ", __builtin_ffsll(S)), S -= (S & (-S));
        printf("%d]", __builtin_ffsll(S));
    }
    inline void print() {
        std::sort(G + 1, G + _index + 1);
        for (int i = 1; i <= _index; ++ i) {
            Sprint(G[i].s_from);
            printf(" --%c--> ", G[i].c);
            Sprint(G[i].s_to);
            printf("\n");
        }
        printf("Final States, DFA:\n");
        for (int i = 1; i <= F_num; ++ i) {
            Sprint(F_val[i]), printf("\n");
        }
    }
}Input, Output;

using namespace std;

int n, m;               // NFA 的状态数和边数
int Fn;                 // NFA 的接受态数
bool charlist[128];     // 字符集

vector <char> clist;

inline Status CupDelta(const Graph& NFA, Status S, char j) {
    bool opt = (j == '*');
    Status Res = opt ? S : 0; // 判断是哪一种
    while (S) {
        int x = __builtin_ffsll(S);
        for (int i = NFA.head[x]; i; i = NFA.G[i].next)
            if (NFA.G[i].c == j) // 转移
                Res |= NFA.G[i].s_to;
        S -= 1ull << (x - 1);
    }
    return Res;
}

inline Status Eps_Closure(const Graph& NFA, Status S) {
    Status Res;
    while ((Res = CupDelta(NFA, S, '*')) != S)
        S = Res;
    return Res;
}

void NFAtoDFA(const Graph& NFA, Graph& DFA) {
    queue <Status> Q; // 处理队列
    Status q0 = Eps_Closure(NFA, 1ull);
    H[q0] = ++ DFA.S_num, DFA.S_val[DFA.S_num] = q0;
    Q.push(q0);
    while (!Q.empty()) {
        Status ns = Q.front();
        Q.pop();
        for (int i = 0; i < clist.size(); ++ i) {
            Status t = Eps_Closure(NFA, CupDelta(NFA, ns, clist[i]));
            if (t == 0) continue;
            bool tag = 0;
            if (H.find(t) == H.end())
                tag = 1, H[t] = ++ DFA.S_num, DFA.S_val[DFA.S_num] = t;
            DFA.add_edge(ns, t, clist[i]);
            if (tag)
                Q.push(t);
        }
    }
    for (int i = 1; i <= DFA.S_num; ++ i)
        if (DFA.S_val[i] & NFA.CupF)
            DFA.F_val[++ DFA.F_num] = DFA.S_val[i];
}

int main() {
    // (ε-)NFA -> DFA
    printf("# Assuming 1 as Initial State.\n");
    printf("Num of States & Arcs:\n");
    read(n, m);// NFA 的状态数和边数
    printf("Data of Arcs (int, int, char):\n");
    for (int i = 1; i <= m; ++ i) {
        int x, y; char z;
        scanf("%d %d %c", &x, &y, &z);//from to邻接表，z不知道是什么
        Input.add_edge(x, y, z);
        charlist[(int) z] = 1;//字符集，用字母来编号？
    }
    for (int i = (int) 'a'; i <= (int) 'z'; ++ i)
        if (charlist[i])
            clist.push_back((char) i);
    printf("Num of Final States, NFA:\n");
    read(Fn);
    printf("Data:\n");
    for (int i = 1; i <= Fn; ++ i) {
        int x; read(x);
        Input.CupF |= (1ull << (x - 1));
    }
    NFAtoDFA(Input, Output);
    Output.print();
    system("pause");
    return 0;
}
