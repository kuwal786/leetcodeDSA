class Solution {

    bool isCollision(vector<pair<int, int>> &cars, int cur, int last, int target){
        if((target - cars[cur].first) * 1LL * cars[last].second  <= (target - cars[last].first) * 1LL * cars[cur].second )
            return true;
    
        return false;
    }

public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int totalCollision = 0;
        int n = position.size();
        int lastPos = n-1;
        vector<pair<int, int>> cars;
        for(int i = 0; i<n; i++){
            cars.push_back({position[i], speed[i]});
        }

        sort(cars.begin(), cars.end());

        for(int i = n-2; i>=0; i--){
            if(isCollision(cars, i, lastPos, target)){
                totalCollision++;
            }
            else
            {
                lastPos = i;
            }
        }

        
        return n - totalCollision;
    }
};