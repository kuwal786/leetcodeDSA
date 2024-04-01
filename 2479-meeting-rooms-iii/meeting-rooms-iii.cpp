class Compare {
    public: bool operator()(pair<long,long> &p1, pair<long,long> &p2)
    {
        if(p1.first == p2.first)
        {
            return p1.second > p2.second;
        }

        return p1.first > p2.first;
    }
};

class CompareVec {
    public: bool operator()(vector<int> &v1, vector<int> &v2)
    {
        if(v1[0] == v2[0])
        {
            return v1[1] < v2[1];
        }

        return v1[0] < v2[0];
    }
};


class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        set<int> indices;
        priority_queue<pair<long,long>, vector<pair<long,long>>, Compare> PQ;
        unordered_map<int, int> freq;

        long long curr_time = 0, delay =0;
        for(int i =0; i<n;i++){
          indices.insert(i); 
        }

        sort(meetings.begin(), meetings.end(), CompareVec());
        
        for(auto meeting: meetings)
        {
            long duration = meeting[1] - meeting[0];
            curr_time = max(curr_time, (long long)meeting[0]);
            while(!PQ.empty() && PQ.top().first <= curr_time)
            {
                //cout<<"insertinmg elment "<<PQ.top().second<<"\n";
                indices.insert(PQ.top().second);
                PQ.pop();
            }

            if(indices.size()==0)
            {
                long  timeToComplete = PQ.top().first;
                int idx = PQ.top().second;
                PQ.pop();
                //delay = delay + timeToComplete -curr_time;
                curr_time = timeToComplete;
                freq[idx]++;
                cout<<idx<<" used 2\n";
                PQ.push({curr_time+duration, idx});
                continue;
            }

            int idx = *indices.begin();
            indices.erase(idx);
            freq[idx]++;
            //cout<<idx<<" used\n";
            PQ.push({curr_time+duration, idx});
        }

        int roomMostUsed = -1, maxUseCount = 0;
        for(auto entry: freq)
        {
            if(roomMostUsed == -1 || entry.second > maxUseCount)
            {
                roomMostUsed = entry.first;
                maxUseCount = entry.second;
            }
            else if(entry.second == maxUseCount)
            {
                if(roomMostUsed > entry.first)
                {
                    roomMostUsed = entry.first;
                }
            }
        }

        return roomMostUsed;
    }
};