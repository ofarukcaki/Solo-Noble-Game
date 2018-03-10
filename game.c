/*
 * Ömer Faruk Çakı
 * 150117821
 * Marmara University - CSE
 * 09.03.2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// class olustur
struct node{
    int peg;            // 1 or 0
    char label[3];      // Coordinate
    struct node *next;  // Next nodwe
    struct node *child; // Child node
    int header;
};

struct node * newNode(){
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->next = NULL;
    new->child = NULL;
    new->label[0] = new->label[1] = new->label[3] = 0;
    new->peg = 0;
    return new;
}

int isHeader(struct node * head,char *label,int n){
    struct node * tmp = head;
    if(strcmp(tmp->label,label) == 0) return 1;  // Eger head ise 1 dondur
    while( tmp != NULL ){
        struct node * tmp2 = tmp;
        while(tmp2 != NULL){
            if( (strcmp(tmp2->label,label) == 0) && tmp2->header == 1) return 1;
            if( (strcmp(tmp2->label,label) == 0) && tmp2->header == 0) return 0;
            tmp2 = tmp2->child;
        }
        tmp = tmp->next;
    }
    return 0;
}

void printChars(int n){     // n: number of corresponding chars / A B C etc.
    int i;
    printf("    ");           // Space for the Numbers column
    for(i=65;i<n+65;i++){
        printf("%c ",i);
    }
//    printf("\n    ");
//    for(i=65;i<n+65;i++){
//        printf("- ");
//    }
    printf("\n");
}

void push(struct node * head, struct node * gelen){
    struct node * iter = head;
    while (iter->next != NULL){
        iter = iter->next;
    }
    iter->next = gelen;
}

void pushChild(struct node * head, struct node * gelen){
    struct node * iter = head;
    while (iter->child != NULL){
        iter = iter->child;
    }
    iter->child = gelen;
}

struct node * installHeader(struct node *head,int n){
    if(head == NULL){
        head = newNode();
        head->child = NULL;
        head->label[0] = 65;
        head->label[1] = 49;
        head->label[2] = '\0';
        head->peg = 1;
        head->header = 1;
        head->next = NULL;
    }
    int i;
    for (i = 0; i < n-1; i++) {
        struct node * new = newNode();
        new->peg = 1;
        new->label[0] = 65+i+1;
        new->label[1] = 49;     //49 = 1
        new->label[2] = '\0';
        new->next = NULL;
        new->child = NULL;
        new->header = 1;
        push(head,new);
    }
    return head;
}

struct node * installChilds(struct node * head,int n){
    int i,j;
    struct node * tmp = head;
    for(i=0;i<n;i++){
        for(j=0;j<n-1;j++){
            struct node * new = newNode();
            new->label[0] = 65+i;
            new->label[1] = 49+j+1;
            new->label[2] = '\0';
            new->next = NULL;
            new->peg = 1;
            new->child = NULL;
            pushChild(tmp,new);
        }
        tmp = tmp->next;
    }
    return head;
}
// Delete node by provided label
struct node * deleteNode(struct node * head, char *label,int n){
    // Eger silinecek node header ise(node->header ==1) sil ve childin nextine nexti bagla
    if(strcmp(label,"A1") == 0){
        struct node * deleted = head;
        head = head->child;
        head->next = deleted->next;
        head->header = 1;
//        free(deleted);
        return head;
    }
    struct node * temp = head;

    if(strcmp(head->label,label) == 0 && head->child != NULL){ // eger ilk head node silinecek ise
        struct node * deleted = head;
        head = head->child;
        head->next = deleted->next;
        return head;
    }
    if(strcmp(head->label,label) == 0 && head->child == NULL){
        head = head->next;
        return head;
    }


    if(isHeader(head,label,n) == 1){  // eger silinecek node headerda ise
        while(temp != NULL){
            // Eger child varsa
            if(strcmp(temp->next->label,label) == 0 && temp->next->child != NULL){
                struct node * deleted = temp->next;
                temp->next = temp->next->child;
                temp->next->header = 1;
                temp->next->next = deleted->next;
                deleted = NULL;
                return head;
            }
                // eger child yoksa
            else if(strcmp(temp->next->label,label) == 0 && temp->next->child == NULL){
                temp->next = temp->next->next;
                return head;
            }
            temp = temp->next;
        }
    }else{      // If it is not a header node
        struct node *tmp = head;
        while (tmp != NULL){
            if(tmp->label[0] == label[0]){  //Eger bu kolonda ise
                struct node * temp2 = tmp;
                while(temp2 != NULL){
                    if(temp2->child->label[1]  == label[1]){ // Node which is going to be deleted
                        struct node * deleted = temp2->child;
                        temp2->child = temp2->child->child;
//                        free(deleted);
                        return head;
                    }
                    temp2 = temp2->child;
                }
            }
            tmp = tmp->next;
        }
    }

    // Eger child node silinecek ise onceki-> child = sonraki
    return head;
}

struct node * deleteMiddleFour(struct node * head, int n){
    char *label = malloc(20);
    int x,y;
    for(x=0;x<2;x++){
        for(y=0;y<2;y++){
            label[0] = 65+(n/2)-1+y;
            label[1] = 49+(n/2)-1+x;
//            printf("_%s_ ",label);
            deleteNode(head,label,n);

        }
    }
    return head;
}

struct node * returnPlace(struct node * head,char *label){
    struct node * tmp =head;
    while(tmp != NULL){
        struct node *tmp2 = tmp;
        while (tmp2 != NULL){
            if( strcmp(tmp2->label,label) == 0 ) return tmp2;
            tmp2 = tmp2->child;
        }
        tmp = tmp->next;
    }
}
// eger node varsa 1 yoksa 0 dondur
int exist(struct node * head,char * label){
    int sonuc = 0;
    struct node * tmp = head;
    while (tmp != NULL){
        struct node * tmp2 = tmp;
        while(tmp2 != NULL){
            if(strcmp(label,tmp2->label) == 0)
                sonuc = 1;
            tmp2 = tmp2->child;
        }
        tmp = tmp->next;
    }
    return sonuc;
}

void table(struct node * head, int n){
    printChars(n);
    int yStart = 49;
    int xStart = 'A';
    int i,j;
    char *label = malloc(20);
//    char *label = (char*)malloc(2* sizeof(char));
    for(i=0;i<n;i++){
        printf("%2d| ",i+1);
        for(j=0;j<n;j++){
            label[0] = xStart+j;
            label[1] = yStart+i;
            if(exist(head,label)){
                printf("X ");
            } else{
                printf("  ");
            }
//            free(label);
        }
        printf("\n");
    }
};

int possible(struct node * head, char *label,int n){
    printf("\nPossible hit location(s): ");
    if(exist(head,label) == 0) return -1;  // No such node
    int x=0;
    // Yukariyi kontrol et
//    char * check = malloc(20);
    char * check = (char*)malloc(2* sizeof(char));
    strcpy(check,label);
    check[1] = (int)label[1]-1;
    if( exist(head,check) == 1){
        check[1] = (int)check[1]-1;
        if(exist(head,check) == 0 && (int)check[1] <=48+n && (int)check[1] > 48 ){
            printf("%s, ",check);
            x++;
//            free(check);
        }
    }

    // Asagiyi kontrol et
    check[0] = label[0];
    check[1] = (int)label[1]+1;
    check[2] = '\0';
    if( exist(head,check) == 1){
        check[1] = (int)check[1]+1;
        if(exist(head,check) == 0 && (int)check[1] <=48+n && (int)check[1] > 48 ){
            printf("%s, ",check);
            x++;
//            free(check);
        }
    }

    // Solu kontrol et
    check[1] = label[1];
    check[0] = (int)label[0]-1;
    check[2] = '\0';
    if( exist(head,check) == 1 ){
        check[0] = (int)check[0]-1;
        if(exist(head,check) == 0 && (int)check[0] <=64+n && (int)check[0] > 64 ){
            printf("%s, ",check);
            x++;
//            free(check);
        }
    }

    // Sagi kontrol et
    check[1] = label[1];
    check[0] = (int)label[0]+1;
    check[2] = '\0';
    if( exist(head,check) == 1){
        check[0] = (int)check[0]+1;
        if(exist(head,check) == 0 && (int)check[0] <=64+n && (int)check[0] > 64 ){
            printf("%s, ",check);
            x++;
//            free(check);
        }
    }
    if(x==0){
        printf("None\n");
        return 0;
    }
    printf("\n");
    return 1;
}

struct node * returnHeader(struct node *head, char * label){
    struct node * t = head;
    while(t != NULL){
        if(t->label[0] == label[0]){
            return t;
        }
        t = t->next;
    }
    return 0;
}

struct node * returnPrevHeader(struct node * head, char *label){  // Return adress of previos header of given column
    struct node * t = head;
    while(t->next != NULL){
        if(t->next->label[0] == label[0]){
            return t;
        }
        t = t->next;
    }
    return 0;
}

struct node * addToColumn(struct node * head, char *label){
    struct node * new = newNode();
    new->peg = 1;
    strcpy(new->label,label);
    struct node * t = head;

    if(label[0] == 'A'){
        if( (int)head->label[1] > (int)label[1]){
            new->next = head->next;
            new->child = head;
            new->header = 1;
            head->header = 1;
            head = new;
            return head;
        }
    }

    while(t != NULL){
        if(label[0] == t->label[0]){  // bu kolonda ise
            if( (int)label[1] < (int)t->label[1]){   // Eger kolonun basina eklenmesi gerekiyorsa
                if(t != head) returnPrevHeader(head,t->label)->next = new;
                new->next = t->next;
                new->child = t;
                new->header = 1;
                t->header = 0;
                t->next = NULL;
                return head;
            }else{
                struct node * t2 = t;
                while(t2 != NULL){
                    if(t2->child == NULL){
                        t2->child = new;
                        return head;
                    }else if( (int)t2->child->label[1] > (int)label[1] ){
                        new->child = t2->child;
                        t2->child = new;
                        return head;
                    }

                    t2 = t2->child;
                }
            }
        }else if( t->next == NULL && (int)label[0] > (int)t->label[0] ){
            t->next = new;
            new->header = 1;
            new->next,new->child = NULL;
            return head;
        }else if( (int)label[0] < t->next->label[0] ){  // o kolon mevcut degil ise
            new->next = t->next;
            t->next = new;
            new->header = 1;
            return head;
        }

        t = t->next;
    }
    return head;
}

struct node * move(struct node * head, char *l1, char *l2, int n){
    head = deleteNode(head,l1,n);

    char *tmp = (char*)malloc(2* sizeof(char));
    strcpy(tmp,l1);

    if(l1[0] == l2[0]){         // Eger nodlar ust uste ise
        if( (int)l1[1] < (int)l2[1] ){      // 49 < 51  yukaridan asagiya  - B1->B3
                        tmp[1] = (int)l1[1]+1;
//            printf("==%s==\n",tmp);
//            returnPlace(head,tmp)->label[1] = l2[1];
            head = deleteNode(head,tmp,n);
        }else{
            int k = (int)l1[1]-1;
            tmp[1] = k;
//            returnPlace(head,tmp)->label[1] = l2[1];
            head = deleteNode(head,tmp,n);
        }

//    }else if(l1[1] == l2[1]){   // Eger node'lar yatayda iseler
    }else{   // Eger node'lar yatayda iseler
        if( (int)l1[0] < (int)l2[0] ){
            tmp[0] = (int)l1[0]+1;
            head = deleteNode(head,tmp,n);
        }else{
            tmp[0] = (int)l1[0]-1;
            head = deleteNode(head,tmp,n);
        }
    }


    head = addToColumn(head,l2);

    return head;
}

void printT(struct node * head){
    printf("\n");
    struct node * t = head;
    while (t != NULL){
        struct node* t2 = t;
        while(t2 != NULL){
                printf("%s(%d) ",t2->label,t2->header);
            t2 = t2->child;
        }
        printf("\n");
        t = t->next;
    }
}

void remaining(struct node * head){
    struct node * t = head;
    int count = 0;
    while(t!=NULL){
        struct node * t2 = t;
        while(t2!=NULL){
            count++;
            t2 = t2->child;
        }
        t = t->next;
    }
    printf("Remaining: %d\n",count);
}

int main(){
    int n=8;

//    do{
//        printf("Enter n: ");
//        scanf("%d",&n);
//    }while (n%2 != 0 || n<=4);

    struct node *head = NULL;

    head = installHeader(head,n);
    head = installChilds(head,n);

    head = deleteMiddleFour(head,n);

//    printT(head);
    table(head,n);
    remaining(head);
    printf("\n");

    char *t1 = (char*)malloc(2* sizeof(char));
    char *t2 = (char*)malloc(2* sizeof(char));
//    for(int k = 0 ; k<20 ; k++){
        B:
        printf("Type the cell coordinate that you want to move: ");
        scanf("%s",t1);
        if(exist(head,t1) == 1){
            int a = possible(head,t1,n);

            if(a==1){
                A:
                printf("Enter destination: ");
                scanf("%s",t2);
                // Eger node bos ve alanin icer's'ndeyse
                if(exist(head,t2) == 0 && (int)t2[0] <=64+n && (int)t2[0] > 64 && (int)t2[1] <=48+n && (int)t2[1] > 48 && t2[2] == '\0'){
                    printf("\n=========================\n\nSuccessful Hit! %s -> %s \n",t1,t2);
                    head = move(head,t1,t2,n);
//                    printT(head);
                    printf("\n");
                    table(head,n);
                    remaining(head);
                    goto B;
                    // move A to B
                } else{
                    printf("Invalid Move\n");
                    goto A;
                }
            }
            printf("\n");
        }else{
            printf("Invalid source!\n");
            goto B;
        }
//    }
    return 0;
}
