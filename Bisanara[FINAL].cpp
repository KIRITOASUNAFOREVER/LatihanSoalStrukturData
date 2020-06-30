#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Tree{
	long long key;
	char nama[100];
	char tampung[100];
	int height;
	Tree *left, *right;
}*root=NULL;

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
struct Tree *insertNode(Tree *curr, long long value,char nama[],char tampung[]){
	if (curr==NULL){
		curr = (Tree *)malloc(sizeof(struct Tree));
		curr->key =  value;
		curr->height = 1;
		strcpy(curr->nama,nama);
		strcpy(curr->tampung,tampung);
		curr->left = curr->right = NULL;
		printf("Success Insert!\n");
		getchar();
		return curr;
	}
	else if(curr->key==value){
		printf("NIM already Present!\n");
		getchar();
		return curr;
		}
	else if (value < curr->key){
		curr->left = insertNode(curr->left, value,nama,tampung);
	}
	else if (value > curr->key){
		curr->right = insertNode(curr->right, value,nama,tampung);
	}
	 
				
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right))+1;
	int balanceFactor = getBalanceFactor(curr);
	
	if (balanceFactor < -1 && value > curr->right->key){// RR case
		return leftRotation(curr);
	}
	
	if (balanceFactor < -1 && value < curr->right->key){//RL Case
		curr->right = rightRotation(curr->right);
		return leftRotation(curr);
	}
	
	if (balanceFactor > 1 && value < curr->left->key){// LL Case
		return rightRotation(curr);
	}
	
	if (balanceFactor > 1 && value > curr->left->key){ // LR Case
		curr->left = leftRotation(curr->left);
		return rightRotation(curr);
	}
// printf("Success Insert!\n");
	return curr;
}
struct Tree * minValueNode(struct Tree* node) 
{ 
    struct Tree* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current->right != NULL) 
        current = current->right; 
  
    return current; 
} 
struct Tree* deleteNode(struct Tree* root, long long  key,char nama[],char tampung[]) 
{ 
  
    if (root == NULL) 
        return root; 
   
    if ( key < root->key ) 
        root->left = deleteNode(root->left, key,nama,tampung); 
   
    else if( key > root->key ) 
        root->right = deleteNode(root->right, key,nama,tampung); 
 
    else
    { 
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            struct Tree *temp = root->left ? root->left : root->right; 
  
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else 
             *root = *temp; 
            free(temp); 
        } 
        else
        { 
            struct Tree* temp = minValueNode(root->left); 
   
            root->key = temp->key; 
  			strcpy(root->nama,temp->nama);
  			strcpy(root->tampung,temp->tampung);
             
            root->left = deleteNode(root->left, temp->key,nama,tampung); 
        } 
    } 

    if (root == NULL) 
      return root; 

    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right)); 
  
    int balance = getBalanceFactor(root); 
  
    // Left Left Case 
    if (balance > 1 && getBalanceFactor(root->left) >= 0) 
        return rightRotation(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalanceFactor(root->left) < 0) 
    { 
        root->left =  leftRotation(root->left); 
        return rightRotation(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalanceFactor(root->right) <= 0) 
        return leftRotation(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalanceFactor(root->right) > 0) 
    { 
        root->right = rightRotation(root->right); 
        return leftRotation(root); 
    } 
  
    return root; 
} 
void printTree(struct Tree *root, int space) 
{ 

    if (root == NULL) 
    {
        return;
    }
    
    else
    {
        printf("\n"); 
        space += 8; 
    printTree(root->right, space); 
    printf("\n"); 
    for (int i = 8; i < space; i++) 
        printf(" "); 
    printf("%s:  %s", root->tampung,root->nama); 
    printTree(root->left, space);
    }
} 
  
void print(struct Tree *root) 
{ 
if(root==NULL)
{
    printf("No Data");
}
else
{
    printTree(root, 0); 
}
}

struct Tree *search(Tree **node, long long value,char nama[],char tampung[]){
	long long penanda;
	char pasti[20];
	//jika pointer current memiliki data
	if((*node)!=NULL){
		//cek, apakah datanya lebih kecil. Jika iya, belok ke kiri
		if(value<(*node)->key){
			search(&(*node)->left,value,nama,tampung);
		//jika lebih besar, maka belok ke kanan
		}else if(value>(*node)->key){
			search(&(*node)->right,value,nama,tampung);
		//jika sama dengan, maka angka ketemu
		}else{
			strcpy(pasti,"Ketemu");
			penanda = (*node)->key;
		}
	//jika tidak ada data lagi (not found)
	}else{
		strcpy(pasti,"Tidak");
	}
	if(strcmp(pasti,"Ketemu")==0){
			root = deleteNode(root , value,nama,tampung);
			printf("Success Delete!\n");
			getchar();
	}
	if(strcmp(pasti,"Tidak")==0){
		printf("No Such NIM!\n");
			getchar();
	}
}

void spasi(){
	for(int i= 0; i<30;i++){
		printf("\n");
	}
}
int main(){
	int choose=0;
	long long temp;
	char tampung[100];
	char digits[20];
	char nama[100];
	long long  inputNumber;
	char name[100];
	
	 do{
       system("cls");
        spasi();
    	printf("\nbisanara.co\n");
    	printf("===========\n");
    	puts("1. Insert");
    	puts("2. View");
    	puts("3. Delete");
    	puts("4. Exit");
    	printf("Choose >> ");
        scanf("%d",&choose);fflush(stdin);
        
        switch(choose)
        {
            case 1:
                system("cls");
                spasi();
                do{
                	printf("Input Name ( 5 - 90 Characters ): \n");
                	scanf("%[^\n]",name);
					fflush(stdin);
				}while(strlen(name) > 90 || strlen(name) < 5);
                
				do{
                	printf("Input NIM ( 10 Characters ): \n ");
					scanf("%s", &digits); fflush(stdin);
				}while(strlen(digits)!=10);
				strcpy(tampung,digits);
				temp=digits[0]-48;
				temp = temp *1000000000;
				temp = temp + ((digits[1]-48)*100000000)+((digits[2]-48)*10000000)+((digits[3]-48)*1000000)+((digits[4]-48)*100000)+((digits[5]-48)*10000)+((digits[6]-48)*1000)+((digits[7]-48)*100)+((digits[8]-48)*10)+((digits[9]-48));
				root = insertNode(root, temp,name,tampung);
				 
                break;
            case 3:
            if(root==NULL){
            	system("cls");
            	spasi();
            	printf("No Data\n");
            	getchar();
            }
            else{
                system("cls");
                spasi();
    			do{
                	printf("Input NIM ( 10 characters ): \n");
					scanf("%s", &digits); fflush(stdin);
				}while(strlen(digits)!=10);
				strcpy(tampung,digits);
				temp=digits[0]-48;
				temp = temp *1000000000;
				temp = temp + ((digits[1]-48)*100000000)+((digits[2]-48)*10000000)+((digits[3]-48)*1000000)+((digits[4]-48)*100000)+((digits[5]-48)*10000)+((digits[6]-48)*1000)+((digits[7]-48)*100)+((digits[8]-48)*10)+((digits[9]-48));
				search(&root,temp,name,tampung);
            }
                break;
            case 2:
                system("cls");
                spasi();
                print(root);
                printf("\n");
                getchar();
                break;
        }
    }while(choose != 4);
	return 0;
}

