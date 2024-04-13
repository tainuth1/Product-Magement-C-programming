#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Admin{
	char email[100], password[100];
	char login_email[100], login_pass[100];
}admin;

struct Product{
	int id;
	char name[100];
	float price, discount;
}pro;

struct Update{
	char new_name[100];
	float new_price, new_discount;
}up;

void input(){
	gotoxy(50, 8);
	printf("Enter ID : "); scanf("%d", &pro.id);
	gotoxy(50, 10);
	printf("Enter Name : "); scanf("%s", &pro.name);
	gotoxy(50, 12);
	printf("Enter Price : "); scanf("%f",&pro.price);
	gotoxy(50, 14);
	printf("Enter Discount : "); scanf("%f", &pro.discount);
	gotoxy(50, 16);
}
void head() {
    printf("+-----+---------------+-------+----------+\n");
    printf("| ID  |     Name      | Price | Discount |\n");
    printf("+-----+---------------+-------+----------+\n");
}

void output() {
    printf("|%3d | %-13s | $%4.2f |   %.2f   |\n", pro.id, pro.name, pro.price, pro.discount);
    printf("+-----+---------------+-------+----------+\n");
}
void update(){
	gotoxy(50, 8);
	printf("Enter New Name : "); scanf("%s", &up.new_name);
	gotoxy(50, 10);
	printf("Enter New Price : "); scanf("%f", &up.new_price);
	gotoxy(50, 12);
	printf("Enter New Discount : "); scanf("%f", &up.new_discount);
}

int main(){
	
	int op,admin_option;
	do{
		gotoxy(43, 8);
		printf("[=====PRODUCT MANGEMENT SYSTEM=====]\n");
		gotoxy(50, 10);
		printf("1. Admin\n");
		gotoxy(50, 12);
		printf("2. Customer\n");
		gotoxy(50, 14);
		printf("0. Exit\n");
		gotoxy(50, 16);
		printf("---> Choose an Option : "); scanf("%d", &op);
		
		switch(op){
			case 1: {
				
				do{
					system("cls");
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
					printf("---> Choose an Option : "); scanf("%d", &admin_option);
					system("cls"); //this one effect to customer case;
					
					switch(admin_option){
						case 1: {
							system("cls");
							FILE *admin_data;
							admin_data = fopen("admin.txt", "a");
							gotoxy(43, 8);
							printf("[=====Register Admin Account=====]\n");
							gotoxy(50, 10);
							printf("Enter Email  : "); scanf("%s", &admin.email);
							gotoxy(50, 12);
							printf("Enter Password: "); scanf("%s", &admin.password);
							fprintf(admin_data, "%s\t%s\n", admin.email, admin.password);
							gotoxy(50, 0);
							printf("[==========]Admin Account Create Successfuly==========]");
							fclose(admin_data);
							
							break;
						}
						case 2:{
							system("cls");
							int crud_option;
							gotoxy(46, 8);
							printf("[=====LOGIN=====]\n");
							gotoxy(50, 10);
							printf("Email : "); scanf("%s", &admin.login_email); 
							gotoxy(50, 12);
							printf("Password : "); scanf("%s", &admin.login_pass);
							gotoxy(50, 14);
							system("cls");
							FILE *admin_data;
							admin_data = fopen("admin.txt", "r");
							
							while(fscanf(admin_data, "%s%s", admin.email, admin.password)==2){
								if(strcmp(admin.login_email, admin.email) == 0 && strcmp(admin.login_pass, admin.password) == 0){
									do{
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
										printf("Please choose an option : "); scanf("%d", &crud_option);
										
										switch(crud_option){
											case 1:{
												system("cls");
												FILE *product_data;
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
													input();
													system("cls");
													fprintf(product_data, "%d\t%s\t%.2f\t%.2f\n", pro.id, pro.name, pro.price, pro.discount);
												}
												
												fclose(product_data);
												system("cls");
												break;
											}
											case 2:{
												system("cls");
												FILE *product_data;
												product_data = fopen("product.txt", "r");
												
												head();
												while(fscanf(product_data, "%d%s%f%f", &pro.id, pro.name, &pro.price, &pro.discount)==4){
													output();
												}
												
												fclose(product_data);
												
												break;
											}
											case 3:{
												system("cls");
												int search;
												
												FILE *product_data;
												product_data = fopen("product.txt", "r");
												
												printf("Enter ID to Search : "); scanf("%d", &search);
												system("cls");
												while(fscanf(product_data, "%d%s%f%f", &pro.id, pro.name, &pro.price, &pro.discount)==4){
													if(search == pro.id){
														head();
														output();
													}
												}
												
												fclose(product_data);
												
												break;
											}
											case 4:{
												system("cls");
												FILE *product_data, *temp_data;
												product_data = fopen("product.txt", "r");
												temp_data = fopen("temp.txt", "w");
												int id_to_update;
												
												gotoxy(50,6);
												printf("Enter Product ID to Update : "); scanf("%d", &id_to_update);
												
												while(fscanf(product_data, "%d%s%f%f", &pro.id, pro.name, &pro.price, &pro.discount)==4){
													if(id_to_update == pro.id){
														update();
														strcpy(pro.name, up.new_name);
														pro.price = up.new_price;
														pro.discount = up.new_discount;
														
														fprintf(temp_data, "%d\t%s\t%.2f\t%.2f\n", id_to_update, up.new_name, up.new_price, up.new_discount);
														system("cls");
														printf("Product updated successfully.\n");
													}else{
											            fprintf(temp_data, "%d\t%s\t%.2f\t%.2f\n", pro.id, pro.name, pro.price, pro.discount);
											        }
												}
												
												fclose(product_data);
												fclose(temp_data);
												
												remove("product.txt");
												rename("temp.txt", "product.txt");
												
												
												break;
											}
											case 5:{
												system("cls");
												int deleted;
												printf("Enter ID to Delete : "); scanf("%d", &deleted);
												
												FILE *product_data, *temp_data;
												product_data = fopen("product.txt", "r");
												temp_data = fopen("temp.txt", "w");
												
												while(fscanf(product_data, "%d%s%f%f", &pro.id, pro.name, &pro.price, &pro.discount)==4){
													if(deleted == pro.id){
														printf("[========Delete Success=======]\n");
													}else{
														fprintf(temp_data, "%d\t%s\t%.2f\t%.2f\n", pro.id, pro.name, pro.price, pro.discount);
													}
												}
												
												fclose(product_data);
												fclose(temp_data);
												
												remove("product.txt");
												rename("temp.txt", "product.txt");
												
												break;
											}
										}
										
									}while(crud_option != 0);
								}
							}
							 
							fclose(admin_data);
							break;
						}
						case 3:{
							FILE *admin_data;
							admin_data = fopen("admin.txt", "r");
							
							while(fscanf(admin_data, "%s %s", admin.email, admin.password)==2){
								printf("=================================\n");
								printf("Email : %s\n", admin.email);
								printf("Password: %s\n", admin.password);
							}
							
							fclose(admin_data);
							
							break;
						}
					}	
					
				}while(admin_option != 0);
				
				break;
			}
			case 2:{
				int pro_id, qty;
				float total, discount, payment;
				FILE *product_data;
				product_data = fopen("product.txt", "r");
				system("cls");
				head();
				while(fscanf(product_data, "%d%s%f%f", &pro.id, pro.name, &pro.price, &pro.discount)==4){
					output();
				}
				
				fclose(product_data);
				
				FILE *pay;
				pay = fopen("product.txt", "r");
				
				gotoxy(50, 2);
				printf("[=====Buy Product=====]\n");
				gotoxy(50, 4);
				printf("Product ID to Buy : "); scanf("%d", &pro_id);
				gotoxy(50, 6);
				printf("Quantity : "); scanf("%d", &qty);
				
				while(fscanf(product_data, "%d%s%f%f", &pro.id, pro.name, &pro.price, &pro.discount)==4){
					if(pro_id == pro.id){
						total = qty*pro.price;
						
						
						
						system("cls");
						
						gotoxy(0, 0);
						printf("\n+========= Invoice =========+\n");
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
					    printf("|  Discount : $%.2f \t    |\n", discount);  
					   	printf("|\t\t\t    |\n");
					    printf("|  Payment : $%.2f\n", payment);
					    printf("+===========================+\n");
											
						
						break;
					}
				}
				
				fclose(pay);
				break;
			}
		}
		
	}while(op!=0);
}
