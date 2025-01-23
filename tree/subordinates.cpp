#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int n;
  cin >> n;
  vector<vector<int>> gr(n);

  auto add_edge = [&gr](int u, int v)
  {
    gr[u].emplace_back(v);
    gr[v].emplace_back(u);
  };

  for (int i = 1; i < n; ++i)
  {
    int p;
    cin >> p;
    --p;
    add_edge(p, i);
  }

  vector<int> sz(n, 0);

  auto dfs = [&sz, &gr](auto &&self, int u, int p) -> void
  {
    sz[u] = 0;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      self(self, v, u);
      sz[u] += (1 + sz[v]);
    }
  };

  dfs(dfs, 0, -1);

  for (int i = 0; i < n; ++i)
  {
    cout << sz[i] << " \n"[i == n - 1];
  }
}

signed main()
{
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  solve();
  return 0;
}