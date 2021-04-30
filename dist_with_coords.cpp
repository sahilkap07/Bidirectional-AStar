#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <unordered_map>
// #include <fstream>  
#include <string>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<vector<int>>> Adj;
typedef long long Len;
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INFINITY_ = numeric_limits<Len>::max() / 4;

class AStar {
    // See the descriptions of these fields in the starter for friend_suggestion
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    // vector<vector<Len>> distance_heur;
    vector<int> workset_;
    vector<pair<bool, bool>> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;
    unordered_map<int, double> umap;

public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len,Len>> xy)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n_, INFINITY_)), visited_(n), xy_(xy)//, distance_heur(2, vector<Len>(n_, INFINITY_))
    { workset_.reserve(n); }

    // See the description of this method in the starter for friend_suggestion
    void clear() {
        for (int i = 0; i < workset_.size(); ++i) {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INFINITY_;
            visited_[v].first = false;
            visited_[v].second = false;
        }
        workset_.clear();
        umap.clear();
    }

    // See the description of this method in the starter for friend_suggestion
    void visit(Queue& q, int side, int v, Len dist, Len& min_dist, Len& dist_heur, int& s, int& t) {

        if (side == 0){
            for (auto i = 0; i < adj_[0][v].size(); i++){
                Len node = adj_[0][v][i];

                if (umap.find(node) == umap.end()) { umap[node] = (sqrt(pow(xy_[t].first - xy_[node].first, 2) + pow(xy_[t].second - xy_[node].second, 2))\
                                                  - sqrt(pow(xy_[s].first - xy_[node].first, 2) + pow(xy_[s].second - xy_[node].second, 2)))/2; }
                if (distance_[0][node] > dist + cost_[0][v][i]){
                    if (distance_[0][node] == INFINITY_) { workset_.emplace_back(node); }
                    distance_[0][node] = dist + cost_[0][v][i];
                    dist_heur = distance_[0][node] + umap[node];
                    min_dist = min(min_dist, distance_[1][node] + distance_[0][node]);
                    q[0].push(make_pair(dist_heur, node));
                }
            } 
        }
        else if (side == 1){
            for (auto i = 0; i < adj_[1][v].size(); i++){
                Len node = adj_[1][v][i];
  
                if (umap.find(node) == umap.end()) { umap[node] = (sqrt(pow(xy_[t].first - xy_[node].first, 2) + pow(xy_[t].second - xy_[node].second, 2))\
                                                  - sqrt(pow(xy_[s].first - xy_[node].first, 2) + pow(xy_[s].second - xy_[node].second, 2)))/2; }
                if (distance_[1][node] > dist + cost_[1][v][i]){
                    if (distance_[1][node] == INFINITY_) { workset_.emplace_back(node); }
                    distance_[1][node] = dist + cost_[1][v][i];
                    dist_heur = distance_[1][node] - umap[node];
                    min_dist = min(min_dist, distance_[1][node] + distance_[0][node]);
                    q[1].push(make_pair(dist_heur, node)); 
                }
            } 
        }
    }

    // Returns the distance from s to t in the graph
    Len query(int s, int t) {
        if (s == t) return 0;
        clear();
        Queue q(2);
        Len dist_heur = 0;
        q[0].push(make_pair(dist_heur, s));
        q[1].push(make_pair(dist_heur, t));
        distance_[0][s] = 0;
        distance_[1][t] = 0;
        workset_.emplace_back(s);
        workset_.emplace_back(t);
        Len dist;
        int node;
        Len min_dist = INFINITY_;

        while(!q[0].empty() || !q[1].empty()) {
            
            if (!q[0].empty()) {
                node = q[0].top().second;
                q[0].pop();

                if (visited_[node].second) break;
                else if (!visited_[node].first){
                    visited_[node].first = true;
                    visit(q, 0, node, distance_[0][node], min_dist, dist_heur, s, t);
                }
            }
            // reverse graph search
            if (!q[1].empty()) {
                node = q[1].top().second;
                q[1].pop();
                
                if (visited_[node].first) break;
                else if (!visited_[node].second){
                    visited_[node].second = true;
                    visit(q, 1, node, distance_[1][node], min_dist, dist_heur, s, t);
                }
            }
            if (q[0].empty() && q[1].empty()) return -1;
        }
        return min_dist;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    // std::ofstream outfile ("test.txt");
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
        // outfile << to_string(astar.query(u-1, v-1)) << std::endl;
    }
    // outfile.close();
}
