#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Admin{
	char email[100], password[100];
	char login_email[100], login_pass[100];
}admin;

struct Product{
	int id;
	char name[100];
	float price, discount;
}pro;

void input(){
	printf("Enter ID : "); scanf("%d", &pro.id);
	printf("Enter Name : "); scanf("%s", &pro.name);
	printf("Enter Price : "); scanf("%f",&pro.price);
	printf("Enter Discount : "); scanf("%f", &pro.discount);
}
void head(){
	printf("ID\t Name\t Price\t Discount\n");
}
void output(){
	printf("%d\t  %s\t $%.2f\t %.2f\n", pro.id, pro.name, pro.price, pro.discount);
}
int main(){
	
	int op,admin_option;
	do{
		system("cls");
		printf("1. Admin\n");
		printf("2. Customer\n");
		printf("0. Exit\n");
		printf("Choose an Option : "); scanf("%d", &op);
		
		switch(op){
			case 1: {
				
				do{
					printf("1. Register\n");
					printf("2. Login\n");
					printf("3. Show All Admin Account\n");
					printf("0. Back\n");
					printf("Choose an Option : "); scanf("%d", &admin_option);
					
					switch(admin_option){
						case 1: {
							system("cls");
							FILE *admin_data;
							admin_data = fopen("admin.txt", "a");
							
							printf("Enter Email  : "); scanf("%s", &admin.email);
							printf("Enter Password: "); scanf("%s", &admin.password);
							fprintf(admin_data, "%s\t%s\n", admin.email, admin.password);
							printf("[==========]Admin Account Create Successfuly==========]");
							fclose(admin_data);
							
							break;
						}
						case 2:{
							int crud_option;
							printf("Email : "); scanf("%s", &admin.login_email); 
							printf("Password : "); scanf("%s", &admin.login_pass);
							
							FILE *admin_data;
							admin_data = fopen("admin.txt", "r");
							
							while(fscanf(admin_data, "%s%s", admin.email, admin.password)==2){
								if(strcmp(admin.login_email, admin.email) == 0 && strcmp(admin.login_pass, admin.password) == 0){
									do{
										printf("1. Input Product\n");
										printf("2. Show product\n");
										printf("3. Search\n");
										printf("4. Update");
										printf("0. Back\n");
										printf("Please choose an option : "); scanf("%d", &crud_option);
										
										switch(crud_option){
											case 1:{
												FILE *product_data;
												product_data = fopen("product.txt", "a");
												int i, n;
												printf("Number Of Product : "); scanf("%d", &n);
												
												for(i=0 ; i<n ; i++){
													printf("[========Enter Product #%d========]\n", i+1);
													input();
													fprintf(product_data, "%d\t%s\t%.2f\t%.2f\n", pro.id, pro.name, pro.price, pro.discount);
												}
												
												fclose(product_data);
												
												break;
											}
											case 2:{
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
												int search;
												
												FILE *product_data;
												product_data = fopen("product.txt", "r");
												
												printf("Enter ID to Search : "); scanf("%d", &search);
												
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
												
												FILE *product_data;
												product_data = fopen("product.txt", "r");
												int update;
												
												printf("Enter Product ID to Update : "); scanf("%d", &update);
												
												while(fscanf(product_data, "%d%s%f%f", &pro.id, pro.name, &pro.price, &pro.discount)==4){
													
												}
												
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
		}
		
	}while(op!=0);
}
