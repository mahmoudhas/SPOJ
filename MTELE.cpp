#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3010;
const int inf  = (1 << 29);

int n, m;
vector<int> adj[MAXN];
vector<int> cost[MAXN];
int ar[MAXN];

int dp[MAXN][MAXN];
int dfs(int u)
{
    dp[u][0] = 0;
    if (u >= n - m)
    {
        dp[u][1] = ar[u];
        return 1;
    }
    int mx = 0;
    int temp[MAXN];
    for (int i = 0; i < adj[u].size(); i++)
    {
        int x = dfs(adj[u][i]);
        mx += x;
        for (int j = 0; j <= mx; j++)
            temp[j] = -inf;
        for (int j = 0; j <= mx; j++)
        {
            for (int k = 0; k <= j; k++)
            {
                int cur = dp[adj[u][i]][k] - cost[u][i];
                temp[j] = max(temp[j], max(dp[u][j], dp[u][j - k] + cur));
            }
        }
        for (int j = 0; j <= mx; j++)
            dp[u][j] = max(dp[u][j], temp[j]);
    }
    return mx;
}

int main()
{
    for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) dp[i][j] = -inf;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n - m; i++)
    {
        int k;
        scanf("%d", &k);
        while (k--)
        {
            int v, l;
            scanf("%d%d", &v, &l);
            v--;
            adj[i].push_back(v);
            cost[i].push_back(l);
        }
    }
    for (int i = n - m; i < n; i++)
    {
        int l;
        scanf("%d", &l);
        ar[i] = l;
    }
    dfs(0);
    int ans = n;
    while (dp[0][ans] < 0)
        ans--;
    printf("%d\n", ans);
}
