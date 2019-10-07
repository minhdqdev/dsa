/*
AI Project; Vietnam tradional game "o an quan" using minimax algorithm 

Author; minhdq99hp

BUG; khi het dan tren san thi printtable van hien la ko co dan.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

const int quanValue = 5; // it's regularly 5 or 10.
const int depthSearch = 7; // >=10 is not good for your machine
const int depthSearch2 = 2;

typedef struct move {
    int number;
    int direction; //1 - anti-clockwise, 0 - clockwise.
} Move;

typedef struct node {
    int value;
    int nodeType; // 0 mean normal node, 1 mean quan node that has a quan, 2 mean quan node that doesn't have a quan.

    struct node *next;
    struct node *prev;
} Node; 

Node *createNewNode(int value, int nodeType){
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->nodeType = nodeType;
    newNode->value = value;
}

Node *getNode(Node *table, int number){
    Node* chosenNode = table;
    for(int i=0; i<number; i++) chosenNode = chosenNode->next;
    return chosenNode;
}

void printTable(Node *n0){
    char a[12][3];

    if(n0->value) sprintf(a[0], "%d", n0->value);
    else strcpy(a[0], " ");

    int n0hasQuan = (n0->nodeType == 1) ? 1 : 0;
    int n6hasQuan = 0;

    int k = 1;
    for(Node* i=n0->next; i!=n0; i=i->next){
        if(i->value) sprintf(a[k], "%d", i->value);
        else strcpy(a[k], " ");

        if(k == 6) n6hasQuan = (i->nodeType == 1) ? 1 : 0; 
        k++;
    }

    printf("    11 10  9  8  7  6 \n");
    printf("+--+--------------+--+\n");
    printf("|%2c|%2s|%2s|%2s|%2s|%2s|%2c|\n", n0hasQuan ? '*' : ' ',a[11], a[10], a[9], a[8], a[7], n6hasQuan ? '*' : ' ');
    printf("|%2s|--------------|%2s|\n", a[0], a[6]);
    printf("|  |%2s|%2s|%2s|%2s|%2s|  |\n", a[1], a[2], a[3], a[4], a[5]);
    printf("+--+--------------+--+\n");
    printf("  0  1  2  3  4  5\n");
}

void saveTableState(Node *table, int saved[]){
    Node* cur = table;
    for(int i=0; i<12; i++){
        saved[i] = cur->value;
        cur = cur->next;
    }
    saved[12] = table->nodeType;
    saved[13] = table->next->next->next->next->next->next->nodeType;
}

void loadTableState(Node *table, int saved[]){
    Node *cur = table;
    for(int i=0; i<12; i++){
        cur->value = saved[i];
        cur = cur->next;
    }
    table->nodeType = saved[12];
    table->next->next->next->next->next->next->nodeType = saved[13];        
}

int max(int a, int b){ return (a >= b) ? 1 : 0; }

void play(Node *table, Move move, int *P1Points, int *P2Points, int *borrow){
    int *p; // use for eating step
    // borrow step
    if(move.number < 6){ // USER's turn
        if(table->next->value == 0 && table->next->next->value == 0 && table->next->next->next->value == 0 && table->next->next->next->next->value == 0 && table->next->next->next->next->next->value == 0){ // have no dan left.
            if(*P1Points >= 5) *P1Points -= 5; // buy dan using points
            else{ // borrow points from the opponent
                *P2Points -= 5;
                *borrow += 5;
            }

            Node *cur = table->next;
            for(int i=0; i<5; i++){
                cur->value = 1;
                cur = cur->next;
            }
        }

        p = P1Points;
    }
    else{
        if(table->prev->value == 0 && table->prev->prev->value == 0 && table->prev->prev->prev->value == 0 && table->prev->prev->prev->prev->value == 0 && table->prev->prev->prev->prev->prev->value == 0){
            if(*P2Points >= 5) *P2Points -= 5;
            else{
                *P1Points -= 5;
                *borrow -= 5;
            }

            Node *cur = table->prev;
            for(int i=11; i>6; i--){
                cur->value = 1;
                cur = cur->prev;
            }
        }

        p = P2Points;
    }

    Node* chosenNode = table;
    for(int i=0; i<move.number; i++) chosenNode = chosenNode->next;
    
    Node* nextNode = (move.direction == 1) ? chosenNode->next : chosenNode->prev;

    while(chosenNode->value > 0){ // distribute quan to each box.
        nextNode->value += 1;
        chosenNode->value -= 1;
        nextNode = (move.direction == 1) ?  nextNode->next : nextNode->prev;
    }

    // eating steps
   
    while(1){
        if(move.direction == 1){
            if(nextNode->nodeType > 0 || 
            (nextNode->value == 0 && nextNode->next->value == 0 && nextNode->next->nodeType != 1)){ // o tiep theo la o quan hoac 2 o trong tro len thi mat luot
                break;
            }
            else if(nextNode->value == 0 && (nextNode->next->value > 0 || nextNode->next->nodeType == 1)){ // an duoc
                *p += nextNode->next->value;
                if(nextNode->next->nodeType == 1){
                    *p += quanValue;
                    nextNode->next->nodeType = 2;
                }
                nextNode->next->value = 0;

                if(nextNode->next->next->value == 0 && nextNode->next->next->nodeType != 1) nextNode = nextNode->next->next;
            }
            else{ // o dan binh thuong, tiep tuc rai
                chosenNode = nextNode;
                while(chosenNode->value > 0){ // distribute quan to each box.
                    nextNode->value += 1;
                    chosenNode->value -= 1;

                    nextNode = nextNode->next;
                }
            }
        }
        else{
            if(nextNode->nodeType > 0 || 
            (nextNode->value == 0 && nextNode->prev->value == 0 && nextNode->prev->nodeType != 1)){ // o tiep theo la o quan hoac 2 o trong tro len thi mat luot
                break;
            }
            else if(nextNode->value == 0 && (nextNode->prev->value > 0 || nextNode->prev->nodeType == 1)){ // an duoc
                *p += nextNode->prev->value;
                if(nextNode->prev->nodeType == 1){
                    *p += quanValue;
                    nextNode->prev->nodeType = 2;
                }
                nextNode->prev->value = 0;

                if(nextNode->prev->prev->value == 0 && nextNode->prev->prev->nodeType != 1) nextNode = nextNode->prev->prev;
            }
            else{ // o dan binh thuong, tiep tuc rai
                chosenNode = nextNode;

                while(chosenNode->value > 0){ // distribute quan to each box.
                    nextNode->value += 1;
                    chosenNode->value -= 1;

                    nextNode = nextNode->prev;
                }
            }
        }
    }

}

int isMovesleft(Node *table){
    /*
        Check xem o quan con quan va dan hay khong.
    */
    if(table->value == 0 && table->nodeType == 2 &&
       table->next->next->next->next->next->next->value == 0 &&
       table->next->next->next->next->next->next->nodeType == 2) return 0;
    return 1;
}

int evaluate(Node *table, int P1Points, int P2Points, int borrow){
    /*
        Evaluate the value of game's state.
    */

    // If there is no move left, "HET QUAN TOAN DAN KEO VE"
    if(!isMovesleft(table)) for(Node *i=table->next, *j=getNode(table, 7); j!=table; i=i->next, j=j->next){ P1Points += i->value; P2Points += j->value;}
    return (P1Points - borrow) - (P2Points + borrow);
}

int miniMax(Node *table, int depth, int isMax, int P1Points, int P2Points, int borrow){
    int score = evaluate(table, P1Points, P2Points, borrow);

    if(!isMovesleft(table) || depth == depthSearch) return score;

    Move move;
    int best;
    int saved[14];

    // maximizer's move
    // In this case, USER is maximizer
    if(isMax){
        best = -10000;

        // try all the possible moves
        for(int number=1; number<6; number++){
            // check whether if this number is available
            if(getNode(table, number)->value == 0) continue;

            move.number = number;
            for(int direction=0; direction<2; direction++){
                move.direction = direction;
                
                // save the state
                saveTableState(table, saved);

                // make a move
                play(table, move, &P1Points, &P2Points, &borrow);
                best = max(best, miniMax(table, depth+1, !isMax, P1Points, P2Points, borrow));

                // undo the move - load the saved state
                loadTableState(table, saved);    
            }
        }
    }
    // minimizer's move - AI
    else{
        best = 10000;

        // try all the possible moves
        for(int number=7; number<12; number++){
            // check whether if this number is available
            if(getNode(table, number)->value == 0) continue;

            move.number = number;
            for(int direction=0; direction<2; direction++){
                move.direction = direction;
                
                // save the state
                saveTableState(table, saved);
                // make a move
                play(table, move, &P1Points, &P2Points, &borrow);

                best = max(best, miniMax(table, depth+1, !isMax, P1Points, P2Points, borrow));

                // undo the move - load the saved state
                loadTableState(table, saved);    
            }
        }
    }
    return best;
}

int miniMax2(Node *table, int depth, int isMax, int P1Points, int P2Points, int borrow){
    int score = evaluate(table, P1Points, P2Points, borrow);

    if(!isMovesleft(table) || depth == depthSearch2) return score;

    Move move;
    int best;
    int saved[14];

    // maximizer's move
    // In this case, USER is maximizer
    if(isMax){
        best = -10000;

        // try all the possible moves
        for(int number=1; number<6; number++){
            // check whether if this number is available
            if(getNode(table, number)->value == 0) continue;

            move.number = number;
            for(int direction=0; direction<2; direction++){
                move.direction = direction;
                
                // save the state
                saveTableState(table, saved);

                // make a move
                play(table, move, &P1Points, &P2Points, &borrow);
                best = max(best, miniMax(table, depth+1, !isMax, P1Points, P2Points, borrow));

                // undo the move - load the saved state
                loadTableState(table, saved);    
            }
        }
    }
    // minimizer's move - AI
    else{
        best = 10000;

        // try all the possible moves
        for(int number=7; number<12; number++){
            // check whether if this number is available
            if(getNode(table, number)->value == 0) continue;

            move.number = number;
            for(int direction=0; direction<2; direction++){
                move.direction = direction;
                
                // save the state
                saveTableState(table, saved);
                // make a move
                play(table, move, &P1Points, &P2Points, &borrow);

                best = max(best, miniMax(table, depth+1, !isMax, P1Points, P2Points, borrow));

                // undo the move - load the saved state
                loadTableState(table, saved);    
            }
        }
    }
    return best;
}

Move findBestMinMove(Node *table, int P1points, int P2points, int borrow){
    int bestVal = 10000;
    Move bestMove, move;
    int saved[14];
    // evaluate all possible moves
    for(int number=7; number<12; number++){
        // check whether if this number is available
        if(getNode(table, number)->value == 0) continue;

        
        move.number = number;
        for(int direction=0; direction<2; direction++){
            move.direction = direction;
            // save the state
            saveTableState(table, saved);
            
            // make a move
            play(table, move, &P1points, &P2points, &borrow);
            
            // compute evaluation for this move
            int moveVal = miniMax2(table, 0, 0, P1points, P2points, borrow);

            // undo the move
            loadTableState(table, saved);
            // update the bestMove
            if(moveVal < bestVal){
                memcpy(&bestMove, &move, sizeof(move));
                bestVal = moveVal;
            }
        }
    }

    return bestMove;
}

Move findBestMaxMove(Node *table, int P1points, int P2points, int borrow){
    int bestVal = -10000;
    Move bestMove, move;
    int saved[14];
    // evaluate all possible moves
    for(int number=1; number<6; number++){
        // check whether if this number is available
        if(getNode(table, number)->value == 0) continue;

        
        move.number = number;
        for(int direction=0; direction<2; direction++){
            move.direction = direction;
            // save the state
            saveTableState(table, saved);
            
            // make a move
            play(table, move, &P1points, &P2points, &borrow);
            
            // compute evaluation for this move
            int moveVal = miniMax(table, 0, 1, P1points, P2points, borrow);

            // undo the move
            loadTableState(table, saved);
            // update the bestMove
            if(moveVal > bestVal){
                memcpy(&bestMove, &move, sizeof(move));
                bestVal = moveVal;
            }
        }
    }

    return bestMove;
}

void freeTable(Node *table){
    Node* freeNode = table->next;
    Node* nextNode = table->next;

    while(nextNode != table){
        nextNode = freeNode->next;
        free(freeNode);
        freeNode = nextNode;
    }
    free(table);
}

Node *createNewTable(){
    Node* n0 = createNewNode(0, 1);
    Node* n1 = createNewNode(5, 0);
    Node* n2 = createNewNode(5, 0);
    Node* n3 = createNewNode(5, 0);
    Node* n4 = createNewNode(5, 0);
    Node* n5 = createNewNode(5, 0);
    Node* n6 = createNewNode(0, 1);
    Node* n7 = createNewNode(5, 0);
    Node* n8 = createNewNode(5, 0);
    Node* n9 = createNewNode(5, 0);
    Node* n10= createNewNode(5, 0);
    Node* n11= createNewNode(5, 0);
 
    n0->next = n1;
    n0->prev = n11;
    n1->next = n2;
    n1->prev = n0;
    n2->next = n3;
    n2->prev = n1;
    n3->next = n4;
    n3->prev = n2;
    n4->next = n5;
    n4->prev = n3;
    n5->next = n6;
    n5->prev = n4;
    n6->next = n7;
    n6->prev = n5;
    n7->next = n8;
    n7->prev = n6;
    n8->next = n9;
    n8->prev = n7;
    n9->next = n10;
    n9->prev = n8;
    n10->next = n11;
    n10->prev = n9;
    n11->next = n0;
    n11->prev = n10;

    return n0;
}

int main(){
    srand(time(NULL));
    Node *table = createNewTable();

    Move move;

    int state = rand() % 2;
    int P1Points = 0, P2Points = 0, borrow = 0;

    Node* chosenNode;

    printf("+----- O AN QUAN -----+\n\n");
    printTable(table);
    printf("\n");

    while(1){
        // check game's state
        if(table->nodeType == 2 && getNode(table, 6)->nodeType == 2 && table->value == 0 && getNode(table, 6)->value == 0){ //end game
            // HET QUAN TOAN DAN KEO VE
            for(Node *i=table->next, *j=getNode(table, 7); j!=table; i=i->next, j=j->next){ P1Points += i->value; P2Points += j->value;}

            P1Points -= borrow;
            P2Points += borrow;

            if(P1Points > P2Points) printf("You win !\n");
            else if(P1Points < P2Points) printf("You lose !\n");
            else printf("Draw !\n");

            break;
        }

        if(state){ // USER's turn
            move = findBestMaxMove(table, P1Points, P2Points, borrow);
            play(table, move, &P1Points, &P2Points, &borrow);
            printf("AI_1's move: %d %d\n", move.number, move.direction);
        }
        else{ // AI's turn
            move = findBestMinMove(table, P1Points, P2Points, borrow);
            play(table, move, &P1Points, &P2Points, &borrow);
            printf("AI_2's move: %d %d\n", move.number, move.direction);
        }

        // switch turn
        state = (state) ? 0 : 1;

        printTable(table);
        printf("AI_1: %d - AI_2: %d\n\n", P1Points, P2Points);
    }

    free(table);

    return 0;
}