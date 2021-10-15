#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define INF 1000000

typedef struct{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph(){
    Graph n;
    n.edges = make_jrb();
    n.vertices = make_jrb();
    return n;
}

void addVertex(Graph graph, int id, char *name){
        JRB node = jrb_find_int(graph.vertices, id);

        if(node == NULL){
            jrb_insert_int(graph.vertices, id, new_jval_s(name));
        }
        else node->val = new_jval_s(name);
}

char *getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL) return NULL;
    else return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2, double weight){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL){
        JRB subTree = make_jrb();
        node = jrb_insert_int(graph.edges, v1, new_jval_v(subTree));
    }

    JRB subTree = (JRB)jval_v(node->val);
    jrb_insert_int(subTree, v2, new_jval_d(weight));
}

double getEdgeValue(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL) return INF;
    else{
        JRB subTree = (JRB)jval_v(node->val);
        JRB subNode = jrb_find_int(subTree, v2);
        if(subNode == NULL) return INF;
        else return jval_d(subNode->val);
    }
}

int hasEdge(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL) return 0;
    else{
        JRB subTree = (JRB)jval_v(node->val);
        JRB subNode = jrb_find_int(subTree, v2);
        if(subNode == NULL) return 0;
        else return 1;
    }
}

int indegree(Graph graph, int v, int *output){
    JRB node;

    int total = 0;

    jrb_traverse(node, graph.edges){
        JRB subTree = (JRB)jval_v(node->val);

        JRB foundNode = (JRB)jrb_find_int(subTree, v);

        if(foundNode != NULL) output[total++] = jval_i(node->key);
    }

    return total;
}

int outdegree(Graph graph, int v, int *output){
    JRB node = jrb_find_int(graph.edges, v);

    int total = 0;

    if(node == NULL) return total;

    JRB foundNode;
    JRB subTree = (JRB)jval_v(node->val);

    jrb_traverse(foundNode, subTree){
        output[total++] = jval_i(foundNode->key);
    }
    return total;
}

void printVertices(Graph graph){
    JRB node;
    printf("Vertices:");
    jrb_traverse(node, graph.vertices){
        printf("%4s", jval_s(node->val));
    }
    printf("\n");
}

void printOutdegree(Graph graph, int v){
    int output[1000];
    int total;

    total = outdegree(graph, v, output);

    printf("Outdegree of %d:", v);
    JRB node;
    for(int i=0; i<total; i++){
        node = jrb_find_int(graph.vertices, output[i]);

        if(node != NULL) printf("%4s", jval_s(node->val));
    }
    printf("\n");
}

void printIndegree(Graph graph, int v){
    int output[1000];
    int total;

    total = indegree(graph, v, output);

    printf("Indegree of %d:", v);
    JRB node;
    for(int i=0; i<total; i++){
        node = jrb_find_int(graph.vertices, output[i]);

        if(node != NULL) printf("%4s", jval_s(node->val));
    }
    printf("\n");
}

double shortestPath(Graph g, int s, int t, int* path, int*length){
   double distance[1000], min, w, total;
   int previous[1000], tmp[1000];
   int n, output[100], i, u, v, start;
   Dllist ptr, queue, node;

   for (i=0; i<1000; i++)
       distance[i] = INF;
   distance[s] = 0;
   previous[s] = s;
       
   queue = new_dllist();
   dll_append(queue, new_jval_i(s));

   while(!dll_empty(queue)){
      // get u from the priority queue   
      min = INF;   
      dll_traverse(ptr, queue){
          u = jval_i(ptr->val);              
          if (min > distance[u]){
             min = distance[u];
             node = ptr;
          }                 
      }
      dll_delete_node(node);
      
      if (u == t) break; // stop at t
      
      n = outdegree(g, u, output);
      for (i=0; i<n; i++){
          v = output[i];
          w = getEdgeValue(g, u, v);
          if ( distance[v] > distance[u] + w )
          {    
              distance[v] = distance[u] + w;
              previous[v] = u;
          }     
          dll_append(queue, new_jval_i(v));
      }
   }
   total = distance[t]; 
   if (total != INF)
   {
       tmp[0] = t;
       n = 1;              
       while (t != s)
       {
             t = previous[t];
             tmp[n++] = t;
       }
       for (i=n-1; i>=0; i--)
           path[n-i-1] = tmp[i];
       *length = n;                
   }
   return total;   
}


int main(){
    Graph g = createGraph();

    addVertex(g, 1, "S");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addVertex(g, 4, "V4");
    addVertex(g, 5, "V5");
    addVertex(g, 6, "V6");
    addVertex(g, 7, "V7");
    addVertex(g, 8, "T");

    addEdge(g, 1, 2, 9);
    addEdge(g, 1, 6, 14);
    addEdge(g, 1, 7, 15);
    addEdge(g, 2, 3, 24);
    addEdge(g, 6, 3, 18);
    addEdge(g, 6, 5, 30);
    addEdge(g, 6, 7, 5);
    addEdge(g, 7, 5, 20);
    addEdge(g, 5, 4, 11);
    addEdge(g, 3, 5, 2);
    addEdge(g, 4, 3, 6);
    addEdge(g, 3, 8, 19);
    addEdge(g, 5, 8, 16);
    addEdge(g, 4, 8, 6);
    addEdge(g, 7, 8, 44);

    int s, t, length, path[1000];

    s = 1;
    t = 8;

    double weight = shortestPath(g, s, t, path, &length);

    if(weight == INF) printf("No path between %d and %d.\n", s, t);

    for(int i=0; i<length; i++) printf("%4d", path[i]);
    printf("\n");

    printf("Total weight: %.2f\n", weight);

    return 0;
}
