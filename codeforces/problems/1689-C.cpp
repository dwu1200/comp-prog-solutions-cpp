#define interactive 0

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define ROF(i,a,b) for (int i = (b) - 1; i >= (a); --i)
#define REP(a) FOR(_,0,a)
#define EACH(a,x) (auto& a: x)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;
typedef pair<ll, ll> pl;

ll mod = /*1e9 + 7;*/ 998244353;
int BIG32 = 1e9 + 5;

ll powmod(ll a,ll b) {ll res = 1; a %= mod; assert(b >= 0); for(; b; b >>= 1){if (b & 1) res = res * a % mod; a = a * a % mod;} return res;}

template <typename T> void output_vector(vector<T> &V, bool spaces=true) {for (auto v : V) {if (spaces) cout << v << ' '; else cout << v;} if (interactive) cout << endl; else cout << '\n';}
template <typename T> T max(vector<T> &V) {return *max_element(V.begin(), V.end());}
template <typename T> T min(vector<T> &V) {return *min_element(V.begin(), V.end());}
template <typename T> T sum(vector<T> &V) {return accumulate(V.begin(), V.end(), T(0));}
template <typename T> int bisect_left(vector<T> &V, T x) {return lower_bound(V.begin(), V.end(), x) - V.begin();} // must be sorted
template <typename T> int bisect_right(vector<T> &V, T x) {return upper_bound(V.begin(), V.end(), x) - V.begin();} // must be sorted

// preprocess //
void prepare() {

}
// preprocess //

int get_st_sizes(vector<int> &sizes, set<int> &visited, vector<vector<int>> &graph, int node) {
    visited.insert(node);
    int s = 1;
    for (int y : graph[node]) {
        if (visited.count(y)) continue;
        s += get_st_sizes(sizes, visited, graph, y);
    }
    sizes[node] = s;
    return s;
}

int dfs(vector<int> &dp, vector<int> &sizes, set<int> &visited, vector<vector<int>> &graph, int node) {
    visited.insert(node);
    for (auto it = graph[node].begin(); it != graph[node].end(); it++) {
        if (visited.count(*it)) {
            graph[node].erase(it);
            break;
        }
    }
    if (graph[node].size() == 1) {
        dp[node] = max(dp[node], sizes[graph[node][0]] - 1);
    }
    else if (graph[node].size() == 2) {
        dp[node] = max(dp[node], sizes[graph[node][0]] - 1 + dfs(dp, sizes, visited, graph, graph[node][1]));
        dp[node] = max(dp[node], sizes[graph[node][1]] - 1 + dfs(dp, sizes, visited, graph, graph[node][0]));
    }
    return dp[node];
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> G(n + 1, vector<int>());
    REP(n - 1) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> S(n + 1), DP(n + 1, 0); set<int> V;
    get_st_sizes(S, V, G, 1);
    V.clear();
    dfs(DP, S, V, G, 1);
    cout << DP[1] << '\n';
}

int main()
{
    cout.tie(nullptr); cin.tie(nullptr); ios_base::sync_with_stdio(false);
    prepare();
    if (interactive) solve();
    else {
        int t; cin >> t; REP(t) {
            solve();
        }
    }
    return 0;
}