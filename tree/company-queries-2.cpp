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
  int n, q;
  cin >> n >> q;
  vector<vector<int>> gr(n + 1);

  auto add_edge = [&gr](int u, int v)
  {
    gr[u].emplace_back(v);
    gr[v].emplace_back(u);
  };

  for (int i = 2; i <= n; ++i)
  {
    int boss;
    cin >> boss;
    add_edge(i, boss);
  }

  int LG = __lg(n);
  vector<vector<int>> parent(LG + 1, vector<int>(n + 1, -1));
  vector<int> depth(n + 1, 0);
  // parent[k][i] -> node which is at a height 2^k above node i
  // thus parent[0][i] is just the parent

  // depth[i] -> depth of node i from the root of the tree

  auto dfs = [&parent, &gr, &depth](auto &&self, int u, int p) -> void
  {
    parent[0][u] = p;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      depth[v] = 1 + depth[u];
      self(self, v, u);
    }
  };

  dfs(dfs, 1, -1);

  auto get_lca = [&parent, &depth, LG](int u, int v)
  {
    if (depth[u] < depth[v])
    {
      swap(u, v);
    }
    // u is deeper than v

    // try to bring u to the same level as v
    int diff = depth[u] - depth[v];
    for (int k = LG; k >= 0; --k)
    {
      if ((diff >> k) & 1)
      {
        u = parent[k][u];
      }
    }
    if (u == v)
    {
      return u;
    }

    for (int k = LG; k >= 0; --k)
    {
      if (parent[k][u] != parent[k][v])
      {
        u = parent[k][u], v = parent[k][v];
      }
    }

    return parent[0][u];
  };

  // now lets compute the remaining parent
  for (int k = 1; k <= LG; ++k)
  {
    for (int i = 1; i <= n; ++i)
    {
      int p = parent[k - 1][i];
      // 2^k = 2^k-1 + 2^k-1
      if (p == -1)
      {
        parent[k][i] = p;
      }
      else
      {
        parent[k][i] = parent[k - 1][p];
      }
    }
  }

  while (q--)
  {
    int u, v;
    cin >> u >> v;
    int ans = get_lca(u, v);
    cout << ans << '\n';
  }
}

signed main()
{
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  solve();
  return 0;
}