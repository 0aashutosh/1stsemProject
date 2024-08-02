#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>
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
	int year;
	int month;
	int date;
	int hour;
	char username[50];
}book,bookck;

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
}

int logout()
{
	system("cls");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\n\t\t\t\tYou have been logout");
	printf("\n\n\n----------------------------------------------------------------------------------------------------------------------\n");

	getch();
	main();
}
void view_bookings(){
    FILE *fp;
    struct booking b;
    system("cls");
    printf("\n\n\t\t\t\t\tVIEW BOOKINGS\n\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("bookings.txt", "r");
    if (fp == NULL) 
	{
        printf("No bookings found!\n");
        getch();
        return;
    }

    while (fread(&b, sizeof(struct booking), 1, fp) == 1) 
	{
        printf("Username: %s\n", b.username);
//        printf("Date: %02d\n", b.hour);
        printf("DATE: %d-%02d-%02d\nTIME: %02d:00\n", b.year,b.month,b.hour,b.hour);
        printf("----------------------------------------------------------------------------------------------------------------------\n");
    }

    fclose(fp);
    getch();
}


void manageprofile(struct signup *user,int role)
{
	int choice=0;
    char newpassword[50];
    char ckpass[50];
//    long long int newcontactnumber;
	struct signup u;
	 char oldpassword[50];
	 FILE *fp;
	profilemenu:
    system("cls");
    printf("\n\n\t\t\t\t\tMANAGE PROFILE\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t1. Change password");
//    printf("\n\t\t2. Update contact number");
    printf("\n\t\t2. Back to main menu");
    printf("\n\n\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);

    switch (choice) {
        case 1:
            
			
			
			switch(role)//role	1 is for admin and 2 is for user/customer
			{
				case 1:
					fp = fopen("owner.txt", "r+");
    	    	    if (fp == NULL) 
					{
						
	            	    printf("Error opening file!");
    	            	exit(1);
        	    	}
        	    	break;
        	    	
        	    case 2:
        	    	fp = fopen("users.txt", "r+");
    	        	if (fp == NULL) 
					{
            		    printf("Error opening file!");
                		exit(1);
            		}
            		break;
            		
            	default:
            		system("cls");
            		printf("\n\n\n\t\t\tERROR IN SYSTEM!");
            		exit(0);
			}
			menu12:
			printf("\nEnter old password: ");
            gets(oldpassword);
            if (strcmp(oldpassword, user->password) != 0) 
			{
                printf("\n\nOld password isn't correct");
                getch();
                goto profilemenu;
            }
            printf("\nEnter new password: ");
            gets(newpassword);
            while (fread(&u, sizeof(struct signup), 1, fp) == 1) 
			{
			
                if (strcmp(u.username, user->username) == 0) 
				{
                    strcpy(u.password, newpassword);
                    fseek(fp, -(long)sizeof(struct signup), SEEK_CUR);
                    fwrite(&u, sizeof(struct signup), 1, fp);
                    printf("\nPassword updated successfully!");
                    break;
                }
                else
                {
                	printf("Username doesnot match!!");
                	goto profilemenu;
				}
            }
			rewind(fp);
            fclose(fp);
            break;

//        case 2:
//
//            fflush(stdin);
//            anotherone:
//            printf("\nEnter old contact number: ");
//            scanf("%lld", &user->contactnumber);
//            while(fread(&u, sizeof(struct signup), 1, fp) == 1)
//            {
//            	
//			
//			if(u.contactnumber==user->contactnumber)
//				{
//					printf("\nEnter new contact number: ");
//					scanf("%lld",&newcontactnumber);
//					if(newcontactnumber< 9700000000 ||  newcontactnumber> 9899999999)
//					{
//						newcontactnumber=0;
//						printf("\n\n\t\t\t\tContact length is not correct!");
//						getch();
//						goto anotherone;
//					}
//					u.contactnumber=newcontactnumber;
//					fp = fopen("users.txt", "a+");
//       	    		if (fp == NULL) 
//					{
//    	            	printf("Error opening file!");
//        	        	exit(1);
//        	    	}
////                    u.contactnumber = user->contactnumber;
//        		    fseek(fp, -(long)sizeof(struct signup), SEEK_CUR);
//            		fwrite(&u, sizeof(struct signup), 1, fp);
//                	printf("\nContact number updated successfully!");
//					getch();
//					goto profilemenu;
//					break;
//				}
//			}
//            
//            	fclose(fp);
//            	break;

        case 2:
            break;

        default:
            printf("Invalid input! Please enter input among choices!\n");
            getch();
            goto profilemenu;
    }

//    getch();
}

int adminMenu()
{
	int choice=0,role=1;
    FILE *fp;
	ownermenu:
    system("cls");
    printf("\n\n\t\t\t\t\tWELCOME OWNER\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\t1. View All Bookings");
    printf("\n\t\t2. View feedback");
    printf("\n\t\t3. Manage profile");
    printf("\n\t\t4. View profile");
    printf("\n\t\t5. Logout");
    fflush(stdin);
    printf("\n\n\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    fflush(stdin);

    switch (choice) 
	{
        case 1:
            view_bookings();
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
			printf("\n\nPress any key to continue!");
			getch();
			goto ownermenu;
            break;
            
        case 3:
        	manageprofile(&owner,role);
			goto ownermenu;
			break;
			
		case 4:
			loading();
			system("cls");
			printf("\n\t\t.......................................\n\t\t.");
			printf("\n\n\t\t\t\tName: ");
			puts(owner.fullname);
			printf("\n\t\t.......................................\n\t\t.");		
			
			printf("\n\t\tUsername: ");
			puts(owner.username);
			printf("\n\t\t.......................................\n\t\t.");	
			printf("\n\t\tContact Number: %lld",owner.contactnumber);
			printf("\n\t\t.......................................\n\t\t.");	
			printf("\n\t\tEsewa Number: %lld",owner.esewa_no);
			printf("\n\t\t.......................................\n\t\t.");
			getch();
			goto ownermenu;
			break;


        case 5:
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
	FILE *fp;
//	char ckpass[50];
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
			printf("\n\n\t\t\t\t\tSIGNUP MENU\n\n");
			printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
			printf("\n\n\t\t\t1.ADMIN\t\t\t2.CUSTOMER\t\t\t3.Return\n\n\n\n");
			printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
			fflush(stdin);
			printf("\n\t\t\t\t\t\tEnter your choice: ");
			scanf("%d",&role);
			switch(role)
			{
				case 2:
					
//					FILE *fp;
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
						users.contactnumber=0;
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
					printf("----------------------------------------------------------------------------------------------------------------------");
		
					printf("\n\n\n\t\t\tSignup sucessfull\t\t\t\n\n\n ");
					printf("----------------------------------------------------------------------------------------------------------------------");
					getch();
					fclose(fp);
					break;
				
	
				case 1:
					fp=fopen("owner.txt","r");	
					if(fread(&owner,sizeof(struct signup),1,fp)==1)
					{
						
						fclose(fp);
						loading();
						system("cls");
						printf("\n\n--------------------------------------------------------------------------------------------------------------------------------");
						printf("\n\n\t\t\t\tADMIN ALREADY EXISTS!!");
						printf("\n\n--------------------------------------------------------------------------------------------------------------------------------");
						getch();
						goto menu;
					}		
					signupmenu1:
					system("cls");
					printf("\n\n\t\t\t\t\tSIGNUP FORM FOR ADMIN\n\n");
					printf("----------------------------------------------------------------------------------------------------------------------\n\n");
					fflush(stdin);
					printf("\n\n\t\t\t\t\tEnter your full name: ");
					gets(owner.fullname);
					fflush(stdin);
					printf("\t\t\t\t\tEnter username: ");
					gets(owner.username);
					fflush(stdin);
					printf("\t\t\t\t\tEnter password: ");
					
					gets(owner.password);
					fflush(stdin);
					printf("\t\t\t\t\tEnter confirmation password: ");
					gets(ckpass);
					if(strcmp(ckpass,owner.password)!=0)
					{
						printf("Both password should match!");
						getch();
						goto signupmenu1;
					}
					fflush(stdin);
					printf("\t\t\t\t\tEnter contact number: ");
					scanf("%lld",&owner.contactnumber);
					if(owner.contactnumber < 9700000000 || owner.contactnumber > 9899999999)
					{	
						printf("Contact length is not correct!");
						getch();
						goto signupmenu1;
					}	
					printf("\t\t\t\t\tEnter esewa number: ");
					scanf("%lld",&owner.esewa_no);
					fflush(stdin);
					printf("\t\t\t\t\tEnter your passkey (NOTE : REMEMBER TO KEEP THIS SAFE): ");
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
					break;
				
				case 3:
					loading();
					goto menu;
					
					
				default:
					printf("Invalid input! Please enter input among choices!");
					fflush(stdin);
					getch();
					system("cls");
					goto re;	
			}	
			
			goto menu;
			break;
		
		case 2://for login
			count=0;
			flag=0;
			system("cls");
			loggin:
			printf("\n\n\t\t\t\t\tLOGIN MENU\n\n");
			printf("----------------------------------------------------------------------------------------------------------------------");
			printf("\n\n\t\t1.ADMIN\t\t\t2.CUSTOMER\t\t\t3.Return\n\n\n\n");
			printf("----------------------------------------------------------------------------------------------------------------------");
			fflush(stdin);
			printf("\n\t\t\t\t\tEnter your choice: ");
			scanf("%d",&role);
			switch(role)
			{
				case 2:
					
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
								goto menu;
							}
							break;
						}	
					}
				
					if(!flag)
					{
						count++;
						printf("Incorrect password  ");
						
						if(count>3)
						{
							printf("\n\nAttempt Limit Reached. Redirecting to password recovery...\n");
							goto there;
						}
						printf("\n\nTry again");
						getch();
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
                	        	        system("cls");
                    	        	    goto loggin;
    	                	        }
                        		}
                        		printf("\n Incorrect Passkey");
        	             		fclose(p);
            	        	    goto menu;
            	        	    
            	        	case 2:
            	        		system("cls");
            	        		printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
								printf("\n\t\t\t\t\t\t\tTHANK YOU FOR YOUR TIME\n");
								printf("\t--------------------------------------------------------------------------------------------------------------------------------------");

                        		exit(0);
                        		
                        	default:
                        		printf("Wrong input");
                        		goto there;
						}
						
				
					}
					break;
					
				case 1:	
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
							printf("\n\nAttempt Limit Reached. Redirecting to password recovery\n");
							loading();
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
//  	            	                  inputpass(login.password); // SEEK_SET for beginning of the file, SEEK_END end of file
										gets(owner.password);
    	                	            fseek(p, -(long)sizeof(struct signup), SEEK_CUR); // SEEK_CUR means current position
        	       	        	        fwrite(&owner, sizeof(struct signup), 1, p);
           	        	        	    printf("\nPassword changed successfully.");
               	        	        	fclose(p);
               	        	        	printf("Redirecting\n");
               	        	        	loading();
               	        	        	
	                   	        	    goto menu;
    	                	        }
       	                		}
            	            	printf("\n Incorrect Verifier Code.");
        	    	       		fclose(p);
            	    	   	    exit(0);
            	       		    break;
            	        		
            	       		case 2:
            	       			system("cls");
            	        		printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
								printf("\n\t\t\t\t\t\t\tTHANK YOU FOR YOUR TIME\n");
								printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
                       			exit(0);
                        		
                       		default:
                       			printf("Wrong input");
                       			goto there1;
						}
						
					}
					break;
				
				case 3:
					loading();
					goto menu;
					
				default:
					printf("Invalid input! Please enter input among choices!");
					fflush(stdin);
					getch();
					goto menu;	
			}
		
			end:
			break;
			
		case 3:
			loading();
			
			system("cls");			
			printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
			printf("\n\t\t\t\t\t\t\tTHANK YOU FOR YOUR TIME\n");
			printf("\t--------------------------------------------------------------------------------------------------------------------------------------");
//			getch();
			exit(0);
		
		default:
			printf("Invalid input! Please enter input among choices!");
			fflush(stdin);
			getch();
			goto menu;			
	}
	return 0;
}




int userMenu()
{
	int choice=0,role=2;
	FILE *fp;
	FILE *f;
	struct booking b1;
	usermenu:
	system("cls");
	printf("\n\n\t\t\t\t\tWELCOME USER %s\n",users.fullname);
	printf("----------------------------------------------------------------USERMENU-----------------------------------------------------------------\n\n\n");
	printf("\n\t\t1.Book arena");
	printf("\n\t\t2.Manage profile");
	printf("\n\t\t3.Make Feedback");
	printf("\n\t\t4.View profile info");
	printf("\n\t\t5.View my booking");	
	printf("\n\t\t6.Logout");
	fflush(stdin);
	printf("\n\n\n\t\tEnter your choice: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			bookarena();
			goto usermenu;
			break;
			
		case 2:
			manageprofile(&users,role);
			goto usermenu;
			break;
			
		case 3:
			fp=fopen("report.txt","a");		
			fflush(stdin);
			printf("Enter your report: ");
			gets(r.report);
			strcpy(r.name,users.fullname);
			fwrite(&r,sizeof(struct report),1,fp);
			printf("\n\n\tReport sent! Press any key to continue!");
			getch();
			system("cls");
			fclose(fp);
			goto usermenu;
			
		case 4:
			loading();
			system("cls");
			printf("\n\t\t.......................................\n\t\t.");
			printf("\n\n\t\t\t\tName: ");
			puts(users.fullname);
			printf("\n\t\t.......................................\n\t\t.");		
			
			printf("\n\t\tUsername: ");
			puts(users.username);
			printf("\n\t\t.......................................\n\t\t.");	
			printf("\n\t\tContact Number: %lld",users.contactnumber);
			printf("\n\t\t.......................................\n\t\t.");	
			getch();
			goto usermenu;
			break;
			
		case 5:
			f= fopen("bookings.txt", "r+");
			system("cls");
		    printf("\n\n\t\t\t\t\tVIEW BOOKINGS\n\n");
    		printf("----------------------------------------------------------------------------------------------------------------------\n");
    		
			while(fread(&b1,sizeof(struct booking),1, f) == 1) 
			{
				if(strcmp(b1.username,users.username)==0)
				{
					printf("Username: %s\n", b1.username);
//        printf("Date: %02d\n", b.hour);
        			printf("Time: %d-%02d-%02d %02d:00", b1.year,b1.month,b1.date,b1.hour);
        			printf("\n----------------------------------------------------------------------------------------------------------------------\n");
	    		}
			}

	        fclose(f);
    		getch();
    		goto usermenu;
    		break;
    		
		case 6:
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
 	FILE *ptr;
	int i=0,total=0;
	struct signup esewa;
    time_t t= time(NULL);
	struct tm tm = *localtime(&t);	
    book:
    system("cls");
    printf("\n\n\t\t\t\t\tBOOKING ARENA\n\n");
    printf("\nDATE: %d-%02d-%02d\nTIME: %02d:%2d\n",tm.tm_year+1900,tm.tm_mon,tm.tm_mday,tm.tm_hour,tm.tm_min);
    printf("\n\n(DISCLAIMER: The time '6-22' is 24 hour format\tThe booking rate is  Rs.1200 per booking)\n(Our system cannot book between hours line '6:30'. It will break the consistency of time availability)");
    printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    fflush(stdin); 	
    book1:
    printf("\nEnter MONTH(1-12): ");
	scanf("%d", &book.month);
	fflush(stdin);
	if( book.month<tm.tm_mon|| book.month >12)
	{
	
    	printf("\nPlease enter valid date!");
    	getch();
    	goto book;
	}
	printf("Enter date(1-31): ");
    scanf("%d", &book.date);  	
	if(book.date<1 || book.date>31)
	{
   		printf("\nPlease enter valid date: ");
   		system("cls");
   		goto book;
	}
	printf("Enter time(6-22): ");
    scanf("%d", &book.hour);  	  	
   	if(book.hour<6 || book.hour>22)
   	{
   		printf("\nTime is not available!!");
   		getch();
   		goto book;
	}
	book.year=tm.tm_year+1900;
	p = fopen("bookings.txt", "r");
    while(fread(&bookck,sizeof(struct booking),1,p)==1)
    {
    	if(book.hour==bookck.hour && book.month==bookck.month && book.date==bookck.date)
    	{
    		printf(" \n\t\tGiven time and date is already booked! Please try again");
    		getch();
    		goto book1; 
		}
	}
	fclose(p);
	strcpy(book.username, users.username);
    fp = fopen("bookings.txt", "a");
    if (fp == NULL) 
	{
    	printf("Error opening file!");
    	exit(0);
    }
    fwrite(&book,sizeof(struct booking),1,fp);
	fclose(fp);
    total=1200;
    ptr = fopen("owner.txt", "r+");
    fread(&esewa,sizeof(struct signup),1,ptr);
    printf("\n\n--------------------------------------------------------------------------------------------------------------------------------");
	printf("\n\t\t\t\tBOOKING SUCCESSFUL!\n");
    printf("\n\t\t\t\tYour total is %d",total);
    printf("\n\n--------------------------------------------------------------------------------------------------------------------------------\n\n\t\t\t");
    printf("(*Pay this in thisEsewa number=%lld)",esewa.esewa_no);
	getch();
	
}

