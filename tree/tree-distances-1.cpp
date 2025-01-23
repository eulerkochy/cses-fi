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

  vector<int> in_dp(n + 1);
  vector<int> out_dp(n + 1);
  // in_dp[i] -> maximum height reachable from node i inside the subtree rooted at node i
  // out_dp[i] -> maximum height reachable from node i outside the subtree rooted at node i

  auto dfs_in = [&in_dp, &gr](auto &&self, int u, int p) -> void
  {
    in_dp[u] = 0;
    int max_h1 = -1;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      self(self, v, u);
      in_dp[u] = max(in_dp[u], 1 + in_dp[v]);
    }
  };

  auto dfs_out = [&gr, &out_dp, &in_dp](auto &&self, int u, int p) -> void
  {
    // the trick for calculating out_dp is you know the value of out_dp at node u
    // compute out_dp for the children and recurse

    // calculate the maximum height of the children

    int max_h1 = -2, max_h2 = -2;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      int h = in_dp[v];
      if (h >= max_h1)
      {
        max_h2 = max_h1;
        max_h1 = h;
      }
      else if (h > max_h2)
      {
        max_h2 = h;
      }
    }

    for (auto v : gr[u])
    {
      if (v == p)
        continue;

      int use = (in_dp[v] == max_h1) ? max_h2 : max_h1;

      out_dp[v] = 1 + out_dp[u];
      out_dp[v] = max(out_dp[v], 2 + use);
      self(self, v, u);
    }
  };

  dfs_in(dfs_in, 1, 0);

  out_dp[1] = 0;
  dfs_out(dfs_out, 1, 0);

  int ans = 0;

  for (int i = 1; i <= n; ++i)
  {
    int dist = max(in_dp[i], out_dp[i]);
    cout << dist << " \n"[i == n];
  }
}

signed main()
{
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  solve();
  return 0;
}