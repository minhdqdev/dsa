/*
Final Exam IT3240E
Dang Quang Minh - 20176823
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include "utils.c"


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
    // else node->val = new_jval_s(name);
}

char *getVertex(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);
    if(node == NULL) return NULL;
    else return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2, double weight){
    printf("%d - %d - %f\n", v1, v2, weight);

    JRB node = jrb_find_int(graph.edges, v1);
    if(node == NULL){
        JRB subTree = make_jrb();
        node = jrb_insert_int(graph.edges, v1, new_jval_v(subTree));
    }

    JRB subTree = (JRB)jval_v(node->val);
    node = jrb_find_int(subTree, v2);
    if(node == NULL) jrb_insert_int(subTree, v2, new_jval_d(weight));
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
    printf("Vertices: | ");
    jrb_traverse(node, graph.vertices){
        printf("%4s | ", jval_s(node->val));
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
    int output[100], u, v, start;
    Dllist ptr, queue, node;

    for(int i=0; i<1000; i++){
        distance[i] = INF;
        previous[i] = -1;
    }
    distance[s] = 0;
    previous[s] = s;
        
    queue = new_dllist();

    JRB vertex;
    jrb_traverse(vertex, g.vertices){
        dll_append(queue, vertex->key);
    }
    while(!dll_empty(queue)){
        min = INF;
        int k;
        dll_traverse(ptr, queue){
            u = jval_i(ptr->val);
            if(min > distance[u]){
                min = distance[u];
                k = u;
                node = ptr;
            }       
        }
        if(min == INF){
            node = dll_first(queue);
            k = jval_i(node->val);
        }
        dll_delete_node(node);
        
        int n = outdegree(g, k, output);
        
        for (int i=0; i<n; i++){
            v = output[i];
            w = getEdgeValue(g, k, v);

            if(distance[v] > distance[k] + w){    
                distance[v] = distance[k] + w;
                previous[v] = k;
            }
        }
    }
    total = distance[t]; 
    if(total != INF){
        tmp[0] = t;
        int n = 1;              
        while(t != s){
            t = previous[t];
            tmp[n++] = t;
        }
        for(int i=n-1; i>=0; i--) path[n-i-1] = tmp[i];
        *length = n;                
    }
   return total; 
}

double shortestPathWalk(Graph g, int s, int t, int* path, int*length){
    double distance[1000], min, w, total;
    int previous[1000], tmp[1000];
    int output[100], u, v, start;
    Dllist ptr, queue, node;

    for(int i=0; i<1000; i++){
        distance[i] = INF;
        previous[i] = -1;
    }
    distance[s] = 0;
    previous[s] = s;
        
    queue = new_dllist();

    JRB vertex;
    jrb_traverse(vertex, g.vertices){
        dll_append(queue, vertex->key);
    }
    while(!dll_empty(queue)){
        min = INF;
        int k;
        dll_traverse(ptr, queue){
            u = jval_i(ptr->val);
            if(min > distance[u]){
                min = distance[u];
                k = u;
                node = ptr;
            }       
        }
        if(min == INF){
            node = dll_first(queue);
            k = jval_i(node->val);
        }
        dll_delete_node(node);
        
        int n = outdegree(g, k, output);
        
        for (int i=0; i<n; i++){
            v = output[i];
            w = getEdgeValue(g, k, v);

            if(w >= 50){
                if(distance[v] > distance[k] + w){    
                    distance[v] = distance[k] + w;
                    previous[v] = k;
                }
            }
        }
    }
    total = distance[t]; 
    if(total != INF){
        tmp[0] = t;
        int n = 1;              
        while(t != s){
            t = previous[t];
            tmp[n++] = t;
        }
        for(int i=n-1; i>=0; i--) path[n-i-1] = tmp[i];
        *length = n;                
    }
   return total; 
}

Graph readGraphFromFile(const char *filename){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    Graph graph = createGraph();

    char buffer[500];

    int a, b, count;

    int flag = 0;
    while(fgets(buffer, 500, fp)){
        removeNewline(buffer);
        char *output[3];
        int n = split(buffer, " ", output);

        if(flag == 0){
            a = atoi(output[0]);
            b = atoi(output[1]);
            flag = 1;
        }
        else if(flag == 1){
            if(count++ < b){
                int v1 = atoi(output[0]);
                int v2 = atoi(output[1]);
                int weight = atoi(output[2]);

                char *name1 = (char*)malloc(sizeof(char) * 10);
                char *name2 = (char*)malloc(sizeof(char) * 10);

                sprintf(name1, "Castle %d", v1);
                sprintf(name2, "Castle %d", v2);

                addVertex(graph, v1, name1);
                addVertex(graph, v2, name2);
                addEdge(graph, v1, v2, weight);
                addEdge(graph, v2, v1, weight);
            }
            
        }

    }

    fclose(fp);
    return graph;
}

void printEdgesMatrix(Graph graph){
    int n = 0;
    int vertexIds[1000];
    JRB node;
    jrb_traverse(node, graph.vertices) vertexIds[n++] = jval_i(node->key);

    printf("Edges Matrix: \n");
    printf("     ");
    for(int i=0; i<n; i++){ 
        printf("%5d", vertexIds[i]);
    }
    printf("\n");

    for(int i=0; i<n; i++){
        printf("%3d: ", vertexIds[i]);
        JRB node = jrb_find_int(graph.edges, vertexIds[i]);
        if(node == NULL){
            // for(int i=0; i<n; i++) printf("%5c", ' ');
            // printf("\n");
            continue;
        }
        JRB subTree = (JRB)jval_v(node->val);

        double w[1000];
        for(int j=1; j<=1000; j++) w[j] = INF;

        jrb_traverse(node, subTree){
            int nodeId = jval_i(node->key);
            w[nodeId] = jval_d(node->val);
        }

        for(int j=0; j<n; j++){
            if(w[vertexIds[j]] < INF) printf("%5.0f", w[vertexIds[j]]);
            else printf("%5c", ' ');
        }
        printf("\n");
    }
    printf("\n");     
}

Graph quest1(){
    char filename[] = "dothi.txt";

    // printf("Enter filename: ");
    // fgets(filename, 100, stdin);

    Graph graph = readGraphFromFile(filename);

    printVertices(graph);

    printEdgesMatrix(graph);

    return graph;
}

void quest2(Graph graph){
    JRB node;
    jrb_traverse(node, graph.vertices){
        char *vertexName = jval_s(node->val);
        printf("%-9s: ", vertexName);
        JRB e = jrb_find_int(graph.edges, jval_i(node->key));
        if(e != NULL){
            JRB subTree = (JRB)jval_v(e->val);
            JRB subNode;
            jrb_traverse(subNode, subTree) printf("%d ", jval_i(subNode->key));
        }
        printf("\n");
    }    
    printf("\n");
}

void quest3(Graph graph){
    JRB node;
    printf("3.a: \n");
    jrb_traverse(node, graph.vertices){
        int output[100];
        int n = indegree(graph, jval_i(node->key), output);

        int flag = 1; // chi di bo dc
        for(int i=0; i<n; i++){
            if(getEdgeValue(graph, output[i], jval_i(node->key)) < 50){
                flag = 0;
                break;
            }
        }

        if(flag) printf("%d ", jval_i(node->key));
    }
    printf("\n");

    printf("3.b: \n");
    int maxIndegree = -1;
    jrb_traverse(node, graph.vertices){
        int output[100];
        int n = indegree(graph, jval_i(node->key), output);
        if(n > maxIndegree) maxIndegree = n;
    }

    jrb_traverse(node, graph.vertices){
        int output[100];
        int n = indegree(graph, jval_i(node->key), output);

        if(n == maxIndegree){
            printf("%d ", jval_i(node->key));
        }
    }
    printf("\n\n");
}

void quest4(Graph graph){
    int s, t;
    printf("Enter the source: ");
    scanf("%d", &s); getchar();
    printf("Enter the destination: ");
    scanf("%d", &t); getchar();

    int flag1 = 0;
    int flag2 = 0;
    JRB node;
    jrb_traverse(node, graph.vertices){
        if(s == jval_i(node->key)) flag1 = 1;
        if(t == jval_i(node->key)) flag2 = 1;
    }

    if(!flag1 || !flag2){
        printf("ROUTE NOT FOUND\n");
        return;
    }

    int path[100];
    int length;
    double totalWeight = shortestPath(graph, s, t, path, &length);
    
    if(totalWeight >= INF) printf("ROUTE NOT FOUND\n");
    else{
        printf("%.0f: ", totalWeight);
        for(int i=0; i<length; i++) printf("%d ", path[i]);
    }    
    printf("\n\n");
}

void quest5(Graph graph){
    int s, t;
    printf("Enter the source: ");
    scanf("%d", &s); getchar();
    printf("Enter the destination: ");
    scanf("%d", &t); getchar();

    int flag1 = 0;
    int flag2 = 0;
    JRB node;
    jrb_traverse(node, graph.vertices){
        if(s == jval_i(node->key)) flag1 = 1;
        if(t == jval_i(node->key)) flag2 = 1;
    }

    if(!flag1 || !flag2){
        printf("ROUTE NOT FOUND\n");
        return;
    }
    
    int path[100];
    int length;
    double totalWeight = shortestPathWalk(graph, s, t, path, &length);
    
    if(totalWeight >= INF) printf("ROUTE NOT FOUND\n");
    else{
        printf("%.0f: ", totalWeight);
        for(int i=0; i<length; i++) printf("%-2d", path[i]);
    }    
    printf("\n\n");
}

void printMenu(){
    printf("1. Read database\n");
    printf("2. Print adjacent list\n");
    printf("3. Analysis\n");
    printf("4. Find shortest path 1\n");
    printf("5. Find shortest path 2\n");
    printf("0. Exit program\n");
    printf("Your choice: ");
}

int main(int argc, char* argv[]){
    int ans = 1;

    Graph graph;

    while(ans != 0){
        printMenu();
        scanf("%d", &ans); getchar();

        switch(ans){
            case 1: graph = quest1(); break;
            case 2: quest2(graph); break;
            case 3: quest3(graph); break;
            case 4: quest4(graph); break;
            case 5: quest5(graph); break;
            case 0: break;
        }
    }
    return 0;
}