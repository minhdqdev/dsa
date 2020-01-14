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

    if(node == NULL) jrb_insert_int(graph.vertices, id, new_jval_s(name));
    else node->val = new_jval_s(name);
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
    JRB node = jrb_find_str(graph.routes, route_id);

    if(node == NULL){
        JRB s = make_jrb();
        node = jrb_insert_str(graph.routes, route_id, new_jval_v(s));
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
    else{
        subNode->val.d = weight;        
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
	printf("\n+ ---- BUS MAP ---- +\n");
    printf("1. Find shortest path\n");
    printf("2. Print all vertices\n");
    printf("3. Print all vertices of route\n");
    printf("0. Exit\n");
    printf("Your choice: ");
}

void printVertices(Graph graph){
    JRB node;
    printf("\nVertices: \n");
    jrb_traverse(node, graph.vertices){
        printf("%d : %s\n", jval_i(node->key), jval_s(node->val));
    }
    printf("\n");
}

void printVerticesOfRoute(Graph graph, char *route_id){
    JRB node = jrb_find_str(graph.routes, route_id);

    if(node == NULL){
        printf("Can't find route %s.\n", route_id);
        return;
    }

    JRB subTree = (JRB)jval_v(node->val);
    JRB subNode;
    printf("Vertices of route %s: ", route_id);
    jrb_traverse(subNode, subTree){
        printf("%s - ", getVertexNameById(graph, jval_i(subNode->key)));
    }
    printf("\n");
}

void printRoutes(Graph graph){
    JRB node;

    printf("Routes: ");
    jrb_traverse(node, graph.routes){
        printf("%s - ", jval_s(node->key));
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
            char *verticeId = (char*)malloc(sizeof(char) * 10);

            while(buffer[index] != '\0'){
                if(buffer[index] == ':'){
                    strncpy(verticeId, buffer, index-1);
                    id = atoi(verticeId);

                    strncpy(verticeName, buffer+index+2, sizeof(char) * 500);
                    addVertex(graph, id, verticeName);
                    // printf("%d - %s\n", id, verticeName);
                    break;
                }
                index++;
            }   

            // free(verticeName);
            // free(verticeId);
        } 
        else if(flag == 1){ // read route_id
            route_id = (char*)malloc(sizeof(char) * 20);
            strncpy(route_id, buffer, sizeof(char) * 20);
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

                        // printf("W: %d\n", weight);

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

double findShortestPath(Graph graph, int s, int t, int *path, int *length){
    double distance[1000], total;
    int previous[1000], u, visit[1000], tmp[1000];
    int i, number;
    
    if(s == t){
    	printf("You are where you need to be ^_^!");
		return 0;	
	}
    
    for (int i=0; i<1000; i++){
        distance[i] = INF;
        visit[i] = 0;
        previous[i] = 0;
    }
    distance[s] = 0;
    previous[s] = s;
    visit[s] = 1;
    
    Dllist ptr, queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(s));
    
    // Duyet Queue
    while (!dll_empty(queue)){
        node = dll_first(queue);
        int u = jval_i(node->val);
        dll_delete_node(node);
        int output[100];
        number = outdegree(graph,u,output);
        for (int i =0; i<number; i++) {
            if (visit[output[i]]==0) {
                visit[output[i]] = 1;
                dll_append(queue,new_jval_i(output[i]));
            }
            if ((getEdgeValue(graph,u,output[i])+distance[u])<distance[output
                                                                       [i]]) {
                distance[output[i]]= getEdgeValue(graph,u,output[i])+distance[u];
                previous[output[i]] = u;
            }
        }
    }
   total = distance[t];//Gan gia tri tu s den t cho bien total
   if (total != INF)//Neu total khac INFINITIVE VALUE
   {
	   //Luu cac vertex tren duong tu s den v da chon vao trong mang temp, nhung luu nguoc tu t
       tmp[0] = t;
       number = 1;              
       while (t != s)
       {
             t = previous[t];
             tmp[number++] = t;
       }
       for (i=number-1; i>=0; i--)//Traverse nguoc lai tmp la ra mang path: con duong ngan nhat tu s den t theo chieu xuoi
           path[number-i-1] = tmp[i];
       *length = number;//length la tong so vertices trong da traverse qua tren con duong ngan nhat tu s toi t          
   }
   return total;//Tra ve total - khoang cach ngan nhat tu s den t
}

int getRoutesFromPath(Graph graph, int* output, int length){
    int numOfRoutes = 0;
    char routeNameList[100][10];

    Dllist listOfRoutes = new_dllist();

    for(int i=0; i<length-1; i++){
        JRB candidateRoutes = make_jrb();

        JRB node;
        jrb_traverse(node, graph.routes){
            JRB subTree = (JRB)jval_v(node->val);
            JRB subNode;
            int check1 = 0, check2 = 0;

            jrb_traverse(subNode, subTree){
                if(jval_i(subNode->key) == output[i]) check1 = 1;
                else if(jval_i(subNode->key) == output[i+1]) check2 = 1; 

                if(check1 && check2) break;
            }

            if(check1 && check2){ 
                JRB a = jrb_find_int(graph.edges, output[i]);
                JRB subTree = (JRB)jval_v(a->val);
                JRB b = jrb_find_int(subTree, output[i+1]);

                if(b != NULL){ // found a candidate route
                    jrb_insert_str(candidateRoutes, jval_s(node->key), new_jval_i(1));
                }
            }
        }
        dll_append(listOfRoutes, new_jval_v(candidateRoutes));

        // jrb_traverse(node, candidateRoutes){
        //     char* routeName = jval_s(node->key);
        //     printf("%s ", routeName);
        // }
        // printf("\n");
    }

    int n = 0;
    char l[100][10];
    
    Dllist node = dll_first(listOfRoutes);
    JRB sub = (JRB)jval_v(node->val);
    JRB s;
    jrb_traverse(s, sub){
        strcpy(l[n++], jval_s(s->key));
    }

    // printf("n: %d\n", n);

    for(Dllist nd=node->flink; nd!=listOfRoutes; nd=nd->flink){
        int m = 0;
        char r[100][10];

        sub = (JRB)jval_v(nd->val);

        jrb_traverse(s, sub) strcpy(r[m++], jval_s(s->key));

        // printf("m: %d\n", m);

        // get intersection
        int numIntersection = 0;
        char k[100][10];
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(strcmp(l[i], r[j]) == 0){
                    strcpy(k[numIntersection++], l[i]);
                }
            }
        }

        if(numIntersection == 0){ // found a route
            // printf("Route: %s\n", l[0]);
            strcpy(routeNameList[numOfRoutes++], l[0]);

            for(int i=0; i<m; i++){
                strcpy(l[i], r[i]);
            }
            n = m;
        }
        else{
            // l = k;
            for(int i=0; i<numIntersection; i++){
                strcpy(l[i], k[i]);
            }
            n = numIntersection;
        }
    }
    
    strcpy(routeNameList[numOfRoutes++], l[0]);

    printf("The routes you have to take is: \n");
    printf("%s", routeNameList[0]);
    for(int i=1; i<numOfRoutes; i++){
        printf(" -> %s", routeNameList[i]);
    }
    printf("\n");


    return numOfRoutes;
}

int main(){
    Graph g = createGraph();

    loadFromFile(g, "bus_data.txt");

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
                int length=0, output[100];

                char name1[300];
                char name2[300];
                char temp[300];
                char sure[300];
                printf("Fill in the information...\n");
                printf("Press ENTER to continue...\n");
                getchar();
                printf("Picking up point: ");
                fflush(stdin);
                fgets(name1, 300, stdin);
                removeNewline(name1);
                strip(name1, temp);
                strcpy(name1, temp);

                v1 = getVertexIdByName(g, name1);
                if(v1 == -1){
                    printf("Invalid picking up point!\n");
                    continue;
                }
                
                printf("Dropping point: ");
                //fflush(stdin);
                fgets(name2, 300, stdin);
                removeNewline(name2);
                strip(name2, temp);
                strcpy(name2, temp);
                v2 = getVertexIdByName(g, name2);
                
                //printf("%d:%s %d:%s!",v1, name1, v2, name2);
                if(v2==-1){
                    printf("Invalid dropping point!\n");
                    continue;
                }
                
                // printf("%d:%s %d:%s\n",v1, name1, v2, name2);
                // n is the number of vertices
                // output is the array of vertices' id (or name)
                // Ex: 01 -> 04 -> 26
                int n;
                n = findShortestPath(g, v1, v2, output, &length);
                // printf("%d\n", n);
                printf("The shortest path from %s to %s is:\n", getVertexNameById(g, v1), getVertexNameById(g, v2));
                if(n == INF){
                    printf("There is no path from %s to %s!\n", getVertexNameById(g, v1), getVertexNameById(g, v2));
                }
                else{
                    printf("%s", getVertexNameById(g, output[0]));
                    for(int i=1; i<length; i++){
                        printf(" -> %s", getVertexNameById(g, output[i]));	
                    }	
                    printf("\n\n");

                    // for(int i=0; i<length; i++) printf("%d  ", output[i]);
                    // printf("\n");

                    // char routes[100][10];
                    
                    int numOfRoutes = getRoutesFromPath(g, output, length);
                
                    
                    
                }
                printf("\nFinished!\n");

                // n is the number of route
                // input is the array of vertices' id
                // output is the array of route
                // Ex: 01 -> 5A -> 21A 
                //int m = getRouteFromPath(g, input, output);
                // printf("Press ENTER to continue...\n");
                break;
            }
            case 2:{
                printVertices(g);
                break;
            }
            case 3:{
                printRoutes(g);
                char *route_id = (char*)malloc(sizeof(char) * 10);

                printf("Enter the route_id: ");
                fgets(route_id, 10, stdin);
                removeNewline(route_id);

                printVerticesOfRoute(g, route_id);

                free(route_id);
                break;
            }
            case 0:{
                running = 0;
                dropGraph(g);
                printf("Exit program !\n");
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