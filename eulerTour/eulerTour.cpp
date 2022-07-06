/*
Competitive Boiler Plate
    Rahul chhabra (3rd year computer science student).
*/
#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
#define FAST            ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define ll 				long long int
#define ld				long double
#define mod             1000000007
#define endl			"\n"
#define inf             2e18
#define pb 				push_back
#define eb				emplace_back
#define vi              std::vector<ll>
#define vs				std::vector<std::string>
#define vvi             std::vector<vector<ll>>
#define vc              std::vector<char>
#define pii             std::pair<ll,ll>
#define ump				std::unordered_map
#define mp 				std::make_pair
#define pq_max          std::priority_queue<ll>
#define pq_min          std::priority_queue<ll,vi,std::greater<ll> >
#define all(n) 			n.begin(),n.end()
#define ff 				first
#define ss 				second
#define mid(l,r)        (l+(r-l)/2)
#define bitc(n) 		__builtin_popcount(n)
#define loop(i,a,b) 	for(int i=(a);i<=(b);i++)
#define looprev(i,a,b) 	for(int i=(a);i>=(b);i--)
#define iter(container, it) for(__typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define log(args...) 	{ std::string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); std::stringstream _ss(_s); std::istream_iterator<std::string> _it(_ss); err(_it, args); }
#define logarr(arr,a,b)	for(int z=(a);z<=(b);z++) std::cout<<(arr[z])<<" ";std::cout<<"\n";	
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef trie<std::string,null_type,trie_string_access_traits<>,pat_trie_tag,trie_prefix_search_node_update> pbtrie;

ll inline powerM(ll a, ll b, ll p){
    a %= p;
    ll ans = 1;
    while(b>0){
        if(b & 1)
            ans = (ans*a)%p;
        a = (a*a)%p;
        b >>= 1;
    }
    return ans;
}
ll power(ll a,ll b) {
	ll ans = 1;
	while(b) {
		if(b&1) ans *=a;
		a*=a;
		b >>= 1;
	}
	return ans;
}
 
 
//MOD INVERSE (ONLY WORKS WHEN P IS PRIME)
ll mod_inv(ll n, ll p){
    return powerM(n,p-2, p);
}
const int M = 3e5 + 5;
 
//SIEVE IN O(N) TIME (FOR N UPTO 1e7 OTHERWISE YOU'LL FACE MEMORY ISSUES)
vi lp(M);
vi pr;
void sieve()
{
	lp[0] = 1; 
 
	for(int i = 2 ; i < M ; i++)
	{
		if(lp[i] == 0)
		{
			//this is a prime
			lp[i] = i;
			pr.push_back(i);
		}
		for(int j = 0 ; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] < M; j++)
			lp[i * pr[j]] = pr[j];
	}
}
int leftMostBit(ll x) {
	int pos = -1;
	int idx = 0;
	while(x) {
		if(x&1) pos = idx;
		x >>= 1;
		idx++; 
	}
	return pos;
}
int dx[] = {1,0,-1,0,1,-1,1,-1}; 
int dy[] = {0,1,0,-1,1,1,-1,-1};
vi vectorInput(int n) {
	vi nums(n);
	for(ll &x : nums) cin >> x;
	return nums;
}
void google(int tt) {
	cout << "Case #" << tt <<": ";
}
class BIT {
private:
	vector<ll> tree;
	ll n;
public:
	BIT(ll n) {
		this->n = n;
		tree.resize(n+1,0);
	}
	void Build(vi &nums,int n) {
		loop(i,1,n) {
			addIndex(i,nums[i]);
		}
	}
	void addIndex(int idx,ll value) {
		while(idx <= n) {
			tree[idx] += value;
			idx += idx & -idx;
		}
	}
	ll getSum(ll idx) {
		ll sum = 0;
		while(idx) {
			sum += tree[idx];
			idx = idx&(idx-1);
		}
		return sum;
	}
	ll query(ll l,ll r) {
		ll leftRange = getSum(l-1);
		ll rightRange = getSum(r);
		return rightRange-leftRange;
	}
	void pointUpdate(int idx,ll value,ll prev) {
		while(idx <= n) {
			tree[idx] = tree[idx]-prev+value;
			idx += idx & -idx;
		}
	}
};
const int N = 2e5+5;
int lt[N],st[N],et[N];
vi gr[N];
int t = 0;
// EULER TOUR 
void dfs(int node,int par,vi& nums) {
    st[node] = ++t;
    lt[t] = nums[node];
    for(int adj : gr[node]) {
        if(adj != par) {
            dfs(adj,node,nums);
        }
    } 
    et[node] = t;
}
void solve() {
    int n,q;
    cin >> n >> q;
    t = 0;
    vi nums(n+1,0);
    loop(i,1,n) cin >> nums[i];
    loop(i,1,n-1) {
        int u,v;
        cin >> u >> v;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    dfs(1,0,nums);
    BIT *ft = new BIT(n+1);
    loop(i,1,n) ft->addIndex(i,lt[i]);
    while(q--) {
        int type;cin >> type;
        if(type == 1) {
            int s,val;
            cin >> s >> val;
            ft->pointUpdate(st[s],(ll)val,lt[st[s]]);
            lt[st[s]] = (ll)val;
        }
        else {
            int s;cin >> s;
            cout << ft->query(st[s],et[s]) << "\n";
        }
    }
}
void file_i_o()
{
    
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
 
int main(int argc, char const *argv[]) {
	//file_i_o();
    solve();
    // Write your code here...
    return 0;
}
