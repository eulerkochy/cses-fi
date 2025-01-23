#include <bits/stdc++.h>

using namespace std;

// ################################## Debugging statements  ##################################
string to_string(string s) { return '"' + s + '"'; }
string to_string(char s) { return "'" + string(1, s) + "'"; }
string to_string(const char *s) { return to_string((string)s); }
string to_string(bool b) { return (b ? "true" : "false"); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

template <typename A>
string to_string(A v)
{
  bool first = true;
  string res = "{";
  for (const auto &x : v)
  {
    if (!first)
    {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}
void debug_out() { std::cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
  std::cerr << " " << to_string(H);
  debug_out(T...);
}
#define TRACE // comment this out for submission
#ifdef TRACE
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif
// ###########################################################################################

void solve()
{
  int n;
  cin >> n;
  vector<vector<int>> gr(n + 1);

  auto add_edge = [&gr](int u, int v)
  {
    gr[u].emplace_back(v);
    gr[v].emplace_back(u);
  };

  for (int i = 1; i < n; ++i)
  {
    int u, v;
    cin >> u >> v;
    add_edge(u, v);
  }

  vector<long long> sz(n + 1);
  vector<long long> in_dp(n + 1);
  vector<long long> out_dp(n + 1);
  // sz[i]     -> size of subtree rooted at node i
  // in_dp[i]  -> sum of distances from node i inside the subtree rooted at node i
  // out_dp[i] -> sum of distances from node i outside the subtree rooted at node i

  auto dfs = [&sz, &gr](auto &&self, int u, int p) -> void
  {
    sz[u] = 1;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      self(self, v, u);
      sz[u] += sz[v];
    }
  };

  auto dfs_in = [&in_dp, &gr, &sz](auto &&self, int u, int p) -> void
  {
    in_dp[u] = (sz[u] - 1);
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      self(self, v, u);
      in_dp[u] += in_dp[v];
    }
  };

  auto dfs_out = [&gr, &out_dp, &in_dp, &sz, n](auto &&self, int u, int p) -> void
  {
    // the trick for calculating out_dp is you know the value of out_dp at node u
    // compute out_dp for the children and recurse
    auto value = (n - sz[u] + 1) + out_dp[u];
    long long sum = 0;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      long long node_value = 2 * sz[v] + in_dp[v];
      sum += node_value;
    }

    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      long long node_value = 2 * sz[v] + in_dp[v];
      out_dp[v] = value + (sum - node_value);
      self(self, v, u);
    }
  };

  dfs(dfs, 1, 0);

  dfs_in(dfs_in, 1, 0);

  out_dp[1] = 0;
  dfs_out(dfs_out, 1, 0);

  for (int i = 1; i <= n; ++i)
  {
    auto value = in_dp[i] + out_dp[i];
    cout << value << " \n"[i == n];
  }
}

signed main()
{
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  solve();
  return 0;
}