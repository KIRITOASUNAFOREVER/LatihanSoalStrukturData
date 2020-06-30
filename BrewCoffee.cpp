#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct data{
	char nama[100];
	char type[25];
	int qty;
	int price;
	data *next,*prev;
}*head,*tail,*current;

struct Data{
	char nama1[100];
	char type1[25];
	int qty1;
	int totalPrice;
	Data *next1,*prev1;
}*head1,*tail1,*current1;

void pushTail(char nama[],char type[],int qty,int price)
{
	current = (data*)malloc(sizeof(struct data));
	
	strcpy(current->nama,nama);
	strcpy(current->type,type);
	current->qty = qty;
	current->price = price;
	current->next=current->prev=NULL;
	
	if(head==NULL)
	{
		head=tail=current;
	}
	else
	{
		current->prev=tail;
		tail->next=current;
		tail=current;
	}
}

void pushTailBelanja(char nama1[],char type1[],int qty1,int totalPrice)
{
	current1 = (Data*)malloc(sizeof(struct Data));
	
	strcpy(current1->nama1,nama1);
	strcpy(current1->type1,type1);
	current1->qty1 = qty1;
	current1->totalPrice = totalPrice;
	current1->next1 = current1->prev1 = NULL;
	
	if(head1==NULL)
	{
		head1=tail1=current1;
	}
	else
	{
		current1->prev1=tail1;
		tail1->next1=current1;
		tail1=current1;
	}
}

void substractOrder()
{
    current1 = head1;
    char nama[100];
	current = head;
	if(head1==NULL){
		printf("No data");
	}else if(head1==tail1){
	     strcpy(nama,current1->nama1);
	    while(strcmp(nama,current->nama)!=0)
	    {
	        current = current->next;
        }	    
		head1=tail1=NULL;
		free(current1);
	}else{
	    strcpy(nama,current1->nama1);
	    while(strcmp(nama,current->nama)!=0)
	    {
	        current = current->next;
        }
	    
		head1=head1->next1;
		head1->prev1=NULL;
		free(current1);
	}
    
}

void popHead(){
	current1=head1;
	char nama[100];
	current = head;
	if(head1==NULL){
		printf("No data");
	}else if(head1==tail1){
	     strcpy(nama,current1->nama1);
	    while(strcmp(nama,current->nama)!=0)
	    {
	        current = current->next;
        }
	    current->qty = current->qty + current1->qty1;
		head1=tail1=NULL;
		free(current1);
	}else{
	    strcpy(nama,current1->nama1);
	    while(strcmp(nama,current->nama)!=0)
	    {
	        current = current->next;
        }
	    current->qty = current->qty + current1->qty1;
		head1=head1->next1;
		head1->prev1=NULL;
		free(current1);
	}
}

void popAllOrder()
{
    while(head1!=NULL){
        substractOrder();
    }
}

void popAll(){
	while(head1!=NULL){
		popHead();
	}
}

int jumlah()
{
    int jumlah = 0;
    current=head;
    	while(current!=NULL)
		{
			jumlah++;
			current=current->next;
		}
		return jumlah;
}

int stokBarang(int nilai)
{
    int hitung = nilai-1;
    int cek = head->qty;
    current = head;
    while(current!=NULL && hitung!=0)
    {
        current = current->next;
        cek = current->qty;
        hitung--;
    }
    return cek;
}

void popMid(int nilai)
{
    int count = nilai-1;
    int hapus = head->price;
	current=head;
	while(current!=NULL && count!=0)
	{
	    current = current->next;
	    hapus = current->price;
	    count--;
    }
	if(head==tail)
	{
		head=tail=NULL;
		free(current);
	}
	else{
		if(hapus==head->price) 
		{
			head=head->next;
			head->prev=NULL;
			free(current);
		}
		else if(hapus==tail->price) 
		{
			current=tail;
			tail=tail->prev;
			tail->next=NULL;
			free(current);
		}
		else
		{
			current->prev->next=current->next;
			current->next->prev=current->prev;
			free(current);
		}
	}
}

void view()
{
	current=head;
	int i = 0;
	if(current==NULL)
	{
	    printf("===============================================================================");
        printf("                          +++++ Brew Coffee Shop +++++                             ");
        printf("Welcome, Mr./Mrs. Admin\n\n\n");
        printf("=============================================================================== ");
	    printf("No.| %-20s | %-10s | %-12s | %-20s  |\n","Menu","Type","Quantity","Price");
	    printf("------------------------------------------------------------------------------- ");
		printf("No Data\n");
		printf("-------------------------------------------------------------------------------");
	}
	else
	{
	    printf("===============================================================================");
        printf("                          +++++ Brew Coffee Shop +++++                             ");
        printf("Welcome, Mr./Mrs. Admin\n\n\n");
        printf("=============================================================================== ");
	    printf("No.| %-20s | %-10s | %-12s | %-20s  |\n","Menu","Type","Quantity","Price");
	    printf("-------------------------------------------------------------------------------");
	    printf("\n");
		while(current!=NULL)
		{
			printf("%-3d| %-20s | %10s | %12d | %10d            |\n",i+1,current->nama,current->type,current->qty,current->price);
			current=current->next;
			i++;
		}
		printf("-------------------------------------------------------------------------------");
	}
}
void hanyaKurang(int angka,int jumlah)
{
    int count = angka-1;
    char name[100];
    char type[20];
    int harga;
    strcpy(name,head->nama);
    strcpy(type,head->type);
    harga = head->price;
    current1= head1;
	current=head;
	
	while(current!=NULL && count!=0)
	{
	    current = current->next;
	    strcpy(name,current->nama);
	    strcpy(type,current->type);
	    harga = current->price;
	    count--;
    }
    int total = jumlah * harga;
        
    current->qty = current->qty - jumlah;
}
void viewPembelian(int angka,int jumlah)
{
    int count = angka-1;
    char name[100];
    char type[20];
    int harga;
    strcpy(name,head->nama);
    strcpy(type,head->type);
    harga = head->price;
    current1= head1;
	current=head;
	
	while(current!=NULL && count!=0)
	{
	    current = current->next;
	    strcpy(name,current->nama);
	    strcpy(type,current->type);
	    harga = current->price;
	    count--;
    }
    int total = jumlah * harga;
        
    current->qty = current->qty - jumlah;
    
	int i = 0;
	
	if(current1==NULL)
	{
		printf(" Data is empty\n");
	}
	else
	{
	    printf("\n\n");
        printf("Your Order : \n");
        printf("=============================================================================== ");
	    printf("No.| %-20s | %-10s | %-12s | %-20s  |\n","Menu","Type","Quantity","Total Price  ");
	    printf("------------------------------------------------------------------------------- ");
		while(current1!=NULL)
		{
			printf("%-3d| %-20s | %10s | %12d | %10d            |\n",i+1,current1->nama1,current1->type1,current1->qty1,current1->totalPrice);
			current1=current1->next1;
			i++;
		}
		printf("-------------------------------------------------------------------------------");
	}
}

void viewCustomer(char name[])
{
	current=head;
	int i = 0;
	if(current==NULL)
	{
	    printf("===============================================================================");
        printf("                          +++++ Brew Coffee Shop +++++                             ");
        printf("Welcome, Mr./Mrs. %s\n\n\n",name);
        printf("=============================================================================== ");
	    printf("No.| %-20s | %-10s | %-12s | %-20s  |\n","Menu","Type","Quantity","Price");
	    printf("------------------------------------------------------------------------------- ");
		printf("No Data\n");
		printf("-------------------------------------------------------------------------------");
	}
	else
	{
	    printf("===============================================================================");
        printf("                          +++++ Brew Coffee Shop +++++                             ");
        printf("Welcome, Mr./Mrs. %s\n\n\n",name);
        printf("=============================================================================== ");
	    printf("No.| %-20s | %-10s | %-12s | %-20s  |\n","Menu","Type","Quantity","Price");
	    printf("-------------------------------------------------------------------------------");
	    printf("\n");
		while(current!=NULL)
		{
			printf("%-3d| %-20s | %10s | %12d | %10d            |\n",i+1,current->nama,current->type,current->qty,current->price);
			current=current->next;
			i++;
		}
		printf("-------------------------------------------------------------------------------");
	}
	viewPembelian(1,0);
}

int cekBelanja(int angka,int jumlah)
{
    int count = angka-1;
    char name[100];
    char type[20];
    int harga;
    strcpy(name,head->nama);
    strcpy(type,head->type);
    harga = head->price;
    current1= head1;
	current=head;
	int hasilCek = 0;
	
	while(current!=NULL && count!=0)
	{
	    current = current->next;
	    strcpy(name,current->nama);
	    strcpy(type,current->type);
	    harga = current->price;
	    count--;
    }
    int total = jumlah*current->price;
    while(current1!=NULL)
    {
        if(strcmp(name,current1->nama1)==0)
        {
            current1->qty1 = current1->qty1  + jumlah;
            current1->totalPrice = current1->totalPrice + total;
            hasilCek = 1;
            break;
        }
        else
        {
            hasilCek = 0;
        }
       
        current1 = current1->next1;
    }
    return hasilCek;
}

int main()
{
    static int count = 1;
    static int sekali = 1;
    int banyak=  jumlah();
	int choose;
	int angka;
	char password[15];
	char nama[100];
	char type[10];
	int qty;
	int jumlah1;
	int price;
	char customerName[25];
	int pilihanCustomer;
	int jumlahOrder;
	int banyakBarang;
	int hasilCek = 0;
	
	char pilihan[100];
    
        do{
            printf("enter your name: ");
            scanf("%[^\n]",&pilihan);fflush(stdin);
        }while(strlen(pilihan)<=3);
            if(strcmp(pilihan,"admin")==0)
        { 
        system("cls");
            int pilih;
                     do{   
                        if(count==1)
                        {
                            pushTail("Americano","Coffee",24,19000);
                            pushTail("Chocolate Baked","Non-coffee",15,24000);
                            pushTail("Alberto","Coffee",7,44000);
                            count++;
                        }
                        
                        view();
                        printf(" 1. Add item\n");
                        printf("2. Remove item\n");
                        printf("3. Exit\n");
                        printf("Enter your action: ");
                        scanf("%d",&pilih);fflush(stdin);
                         switch(pilih)
                        {
                            case 1:
                                do{
                                    printf("Insert item name: ");
                                    scanf("%[^\n]",&nama);fflush(stdin);
                                    if(strlen(nama) < 5 || strlen(nama) > 19)
                                    {
                                        printf("input length of name between 5 and 19");
                                    }
                                }while(strlen(nama) < 5 || strlen(nama) > 19);
                        
                                do{
                                    printf("Type of Coffee[yes/no]: ");
                                    scanf("%s",&type);fflush(stdin);fflush(stdin);
                                }while(strcmp(type,"yes")!=0 && strcmp(type,"no")!=0);
                        
                                do{
                                    printf("Insert the quantity of the item: ");
                                    scanf("%d",&qty);fflush(stdin);
                                }while(qty < 1 || qty > 100);
                        
                                do{
                                    printf("Insert the price of the item: ");
                                    scanf("%d",&price);fflush(stdin);
                                }while(price < 10000 || price > 200000);
                                if(strcmp(type,"yes")==0)
                                {
                                    pushTail(nama,"Coffee",qty,price);
                                }
                                else
                                {
                                    pushTail(nama,"Non-coffee",qty,price);
                                }
                                
                        break;
                        case 2:
                            current = head;
                            if(current==NULL)
                            {
                                printf("Tidak Ada Stok Barang yang bisa dihapus\n");
                                getchar();
                            }
                            else
                            {
                                jumlah1 = jumlah();
                            do{
                                printf("Choose Number to Delete [1 - %d]: ",jumlah1);
                                scanf("%d",&angka);fflush(stdin);
                            }while(angka < 1 || angka > jumlah1);
                                popMid(angka);
                            }    
                        break;
                        case 3:
                            system("cls");
                            return main();    
                        break;
                    }
                     }while(pilih!=3 || pilih < 1 || pilih > 3);
                    
                }
                else
                {
                    system("cls");
                    if(count==1)
                {
                    pushTail("Americano","Coffee",24,19000);
                    pushTail("Chocolate Baked","Non-coffee",15,24000);
                    pushTail("Alberto","Coffee",7,44000);
                    count++;
                }
                
                do{
                    viewCustomer(pilihan);
                    printf(" 1. Buy item\n");
                    printf("2. Cancel item\n");
                    printf("3. Exit\n");
                    printf("Enter your action: ");
                    scanf("%d",&pilihanCustomer);fflush(stdin);
                switch(pilihanCustomer)
                {
                    case 1:
                        current = head;
                        if(current==NULL)
                        {
                            printf("Tidak ada barang yang bisa dibeli");
                            getchar();
                        }
                        else
                        {
                            jumlah1 = jumlah();
                        do{
                            printf("choose your menu [1 - %d]: ",jumlah1);
                            scanf("%d",&angka);fflush(stdin);
                        }while(angka < 1 || angka > jumlah1);
                        banyakBarang = stokBarang(angka);
                        if(banyakBarang > 0)
                        {
                            do{
                                printf("enter the quantity [1 - %d]: ",banyakBarang);
                                scanf("%d",&jumlahOrder);fflush(stdin);
                            }while(jumlahOrder < 1 || jumlahOrder > banyakBarang);
                            
                            
                            hasilCek = cekBelanja(angka,jumlahOrder);
                            if(hasilCek==1)
                            {
                                printf("");
                            }
                            else
                            {
                                pushTailBelanja(current->nama,current->type,jumlahOrder,jumlahOrder*current->price);
                            }
                            
                            hanyaKurang(angka,jumlahOrder);
                        }
                        else
                        {
                            printf("Stok Barang Habis");
                        }
                        }
                        
                    break;
                    case 2:
                        if(head1==NULL)
                        {
                            printf("");
                        }
                        else
                        {
                            popAll();
                        }                       
                    break;
                    case 3:
                        popAllOrder();
                        system("cls");
                        return main();
                    break;
                }
                }while(pilihanCustomer!=3 || pilihanCustomer ==1 || pilihanCustomer==2);       
                }		  
}
