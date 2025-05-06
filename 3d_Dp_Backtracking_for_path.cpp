#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define vi vector<ll>
#define pll pair<ll, ll>
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define sz(a) (ll)a.size()
#define pb push_back
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll N = 4e5 + 10;
const ll M = 1e9 + 7;
const ll INF = 1e18;
const ll MOD = 1e9 + 7;

void solve() {
    ll n, m, pos;
    cin >> n >> m >> pos;
    const ll T = pos; // Maximum number of time steps

    // Input array 'a' where a[i] denotes max lines that can be tripped from station i
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // Input for forbidden lines
    ll forbidden_count;
    cin >> forbidden_count;
    set<pair<int, int>> forbidden;
    for (ll i = 0; i < forbidden_count; i++) {
        int station, line;
        cin >> station >> line;
        forbidden.insert({station, line});
    }

    // Power loss for each station, line, and time with prefix sum
    vector<vector<vector<ll>>> g(n + 1, vector<vector<ll>>(m + 1, vector<ll>(T + 1, 0)));
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            for (ll t = 0; t <= T; t++) {
                ll x;
                cin >> x;
                g[i][j][t] = g[i][j - 1][t] + x;  // In-place prefix sum
            }
        }
    }

    // DP and path table initialization
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(pos + 1, vector<ll>(T + 1, -INF)));
    vector<vector<vector<tuple<int, int, int, int>>>> path(n + 1,
        vector<vector<tuple<int, int, int, int>>>(pos + 1,
            vector<tuple<int, int, int, int>>(T + 1, {-1, -1, -1, -1})));

    dp[0][0][0] = 0;  // Base case

    // Fill the DP table
    for (ll i = 1; i <= n; i++) {
        for (ll j = 0; j <= pos; j++) {
            for (ll t = 0; t <= T; t++) {
                dp[i][j][t] = dp[i - 1][j][t];  // No line tripped from this station
                path[i][j][t] = {i - 1, j, t, 0};

                for (ll k = 1; k <= min(j, a[i]); k++) {
                    // Check if any of the first k lines is forbidden (due to prefix use)
                    bool is_forbidden = false;
                    for (ll line = 1; line <= k; line++) {
                        if (forbidden.count({i, line})) {
                            is_forbidden = true;
                            break;
                        }
                    }
                    if (is_forbidden) continue;

                    for (ll prev_t = 0; prev_t < t; prev_t++) {
                        if (j >= k) {
                            ll new_loss = dp[i - 1][j - k][prev_t] + g[i][k][t];
                            if (new_loss > dp[i][j][t]) {
                                dp[i][j][t] = new_loss;
                                path[i][j][t] = {i - 1, j - k, prev_t, k};
                            }
                        }
                    }
                }
            }
        }
    }

    // Get the best answer
    ll max_power_loss = -INF, final_t = -1;
    for (ll t = 0; t <= T; t++) {
        if (dp[n][pos][t] > max_power_loss) {
            max_power_loss = dp[n][pos][t];
            final_t = t;
        }
    }

    cout << "Maximum Power Loss: " << max_power_loss << endl;

    // Backtrack to print trip sequence
    vector<tuple<int, int, int>> tripped_lines;
    int curr_n = n, curr_j = pos, curr_t = final_t;
    // While backtracking:
    while (curr_n > 0 && curr_j > 0 && curr_t >= 0) {
        tuple<int, int, int, int> info = path[curr_n][curr_j][curr_t];
        int prev_n = get<0>(info);
        int prev_j = get<1>(info);
        int prev_t = get<2>(info);
        int cut_k  = get<3>(info);

        if (cut_k > 0) {
            tripped_lines.emplace_back(curr_n, cut_k, curr_t);
            curr_j = prev_j;
        }
        curr_n = prev_n;
        curr_t = prev_t;
    }

    // When printing tripped lines:
    for (auto &tup : tripped_lines) {
        int station = get<0>(tup);
        int k = get<1>(tup);
        int time = get<2>(tup);
        cout << "Station: " << station << ", Lines Cut: " << k << ", Time: " << time << '\n';
    }
}



signed main(){
    fast
 
    #ifndef ONLINE_JUDGE
        freopen("io/input.txt", "r", stdin);
        freopen("io/output.txt", "w", stdout);
        freopen("io/error.txt", "w", stderr);
    #endif
 
    ll T = 1;
    cin>>T;
    bool findit = false;
    for(int i=0;i<T;i++)
        solve();
 
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
    return 0;
}