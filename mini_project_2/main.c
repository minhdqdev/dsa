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
    JRB routes;
} Graph;

Graph createGraph(){
    Graph newGraph;

    newGraph.edges = make_jrb();
    newGraph.vertices = make_jrb();
    newGraph.routes = make_jrb();

    return newGraph;
}

void addVertex(Graph graph, int id, char *name){
    JRB node = jrb_find_int(graph.vertices, id);

    if(node == NULL){
        jrb_insert_int(graph.vertices, id, new_jval_s(name));
    }
    else{
        node->val = new_jval_s(name);
    }
}

char *getVertexNameById(Graph graph, int id){
    JRB node = jrb_find_int(graph.vertices, id);

    if(node == NULL) return NULL;
    return jval_s(node->val);
}

int getVertexIdByName(Graph graph, char *name){
    JRB node;

    jrb_traverse(node, graph.vertices){
        if(strcmp(name, jval_s(node->val)) == 0) return jval_i(node->key);
    }

    return -1;
}

void addVertexToRoute(Graph graph, char *route_id, int v){
    JRB node = jrb_find_str(graph.edges, route_id);

    if(node == NULL){
        JRB subNode = make_jrb();
        node = jrb_insert_str(graph.routes, route_id, new_jval_v(subNode));
    }

    JRB subTree = (JRB)jval_v(node->val);

    JRB subNode = jrb_find_int(subTree, v);

    if(subNode == NULL){
        jrb_insert_int(subTree, v, new_jval_i(1));
    }


}

void addEdge(Graph graph, int v1, int v2, double weight){
    JRB node = jrb_find_int(graph.edges, v1);
    
    if(node == NULL){
        JRB tree = make_jrb();
        node = jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }

    JRB subTree = (JRB)jval_v(node->val);

    JRB subNode = jrb_find_int(subTree, v2);

    if(subNode == NULL){
        jrb_insert_int(subTree, v2, new_jval_d(weight));
    }
    
}

double getEdgeValue(Graph graph, int v1, int v2){
    JRB node = jrb_find_int(graph.edges, v1);

    if(node == NULL) return INF;
    else{
        JRB subTree = (JRB)jval_v(node->val);
        JRB node2 = jrb_find_int(subTree, v2);

        if(node2 == NULL) return INF;
        else return jval_d(node2->val);
    }
}

void print_menu(){
	printf("\n----- BUS MAP -----\n");
    printf("1. Find shortest path\n");
    printf("2. Print all vertices\n");
    printf("0. Exit\n");
    printf("Your choice: ");
}

void printVertices(Graph graph){
    JRB node;
    printf("Vertices:");
    jrb_traverse(node, graph.vertices){
        printf("%d : %s\n", jval_i(node->key), jval_s(node->val));
    }
    printf("\n");
}

void loadFromFile(Graph graph, const char *filename){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[500];
    char *route_id;
    int flag = -1;
    while(fgets(buffer, 500, fp)){
        removeNewline(buffer);

        if(strcmp(buffer, "# VERTICES") == 0){
            flag = 0;
            continue;
        }
        else if(strcmp(buffer, "# ROUTE_ID") == 0){
            flag = 1;
            continue;
        }
        else if(strcmp(buffer, "## EDGES") == 0){
            flag = 2;
            continue;
        }

        if(flag == 0){ // read vertices
            int index = 0; // index of ':' character
            int id;
            char *verticeName = (char*)malloc(sizeof(char) * 500);
            char verticeId[10];

            while(buffer[index] != '\0'){
                if(buffer[index] == ':'){
                    strncpy(verticeId, buffer, index-1);
                    id = atoi(verticeId);

                    strncpy(verticeName, buffer+index+2, sizeof(char) * 500);
                    addVertex(graph, id, verticeName);
                    break;
                }
                index++;
            }   
        } 
        else if(flag == 1){ // read route_id
            route_id = (char*)malloc(sizeof(char) * 20);
            strncpy(route_id, buffer, sizeof(route_id));
        }
        else if(flag == 2){ // read edges
            int rindex = 0; // index of the first space character
            int lindex = 0; // index of the last space character

            char *temp;
            while(buffer[rindex] != '\0'){
                if(buffer[rindex] == ' '){
                    if(lindex == 0) lindex = rindex;
                    else{
                        int v1, v2, weight;
                        // get vertex 1
                        temp = (char*)malloc(sizeof(char) * 20);
                        strncpy(temp, buffer, lindex);
                        v1 = atoi(temp);
                        // get vertex 2
                        temp = (char*)malloc(sizeof(char) * 20);
                        strncpy(temp, buffer+lindex+1, rindex-lindex-1);
                        v2 = atoi(temp);
                        // get weight of edge
                        weight = atof(buffer+rindex+1);

                        addEdge(graph, v1, v2, weight);

                        addVertexToRoute(graph, route_id, v1);
                        addVertexToRoute(graph, route_id, v2);
                        break;
                    }
                }
                rindex++;
            }
        }
    }
    fclose(fp);
}

void dropGraph(Graph graph){
    JRB node;

    jrb_traverse(node, graph.vertices){
        free(jval_s(node->val));
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

int indegree (Graph graph, int v, int* output){
    JRB tree, node;
    int total = 0;   
    jrb_traverse(node, graph.edges){
       tree = (JRB) jval_v(node->val);
       if (jrb_find_int(tree, v)){
          output[total] = jval_i(node->key);
          total++;
       }                
    }
    return total;   
}

int outdegree (Graph graph, int v, int* output){
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node==NULL) return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree){
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
}

double findShortestPath(Graph g, int s, int t, int *path, int *length){
    /*
    s la key cua vertex bat dau, t la key cua vertex la ket thuc
    */
    double distance[1000], min, w, total;
    int previous[1000]; // array of parents of vertices. 
    int tmp[1000]; // array of vertices on shortest path.
    
    int n, output[100], i, u, v, start;
    Dllist ptr, queue, node;

    if(s == t){
   	    printf("You are where you need to be ^_^!");
   	    return 0;
    }

    for (i=0; i<1000; i++) distance[i] = INF;
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
      
        if (u == t) break;
    
        n = outdegree(g, u, output);
        for(i=0; i<n; i++){
            v = output[i];
            w = getEdgeValue(g, u, v);
            if(distance[v] > distance[u] + w){
                distance[v] = distance[u] + w;
                previous[v] = u;
            }     
            dll_append(queue, new_jval_i(v));
        }
    }

   total = distance[t];
   if(total != INF){
        tmp[0] = t;
        n = 1;              
        while (t != s){
            t = previous[t];
            tmp[n++] = t;
        }
        for (i=n-1; i>=0; i--)
            path[n-i-1] = tmp[i];
        *length = n;         
   }else{
   		printf("There is no path from %s to %s!\n", getVertexNameById(g, s), getVertexNameById(g, t));
   		return 0;
   }
   return total;
}

int main(){
    // load graph from file
    Graph g = createGraph();

    loadFromFile(g, "output.txt");

    // addVertex(g, 10, "Ha Noi");
	// addVertex(g, 15, "HCM");
	// addVertex(g, 23, "Nam Dinh");
	// addVertex(g, 27, "Quang Ninh");
	// addVertex(g, 28, "Hai Phong");
	// addVertex(g, 31, "Nghe An");
	// addVertex(g, 33, "Tay Nguyen");
	// addEdge(g, 10, 15, 2.3);
	// addEdge(g, 15, 23, 4.5);
	// addEdge(g, 27, 28, 4.2);
	// addEdge(g, 28, 31, 3.7);
	// addEdge(g, 31, 33, 3.2);
	// addEdge(g, 10, 31, 2.0);

    int running = 1;

    while(running){
        int ans;

        print_menu();
        scanf("%d", &ans); getchar();

        switch(ans){
            case 1:{
                // finding shortest path
                int v1;
                int v2;
                int length, output[100];

                char name1[100];
                char name2[100];

                printf("Picking up point: ");
                // fflush(stdin);
                fgets(name1, 500, stdin);
                removeNewline(name1);

                v1 = getVertexIdByName(g, name1);
                if(v1 == -1){
                    printf("Invalid picking up point!\n");
                    continue;
                }
                
                printf("Dropping point: ");
                // fflush(stdin);
                fgets(name2, 500, stdin);
                removeNewline(name2);
                v2 = getVertexIdByName(g, name2);
                if(v2 == -1){
                    printf("Invalid dropping point!\n");
                    continue;
                }
                // n is total weights of the shortest path
                double n = findShortestPath(g, v1, v2, output, &length);
                
                printf("Shortest Path: ");
                for(int i=0; i<length-1; i++){
                    printf("%s => ", getVertexNameById(g, output[i]));
                }
                printf("%s\n", getVertexNameById(g, output[length-1]));

                // length is the number of route
                // input is the array of vertices' id
                // output is the array of route
                // Ex: 01 -> 5A -> 21A 
                //int m = getRouteFromPath(g, input, output);
                //printf("Press any button to continue...");
                break;
            }
            case 0:{
                running = 0;
                dropGraph(g);
                printf("Exit program !\n");
                break;
            }
            case 2:{
                printVertices(g);
                break;
            }
            default:{
                printf("Invalid option!\n");
                break;
            }            
        }
    }
    return 0;
}