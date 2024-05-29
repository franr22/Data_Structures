#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"

void Graph::addEdge(int from, int to, int cost){
    adjacencyList[from].push_back(Edge(to,cost));
}

vector<int> Graph::dijkstra(int source) const{
    vector<int> distance(adjacencyList.size(), INFINITE_COST);
    vector<int> keys(adjacencyList.size(), -1);
    ArrayHeap<pair<int,int>> front;
    pair<int, int>a = {0, source};
    distance[source] = 0;
    keys[source] = front.insert(a);

    while(front.getNumItems() != 0){
        int current = front.getMinItem().second;
        front.removeMinItem();

        for(list<Edge>::const_iterator i = adjacencyList[current].begin();
        i != adjacencyList[current].end(); i++){
            const Edge& edge = *i;

            if(distance[current] + edge.cost < distance[edge.to]){
                distance[edge.to] = edge.cost + distance[current];
                if(!front.isOnHeap(keys[edge.to])){
                    keys[edge.to] = front.insert({distance[edge.to], edge.to});
                }
                else{
                    front.changeItemAtKey(keys[edge.to], {distance[edge.to], edge.to});
                }
            }
        }
    }
    return distance;
}
