#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

// 构建二维前缀和
void buildPrefixSum(const vector<vector<int>>& grid, vector<vector<int>>& sum) {
    size_t m = grid.size(), n = grid[0].size();
    sum.assign(m + 1, vector<int>(n + 1, 0));
    for(size_t i = 1; i <= m; ++i)
        for(size_t j = 1; j <= n; ++j)
            sum[i][j] = grid[i-1][j-1] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
}

// 查找所有 x 行 y 列 的全 1 子矩阵左上角坐标
vector<pair<int, int>> findSubmatrices(
    const vector<vector<int>>& grid,
    int x, int y,
    vector<vector<int>>& sum,
    bool checkOverlap = false
) {
    int m = grid.size(), n = grid[0].size();
    buildPrefixSum(grid, sum);
    // 标记已被覆盖的位置
    vector<vector<bool>> covered(m, vector<bool>(n, false));
    vector<pair<int, int>> res;
    for(int i = 0; i <= m - x; ++i) {
        for(int j = 0; j <= n - y; ++j) {
            int areaSum = sum[i+x][j+y] - sum[i][j+y] - sum[i+x][j] + sum[i][j];
            if(areaSum == x * y) 
            {
                if(!checkOverlap)
                    res.emplace_back(i, j);
                else {
                    // 检查该区域是否已被覆盖
                    bool overlap = false;
                    for(int a = 0; a < x && !overlap; ++a)
                        for(int b = 0; b < y && !overlap; ++b)
                            if(covered[i+a][j+b]) overlap = true;
                    if(overlap) continue;

                    res.emplace_back(i, j);
                    // 标记覆盖
                    for(int a = 0; a < x; ++a)
                        for(int b = 0; b < y; ++b)
                            covered[i+a][j+b] = true;
                }
            }
        }
    }
    return res;
}

// 对子矩阵左上角坐标进行聚类，能通过上下左右平移连接起来的归为一类
vector<vector<pair<int, int>>> clusterSubmatrices(const vector<pair<int, int>>& rects, int x, int y) {
    // 建立所有rect坐标的set，便于查找
    set<pair<int, int>> rectSet(rects.begin(), rects.end());
    set<pair<int, int>> visited;
    vector<vector<pair<int, int>>> clusters;

    // 相邻的平移方向 (上下左右)
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    for (const auto& p : rects) {
        if (visited.count(p)) continue;
        vector<pair<int, int>> cluster;
        queue<pair<int, int>> q;
        q.push(p);
        visited.insert(p);

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            cluster.push_back(cur);
            for (int d = 0; d < 4; ++d) {
                // 上下平移其实就是x方向±1，左右平移是y方向±1
                int nx = cur.first + dx[d];
                int ny = cur.second + dy[d];
                pair<int, int> np(nx, ny);
                // 判断是否相邻（即子矩阵左上角是否正好相邻）
                if (rectSet.count(np) && !visited.count(np)) {
                    visited.insert(np);
                    q.push(np);
                }
            }
        }
        clusters.push_back(cluster);
    }
    return clusters;
}

// 对每个聚类，计算其中有多少个不重叠的网格区域，并返回每类中的这些区域
// 输入：clusters（每类的所有左上角坐标），x, y（子矩阵大小）
// 输出：vector<vector<pair<int,int>>>，每个聚类中不重叠子矩阵的左上角坐标集合
vector<vector<pair<int, int>>> getNonOverlappingInClusters(
    const vector<vector<pair<int, int>>>& clusters,
    int x, int y
) {
    vector<vector<pair<int, int>>> result;
    for(const auto& cluster : clusters) {
        // 先将所有子矩阵左上角按行优先、列次之排序，保证贪心选择顺序
        vector<pair<int, int>> rects = cluster;
        sort(rects.begin(), rects.end());
        // 计算该聚类的边界
        int maxRow = 0, maxCol = 0;
        for(const auto& p : rects) {
            maxRow = max(maxRow, p.first + x);
            maxCol = max(maxCol, p.second + y);
        }
        // 标记覆盖
        vector<vector<bool>> covered(maxRow, vector<bool>(maxCol, false));
        vector<pair<int, int>> selected;
        for(const auto& p : rects) {
            bool overlap = false;
            for(int a = 0; a < x && !overlap; ++a)
                for(int b = 0; b < y && !overlap; ++b)
                    if(covered[p.first + a][p.second + b]) overlap = true;
            if(overlap) continue;
            selected.push_back(p);
            for(int a = 0; a < x; ++a)
                for(int b = 0; b < y; ++b)
                    covered[p.first + a][p.second + b] = true;
        }
        result.push_back(selected);
    }
    return result;
}

// 生成测试用的二值矩阵
vector<vector<int>> generateTestMatrix() {
    vector<vector<int>> grid = {
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    return grid;
}

// 打印二维数组（支持倒序显示，带坐标轴和行列标记，x轴在下方且对齐）
void printMatrixWithAxis(const vector<vector<int>>& mat, const string& title, int width=2) {
    int m = static_cast<int>(mat.size());
    int n = static_cast<int>(mat[0].size());

    cout << title << endl;

    // 打印矩阵内容和y轴
    for (int i = m - 1; i >= 0; --i) {
        // 打印y轴行号
        cout << setw(2) << i << " |";
        for (int j = 0; j < n; ++j)
            cout << " " << setw(width) << mat[static_cast<size_t>(i)][static_cast<size_t>(j)];
        cout << endl;
    }

    // 打印与数据对齐的分隔线
    cout << "   +";
    for (int j = 0; j < n; ++j)
        cout << string(static_cast<size_t>(width + 1), '-');
    cout << endl;

    // 打印x轴（列号），确保与矩阵对齐
    cout << "    ";
    for (int j = 0; j < n; ++j)
        cout << " " << setw(width) << j;
    cout << endl;
}

int main() {
    vector<vector<int>> grid = generateTestMatrix();
    int x = 3, y = 3; // 查找3行3列的全1子矩阵

    // 输出原始二值图
    printMatrixWithAxis(grid, "Original Binary Matrix (10x10):");

    // 计算前缀和并查找所有可行的子矩阵
    vector<vector<int>> sum;
    auto rects = findSubmatrices(grid, x, y, sum);

    // 输出前缀和图
    //printMatrixWithAxis(sum, "Prefix Sum Matrix (11x11):", 4);

    // 输出所有可行的左上角坐标
    cout << "All top-left coordinates of " << x << "x" << y << " submatrices full of 1s:" << endl;
    for(const auto& p : rects)
        cout << "(row=" << p.first << ", col=" << p.second << ")" << endl;
    cout << endl;

    // 查找不重叠的子矩阵
    vector<vector<int>> sum2;
    auto nonOverlapRects = findSubmatrices(grid, x, y, sum2, true);
    cout << "Non-overlapping top-left coordinates of " << x << "x" << y << " submatrices (maximal set):" << endl;
    for(const auto& p : nonOverlapRects)
        cout << "(row=" << p.first << ", col=" << p.second << ")" << endl;
    cout << endl;

    // 聚类融合
    auto clusters = clusterSubmatrices(rects, x, y);

    // 输出聚类结果
    cout << "Clusters of submatrices (by adjacency):" << endl;
    int cid = 1;
    for (const auto& cluster : clusters) {
        cout << "Cluster #" << cid++ << ": ";
        for (const auto& p : cluster) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }
    cout << endl;

    // 统计每个聚类中不重叠的网格区域
    auto clusterNonOverlap = getNonOverlappingInClusters(clusters, x, y);
    cout << "Non-overlapping submatrices in each cluster:" << endl;
    for(size_t i = 0; i < clusterNonOverlap.size(); ++i) {
        cout << "Cluster #" << (i+1) << ": ";
        for(const auto& p : clusterNonOverlap[i]) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << ", count = " << clusterNonOverlap[i].size() << endl;
    }
    cout << endl;

    return 0;
}