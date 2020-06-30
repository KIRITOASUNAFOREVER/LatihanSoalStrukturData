#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Tree{
	int level;
	int height;
	char name[25];
	char job[10];
	Tree *left, *right;
}*root=NULL;

struct data{
	int level;
	char name[25];
	char job[10];
	data *next,*prev;
}*head,*tail,*current;

int getMax (int height1, int height2){
	if (height1 > height2){
		return height1;
	}else{
		return height2;
	}
}

int getHeight(Tree *curr){
	if (curr==NULL){
		return 0;
	}else{
		return curr->height;
	}
}

int getBalanceFactor(Tree *curr){
	if (curr==NULL){
		return 0;
	}else{
		return getHeight(curr->left)-getHeight(curr->right);
	}
}

struct Tree *leftRotation(Tree *curr){
	Tree *child = curr->right;
	Tree *grandChild = child->left;
	
	child->left = curr;
	curr->right = grandChild;
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right))+1;
	child->height = getMax(getHeight(child->left), getHeight(child->right))+1;
	
	return child;
}

struct Tree *rightRotation(Tree *curr){
	Tree *child = curr->left;
	Tree *grandChild = child->right;
	
	child->right = curr;
	curr->left = grandChild;
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right))+1;
	child->height = getMax(getHeight(child->left), getHeight(child->right))+1;
	
	return child;
}
struct Tree *insertNode(Tree *curr, int level,char name[],char job[],int tinggi){
	if(tinggi < 4){
		if (curr==NULL){
			curr = (Tree *)malloc(sizeof(struct Tree));
			curr->level = level;
			curr->height = 1;
			strcpy(curr->name,name);
			strcpy(curr->job,job);
			curr->left = curr->right = NULL;
			printf("Success to add new player..\n\n");
			printf("Press enter to continue..");
			return curr;
		}
		else if (level < curr->level){
			curr->left = insertNode(curr->left, level,name,job,tinggi+1);
		}
		else if (level > curr->level){
			curr->right = insertNode(curr->right, level,name,job,tinggi+1);
		}
		curr->height = getMax(getHeight(curr->left), getHeight(curr->right))+1;
		int balanceFactor = getBalanceFactor(curr);
		
		if (balanceFactor < -1 && level > curr->right->level){// RR case
			return leftRotation(curr);
		}
		
		if (balanceFactor < -1 && level < curr->right->level){//RL Case
			curr->right = rightRotation(curr->right);
			return leftRotation(curr);
		}
		
		if (balanceFactor > 1 && level < curr->left->level){// LL Case
			return rightRotation(curr);
		}
		
		if (balanceFactor > 1 && level > curr->left->level){ // LR Case
			curr->left = leftRotation(curr->left);
			return rightRotation(curr);
		}
		return curr;
	}
	else{
		printf("Maximum tree level is 4...\n");
		return curr;
	}
	getchar();
}

void pushTail(int level,char name[], char job[])
{
	current = (data*)malloc(sizeof(struct data));
	
	current->level = level;
	strcpy(current->name,name);
	strcpy(current->job,job);
	current->next=current->prev=NULL;
	
	if(head==NULL)
	{
		head = tail = current;
	}
	else
	{
		current->prev=tail;
		tail->next=current;
		tail=current;
	}
}

void preOrder(Tree *curr){
	if(curr!=NULL){
		printf("%d ", curr->level);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(Tree *curr) 
{
    if(curr!=NULL)
    {
        inOrder(curr->left);
        printf("%d ", curr->level);
        inOrder(curr->right);
    }
}

void postOrder(Tree *curr) 
{
    if(curr!=NULL)
    {
        postOrder(curr->left);
        postOrder(curr->right);
        printf("%d ",curr->level);
    }
}

int cari(char name[])  
{  
    current = (data*)malloc(sizeof(struct data));
    int i=0,flag;
	int level; 
    
    current = head;   
    if(current == NULL)  
    {  
        printf("There is no data left to be shown...\n");
        printf("\nPress enter to continue..."); 
        getchar();
    }  
    else  
    {   
        while (current!=NULL)  
        {  
            if(strcmp(current->name,name)==0)  
            {  
                level = current->level;
                flag=0;
                break;  
            }   
            else  
            {  
                flag=1;  
            }  
            i++;  
            current = current->next;  
        }  
        if(flag==1)  
        {  
            printf("Data that you requested cannot be found...");
            printf("\nPress enter to continue..."); 
        }
		else{
			return level;
		}  
    }
}

struct Tree *search(Tree **node, int level){
	//jika pointer current memiliki data
	if((*node)!=NULL){
		//cek, apakah datanya lebih kecil. Jika iya, belok ke kiri
		if(level < (*node)->level){
			search(&(*node)->left,level);
		//jika lebih besar, maka belok ke kanan
		}else if(level > (*node)->level){
			search(&(*node)->right,level);
		//jika sama dengan, maka angka ketemu
		}else{
			root = deleteNode(root , level);
		}
	}
}

void popHeadAll()
{
	current = head;
	if(head==tail)
	{
		head=tail=NULL;
		free(current);
	}
	else
	{
	    head=head->next;
		head->prev=NULL;
		free(current);
	}
}

void popAll(){
	while(head!=NULL){
		popHeadAll();
	}
}

int LevelRandom(int lower, int upper,  int count) 
{ 
    int num = (rand() % (upper - lower + 1)) + lower; 
    return num;
} 

int main(){
	int choose=0;
	int level;
	char name[25];
	char job[10];
	int lower = 1, upper = 100, count = 1;
	int tempLevel = 0;
	
	 do{
       system("cls");
    	printf("\nBluejack's Ragnarok Online Player Profile\n");
    	printf("===========================================\n");
    	puts("1. Add (PUSH) New Ragnarok Online Player");
    	puts("2. Show Ragnarok Online Player Profile");
    	puts("3. InOrder, PreOrder, PostOrder");
    	puts("4. Exit");
    	printf("Input your choice : ");
        scanf("%d",&choose);
        
        switch(choose)
        {
            case 1:
            	system("cls");
            	do{
            		printf("Input player's name [1..20 characters] : ");
					scanf("%s", &name); fflush(stdin);
				}while(strlen(name) < 1 || strlen(name) > 20);
				
				do{
					printf("Input player's job ['Swordsman','Thief','Mage','Archer'] : ");
					scanf("%s",&job);fflush(stdin);
				}while(strcmp(job,"Swordsman")!=0 && strcmp(job,"Thief")!=0 && strcmp(job,"Mage")!=0 && strcmp(job,"Archer")!=0);
				
				srand(time(0)); 
				level = LevelRandom(lower, upper, count); 
				printf("Player Got Level : %d\n\n",level);
				root = insertNode(root, level,name,job,0);
				pushTail(level,name,job);
				getchar();
                break;
            case 2:
            	system("cls");
            	if(root==NULL){
            		printf("There is no data left to be shown...\n");
            		printf("\nPress enter to continue...");
            		getchar();	
				}else{
                do{
            		printf("Input player's name that you want to search [1..20 characters] : ");
					scanf("%s", &name); fflush(stdin);
				}while(strlen(name) < 1 || strlen(name) > 20);
                tempLevel = cari(name);
                search(&root,tempLevel);
//                getchar();
				}
				getchar();
                break;
            case 3:
            	system("cls");
            	if(root==NULL)
            	{
            		printf("There is no data left to be shown...\n");
            		printf("\nPress enter to continue...");
            		getchar();
				}
				else{
					printf("PreOrder : ");
					preOrder(root);
					printf("\n");
					printf("InOrder : ");
					inOrder(root);
					printf("\n");
					printf("PostOrder : ");
					postOrder(root);
					printf("\n\nPress enter to continue...");
					getchar();
				}
				getchar();
                break;
            case 4:
            	printf("\nThanks for using our program ^^\n");
            	printf("-Express Our Ability-");
            	popAll();
                break;
        }
    }while(choose < 1 || choose > 4 || choose != 4);
	return 0;
}
