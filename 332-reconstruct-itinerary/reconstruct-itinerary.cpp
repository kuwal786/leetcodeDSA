class Solution {
    map<string, multiset<string>> graph;
    vector<string> route;

    void visit(string source)
    {
        while(graph[source].size())
        {
            string next = *graph[source].begin();
            graph[source].erase(graph[source].find(next));
            visit(next);
        }

        route.push_back(source);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for(auto flight: tickets)
        {
            graph[flight[0]].insert(flight[1]);
        }

        visit("JFK");

        reverse(route.begin(), route.end());

        return route;
    }
};