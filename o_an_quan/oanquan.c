#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int quanValue = 5;

typedef struct node {
    int value;
    int nodeType; // 0 mean normal node, 1 mean quan node that has a quan, 2 mean quan node that doesn't have a quan.

    struct node *next;
    struct node *prev;
} Node; 

Node* createNewNode(int value, int nodeType){
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->nodeType = nodeType;
    newNode->value = value;
}

void printTable(Node* n0){
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

void play(Node* table, Node* choosenNode, char direction, int *P1Points){
    Node* nextNode = (direction == 'a') ? choosenNode->next : choosenNode->prev;

    while(choosenNode->value > 0){ // distribute quan to each box.
        nextNode->value += 1;
        choosenNode->value -= 1;
        nextNode = (direction == 'a') ?  nextNode->next : nextNode->prev;
    }

    // eating steps
    while(1){
        if(direction == 'a'){
            if(nextNode->nodeType > 0 || 
            (nextNode->value == 0 && nextNode->next->value == 0 && nextNode->next->nodeType != 1)){ // o tiep theo la o quan hoac 2 o trong tro len thi mat luot
                break;
            }
            else if(nextNode->value == 0 && (nextNode->next->value > 0 || nextNode->next->nodeType == 1)){ // an duoc
                *P1Points += nextNode->next->value;
                if(nextNode->next->nodeType == 1){
                    *P1Points += quanValue;
                    nextNode->next->nodeType = 2;
                }
                nextNode->next->value = 0;

                if(nextNode->next->next->value == 0 && nextNode->next->next->nodeType != 1) nextNode = nextNode->next->next;
            }
            else{ // o dan binh thuong, tiep tuc rai
                choosenNode = nextNode;
                while(choosenNode->value > 0){ // distribute quan to each box.
                    nextNode->value += 1;
                    choosenNode->value -= 1;

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
                *P1Points += nextNode->prev->value;
                if(nextNode->prev->nodeType == 1){
                    
                    *P1Points += quanValue;
                    nextNode->prev->nodeType = 2;
                }
                nextNode->prev->value = 0;

                if(nextNode->prev->prev->value == 0 && nextNode->prev->prev->nodeType != 1) nextNode = nextNode->prev->prev;
            }
            else{ // o dan binh thuong, tiep tuc rai
                choosenNode = nextNode;

                while(choosenNode->value > 0){ // distribute quan to each box.
                    nextNode->value += 1;
                    choosenNode->value -= 1;

                    nextNode = nextNode->prev;
                }
            }
        }
    }

}

int main(){
    srand(time(NULL));

    // Setup table
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
    Node* table = n0;

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


    int number;
    char direction;

    int state = rand() % 2;
    int P1Points = 0, P2Points = 0, borrow = 0;

    Node* choosenNode;

    printf("+----- O AN QUAN -----+\n\n");
    printTable(table);
    printf("\n");

    while(1){
        // check game's state
        if(n0->nodeType == 2 && n6->nodeType == 2 && n0->value == 0 && n6->value == 0){ //end game
            // HET QUAN TOAN DAN KEO VE
            for(Node* i=n0->next; i!=n6; i=i->next) P1Points += i->value;
            for(Node* i=n6->next; i!=n0; i=i->next) P2Points += i->value;

            P1Points -= borrow;
            P2Points += borrow;

            if(P1Points > P2Points) printf("You win !\n");
            else if(P1Points < P2Points) printf("You lose !\n");
            else printf("Draw !\n");

            break;
        }
        else { // still continue
            // check your field
            if(n1->value == 0 && n2->value == 0 && n3->value == 0 && n4->value == 0 && n5->value == 0){ // have no dan left.
                if(P1Points >= 5) P1Points -= 5; // buy dan using points
                else{ // borrow points from the opponent
                    P2Points -= 5;
                    borrow += 5;
                }

                n1->value = 1;
                n2->value = 1;
                n3->value = 1;
                n4->value = 1;
                n5->value = 1;
            }
            // check opponent field
            if(n7->value == 0 && n8->value == 0 && n9->value == 0 && n10->value == 0 && n11->value == 0){
                if(P2Points >= 5) P2Points -= 5;
                else{
                    P1Points -= 5;
                    borrow -= 5;
                }

                n7->value = 1;
                n8->value = 1;
                n9->value = 1;
                n10->value = 1;
                n11->value = 1;
            }
        }

        if(state){ // USER's turn
            // ask for next move
            while(1){
                printf("USER's move: ");
                scanf("%d %c", &number, &direction);

                if(number > 5 || number == 0){
                    printf("Must choose a number between 1 and 5, direction 'a' or 'c'\n");
                    continue;
                }

                switch(number){
                    case 1: choosenNode = n1; break;
                    case 2: choosenNode = n2; break;
                    case 3: choosenNode = n3; break;
                    case 4: choosenNode = n4; break;
                    case 5: choosenNode = n5; break;
                    default: break;
                }
                
                if(choosenNode->value == 0){
                    printf("Your choosen box has no dan left, please choose another one.\n");
                    continue;
                }
                break;            
            }
            // make a move    
            play(table, choosenNode, direction, &P1Points);
        }
        else{ // AI's turn
            while(1){
                number = rand() % 5 + 7;
                direction = (rand() % 2) ? 'a' : 'c';

                switch(number){
                    case 11: choosenNode = n11; break;
                    case 10: choosenNode = n10; break;
                    case 9: choosenNode = n9; break;
                    case 8: choosenNode = n8; break;
                    case 7: choosenNode = n7; break;
                    default: break;
                }
                
                if(choosenNode->value == 0) continue;
                break;            
            }  

            play(table, choosenNode, direction, &P2Points);

            printf("AI's move: %d %c\n", number, direction);
        }

        // switch turn
        state = (state) ? 0 : 1;

        printTable(table);
        printf("USER: %d - AI: %d\n\n", P1Points, P2Points);
    }

    return 0;
}