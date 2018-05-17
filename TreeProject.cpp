//Σταύρος Λιούλιας
//ΑΜ:2025201100042
//Windows 7 64-bit
//Intel Core i5-2430M CPU 2,4GHz
#include <stdlib.h>
#include <stdio.h> // gia eisodo/exodo
#include <assert.h>  // gia tin synartisi assert
#include <stdbool.h> // typos boolean
#include<string.h>
struct listnode
	{
	int item;
	struct listnode *next;
	};
typedef struct treeNode TreeNode;

// struct gia ton kombo enos dyadikou dentrou
typedef struct treeNode {
  int item;
  TreeNode *left;
  TreeNode *right;

  // to epomeno melos xrhsimopoieitai apokleistika gia thn ektypwsi tou dentrou
  int rank;  // h seira tou item (1o, 2o, 3o klp), ypologizetai me th synartisi inorder 
} TreeNode;


// Epektasi tis inorder diasxisis pou apothikeyei gia kathe kombo ti seira tou
void inorder(TreeNode *t, int *pr) {
    if (t==NULL) return;

    inorder(t->left, pr);   // episkepsi aristerou ypodentrou tou t

    t->rank = ++(*pr);  // episkepsi komvou t, anathesi timis rank
     
    inorder(t->right, pr);  // episkepsi deksiou ypodentrou tou t
}


typedef TreeNode *T; // o typos T orizetai ws deikths se kombo dentrou

// megisto megethos stoixeiwn ouras 50
#define MaxQSize 50 


// Oura ylopoihmenh me aplo pinaka
typedef struct queue {
   T q[MaxQSize];
   int front, rear;
} Queue;

void init(Queue *q) {
  q->front=q->rear=0;
}

void destroy(Queue *q) {
  q->front=q->rear=0;
}

bool isEmpty(Queue *q) {
    return (q->front==q->rear);
}

bool isFull(Queue *q) {
    return (q->rear==MaxQSize);
}

T dequeue(Queue *queue) {
  assert(!isEmpty(queue));  // elegxos an i oura periexei stoixeia
  return queue->q[queue->front++];
}

void enqueue(Queue *queue, T newitem) {
     assert(!isFull(queue));  // elegxos an i oura exei gemisei
     queue->q[queue->rear++]=newitem;
}

int bsearch(TreeNode *v, int x) {  //anazhthsh stoixeiou
    int result;
    if (v != NULL) {  
     if (x < v->item) 
        return bsearch(v->left, x); 
     else if (x > v->item)
        return bsearch(v->right, x);
     else return 1;  
   } 
else return 0; 
}
TreeNode* insertItem(TreeNode *root, int x) {   //eisagwgh stoixeiou
   TreeNode *v = root;  // v trexon kombos
   TreeNode *pv = NULL; // pv goneas tou v 
   while (v != NULL) {  
      pv = v; 
      if (x < v->item) v=v->left;
      else if (x > v->item) v=v->right;
           else { // yparxei idi, ektypwsi mhnymatos
                  printf("Uparxei hdh sto dentro to stoixeio %d",x);
		  return root;
           }   
   }
   TreeNode *tmp = new TreeNode;
   tmp->item=x; tmp->left=tmp->right=NULL;    
   if (root != NULL) { 
      if (x < pv->item) pv->left=tmp;
         else pv->right=tmp;
   } else root=tmp;
   return root; // epistrofi rizas dentrou
}

// diagrafh stoixeiou apo to dentro (edw ylopoieitai mono h periptwsh pou to stoixeio brisketai se fylo)
// to proot einai deiktis se metablhth pou deixnei sth riza tou dentrou
bool deleteItem(TreeNode *root, int x)
{
   TreeNode *t=root;  // trexon kombos dentrou, arxika h riza tou
   TreeNode *part=NULL; // goneas trexon kombou

   // anazhthsh gia to x sto dentro
   while (t!=NULL)
	if (x<t->item) {
		part=t;
		t=t->left; // phgaine sto aristero ypodentro
	}
	else if (x>t->item) {
		part=t;
		t=t->right; // phgaine sto dexi ypodentro
	}
	else break;  // brethike 


  if (t==NULL) return false; // den brethike

  // periptwsh pou to x brethike se fyllo
  if (t->left==NULL && t->right==NULL) {
     delete t; // diagrafi kombou
          
     if	(part==NULL) root=NULL; // an to x htan sth riza tou dentrou h riza twra ginetai NULL
     else {	
	     if (x<part->item)  // itan aristero paidi tou gonea tou
			part->left=NULL;
	     else part->right=NULL; // allios itan dexi paidi
     }
     
     return true;


  }
  
  // edw tha prepei na mpei o kwdikas gia tis dyo alles periptwseis

  return false;
   
}
void print(TreeNode *t){
     if (t==NULL) {
        printf("Tree is empty\n");
        return;
     }
     
     if (t->left != NULL) print(t->left);    
     if (t->right != NULL) print(t->right);
     
     printf("%d\n", t->item);
}

// synarthsh ektypwsis dentrou
void printTree(TreeNode *t) {

   if (t==NULL) return;

   int rank=0; // metabliti pou apothikeyei to trexon plhthos kombwn pou exei episkeftei i inorder
   inorder(t, &rank); // ypologismos rank kathe kombou tou dentrou

   // levelorder: episkepsi kombwn dentrou ana epipedo 0, 1, 2, klp kai apo aristera pros deksia
   Queue q[2];  // dyo oures mia gia kombous se zygo kai mia se mono epipedo dentrou

   init(&q[0]);
   init(&q[1]);

   const int ItemWidth=3; // orismos platos tou kathe stoixeiou (3 xarakthres)
   int level=0; // trexon epipedo zygo=0, mono=1
   int column=0; // trexousa stili, dhladh posoi xaraktires (kena i arithmoi) exoun typothei stin trexousa grammi mexri stigmis

   enqueue(&q[level],t);

   while (!isEmpty(&q[level])) 
   {

      t=dequeue(&q[level]); // trexon kombos

      int width= ItemWidth * t->rank - column;  // ypologismos apaitoumenou platous se xarakthres
      printf("%*d", width, t->item);  // ektypwsh kleidiou tou kombou t se platos width
      column = ItemWidth * t->rank;

      // eisagwgi stin oura tou epomenou epipedou twn paidiwn tou
      if (t->left!=NULL) 
	enqueue(&q[1-level], t->left);
      if (t->right!=NULL) 
	enqueue(&q[1-level], t->right);

      if (isEmpty(&q[level])) {
	  // trexousa oura einai i oura tou epomenou epipedou
	  level=1-level;
          printf("\n"); // nea grammi
	  column=0;  
      }
   }
   printf("\n");
} // telos tis synartisis printTree


void rotateleft(TreeNode **tnode) {
      assert(*tnode != NULL); // ??µί?? µ? ?e???
      assert((*tnode)->right != NULL); // a??ste?? pa?d?
      TreeNode *tmp = (*tnode)->right; //   µ? ?e??
      (*tnode)->right = tmp->left;
      tmp->left = *tnode;
      *tnode = tmp;
}

void rotateright(TreeNode **tnode) {
      assert(*tnode != NULL); // ??µί?? µ? ?e???
      assert((*tnode)->left != NULL); // a??ste?? pa?d?
      TreeNode *tmp = (*tnode)->left; //   µ? ?e??
      (*tnode)->left = tmp->right;
      tmp->right = *tnode;
      *tnode = tmp;
}
listnode* lnr = NULL;
listnode* interval(TreeNode *n, int low, int up) {
     //assert(n != NULL);
     if (n == NULL) return 0;
     
     if (n->left != NULL && n->item > low) interval(n->left, low, up);
     if (n->item >= low && n->item <= up) {
                 //printf("%d", n->item);
                 listnode *tmp = new listnode;
                 tmp->item = n->item;
                 tmp->next = 0;
                 if (lnr == NULL) lnr = tmp;
                 else {
                      listnode *d = lnr;
                      while (d->next!= NULL) d = d->next;
                      d->next = tmp;
                 }
     }
     if (n->right != NULL && n->item < up) interval(n->right, low, up);
     return lnr;
}
void deleteListNode(listnode* n){
     if (n == NULL) return;
     
     if (n->next != NULL) deleteListNode(n->next);
     
     delete n;
}
int main() {
    TreeNode* root = NULL,* d=NULL; //arxikopoihsh
    char command[20]; //Metavlhth pou voh8a stis epiloges tou xrhsth sto programma
     int item, low, up;
     
     while(1) {
           scanf("%s",&command);
           if (strcmp(command, "insert")==0) { //eisagwgh stoixeiou
                scanf("%d",&item);
                root =insertItem(root,item);                    
           }
           else if (strcmp(command, "search")==0){ //anazhthsh
                scanf("%d",&item);
                if (bsearch(root,item)==1) printf("To stoixeio iparxei\n");
                else printf("To stoixeio den vrethike\n");
                
           }
           else if (strcmp(command, "delete")==0){ //diagrafh
                scanf("%d",&item);
                deleteItem(root, item);
           }
           else if (strcmp(command, "left")==0){ //peristrofh pros ta aristera
                rotateleft(&root);
           }
           else if (strcmp(command, "right")==0){ //peristrofh pros ta dekia
                rotateright(&root);
           }
           else if (strcmp(command, "interval")==0){ //eisagwgh  stoixeiwn apo low mexri kai up se lista kai emfanish tous
                scanf("%d",&low);
                scanf("%d", &up);
                listnode *l1, *l = interval(root, low, up);
                l1 = l;
                while (l != NULL) {
                      printf("%d ", l->item);
                      l = l->next;
                }
                deleteListNode(l1);
           }
           else if (strcmp(command, "exit")==0){ //termatismos programmatos
                exit (0);
           }
           printTree(root); //emfanish tou dentrou se ka8e entolh
      }
}
