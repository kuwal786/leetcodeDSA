class Solution {
    public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {

        int n=coins.size();
        vector<set<int>> g(n);
        
        for(auto& e:edges)  g[e[0]].insert(e[1]),g[e[1]].insert(e[0]);
        queue<int> leaves;

        int totalEdges=edges.size()*2,deleted=0;
        // let's add the leaves which don't have any coins!
        
        for(int i=0;i<n;i++)    if(g[i].size()==1 && coins[i]==0)  leaves.push(i);

        while(leaves.size()){   // keep removing leaves with no coins!
            int leaf=leaves.front();
            leaves.pop();
            if(g[leaf].empty()) continue;// this not has no parent! [last node of the tree]

            int p=*g[leaf].begin();     // parent
            
            g[p].erase(leaf),deleted++;
            g[leaf].erase(p),deleted++;        // clear the entire mappings for it as it's useless now!
            
            if(g[p].size()==1 && coins[p]==0)   leaves.push(p); // if this now becomes a leaf with no coins. 
        }
        // now the leaves would be having the coin! 
        for(int i=0;i<n;i++)    if(g[i].size()==1)  leaves.push(i);
        // now I need to remove the leaf nodes and their immediate parents
        int step=2; //1 for parent and 1 for children
        while(step--){
            int sz=leaves.size();
            while(sz--){
                int leaf=leaves.front();
                leaves.pop();
                if(!g[leaf].size()) continue;// this not has no parent! [last node of the tree]
                
                int p=*g[leaf].begin();     // only parent would be there in leaf!
                
                g[p].erase(leaf),deleted++;
                g[leaf].erase(p),deleted++;

                if(g[p].size()==1)  leaves.push(p);
            
            }
        }
        
        return totalEdges-deleted;
    }
};