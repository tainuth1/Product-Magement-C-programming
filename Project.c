#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct Admin{
	char email[100], password[100];
	char login_email[100], login_pass[100];
}admin;
struct Product{
	int id;
	char name[100];
	float price;
}pro;
struct Update{
	char new_name[100];
	float new_price;
}up;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void regisLog(FILE *admin_data){
	admin_data = fopen("admin.txt", "a");
	gotoxy(43, 8);
	printf("[=====Register Admin Account=====]\n");
	gotoxy(50, 10);
	printf("Enter Email  : "); scanf("%s", &admin.email);
	gotoxy(50, 12);
	printf("Enter Password: "); scanf("%s", &admin.password);
	fprintf(admin_data, "%s\t%s\n", admin.email, admin.password);
	fclose(admin_data);
}


void mainMenu(){
	gotoxy(43, 8);
	printf("[=====PRODUCT MANGEMENT SYSTEM=====]\n");
	gotoxy(50, 10);
	printf("1. Admin\n");
	gotoxy(50, 12);
	printf("2. Customer\n");
	gotoxy(50, 14);
	printf("0. Exit\n");
	gotoxy(50, 16);
}

void PMSmenu(){
	gotoxy(43, 8);
	printf("[=====PRODUCT MANGEMENT SYSTEM=====]\n");
	gotoxy(50, 10);
	printf("1. Register\n");
	gotoxy(50, 12);
	printf("2. Login\n");
	gotoxy(50, 14);
	printf("3. Show All Admin Account\n");
	gotoxy(50, 16);
	printf("0. Back\n");
	gotoxy(50, 18);
}

void manageMenu(){
	gotoxy(46, 6);
	printf("[=====Mangement Menu=====]\n");
	gotoxy(50, 8);
	printf("1. Input Product\n");
	gotoxy(50, 10);
	printf("2. Show product\n");
	gotoxy(50, 12);
	printf("3. Search\n");
	gotoxy(50, 14);
	printf("4. Update\n");
	gotoxy(50, 16);
	printf("5. Delete\n");
	gotoxy(50, 18);
	printf("0. Back\n");
	gotoxy(50, 20);
}

//input product
void inputProduct(FILE *product_data){
	product_data = fopen("product.txt", "a");
	int i, n;
	gotoxy(46, 6);
	printf("[=====Input Product=====]\n");
	gotoxy(50, 8);
	printf("Number Of Product : "); scanf("%d", &n);
	system("cls");
	for(i=0 ; i<n ; i++){
		gotoxy(46, 6);
		printf("[========Enter Product #%d========]\n", i+1);
		gotoxy(50, 8);
		printf("Enter ID : "); scanf("%d", &pro.id);
		gotoxy(50, 10);
		printf("Enter Name : "); scanf("%s", &pro.name);
		gotoxy(50, 12);
		printf("Enter Price : "); scanf("%f",&pro.price);
		system("cls");
		fprintf(product_data, "%d\t%s\t%.2f\n", pro.id, pro.name, pro.price);
	}
	
	fclose(product_data);
	system("cls");
}

//output product
void outputData(FILE *product_data){
	product_data = fopen("product.txt", "r");
	printf("+----+---------------+-------+\n");
    printf("| ID |     Name      | Price |\n");
    printf("+----+---------------+-------+\n");
	while(fscanf(product_data, "%d%s%f", &pro.id, pro.name, &pro.price)==3){
		printf("| %2d | %-13s | $%-4.2f |\n", pro.id, pro.name, pro.price);
    	printf("+----+---------------+-------+\n");
	}
	fclose(product_data);
}

//search function
void searchProduct(FILE *product_data,int search){
	product_data = fopen("product.txt", "r");
	system("cls");
	while(fscanf(product_data, "%d%s%f", &pro.id, pro.name, &pro.price)==3){
		if(search == pro.id){
			printf("+----+---------------+-------+\n");
    		printf("| ID |     Name      | Price |\n");
    		printf("+----+---------------+-------+\n");
			printf("| %2d | %-13s | $%-4.2f |\n", pro.id, pro.name, pro.price);
    		printf("+----+---------------+-------+\n");
		}
	}
	fclose(product_data);
}

//update function
void updateProduct(FILE *product_data,int id_to_update){
	FILE *temp_data = fopen("temp.txt", "w");	
	product_data = fopen("product.txt", "r");
	while(fscanf(product_data, "%d%s%f", &pro.id, pro.name, &pro.price)==3){
		if(id_to_update == pro.id){
			gotoxy(50, 8);
			printf("Enter New Name : "); scanf("%s", &up.new_name);
			gotoxy(50, 10);
			printf("Enter New Price : "); scanf("%f", &up.new_price);
			strcpy(pro.name, up.new_name);
			pro.price = up.new_price;
														
			fprintf(temp_data, "%d\t%s\t%.2f\n", id_to_update, up.new_name, up.new_price);
			system("cls");
			printf("Product updated successfully.\n");
		}else{
			fprintf(temp_data, "%d\t%s\t%.2f\n", pro.id, pro.name, pro.price);
		}
	}
	fclose(product_data);
	fclose(temp_data);
												
	remove("product.txt");
	rename("temp.txt", "product.txt");
}

//delete function
void deleteProduct(FILE *product_data,int deleted){
	FILE *temp_data=fopen("temp.txt", "w");
	product_data = fopen("product.txt", "r");
	while(fscanf(product_data, "%d%s%f", &pro.id, pro.name, &pro.price)==3){
		if(deleted == pro.id){
			printf("[========Delete Success=======]\n");
		}else{
			fprintf(temp_data, "%d\t%s\t%.2f\n", pro.id, pro.name, pro.price);
		}
	}
	fclose(product_data);
	fclose(temp_data);
	remove("product.txt");
	rename("temp.txt", "product.txt");
}

//Main Funtion
int main(){
	FILE *product_data,*admin_data,*pay;
	int op,admin_option;
	char ch;
	int pro_id, qty;
	float total, payment;
	do{
		START:
		mainMenu();
		printf("---> Choose an Option : ");op=getch();
		system("cls");
		switch(op){
			case '1': {
				do{	
					PMSmenu();
					printf("---> Choose an Option : ");
					admin_option=getch();
					system("cls");
					
					switch(admin_option){
						case '1': {
							system("cls");
							regisLog(admin_data);
							system("cls");
							gotoxy(50, 0);
							printf("[==========]Admin Account Create Successfuly[==========]");
							fclose(admin_data);
							break;
						}
						case '2':{
							char crud_option;
							gotoxy(46, 8);
							printf("[=====LOGIN=====]\n");
							gotoxy(50, 10);
							printf("Email : "); scanf("%s", &admin.login_email); 
							gotoxy(50, 12);
							printf("Password : "); scanf("%s", &admin.login_pass);
							gotoxy(50, 14);
							system("cls");
							admin_data = fopen("admin.txt", "r");
							
							while(fscanf(admin_data, "%s%s", admin.email, admin.password)==2){
								if(strcmp(admin.login_email, admin.email) == 0 && strcmp(admin.login_pass, admin.password) == 0){
									do{
										MANAGE:
										manageMenu();
										printf("Please choose an option : ");
										crud_option=getch();
										system("cls");
										switch(crud_option){
											//input product
											case '1':{
												system("cls");
												inputProduct(product_data);
												break;
											}
											//output product
											case '2':{
												system("cls");
												outputData(product_data);
												break;
											}
											//search product
											case '3':{
												system("cls");
												int search;
												gotoxy(50,6);
												printf("Enter ID to Search : "); scanf("%d", &search);
												searchProduct(product_data,search);
												break;
											}
											//update product
											case '4':{
												system("cls");
												int id_to_update;
												gotoxy(50,6);
												printf("Enter Product ID to Update : "); scanf("%d", &id_to_update);
												updateProduct(product_data,id_to_update);
												break;
											}
											//delete product
											case '5':{
												system("cls");
												int deleted;
												gotoxy(50,6);
												printf("Enter ID to Delete : "); scanf("%d", &deleted);
												deleteProduct(product_data,deleted);
												break;
											}
										}	
									}while(crud_option != '0');
								}
							}
							fclose(admin_data);
							break;
						}
						case '3':{
							FILE *admin_data;
							admin_data = fopen("admin.txt", "r");
							while(fscanf(admin_data, "%s %s", admin.email, admin.password)==2){
								printf("=================================\n");
								printf("Email : %s\n", admin.email);
							}
							fclose(admin_data);
							break;
						}
					}	
				}while(admin_option != '0');
				break;
			}
			case '2':{
				AGAIN:	
				product_data = fopen("product.txt", "r");
				system("cls");
				printf("+----+---------------+-------+\n");
    			printf("| ID |     Name      | Price |\n");
    			printf("+----+---------------+-------+\n");
				while(fscanf(product_data, "%d%s%f", &pro.id, pro.name, &pro.price)==3){
					printf("| %2d | %-13s | $%-4.2f |\n", pro.id, pro.name, pro.price);
    				printf("+----+---------------+-------+\n");
				}
				fclose(product_data);
				pay = fopen("product.txt", "r");
				gotoxy(50, 2);
				printf("[=====Buy Product=====]\n");
				gotoxy(50, 4);
				printf("Product ID to Buy : "); scanf("%d", &pro_id);
				if(pro_id == 12345){
					system("cls");
					goto START;
				}
				while(fscanf(product_data, "%d%s%f", &pro.id, pro.name, &pro.price)==3){
					if(pro_id == pro.id){
						gotoxy(50, 6);
						printf("Quantity : "); scanf("%d", &qty);
						gotoxy(45,8);
						total = qty*pro.price;
						payment=total;
						system("cls");
						printf("+========= Invoice =========+\n");
						printf("|  ID : %d\n", pro.id);
						printf("|\t\t\t    |\n");
						printf("|  Name : %s\n", pro.name);
						printf("|\t\t\t    |\n");
						printf("|  Price : $%.2f\n", pro.price);
						printf("|\t\t\t    |\n");
						printf("|  Quantity : %d\n", qty);
						printf("|\t\t\t    |\n");
						printf("|  Total : $%.2f\n", total);
						printf("|\t\t\t    |\n");
						printf("|  Payment : $%.2f\n", payment);
						printf("+===========================+\n");
						
						gotoxy(43,4);
						printf("=====Your purchase is successfully=====\n");
						gotoxy(50,6);
						printf("Press 'Enter' to continue\n");
					    ch=getch();
					    system("cls");
					    if(ch==13) goto AGAIN;
					}
				}
				if(pro_id != pro.id && pro_id != 12345){
					gotoxy(50,6);
					printf("No Item!\n");
					
					gotoxy(50,8);
					printf("Press 'Enter' to continue\n");
				    ch=getch();
				    system("cls");
				    if(ch==13) goto AGAIN;
				}
				fclose(pay);
				break;
			}
		}		
	}while(op!='0');
}
