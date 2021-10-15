// #include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define INF 10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void dropGraph(Graph graph);
double shortestPath(Graph graph, int s, int t, int* path, int*length);

// int main()
// {
//     int i, length, path[100], s, t;
//     double w;
//     Graph g = createGraph();
//     addVertex(g, 0, "V0");
//     addVertex(g, 1, "V1");
//     addVertex(g, 2, "V2");
//     addVertex(g, 3, "V3");
//     addEdge(g, 0, 1, 1);
//     addEdge(g, 1, 2, 3);
//     addEdge(g, 2, 0, 3);
//     addEdge(g, 1, 3, 1);
//     addEdge(g, 3, 2, 1);
//     s = 0;
//     t = 2;
//     w = shortestPath(g, s, t, path, &length);
//     if (w == INF)
//     {
//          printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
//     }else
//     {
//          printf("Path from %s to %s (with total distance %f)\n", getVertex(g, s), getVertex(g, t), w);
//          for (i=0; i<length; i++)
//              printf(" => %s", getVertex(g, path[i]));
//     }
    
//     dropGraph(g);
//     getch();   
// }

Graph createGraph()
{
   Graph g; 
   g.edges = make_jrb();  
   g.vertices = make_jrb();  
   return g;
}

void addVertex(Graph g, int id, char* name)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) // only add new vertex 
         jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));            
}

char *getVertex(Graph g, int id)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) 
        return NULL;
     else                
        return jval_s(node->val);
}     

void addEdge(Graph graph, int v1, int v2, double weight)
{
     JRB node, tree;
     if (getEdgeValue(graph, v1, v2)==INF)
     {
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
     }
}

double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
       return INF;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node==NULL)
       return INF;
    else
       return jval_d(node->val);       
}

int indegree (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total = 0;   
    jrb_traverse(node, graph.edges)
    {
       tree = (JRB) jval_v(node->val);
       if (jrb_find_int(tree, v))
       {
          output[total] = jval_i(node->key);
          total++;
       }                
    }
    return total;   
}

int outdegree (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
}

double shortestPath(Graph g, int s, int t, int* path, int*length)
{
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

   while ( !dll_empty(queue) )
   {
      // get u from the priority queue   
      min = INF;   
      dll_traverse(ptr, queue)
      {
          u = jval_i(ptr->val);              
          if (min > distance[u])
          {
             min = distance[u];
             node = ptr;
          }                 
      }
      dll_delete_node(node);
      
      if (u == t) break; // stop at t
      
      n = outdegree(g, u, output);
      for (i=0; i<n; i++)
      {
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

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
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
