class Solution {
    public List<String> findAllRecipes(String[] recipes, List<List<String>> ingredients, String[] supplies) {
        Map<String, List<String>> adjList = new HashMap<>();
        Map<String, Integer> indegree = new HashMap<>();
        for(int i =0; i<recipes.length; i++)
        {
            for(String ingredient: ingredients.get(i))
            {
                adjList.putIfAbsent(ingredient, new ArrayList<>());
                adjList.get(ingredient).add(recipes[i]);         
                indegree.put(recipes[i], indegree.getOrDefault(recipes[i], 0) + 1);
            }
        }

        Queue<String> q = new LinkedList();

        for(String supply: supplies)
        {
            q.add(supply);
        }

        List<String> answer = new ArrayList<>();

        while(!q.isEmpty())
        {
           String recp = q.poll();

           if(!adjList.containsKey(recp))continue;

           for(String ngb: adjList.get(recp))
           {
               int cnt = indegree.get(ngb)-1;
               indegree.put(ngb, cnt);
               if(cnt == 0)
               {
                    q.add(ngb);
               }
           }
        }

        for(String recp: recipes)
        {
            if(indegree.get(recp) == 0)
                answer.add(recp);
        }

        return answer;
    }
}