#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>

struct signup{
	char fullname[50];
	char username[50];
	char password[50];
	long long int contactnumber;
	long long int esewa_no;
	int passkey;
}users,owner;

struct admin{
	char username[50];
	char password[50];
	long long int contactnumber;

};
      
struct booking{
	int time;
	int date;
	char username[50];
}book;

struct report{
	char name[50];
	char report[150];
}r;

int userMenu();
void report();
void bookarena();
int logout();
int adminMenu();

	
void loading()
{
	printf("\n\nLoading");
//	Sleep(1000);
	printf("");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
}

int logout()
{
	system("cls");
	printf("\n\n\t\t\t\tYou have been logout");
	getch();
	main();
}
void view_bookings() {
    FILE *fp;
    struct booking b;
    system("cls");
    printf("\n\n\t\t\t\t\tVIEW BOOKINGS\n\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("bookings.txt", "r");
    if (fp == NULL) {
        printf("No bookings found!\n");
        getch();
        return;
    }

    while (fread(&b, sizeof(struct booking), 1, fp) == 1) {
        printf("Username: %s\n", b.username);
        printf("Date: %02d\n", b.date);
        printf("Time: %02d\n", b.time);
        printf("----------------------------------------------------------------------------------------------------------------------\n");
    }

    fclose(fp);
    getch();
}
void updatefile(struct signup *user)
{
	char name[10],tname[10];
//	name[10]='users.txt';
//	tname[10]='temp.txt';
	FILE *fp, *fp_temp;
    struct signup u;

    fp = fopen("users.txt", "r");
    fp_temp = fopen("temp.txt", "w");

    if (fp == NULL || fp_temp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    while (fread(&u, sizeof(struct signup), 1, fp) == 1) {
        if (strcmp(u.username, user->username) == 0) 
		{
            fwrite(user, sizeof(struct signup), 1, fp_temp);
        }
		 else 
		{
            fwrite(&u, sizeof(struct signup), 1, fp_temp);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    remove(name);
    rename(tname, name);
}

void manageprofile(struct signup *user)
{
	int choice=0;
    char newpassword[50];
    char ckpass[50];
    long long int newcontactnumber;

	profilemenu:
    system("cls");
    printf("\n\n\t\t\t\t\tMANAGE PROFILE\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t1. Change password");
    printf("\n\t\t2. Update contact number");
    printf("\n\t\t3. Back to main menu");
    printf("\n\n\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);

    switch (choice) {
        case 1:
        	fflush(stdin);
        	printf("Enter old password");
        	gets(ckpass);
        	if(strcmp(ckpass,users.password)!=0)
        	{

        		printf("\n\nOld password isnt correct");
        		getch();
        		goto profilemenu;
			}
            printf("\nEnter new password: ");
            gets(newpassword);
            newpassword[strcspn(newpassword, "\n")] = 0;
            strcpy(user->password, newpassword);
            printf("Password updated successfully!\n");
            updatefile(user);
            break;

        case 2:
            printf("\nEnter new contact number: ");
            scanf("%lld", &newcontactnumber);
            user->contactnumber = newcontactnumber;
            printf("Contact number updated successfully!\n");
            updatefile(user);
            break;

        case 3:
            break;

        default:
            printf("Invalid input! Please enter input among choices!\n");
            getch();
            goto profilemenu;
    }

    getch();
}

int adminMenu()
{
	int choice=0;
    FILE *fp;
	ownermenu:
    system("cls");
    printf("\n\n\t\t\t\t\tWELCOME OWNER\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t1. View All Bookings");
    printf("\n\t\t2. View report");
    printf("\n\t\t3. Logout");
    printf("\n\n\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);

    switch (choice) {
        case 1:
            view_bookings();
            getch();
            goto ownermenu;
            break;

        case 2:
        	fp=fopen("report.txt","r");
            system("cls");
            printf("\n\t\t\t\t\tUSER REPORTS");
            printf("\n----------------------------------------------------------------------------------------------------------------------\n");
            while(fread(&r,sizeof(struct report),1,fp)==1)
            {
            	printf("\n");
            	puts(r.name);
            	printf("\n");
            	puts(r.report);
            	printf("\n");
            	printf("\n----------------------------------------------------------------------------------------------------------------------\n\n");
			}
            break;

        case 3:
        	loading();
            system("cls");
			printf("\n\n\t\t\t\tYou have been logout");
			getch();
			return 1;	
			break;

        default:
            printf("Invalid input! Please enter input among choices!\n");
            getch();
            goto ownermenu;
    }
}
int main()
{
	int role=0,choice=0,log=0;
	int flag=0,key=0;
	FILE *p;
	struct signup user, admin1;
	FILE *ptr;
	int count=0,m=0;
	char ckusername[50],c;
	char ckpass[50];
	menu:
	system("cls");
	printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
	printf("\n\t\t\t\t\t\t\t\t   FUTSAL FUSION\n");
	printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
	printf("\n\n\t\t\t\t\t\t\t\t1.Sign up");//choices for users
	printf("\n\n\t\t\t\t\t\t\t\t2.Login");
	printf("\n\n\t\t\t\t\t\t\t\t3.Exit");
	printf("\n\n\t--------------------------------------------------------------------------------------------------------------------------------------");
	printf("\n\n\t\t\t\t            Enter your choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1://for registration
			system("cls");
			re:
			fflush(stdin);	
			printf("\n\n\t\t\t\t\t\t\t\tSIGNUP\n\n\t--------------------------------------------------------------------------------------------------------------------------------------");
			printf("\n\n\t\t\t\t\t\t\t1.ADMIN\t\t\t2.CUSTOMER\n\n");
			printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
			printf("\n\t\t\t\t\t\tEnter your role: ");
			scanf("%d",&role);
			if(role==2)
			{
				FILE *fp;
				signupmenu:
				system("cls");
				printf("\n\n\t\t\t\t\t\t\t\tSIGNUP FORM FOR CUSTOMER\n\n");
				printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
				fflush(stdin);
				printf("\n\n\t\t\t\t\tEnter your full name: ");
				gets(users.fullname);
				fflush(stdin);
				printf("\t\t\t\t\tEnter username: ");
				gets(users.username);
				fflush(stdin);
				printf("\t\t\t\t\tEnter password: ");
				gets(users.password);
				fflush(stdin);
				printf("\t\t\t\t\tEnter confirmation password: ");
				gets(ckpass);
				if(strcmp(ckpass,users.password)!=0)
				{
					printf("Both password should match!");
					getch();
					goto signupmenu;
				}
				fflush(stdin);
				printf("\t\t\t\t\tEnter contact number: ");
				scanf("%lld",&users.contactnumber);
				if(users.contactnumber < 9700000000 || users.contactnumber > 9899999999)
				{
					printf("\n\n\t\t\t\tContact length is not correct!");
					getch();
					goto signupmenu;
				}
				fflush(stdin);
				printf("\t\t\t\t\tEnter your passkey (NOTE : REMEMBER TO KEEP THIS SAFE): ");
				scanf("%d",&users.passkey);
	
				fp=fopen("users.txt","a");
				if(fp==NULL)
				{
					printf("Error!");
					exit(0);
				}
				fwrite(&users,sizeof(struct signup),1,fp);
				printf("\n\n--------------------------------------------------------------------------------------------------------------------------------");
				printf("\n\n\t\t\t\tSignup sucessfull: ");
				fclose(fp);
			}
	
			if(role==1)
			{
//		struct signup owner;
				FILE *fp;
				char ckpass[50];
				signupmenu1:
				system("cls");
				printf("\n\n\t\t\t\t\tSIGNUP FORM FOR ADMIN\n\n");
				printf("----------------------------------------------------------------------------------------------------------------------\n\n");
				fflush(stdin);
				printf("Enter your full name: ");
				gets(owner.fullname);
				fflush(stdin);
				printf("\nEnter username: ");
				gets(owner.username);
				fflush(stdin);
				printf("Enter password: ");
				gets(owner.password);
				fflush(stdin);
				printf("Enter confirmation password: ");
				gets(ckpass);
				if(strcmp(ckpass,owner.password)!=0)
				{
					printf("Both password should match!");
					getch();
					goto signupmenu1;
				}
				fflush(stdin);
				printf("Enter conntact number: ");
				scanf("%lld",&owner.contactnumber);
				if(owner.contactnumber < 9700000000 || owner.contactnumber > 9899999999)
				{	
					printf("Contact length is not correct!");
					getch();
					goto signupmenu1;
				}	
				printf("\nEnter esewa number: ");
				scanf("%lld",&owner.esewa_no);
				fflush(stdin);
				printf("Enter your passkey (NOTE : REMEMBER TO KEEP THIS SAFE): ");
				scanf("%d",&owner.passkey);
	
				fp=fopen("owner.txt","a");
				if(fp==NULL)
				{
					printf("Error!");
					exit(0);
				}
				fwrite(&owner,sizeof(struct signup),1,fp);
				printf("----------------------------------------------------------------------------------------------------------------------");
	
				printf("\n\n\n\t\t\tSignup sucessfull\t\t\t\n\n\n ");
				printf("----------------------------------------------------------------------------------------------------------------------");
				getch();
				fclose(fp);
			}	
			if(role!=1 && role!=2)
			{
				printf("Invalid input");
				getch();
				system("cls");
				goto re;
			}
			goto menu;
			break;
		
		case 2://for login
			
			system("cls");
			loggin:
			printf("----------------------------------------------------------------------------------------------------------------------");
			printf("\n\n\t\t1.ADMIN\t\t\t2.CUSTOMER\n\n");
			printf("----------------------------------------------------------------------------------------------------------------------");
			printf("\n\t\t\t\t\tEnter your role: ");
			scanf("%d",&role);
			if(role==2)
			{
				ptr=fopen("users.txt","r");
				if(ptr==NULL)
				{
					printf("Error!");
						exit(0);
				}
				system("cls");
				main2:
			
				fflush(stdin);
				
				
					printf("\n\n\t\t\t\t\tLOGIN FORM FOR USERS\n\n");
					printf("----------------------------------------------------------------------------------------------------------------------");
					fflush(stdin);
					printf("\nEnter username: ");
					gets(ckusername);
					fflush(stdin);
					printf("\nEnter password: ");
					gets(ckpass);
					while(fread(&users,sizeof(struct signup),1,ptr)==1)
					{
						if(strcmp(users.username,ckusername)==0 && strcmp(users.password,ckpass)==0)
						{
							flag=1;
							printf("Login successful");
							getch();
							fclose(ptr);
							
							log=userMenu();
							if(log==1)
							{
								loading();
								goto menu;
							}
							break;
						}	
					}
				
					if(!flag)
					{
						count++;
						printf("Incorrect password   %d",count);
						getch();
						if(count>3)
						{
							printf("\n\nAttempt Limit Reached. Redirecting to password recovery...");
							goto there;
						}
						printf("\n\nTry again");
						system("cls");
						rewind(ptr);
						goto main2;
					}
					there:
					while(count>3)
					{
						printf("1.change password ");
						printf("\n2. Exit");
						fflush(stdin);
						printf("\n\nEnter your choice");
						scanf("%d",&m);
						switch(m)
						{
							case 1:
								printf("Enter passkey: ");
								scanf("%d",&key);
								fflush(stdin);
								printf("\nEnter username: ");
								gets(ckusername);
								p = fopen("users.txt", "r+");
                        		if (p == NULL)
	                        	{
    	                        	printf("\n\nNo File Detected");
	        	                    break;
    	        	            }
        	        	        while (fread(&users, sizeof(struct signup), 1, p)==1)
            	        	    {
                	        	    if (strcmp(users.username, ckusername) == 0 && key==users.passkey)
                    	        	{
                        	    		fflush(stdin);
	                        	        printf("\nEnter New Password:");
//  	                              inputpass(login.password); // SEEK_SET for beginning of the file, SEEK_END end of file
										gets(users.password);
    	        	                    fseek(p, -(long)sizeof(struct signup), SEEK_CUR); // SEEK_CUR means current position
        	        	                fwrite(&users, sizeof(struct signup), 1, p);
            	        	            printf("\nPassword changed successfully.");
                	        	        fclose(p);
                    	        	    goto end;
    	                	        }
                        		}
                        		printf("\n Incorrect Verifier Code.");
        	             		fclose(p);
            	        	    exit(0);
            	        	    
            	        	case 2:
            	        		printf("\n Ok BYE BYE");
                        		exit(0);
                        		
                        	default:
                        		printf("Wrong input");
                        		goto there;
						}
						
					}
						
						
					
			
			}
			if(role==1)
			{
				
				count=0;
				ptr=fopen("owner.txt","r");
				if(ptr==NULL)
				{
					printf("Error!");
				exit(0);
				}
				system("cls");
				main3:
				printf("\n\n\t\t\t\t\tLOGIN FORM FOR ADMIN\n\n");
				printf("----------------------------------------------------------------------------------------------------------------------");
				fflush(stdin);
				printf("\nEnter username: ");
				gets(ckusername);
				fflush(stdin);
				printf("\nEnter password: ");
				gets(ckpass);
				while(fread(&owner,sizeof(struct signup),1,ptr)==1)
				{
					if(strcmp(owner.username,ckusername)==0 && strcmp(owner.password,ckpass)==0)
					{
						flag=1;
						printf("Login successful");
						getch();
						fclose(ptr);
						loading();
						log=adminMenu();
						if(log==1)
						{
							
							goto menu;
						}
						break;
					}	
				}
				if(!flag)
					{
						count++;
						printf("Incorrect password   ");
						getch();
						if(count>3)
						{
							printf("\n\nAttempt Limit Reached. Redirecting to password recovery...");
							goto there1;
						}
						printf("\n\nTry again");
						system("cls");
						goto main3;
					}
					there1:
					while(count>3)
					{
						printf("1.change password ");
						printf("\n2. Exit");
						fflush(stdin);
						printf("\n\nEnter your choice");
						scanf("%d",&m);
						switch(m)
						{
							case 1:
								printf("Enter passkey: ");
								scanf("%d",&key);
								fflush(stdin);
								printf("\nEnter username: ");
								gets(ckusername);
								p = fopen("owner.txt", "r+");
                        		if (p == NULL)
	                        	{
    	                        	printf("\n\nNo File Detected");
	        	                    break;
    	        	            }
        	        	        while (fread(&owner, sizeof(struct signup), 1, p)==1)
            	        	    {
                	        	    if (strcmp(owner.username, ckusername) == 0 && key==owner.passkey)
                    	        	{
                        	    		fflush(stdin);
	                        	        printf("\nEnter New Password:");
//  	                              inputpass(login.password); // SEEK_SET for beginning of the file, SEEK_END end of file
										gets(owner.password);
    	        	                    fseek(p, -(long)sizeof(struct signup), SEEK_CUR); // SEEK_CUR means current position
        	        	                fwrite(&owner, sizeof(struct signup), 1, p);
            	        	            printf("\nPassword changed successfully.");
                	        	        fclose(p);
                    	        	    goto end;
    	                	        }
                        		}
                        		printf("\n Incorrect Verifier Code.");
        	             		fclose(p);
            	        	    exit(0);
            	        	    
            	        	case 2:
            	        		printf("\n Ok BYE BYE");
                        		exit(0);
                        		
                        	default:
                        		printf("Wrong input");
                        		goto there1;
						}
						
					}
			}
			
	
			end:
			break;
			
		case 3:
			loading();
			
			system("cls");			
			printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
			printf("\n\t\t\t\t\t\t\t\t\tTHANK YOU FOR YOUR TIME\n");
			printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
			getch();
			exit(0);
		
		default:
			printf("Invalid input! Please enter input among choices!");
			fflush(stdin);
			getch();
			goto menu;			
	}
/*	if(role==1)
	{
		adminMenu();
	}
	if(role==2)
	{
		userMenu();
	}
	if(role==3)
	{
		goto menu;
	}*/
	return 0;
}




int userMenu()
{
	int choice=0;
	FILE *fp;
	usermenu:
	system("cls");
	printf("\n\n\t\t\t\t\tWELCOME USER %s\n",users.username);
	printf("-------MENU----------\n\n\n");
	printf("\n\t\t1.Book arena");
	printf("\n\t\t2.Manage profile");
	printf("\n\t\t3.Report");
	printf("\n\t\t4.Logout");
	printf("\n\n\n\t\tEnter your choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			bookarena();
			break;
			
		case 2:
			manageprofile(&users);
			goto usermenu;
			break;
			
		case 3:
			fp=fopen("report.txt","a");		
			fflush(stdin);
			printf("Enter your report: ");
			gets(r.report);
			strcpy(r.name,users.fullname);
			fwrite(&r,sizeof(struct report),1,fp);
			system("cls");
			fclose(fp);
			goto usermenu;
			
		case 4:
			loading();
			system("cls");
			printf("\n\n\t\t\t\tYou have been logout");
			getch();
			return 1;	
			break;
			
		default :
			printf("Invalid input! Please enter input among choices!");
			getch();
			goto usermenu;
	}
}

void bookarena()
{
	FILE *fp;
 	FILE *fptr;
 	FILE *p;//to check time and date of booking !
	int cnt=0,i=0,total=0;
	/*fptr = fopen("owner.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!");
        exit(0);
    }*/
    book:
    system("cls");
    printf("\n\n\t\t\t\t\tBOOKING ARENA\n\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    fflush(stdin); 
//    fread(&owner,sizeof(struct signup),1,fptr);
    printf("Enter how many times you want to book: ");
    scanf("%d",&cnt);
    if(cnt>3)
    {
    	printf("You cannot book more than 3 hours a day");
    	goto book;
	}
	if(cnt<1)
	{
		printf("Thank you!");
		getch();
		return;
	}
    
    for(i=1;i<=cnt;i++)
    {
    	struct booking bookck;
    	book1:
    	printf("Enter date(THIS MONTH) (1-31): ");
    	scanf("%d", &book.date);
   		fflush(stdin);
   		if(book.date<1 || book.date>31)
   		{
   			printf("Please enter days whithin month: ");
   			getch();
   			goto book;
		}
   		printf("Enter time (6-22): ");
    	scanf("%d", &book.time);  	
    	if(book.time < 6|| book.time > 22)
    	{
    		printf("Time not available!");
    		getch();
    		goto book1;
		}
    	
		p = fopen("bookings.txt", "r");
    /*	if (p == NULL) 
		{
    	    printf("Error opening file!");
    	    exit(0);
    	}*/
    	while(fread(&bookck,sizeof(struct booking),1,p)==1)
    	{
    		if(book.date==bookck.date && book.time==bookck.time)
    		{
    			printf(" Given time and date is already booked! Please try again");
    			getch();
    			goto book1;
			}
		}
		fclose(p);
		
		strcpy(book.username, users.username);
    	fp = fopen("bookings.txt", "a+");
    	if (fp == NULL) 
		{
    	    printf("Error opening file!");
    	    exit(0);
    	}
    	fwrite(&book, sizeof(struct booking), 1, fp);
	}
	fclose(fp);
    total=cnt*1200;
	printf("Booking successful!\n");
    printf("Your total is %d",total);
    getch();
	
}




