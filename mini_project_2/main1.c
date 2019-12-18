#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/jrb.h"
#include "utils.c"
#include "libfdr/dllist.h"
#include "libfdr/jrb.c"
#include "libfdr/dllist.c"
#include "libfdr/jval.c"
#define INFINITIVE_VALUE  10000000
#define INF 10000000

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
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
    }
//    else{
//        node->val = new_jval_s(name);
//    }
}

char *getVertexNameById(Graph graph, int id){//Lay ten cua mot ben xe dua theo id cua tuyen xe day (xem output.txt)
    JRB node = jrb_find_int(graph.vertices, id);

    return jval_s(node->val);
}

int getVertexIdByName(Graph graph, char *name){//Lay id cua mot ben xe bang ten cua ben xe day (xem output.txt)
    JRB node;

    jrb_traverse(node, graph.vertices){
        if(strcmp(name, jval_s(node->val)) == 0) return jval_i(node->key);
    }

    return -1;
}


double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
       return INFINITIVE_VALUE;//Khong ton tai edge
    tree = (JRB) jval_v(node->val);//Tao cay JRB co root la val.v cua node tree, tu node co key.i = v1
    node = jrb_find_int(tree, v2);
    if (node==NULL)
       return INFINITIVE_VALUE;//Khong ton tai edge
    else//Co ton tai edge
       return jval_d(node->val);//Tra ve gia tri val.d tuc gia tri double trong
       							//val cua node co key la v2 trong cay JRB co root la 
								// node co key la v1 ma o trong cay graph.edge (cung la cay JRB).
								//Gia tri nay the hien weight cua edge v1v2.
}

void addEdge(Graph graph, int v1, int v2, double weight)
{
     JRB node, tree;
     if (getEdgeValue(graph, v1, v2)==INFINITIVE_VALUE)//Neu chua ton tai eddge
     {
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));//val.d cua node v2 o trong cay JRB con co root la v1
        											 //thuoc cay JRB me graph.edge chinh la weight cua edge v1v2.
     }
}
void addVertexToRoute(Graph graph, char *route_id, int v){
    JRB node = jrb_find_str(graph.routes, route_id);

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
void print_menu(){
	printf("\n----BUSMAP----\n");
    printf("1. Print all bus stops\n");
    printf("2. Find shortest path\n");
    printf("3. Print all vertices of a bus route\n");
    printf("0. Exit\n");
    printf("Your choice: ");
}

void printVertices(Graph graph){
    JRB node;
    printf("Vertices:\n");
    jrb_traverse(node, graph.vertices){
        printf("%d:%s\n", jval_i(node->key), jval_s(node->val));
    }
    printf("\n");
}
void printRoutes(Graph graph){
    JRB node;
    printf("Routes:");
    jrb_traverse(node, graph.routes){
        printf("%s - \n", jval_i(node->key));
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
void getRoutesfromPath(Graph graph, int* output,int length){
	int an[100][100]; // luu route duoi dang so 
	for (int i=0; i<100; i++)
		for (int j=0; j<100; j++) an[i][j]=NULL;
    for (int i=0; i<length-1; i++){
        printf("%s => %s:", getVertexNameById(graph, output[i]), getVertexNameById(graph, output[i+1]));
        JRB node;
        int count1=0, count2=0 ;
        jrb_traverse(node, graph.routes){
        	
            JRB subTree =(JRB)jval_v(node->val);
            JRB subNode1, subNode2;
            int check1=0,check2=0;
            jrb_traverse(subNode1, subTree){
                if (jval_i(subNode1->key)== output[i]){
                    check1=1;
                }
            }
            jrb_traverse(subNode2, subTree){
                if (jval_i(subNode2->key) == output[i+1]){
                    check2=1;
                }
            }
            int k1=getEdgeValue(graph, output[i+1], output[i]);
            int k2=getEdgeValue(graph, output[i], output[i+1]);
            if (check1 ==1 && check2==1 && ((0<k1 && k1<INFINITIVE_VALUE) ||(0<k2 && k2<INFINITIVE_VALUE))) {
                printf("  %s", jval_i(node->key));
                
                an[i][count1]=count2;
                count1++;
            }  
            count2++;
        }
        printf("\n");
    }
    for (int i=0; i<length-1; i++){
    	for (int r=0; r<100; r++)
    		if (an[i][r]!=NULL) printf("%d ", an[i][r]);
    	printf("\n");
    }
    int re[100];
    for (int i=0; i<length-1; i++){
    	int a=i, b=i+1;
    	int check=0;
    	for (int q=0; q<100; q++)
    		if (an[a][q]!=NULL)
    			for (int p=0; p<100; p++)
    				if (an[b][p]!=NULL){
					 	if (an[a][q] == an[b][p]) re[i]=an[b][p];
    					if (an[a][q] != an [b][p]) re[i]=an[a][q];
    					if (an[a][q] == an[b][p] && an[a][q]==re[i-1]) {
							re[i]=re[i-1];
							break;
						}
					}
	}
	re[length-2]=re[length-3];
	for (int i=0; i<length-1; i++) printf("%d  ", re[i]);
	printf("\n");
	/*for (int i=0; i<length-1; i++){
		JRB node;
		printf("%s ==> %s: ", getVertexNameById(graph,output[i]), getVertexNameById(graph,output[i+1]));
		int count=0;
		
		jrb_traverse(node, graph.routes){
			if (count == re[i]) break;
			count++;
		}
		printf("%s\n", jval_i(node->key));
		;
	}*/
	printf("\n");
	int count=0;
	
	while (count<length-1){
		int dem=0;
		printf("%s => ", getVertexNameById(graph,output[count]));
		for (int i=count; i<length-1; i++)
			if (re[i]==re[count]) dem++;
			else break;
		printf("%s: ", getVertexNameById(graph,output[count+dem]));
		int count1=0;
		JRB node;
		jrb_traverse(node, graph.routes){
			if (count1 == re[count]) break;
			count1++;
		}
		printf("%s\n", jval_i(node->key));
		//printf("%d  %d\n", re[count], dem);
		count=count+dem;
	}

	/*for (int i=0; i<length-1; i++){
		JRB node;
		count=0;
		jrb_traverse(node, graph.routes){
			if (count == re[i]) 
		}
	}*/
}
/*int c[100][100], result[100][100];
int check(int i, int j,int *an){
	if (c[i][j]==0) return 0;
	else return 1;
}
int recur(int v, int length, int * an){
	for (int i=0; i<length; i++){
		for (int j=0; j<100; j++){
			if (a[i][j]!=0 && check(i,j)){
				
			}
		}
	}
	
}*/
void loadFromFile(Graph graph, const char *filename){
    FILE *fp = fopen(filename, "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[200];
    char *route_id;
    int flag = -1;
    while(fgets(buffer, 200, fp)){
		removeNewline(buffer);

        if(strcmp(buffer, "# VERTICES") == 0){
            flag = 0;
            continue;//Nhay den vong lap tiep theo luon
        }
        else if(strcmp(buffer, "# ROUTE_ID") == 0){
            flag = 1;
            continue;//Nhay den vong lap tiep theo luon
        }
        else if(strcmp(buffer, "## EDGES") == 0){
            flag = 2;
            continue;//Nhay den vong lap tiep theo luon
        }

        if(flag == 0){ // read vertices
            int index = 0; // index of ':' character
            int id;
            char *verticeName = (char*)malloc(sizeof(char) * 300);
            char verticeId[10];

            while(buffer[index] != '\0'){
                if(buffer[index] == ':'){
                    strncpy(verticeId, buffer, index-1);
                    id = atoi(verticeId);

                    strncpy(verticeName, buffer+index+2, 300*sizeof(char));
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

            // printf("%s\n", buffer);
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
            // free(temp);
        }
    }

    // printVertices(graph);
    fclose(fp);
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

double findShortestPath(Graph graph, int s, int t, int *path, int *length){
    double distance[1000];
    int previous[1000], u, visit[1000];
    
    if(s == t){
    	printf("You are where you need to be ^_^!");
		return 0;	
	}
    
    for (int i=0; i<1000; i++){
        distance[i] = INFINITIVE_VALUE;
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
        int number = outdegree(graph,u,output);
        for (int i =0; i<number; i++) {
            if (visit[output[i]]==0) {
                visit[output[i]] = 1;
                dll_append(queue,new_jval_i(output[i]));
            }
            if ((getEdgeValue(graph,u,output[i])+distance[u])<distance[output[i]]) {
                distance[output[i]]= getEdgeValue(graph,u,output[i])+distance[u];
                previous[output[i]] = u;
            }
        }
    }
    path[0] = t;
    *length = 1;
    int cur = t;
    while (cur != s){
        path[*length] = previous[cur];
        *length = *length+1;
        cur = previous[cur];
    }
    
    return distance[t];
}

void dropGraph(Graph graph){
    JRB node;

    jrb_traverse(node, graph.vertices){
        free(jval_s(node->val));
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

char *getVertex(Graph g, int id)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) 
        return NULL;
     else                
        return jval_s(node->val);
}

int main(){
    // load graph from file
    int i, input[100], s, t;
    Graph g = createGraph();
    loadFromFile(g, "output.txt");
    int running = 1;
    while(running){
        char ans[100];
        print_menu();
		fflush(stdin);
        fgets(ans, 100, stdin);
        removeNewline(ans);
        if(strlen(ans) > 1){
         	printf("Invalid option!\n");
		}else{
		 	switch(ans[0]){
            case '2':{
                 // finding shortest path
	            int v1;
	            int v2;
	            int length=0, output[100];
				char name1[300];
                char name2[300];
                char sure[300];
			    //printf("Fill in the information...\n");
			    //printf("Press ENTER to continue...\n");
				//getchar();
				printf("Picking up point: ");
				fflush(stdin);
				fgets(name1, 300, stdin);
				removeNewline(name1);
				v1 = getVertexIdByName(g, name1);
                if(v1==-1){
					printf("Invalid picking up point!\n");
				 	continue;
			    }
				 
                printf("Dropping point: ");
                fgets(name2, 300, stdin);
               	removeNewline(name2);
                v2 = getVertexIdByName(g, name2);
                if(v2==-1){
                 	printf("Invalid dropping point!\n");
					continue;
				}
                int n;
				n=findShortestPath(g, v2, v1, output, &length);
				printf("The shortest path from %s to %s is:\n", getVertexNameById(g, v1), getVertexNameById(g, v2));
                if(n == INFINITIVE_VALUE){
                 	printf("There is no path from %s to %s!\n", getVertexNameById(g, v1), getVertexNameById(g, v2));
				}else{
				 	for(int i=0; i<length; i++){
				 		if(i == 0){
				 			printf("%s", getVertex(g, output[i]));
						}
				 		else{
				 			printf("=>%s", getVertex(g, output[i]));	
						}
				 	}	
                    printf("\n");
                    for(int i=0; i<length; i++) printf("%d  ", output[i]);
                    printf("\n");
                    getRoutesfromPath(g, output, length);
				 }
				 printf("\nFinished!\n");

                 // n is the number of route
                 // input is the array of vertices' id
                 // output is the array of route
                 // Ex: 01 -> 5A -> 21A 
                 //int m = getRouteFromPath(g, input, output);
//                 printf("Press ENTER to continue...\n");
                 break;
             }
             case '0':{
                 running = 0;
                 dropGraph(g);
                 printf("Exit program !\n");
                 break;
             }
             case '1':
             	printVertices(g);
             	break;
            case '3':{
                printRoutes(g);
                char *route_id = (char*)malloc(sizeof(char) * 10);
                printf("Enter the route_id: ");
                fgets(route_id, 10, stdin);
                removeNewline(route_id);
                printVerticesOfRoute(g, route_id);
                free(route_id);
                break;
            }
			printf("\nFinished!\n");
            
            default:
             	printf("Invalid option!\n");
//             	printf("Press ENTER to continue...\n");
             	break;
        }
         getchar();   
     	}
	}	      
    return 0;
}
