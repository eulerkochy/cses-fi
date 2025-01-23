#include <bits/stdc++.h>

using namespace std;

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

  vector<pair<int, int>> dp(n + 1);
  // dp[i] -> {max depth reachable from node i, diameter at node i}

  auto dfs = [&dp, &gr](auto &&self, int u, int p) -> void
  {
    dp[u] = make_pair(0, 0);
    int max_h1 = -1, max_h2 = -1;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      self(self, v, u);
      auto &&[h, _] = dp[v];

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

    if (max_h2 != -1)
    {
      dp[u] = {1 + max_h1, 2 + max_h1 + max_h2};
    }
    else if (max_h1 != -1)
    {
      dp[u] = {1 + max_h1, 1 + max_h1};
    }
  };

  dfs(dfs, 1, 0);

  int ans = 0;

  for (int i = 1; i <= n; ++i)
  {
    ans = max({ans, dp[i].second});
  }
  cout << ans << "\n";
}

signed main()
{
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  solve();
  return 0;
}