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

  vector<vector<int>> dp(n + 1, vector<int>(2, 0));
  // dp[i][0] -> # matchings without taking node i
  // dp[i][1] -> # matching taking node i

  auto dfs = [&dp, &gr](auto &&self, int u, int p) -> void
  {
    dp[u][0] = 0;
    dp[u][1] = 0;
    int sum_ch = 0, mx = INT_MIN;
    int num_children = 0;
    for (auto v : gr[u])
    {
      if (v == p)
        continue;
      self(self, v, u);
      dp[u][0] += max(dp[v][0], dp[v][1]);
      sum_ch += dp[v][1];
      mx = max(mx, dp[v][0] - dp[v][1]);
      ++num_children;
    }
    if (num_children > 0)
    {
      dp[u][1] = 1;
      dp[u][1] = max(dp[u][1], 1 + sum_ch + mx);
    }
  };

  dfs(dfs, 1, 0);

  int ans = 0;

  for (int i = 1; i <= n; ++i)
  {
    ans = max({ans, dp[i][0], dp[i][1]});
  }
  cout << ans << "\n";
}

signed main()
{
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  solve();
  return 0;
}