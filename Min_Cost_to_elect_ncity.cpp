#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define vi vector<ll>
#define vvi vector<vi>
#define pll pair<ll, ll>
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define fi first
#define se second
#define nline "\n"
#define sz(a) (ll)a.size()
#define pb push_back

#define mv map<ll, vll>
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll N = 2e3 + 10;
const ll M = 1e9+7;
// stable_sort(a.begin(),a.end())  :  To sort elements and maintain their relative order
// __builtin_popcount(mask) : Counts the number of set bits (1s) in the binary representation of the mask

// DSU code 
ll par[N];
ll siz[N];

void make(ll v){
    par[v]=v;
    siz[v]=1;
}

ll find(ll v){
    if(par[v]==v){
        return v;
    }
    par[v] = find(par[v]);
    return par[v];
}

void Union(ll a,ll b){
    a=find(a);
    b=find(b);
    if(a!=b){
        if(siz[a]<siz[b]){
            swap(a,b);
        }
        par[b]=a;
        siz[a]+=siz[b];
    }
}

void solve(){
    ll n;
    cin>>n;

    // taking inputs of cities and there x,y coordinates
    vector<pair<ll,ll>> cities(n+1);
    for(ll i=1;i<=n;i++){
        cin>>cities[i].first>>cities[i].second;
    }

    // cost[i]-> dost to develop a power station in city i
    vi cost(n+1),k(n+1);
    for(ll i=1;i<=n;i++){
        cin>>cost[i];
    }

    // We are assuming that if we connect 2-cities(say-i,j) with each other using cables
    // the cost of this connection will be (k[i] + k[j]) per km, so total cost(tc) 
    // tc = (k[i] + k[j]) * (distance between city i and city j)

    for(ll i=1;i<=n;i++){
        cin>>k[i];
    }
    
    vector<pair<ll,pair<ll,ll>>> edges;
    for(ll i=1;i<=n;i++){
        edges.pb({cost[i],{0,i}});
    }

    for(ll i=1;i<=n;i++){
        for(ll j=i+1;j<=n;j++){
            ll dist = abs(cities[i].first-cities[j].first) + abs(cities[i].second-cities[j].second);
            ll cost_cur = dist*(k[i]+k[j]);
            edges.pb({cost_cur,{i,j}});
        }
    }

    sort(edges.begin(),edges.end());
    
    
    for(ll i=1;i<=n;i++){
        make(i);
    }

    vector<pair<ll,ll>> connections;
    vi power_stations;

    ll total_ct=0;
    for(auto &edge:edges){
        ll wt = edge.first;
        ll u = edge.second.first;
        ll v = edge.second.second;
        if(find(u)==find(v)){
            // city u and v are already connected
            continue;
        }
        Union(u,v);

        if(u==0 || v==0){
            power_stations.pb(max(u,v));
        }
        else{
            connections.pb({u,v});
        }
        total_ct += wt;
        //cout<<u<<" "<<v<<endl;
    }

    cout<<total_ct<<endl;

    // power_sta -> stores cities in which we created a power station
    cout<<power_stations.size()<<endl;
    for(auto &city:power_stations){
        cout<<city<<" ";
    }cout<<endl;
    
    // connections-> stores all the pairs of connections made between different cities
    cout<<connections.size()<<endl;
    for(auto &pair:connections){
        cout<<pair.first<<" "<<pair.second<<endl;
    }
        

}


signed main(){
    fast
    #ifndef ONLINE_JUDGE
        freopen("io/input.txt", "r", stdin);
        freopen("io/output.txt", "w", stdout);
        freopen("io/error.txt", "w", stderr);
    #endif

    ll T;
    //cin>>T; 
    T=1;
    while(T--){
        solve();
    }
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
    return 0;
}