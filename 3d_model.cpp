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

    // Power loss for each station, line, and time
    vector<vector<vector<ll>>> g(n + 1, vector<vector<ll>>(m + 1, vector<ll>(T + 1, 0)));
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            for (ll t = 0; t <= T; t++) {
                cin >> g[i][j][t];
            }
        }
    }

    // Calculate prefix sum directly in the 'g' vector for each station, line, and time
    for (ll i = 1; i <= n; i++) {
        for (ll k = 2; k <= m; k++) { // Start from k=2 since prefix for k=1 is already the value of g[i][1][t]
            for (ll t = 0; t <= T; t++) {
                g[i][k][t] += g[i][k - 1][t];  // Add the previous line's power loss to get the prefix sum
            }
        }
    }

    // Initialize the dp array with negative infinity for impossible states
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(pos + 1, vector<ll>(T + 1, -INF)));
    dp[0][0][0] = 0; // Base case: zero lines tripped yields zero power loss

    // Fill the DP table
    for (ll i = 1; i <= n; i++) { // Iterate over each station
        for (ll j = 0; j <= pos; j++) { // Total number of lines tripped so far
            for (ll t = 0; t <= T; t++) { // Last tripping time considered
                dp[i][j][t] = dp[i - 1][j][t]; // Start with the previous state

                // Try tripping up to a[i] lines from the current station i, ensuring constraints
                for (ll k = 1; k <= min(a[i], j); k++) {  // Ensure you are not exceeding available trippable lines from this station
                    for (ll prev_t = 0; prev_t < t; prev_t++) {  // Ensure the tripping times are distinct
                        if (j >= k) {  // Ensure total tripped lines don't exceed the limit
                            dp[i][j][t] = max(dp[i][j][t], dp[i - 1][j - k][prev_t] + g[i][k][t]);
                        }
                    }
                }
            }
        }
    }

    // Find the maximum power loss after processing all stations, with exactly 'pos' lines tripped
    ll max_power_loss = -INF;
    for (ll t = 0; t <= T; t++) {
        max_power_loss = max(max_power_loss, dp[n][pos][t]);
    }

    cout << max_power_loss << endl;
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