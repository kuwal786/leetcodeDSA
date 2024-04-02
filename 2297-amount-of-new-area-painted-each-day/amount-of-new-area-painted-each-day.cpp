class Solution {
private:
    map<int,int> ranges;

    int getAns(vector<int> interval)
    {
        int duration = interval[1] - interval[0];
        int start = interval[0], end = interval[1];
        cout<<start<<" "<<end<<"\n";
        auto it = ranges.upper_bound(start);

        while(it!=ranges.end())
        {
            cout<<"loop is here\n";
            if((*it).first <= end)
            {
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
                    cout<<duration<<" inside loop2\n";
                    break;
                }
            }
            else
            {
                break;
            }

            it++;
            ranges.erase(prev(it));
            cout<<duration<<" inside loop\n";
        }
        
        cout<<duration<<"\n";
        if(it!=ranges.begin())
        {
            it = prev(it);
            if((*it).second >= start)
            {
                if((*it).second >= end)
                {
                    return 0;
                }
                else
                {
                    duration-= (*it).second - start; 
                    start = (*it).first;
                    ranges.erase(it);
                }
            }
        }
        
        ranges[start] = end;
        return max(duration, 0);
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