/* Author:Prakriti Regmi
   AIR TICKETING MANAGEMENT SYSTEM
   Wriiten on : June , 2020
*/
#include <stdio.h> 
#include <string.h>
#include <conio.h> 
#include <stdlib.h>
#include "removerename.h"

//list of all the functions in the code
void loading(); 
void login();
void options();
void bookticket();
void flight_time();
void list_data();
void search_ticket();
void edit_ticket();
void cancel_ticket();
void exit_terminal();
void main();

struct variables 
{
	char firstname[50];
	char lastname[50];
	long long num;
	char dep[4], des[4];
	char numberofseats[6];
};

struct variables booking[10];																				//array variables used in the program
  
int i, stream_closed;																					//Global variables

FILE *frecords , *flistdata , *fsearchdata , *feditrecords , *feditedrecords , *fdeleterecords , *fdeletedrecords;			//File pointer variables						  


//function for the laoding animation 

void loading ()
{
	int i;
	system("cls");
	printf("\n\n\n\n\t\t\t\t\tLoading");
	for (i=0;i<30;i++)
	{
		if (i<=3){
			sleep(1);
			printf("%c",219);
		}
		else {
			printf("%c",219);
		}
	}
	sleep(1);	
	options();
}
void login()                                                                       								 //function for the login page
{
	system ("COLOR 0E");																				//changes the console colour
	system ("cls");																						//clears the screen
	int p=0;
	char username[5], password[10], input;
	printf("***************** AIRLINES TICKET RESERVATION SYSTEM *****************");
	printf("\n\n\t\t\tLOGIN PAGE\n\n");
	printf("Enter username:\t");                                                    
	scanf("%s",&username);
	printf("\nEnter password:\t");     
	while(1)                                                        												//loop to enter password
	{
		password[p] = getch();
		if(password[p] == 13) 																				//breaks loop if 'Enter' key is pressed
		break;
		else if (password[p] == 8 && p!=0) 																	//to operate backspace key in the program
		{ 
		    printf("\b");
		    printf(" ");
		    printf("\b");
			p--;  
		}
		else
		{
			printf("*");
			p++;
		}
	}
	password[p]='\0';

	if (strcmp(username,"admin")==0 && strcmp(password,"abcd")==0)              						//condition to check password and execute accordingly
	{
		
		loading();
		
	}
	else
	{
		system ("cls");
		system ("COLOR 04");                                                        							
		
		printf("***************** WELCOME TO CAPTCHA AIRLINES *****************");
		printf("\n\n\t\t\tLOGIN PAGE\n\n");
		printf("\aIncorrect Username or Password!!!\n\nPlease press 'Enter' key to try again.\n"); 				//displays error message with alert bell
		input=getch();
		if (input == 13)  
		{
			main();
		}
		else 
		{
			exit_terminal();
		}
	}
}



//function to display options of program (Menu page)
void options()                                                                  
{
	char choice;
	system("cls");
	system("COLOR 0B");                                                        								//changes bg to black and fg to light aqua
	printf("\n\n\n\n-------------------- ADMIN PANEL --------------------\n\n\n");
	printf("1.	Book a ticket\n\n2.	View all booked tickets\n\n3.	Search ticket information by Contact Number\n\n");
	printf("4.	Edit  ticket details by Contact Number\n\n5.	Cancel a ticket by Contact Number\n\n6.	Exit the system\n\n\n");	
	printf("Enter your choice.\n\n");
	choice = getch();																							//holds the output until another entry		
	switch(choice)
	{
		system("cls");
		case '1' : bookticket();
		break;
		case '2' : list_data();
		break;
		case '3' : search_ticket();
		break;
		case '4' : edit_ticket();
		break;	
		case '5' : cancel_ticket();
		break;
		case '6' : exit_terminal();
		break;
		default: printf ("Invalid");
	}
}

//function to book the ticket
void bookticket()                                                              								 
{     
	char ans;
	system ("cls");
	system("COLOR 0B");
		for (i=0;i<11;i++)																					//loop provides ref_no to the booked tickets
		{
			printf ("Please enter the following details:\n\n");
			printf("\nFirst Name          :\t");                                            
			scanf("%s",booking[i].firstname);													
			printf("\nLast Name           :\t");                                           
			scanf("%s",booking[i].lastname);
			printf("\nContact Number	  :\t");
			scanf("%lli",&booking[i].num);
			dep:																//label for taking dep from the keyboard
			printf("\nEnter your Derparture and Destination Location.\n\t\tType\n\t KTM for Kathmandu\n\t PKR for Pokhara\n\t KEP for Nepalgunj\n\t BIR for Biratnagar.\n\n");
			printf("DEPARTURE  -\t");
			scanf("%s",booking[i].dep);
			if ((strcmp(booking[i].dep,"KTM")==0) || (strcmp(booking[i].dep,"PKR")==0) ||(strcmp(booking[i].dep,"KEP")==0) ||(strcmp(booking[i].dep,"BIR")==0))			/*String comparison for valid Dep and Des*/
			{
				des:															//label for taking des from the keyboard
				printf("DESTINATION-\t");
				scanf("%s",booking[i].des);
				if ((strcmp(booking[i].des,"KTM")!=0)&&(strcmp(booking[i].des,"PKR")!=0)&&(strcmp(booking[i].des,"KEP")!=0)&&(strcmp(booking[i].des,"BIR")!=0))
				{
					printf("\nInvalid Destination.Retry.\n");
					goto des;														//calling the des label
				}
			}
			else 
			{
				system("cls");
				printf("\nInvalid Departure.Retry.\n");
				goto dep;															//calling the des label
			}
			system("CLS");
			system("COLOR 0B");
			printf("\n\n");
			printf("Dear %s,\n\tThe available flight timing as per your request is:\n",booking[i].firstname);
			printf("\nDeparture time\tArrival time\n");
			flight_time(booking[i].dep, booking[i].des);
			
			char request_confirmbooking, request_moredata,ans;
				
			frecords = fopen("records.txt", "a+");									//file pointer (frecords) to store the entires to the file
		
			printf("\n\nDo you want to confirm your Ticket?(Y/N)\t");
			scanf(" %c",&request_confirmbooking);															//confirmation query message before finally recording
			
			if (request_confirmbooking == 'Y' || request_confirmbooking == 'y') 								 
			{
				printf("\nHow many seats do you want to reserve?\t");
				scanf("%s",&booking[i].numberofseats);
				fflush(stdin);							
				printf("\n%s seats confirmed.",booking[i].numberofseats);
				fprintf(frecords,"\n%d|\t%s|\t%s|\t%lli|\t%s|\t%s|\t%s|",i,booking[i].firstname,booking[i].lastname,booking[i].num,booking[i].dep,booking[i].des,booking[i].numberofseats);		//command to write the console entries in the file records.txt. 
				printf("\n\nThe reference number of your ticket is %d.",i);
			}
			else 
			{
				printf("\n\n\t\tPlease wait , you will be redirected to the OPTIONS page.");
				sleep(3);                                                                						//holds the screen for 3 seconds before redirecting to the options function
				options();
			}
		
			printf("\n\nDo you want to exit booking?	");
			scanf(" %c",&request_moredata);
			
			if (request_moredata == 'y' || request_moredata=='Y')
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\t\tThe entered data has been recorded.  Please wait until redirected to the main menu.");
				sleep(2);
				break;																							//breaks the reference no loop
			}		
			else 
			{
				system("cls");
			}											
		}
	options();
	fclose(frecords);																	//closes the file pointer variable (frecords)
}

//userdefined function for returning flight timing
void flight_time(char dep[3], char des[3])							
{
	if (strcmp(dep,"KTM")==0) 
		{
			if (strcmp(des,"PKR")==0) {printf("6:00 am\t\t6:30 am");} 
			if (strcmp(des,"KEP")==0) {printf("9:20 am\t\t10:15 am");} 
			if (strcmp(des,"BIR")==0) {printf("11:40pm\t\t12:30 pm");} 
		}
	else if (strcmp(dep,"PKR")==0) 
		{
			if (strcmp(des,"KTM")==0) {printf("1:20 am\t\t1:50 am");} 
			if (strcmp(des,"KEP")==0) {printf("2:35pm\t\t4:40 pm");}
			if (strcmp(des,"BIR")==0) {printf("7:00 am\t\t8:05 am");}
		} 
	else if(strcmp(dep,"KEP")==0) 
		{
			if (strcmp(des,"KTM")==0) {printf("10:25am\t\t11:20 am");}
			if (strcmp(des,"PKR")==0) {printf("10:45am\t\t12:50 am");}
			if (strcmp(des,"BIR")==0) {printf("5:10 pm\t\t7:30 pm");}
		} 
	else if (strcmp(dep,"BIR")==0) 
		{
			if (strcmp(des,"KTM")==0) {printf("8:00 pm\t\t8:50 pm");}
			if (strcmp(des,"PKR")==0) {printf("1:00 pm\t\t2:05 pm");}
			if (strcmp(des,"KEP")==0) {printf("8:35 am\t\t9:55 am");}
		} 
}

//function to display the list of all the recorded tickets .
void list_data()
{
	flistdata = fopen ("records.txt","r");																	//file pointer variable (flistdata) to read all the content of the string file records.txt
	if (flistdata!= NULL)							    	
	{
		system ("cls");
	
		char list;																											//local variable to store the character fetched from the pointer path
	
		printf("REFERENCE NO|FIRST NAME |LAST NAME |CONTACT NUMBER  |DEPARTURE|DESTINATION |Number of Seats \n\n");
	
		
		while ((list=fgetc(flistdata))!=EOF)																				//loop to sequentially fetch the characters present in the file 
		{																													//loop execution condition : until the end of file flistdata				
			printf("%c",list);							
		}
	
		printf("\n\n\n\n\n*************************************THE END****************************************************"); 			//display to indicate the end of file content
	
		printf("\n\n\n\n\tPress \"any key \" to reach the main menu"); 					
		getch();
	
		options(); 
	}
	else																																//RTE Error handling incase of no existing file 
	{
		system("cls");
		printf("\n\n\n\n\t\t\tThere arenot any booked tickets yet.");
		printf("\n\n\n\n\n\"Please wait until redirected to the menu\" ..........");
		sleep (4);
		options();
	}	
	fclose(flistdata);	
}

//function to search the ticket information with a unique id i.e (contact number)
void search_ticket ()						            														
{
	char contactnumber[20] , rowofdata[100];
	int flag=0;
	system("cls");
	fsearchdata= fopen ("records.txt","r");               																//filepointer fsearchdata for searching record from the file "records.txt"
	system("cls");
	if (fsearchdata != NULL)							
	{
		printf("\n\nFor unique retrieval,");
		printf("\n\n\tPlease enter your contact number:");
		scanf("%s",contactnumber);
											
		while (!feof(fsearchdata))																				//loop to sequentially fetch the lines present in the file 																																		//loop execution condition : until the entil of filepinter fsearchdata 
		{
			fscanf(fsearchdata, "%[^\n]",rowofdata);		 												//command function to fetch data row by row 
			 
			fgetc(fsearchdata); 																		//command function to move the file pointer beyond the '\n' character.
			
			if (strstr(rowofdata,contactnumber) != NULL)    										//condition to compare the row consisting of the input contact number																								//command for substring comparison between the row of record and contact number 
			{
					flag=1;									  
					
					system("cls");
					
					printf("\n\n*******************************************MATCH FOUND**********************************************");
					
					printf("\n\n\tREFERENCE NO|FIRST NAME|LAST NAME |CONTACT NUMBER |DEPARTURE|DESTINATION|Number of Seats|\n\n");
					
					printf("\t\t %s \n", rowofdata);												//command to print the row of record with true if condition	
					
					printf("\n\n\n\n\t\t\t\tPRESS ANY KEY TO REACH THE MAIN MENU");
					getch();
					options();
					
			}
		}
		
		if (flag==0)																											//if condition incase of no match 
			{
				system("cls");
				printf("\n\n\n\t\tNo such contact number has been recorded. Please make sure the information is correct.");
				printf("\n\n\n\n\t\t\t\tPRESS ANY KEY TO REACH THE MAIN MENU");
				getch();
				options();
			}
	}
	else 																									//RTE error handling					
	{
		printf("\n\n\n\n\t\t\t\t\t\tError 404 : File not found.");																	 
		printf("\n\n\n\n\nPRESS ANY KEY TO REACH THE MAIN MENU.");
		getch();																							//holds the screen
		options();
	}
	fclose (fsearchdata);																				//closes the file pointer fsearchdata
}

//function to update the records present in the file 
void edit_ticket()
{
	system("cls");
	struct variables update;
	int flag =0 ;int ref_no ; 
	char contactnumber[12] ;
	char data[128];
	feditrecords=fopen("records.txt","r");									//filepointer to read existing records	
	feditedrecords=fopen("temp.txt","w");									//file pointer to store the updated record in the temp file
	
	if (feditrecords == NULL)
	{
		printf("\n\n\n\n\t\t\t\t\t\tError 404 : File not found.");										//RTE ERROR HANDLING
		printf("\n\n\n\n\nPRESS ANY KEY TO REACH THE MAIN MENU.");
		getch();
		options();
	}
	printf("\n\n\nEnter your contact number:");
	scanf("%s",contactnumber);
	system("cls");
	if (feditrecords != NULL)
	{
		do	
		{
		 	fscanf(feditrecords, "%[^\n]",data);
			fgetc(feditrecords);		
	
			if (strstr (data,contactnumber) != NULL) 										//condition to identify the row of record
			{
				flag=1;
				printf("\n\n\n*****************************************CURRENT RECORD*****************************************\n\n");
				printf("\n\nREFERENCENO|FIRSTNAME|LASTNAME|CONTACT NUMBER|DEPARTURE|DESTINATION|Number of Seats|\n\n");
				printf("\n%s",data);
				printf("\n\nPlease note that the ticket reference number cannot be changed.It can only be withdrawn through cancellation.");
				printf("\n\nEnter existing ref no:");
				scanf("%d",&ref_no);
				printf("\n\nEnter First Name:");
				scanf("%s",update.firstname);
				printf("\n\nEnter Last Name:");
				scanf("%s",update.lastname);
				printf("\n\nEnter Contact ID:");
				scanf("%lli",&update.num);
				dep:																//label for taking dep from the keyboard
				printf("\nEnter your Derparture and Destination Location.\n\t\tType\n\t KTM for Kathmandu\n\t PKR for Pokhara\n\t KEP for Nepalgunj\n\t BIR for Biratnagar.\n\n");
				printf("DEPARTURE  -\t");
				scanf("%s",update.dep);
				if ((strcmp(update.dep,"KTM")==0) || (strcmp(update.dep,"PKR")==0) ||(strcmp(update.dep,"KEP")==0) ||(strcmp(update.dep,"BIR")==0))			//String comparison for valid Dep and Des
				{
				des:															//label for taking des from the keyboard
				printf("DESTINATION-\t");
				scanf("%s",update.des);
				if ((strcmp(update.des,"KTM")!=0)&&(strcmp(update.des,"PKR")!=0)&&(strcmp(update.des,"KEP")!=0)&&(strcmp(update.des,"BIR")!=0))
				{
					printf("\nInvalid Destination.Retry.\n");
					goto des;														//calling the des label
				}
				printf("\n\nEnter number of seats to reserve:");
				scanf("%s",&update.numberofseats);
				fprintf(feditedrecords,"\n%d|\t%s|\t%s|\t%lli|\t%s|\t%s|\t%s|",ref_no,update.firstname,update.lastname,update.num,update.dep,update.des,update.numberofseats);  //writes the input data into the file
				}
			}
			else
			{
				fprintf(feditedrecords,"\n%s",data);
			}	
		}
		while (fscanf(feditrecords,"%[^\n\r]s",data)!=EOF);						//loop condition until the end of file.
	if (flag == 0 )
	{
		printf("\n\n\n\n\t\t No booking has been enlisted with the number %s.Please make sure the information is correct",contactnumber);	
	}
	else 
	{
		printf("\n\n\n\n\t\tNew data has been successfully updated.");
	}
	
	fflush(feditedrecords);																	//prevents file from garbage
	fclose(feditrecords);
	fclose(feditedrecords);
	
	stream_closed = _fcloseall();												//closes all the open file streams to enable the rename and remove function .
	
	//function compiled in the user defined header file "removerename.h"		
	remove_rename();											//removes the file record.txt and renames the  file temp.txt consisting of the updated list as records.txt
}
	printf("\n\n\n\n\nPRESS ANY KEY TO REACH THE MAIN MENU.");
	getch();
	options();
}

//function to cancel the ticket
void cancel_ticket()
{
	system ("cls");											
	int flag =0 ; 
	char req;  char num[15]; char data[200];
	      		
	fdeleterecords=fopen("records.txt","r");														//opens the file pointer fdeleterecords to read the existing data
	fdeletedrecords=fopen("temp.txt","w");													//opens the file pointer fdeleterecords pointing to a new file "temp.txt" to update the data as per the user preference.

	if (fdeleterecords == NULL)
	{
		printf("\n\n\n\n\t\t\t\t\t\tError 404 : File not found.");								//RTE ERROR HANDLING
		printf("\n\n\n\n\nPRESS ANY KEY TO REACH THE MAIN MENU.");
		getch();
		options();
	}
	
	printf("\n\n\nEnter your contact number:");
	scanf("%s",num);																	//inputs contact id for unique identification of data 

		
	if (fdeleterecords != NULL)	
	{ 
		do
		{
			fscanf(fdeleterecords, "%[^\n]",data);		 									//command function to fetch data row by row 
			fgetc(fdeleterecords);
		
			if (strstr(data,num) != NULL) 						//substring comparison between the input contact number and the row of data fetched from file 
			{
				flag=1;
				system("cls");
				printf("\n\n\n*********************************************CURRENTLY PRESENT RECORD*********************************************************\n\n");
				printf("\n\nREFERENCENO|FIRST NAME|LAST NAME|CONTACT NUMBER|DEPARTURE|DESTINATION|Number of Seats|\n\n");
				printf("\n%s",data);																			//prints the match
				printf("\n\nAre you sure you want to cancel your ticket?(Y/N)\t");					//confirmation query message before finally updating the file
				scanf(" %c",&req);
				if (req =='y' || req == 'Y')
				{
					flag=2;												// skips fprintf-ing of that specific row of data in the file temp.txt 
				}
				else 
				{
					flag=3;
					fprintf(fdeletedrecords,"%s\n",data);					//fprints the data into the file "temp.txt"
				}
			}
			else
			{
				fprintf(fdeletedrecords,"%s\n",data);					//fprints the data not consisting of the substring (num) into the file "temp.txt" 
			}
		}
		while (fscanf(fdeleterecords,"%[^\n\r]s",data)!=EOF);
		}
			fflush(fdeletedrecords);												//prevents file from garbage
			fclose(fdeleterecords);												//closes file pointer pointing at file records.txt 
			fclose(fdeletedrecords);										//closes file pointer pointing at file temp.txt 
			
			system("cls");
			
			if (flag ==2)
			{
				printf("\n\n\n\n\t\tYour ticket has been cancelled successfully.");
			}
			if (flag==3)
			{
				printf("\n\n\n\n\t\tData left unmodified.");
			}
			if (flag ==0)
			{
				printf("\n\n\n\n\t\tNo matching record found.");
			}
			
			stream_closed = _fcloseall();							//closes all the open file streams to enable the rename and remove function .
			
			//function compiled in the user defined header file "removerename.h"
			remove_rename();										//removes the file record.txt and renames the  file temp.txt consisting of the updated list as records.txt
  	printf("\n\n\n\n\nPRESS ANY KEY TO REACH THE MAIN MENU.");
	getch();
	options();	
}

//function to end the program
void exit_terminal()                                                               
{
	system("cls");
	system("COLOR 0A");
	printf ("\n\n\n\t\t\tYOU HAVE SUCCESSFULLY LOGGED OUT.");
	printf ("\n\n\n\n\n\tThank you for using the program.\n\nIncase you think that the program could do/be better , fork it and do pull a request.\nI am here to get better with your help :)");
	
	exit(0);
}

//main function
void main()                                                                        
{
	login();
}
