class Solution {
private:
    map<int,int> ranges;

    int getAns(vector<int> interval)
    {
        int duration = interval[1] - interval[0];
        int start = interval[0], end = interval[1];
        auto it = ranges.upper_bound(start);

        while(it!=ranges.end())
        {
            if((*it).first > end)break;

            if((*it).second <=end)
            {
                duration-= (*it).second - (*it).first;
            }
            else
            {
                duration-= end - (*it).first;
                end = (*it).second;
                it++;
                ranges.erase(prev(it));
                break;
            }
            
            it++;
            ranges.erase(prev(it));
        }
        
        if(it!=ranges.begin())
        {
            it = prev(it);
            if((*it).second >= end)
            {
                return 0;
            }

            if((*it).second >= start)
            {
                duration-= (*it).second - start; 
                start = (*it).first;
                ranges.erase(it);

            }
        }
        
        ranges[start] = end;
        return duration;
    } 

public:
    vector<int> amountPainted(vector<vector<int>>& paint) {
        vector<int> ans;

        for(auto v: paint)
        {
            ans.push_back(getAns(v));
        }

        return ans;
    }
};