/*
Directed Graph implemented by Red-Black Tree

Author: minhdq99hp
*/
#include <stdio.h>

int main(){
    Graph g = createGraph();

    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");

    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 1, 3);

    if(DAG(g)) print("The graph is a cycle\n");
    else printf("Have cycles in the graph\n");

    return 0;
}