class Solution {
public:
    unordered_map<string, pair<string, double>> parent;
    unordered_map<string, int> rank;
    pair<string, double> find (string& node){
        if(!parent.count(node)){
            parent[node] = {node, 1};
            rank[node] = 1;
        }
        if(parent[node].first==node)return parent[node];
        auto [parenttop, valuetop] = find(parent[node].first);
        parent[node].first = parenttop;
        parent[node].second *= valuetop;
        return parent[node];
    }
    bool merge(string& a, string& b, double value){
        auto [parenta, valuea] = find(a);
        auto [parentb, valueb] = find(b);
        if(parenta==parentb) return false;
        if(rank[parenta]<rank[parentb]){
           swap(parenta, parentb); swap(a, b); value = 1.0/value;
        }
        rank[parenta]+=rank[parentb];
        parent[parentb].first= parenta;
        parent[parentb].second = parent[a].second*value*1.0/parent[b].second;
        return true;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        
        
        for (int i =0 ; i<equations.size(); ++i)
            merge(equations[i][0], equations[i][1], values[i]);
        
        vector<double> answer;
        
        for (int i = 0; i<queries.size(); ++i){
            auto& first = queries[i][0], &second = queries[i][1];
            if(!parent.count(first) || !parent.count(second)) {answer.push_back(-1); continue;}
            auto[parenta, valuea] = find(first);
            auto[parentb, valueb] = find(second);
            if(parenta!=parentb){answer.push_back(-1); continue;}
            answer.push_back(1.0*valueb/valuea);
        }
        return answer;
    }
};