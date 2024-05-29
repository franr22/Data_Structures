#include "graph-proj6.h"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int INFINITE = 1000000000;
const int SERVER_LENGTH = 7;

int main() {
    int nEdges, cost;
    int minCost = INFINITE;
    int vertexCount = 0;
    map<string, int> vertexMap;
    vector<bool> isServer;
    vector<int> totalDelays;
    string n1, n2;
    stringstream streams;

    cin >> nEdges;
    for(int i = 0; i < nEdges; i++){
        cin >> n1 >> n2 >> cost;
        streams << n1 << " " << n2 << " " << cost << endl;

        if(vertexMap.find(n1) == vertexMap.end()){
            vertexMap[n1] = vertexCount;
            isServer.push_back(n1.size() >= SERVER_LENGTH &&
            n1.substr(n1.size() - SERVER_LENGTH) == "_server");
            vertexCount++;
        }

        if(vertexMap.find(n2) == vertexMap.end()) {
            vertexMap[n2] = vertexCount;
            isServer.push_back(n2.size() >= SERVER_LENGTH &&
            n2.substr(n2.size() - SERVER_LENGTH) == "_server");
            vertexCount++;
        }

    }

    Graph graph(vertexMap.size());

    for(int i = 0; i < nEdges; i++){
        streams >> n1 >> n2 >> cost;
        graph.addEdge(vertexMap[n1], vertexMap[n2], cost);
    }

    for(int i = 0; i < isServer.size(); i++){
        if(isServer[i]){
            totalDelays.push_back(0);
            vector<int> aEdges = graph.dijkstra(i);
            for(int j = 0; j < isServer.size(); j++){
                if(aEdges[j] >= 0 && totalDelays[i] < INFINITE){
                    totalDelays[i] += aEdges[j];
                }
            }
            if(totalDelays[i] >= 0) {
                if (totalDelays[i] < minCost) {
                    minCost = totalDelays[i];
                }
            }
        }
        else{
            totalDelays.push_back(INFINITE);
        }
    }

    if(minCost != INFINITE){
        cout << "total delay: " << minCost << endl;
        for(map<string,int>::iterator  i = vertexMap.begin();
        i != vertexMap.end(); i++) {
            int index = i->second;
            if (isServer[index] && totalDelays[index] == minCost) {
                cout << i->first << endl;
            }
        }
    }
    else{
        cout << "no server can serve the whole network" << endl;
    }

    return 0;
}
