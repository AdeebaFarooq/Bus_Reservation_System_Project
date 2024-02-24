// C Program to implement Bus Reservation System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define busr 8
#define busc 5
#define maxs 40
// Define a structure to store bus information
struct Bus {
	int busNumber;
	char source[50];
	char destination[50];
	int totalSeats;
	int availableSeats;
	int bookedseats[busr][busc];
	float fare;
	float childticket;
	//struct Bus *nextbus;
};

// Define a structure to store passenger information
struct Passenger {
	char name[50];
	int age;
	int seatNumber;
	int busNumber;
	int userid;
	struct Passenger *next;
	struct Passenger *prev;
};
struct Passenger *start=NULL;

// Define a structure to store user login information
struct User {
	char username[50];
	char password[50];
};

// Function to display the main menu
void displayMainMenu()
{
    printf("\n=== AV TRAVELS ===\n");
	printf("\n=== Bus Reservation System ===\n");
	printf("1. Login\n");
	printf("2.sign up\n");
	printf("3. Exit\n");
	printf("Enter your choice: ");
}

// Function to display the user menu
void displayUserMenu()
{
    printf("\n=== WELCOME TO AV TRAVELS==\n");
	printf("\n=== User Menu ===\n");
	printf("1. Book a Ticket\n");
	printf("2. Cancel a Ticket\n");
	printf("3. Check Bus Status\n");
	printf("4. view passenger details\n");
	printf("5. view All Buses \n");
	printf("6. Search Bus\n");
	printf("7. Logout\n");
	printf("Enter your choice: ");
}
void searchbus(struct Bus buses[],int n)
{
    char src[100],des[100];
    printf("enter your source");
    scanf("%s", &src);
     printf("enter your destination");
    scanf("%s", &des);
    int i;
    int flag=0;
    for(i=0;i<n;i++)
    {

        if (strcmp(buses[i].source, src)==0 && strcmp(buses[i].destination, des)==0)
        {

            printf("There is a bus for you with bus number %d",buses[i].busNumber );
            flag=1;
           break;
        }
    }
    if (flag==0)
        printf("sorry, we did'nt find a bus for you");


}
void viewallbuses(struct Bus buses[],int n)
{
    int i;
    for(i=0;i<n;i++)
  printf("bus number: %d, start:%s destination: %s Fare: %f  Child Ticket: %f\n" ,buses[i].busNumber, buses[i].source, buses[i].destination, buses[i].fare, buses[i].childticket);
}
void viewdetails()
{
    struct Passenger *detpas;
    detpas=start;
   while(detpas->next!=NULL)
   {
        printf("name %s age %d bus number %d\n",detpas->name,detpas->age,detpas->busNumber);
        detpas=detpas->next;
    }//while(detpas->next!=NULL);
    printf("name %s age %d bus number %d\n",detpas->name,detpas->age,detpas->busNumber);
}

// Function to perform user login
int loginUser(struct User users[], int numUsers,
			char username[], char password[])
{
    int thiss=0,fil=0,x,k=0;
	for (int i = 0; i < numUsers; i++) {
		if (strcmp(users[i].username, username) == 0
			&& strcmp(users[i].password, password) == 0) {
			thiss=1; // Return the index of the logged-in
            x=i;// user
		}
	}
	int A=0;
    FILE *file;
    char filename[] = "userdata.txt"; // Fixed filename
    char enteredUsername[100];
    char enteredPassword[100];

    // Open the file in read mode
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("sorry login cannot be done\n", filename);
        return -1;
    }
    // Count the number of users in the file
    int numusers = 0;
    while (fscanf(file, "%[^,],%s\n", enteredUsername, enteredPassword) == 2) {
        numUsers++;
    }
    // Rewind the file to the beginning
    rewind(file);

    // Allocate memory for user data
    struct User *Users = malloc(numUsers * sizeof(struct User));

    // Read user data from the file
    for (int i = 0; i < numUsers; i++) {
        fscanf(file, "%[^,],%s\n", Users[i].username, Users[i].password);
    }

    // Close the file
    fclose(file);
   strcpy(enteredUsername, username);
   strcpy(enteredPassword, password);
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(Users[i].username, enteredUsername) == 0 && strcmp(Users[i].password, enteredPassword) == 0) {
            fil=1 ;
            k=i;// Authentication successful
        }
    }
    // Authenticate the user
    int y=-1;
        if(thiss==1)
            y = x;
        else if (fil==1){
            y = k+5;
        }
        return y;
    }
    // Return -1 if login fails

//signup user
int signup(char user[],char password[],int numUsers){
    FILE *file;
    char firstData[100];
    char secondData[100];
    char filename[] = "userdata.txt";
    char enteredUsername[100];
    char enteredPassword[100];
    int i,fil=0,k=0;

    // Open the file in read mode
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("sorry login cannot be done\n", filename);
        return -1;
    }

    // Count the number of users in the file
    while (fscanf(file, "%[^,],%s\n", enteredUsername, enteredPassword) == 2) {
        numUsers++;
    }
    // Rewind the file to the beginning
    rewind(file);

    // Allocate memory for user data
    struct User *Users = malloc(numUsers * sizeof(struct User));

    // Read user data from the file
    for (int i = 0; i < numUsers; i++) {
        fscanf(file, "%[^,],%s\n", Users[i].username, Users[i].password);
    }

    // Close the file
    fclose(file);
    strcpy(enteredUsername, user);
    strcpy(enteredPassword, password);
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(Users[i].username, enteredUsername) == 0) {
            fil=1 ;
        }
    }
    if(fil==0){
    // Open a file in append mode
    file = fopen("userdata.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Ask for and read the first data
    strcpy(firstData,user);
    firstData[strcspn(firstData, "\n")] = 0;  // Remove newline character

    // Ask for and read the second data
    strcpy(secondData,password);
    secondData[strcspn(secondData, "\n")] = 0;  // Remove newline character

    // Append the concatenated data to the file
    fprintf(file, "%s, %s\n", firstData, secondData);

    // Close the file
    fclose(file);
    i=numUsers;
    }
    else{

    printf("Username already exists, please try again!");
    printf("\nREENTER USER NAME :");
    scanf("%s",user);
    printf("\nRENTER PASSWORD :");
    scanf("%s",password);
    i=signup(user,password,numUsers);
    }
    return i;
}

// Function to book a ticket
void bookTicket(struct Bus buses[], int numBuses, int userId)
{
	printf("\nEnter Bus Number: ");
	int busNumber;
	scanf("%d", &busNumber);
	// Find the bus with the given busNumber
	int busIndex = -1;
	for (int i = 0; i < numBuses; i++) {
		if (buses[i].busNumber == busNumber) {
			busIndex = i;
			break;
		}
	}

	if (busIndex == -1) {
		printf("Bus with Bus Number %d not found.\n",
			busNumber);
	}
	else if (buses[busIndex].availableSeats == 0) {
		printf("Sorry, the bus is fully booked.\n");
	}
	else {
            int n,i,a[50],count=1;
            int arr[8][5],c,j,pp=0,cp=0,ap=0,z=1,r,h,x,ticket,sc=0,flag=0,k,pr;
            float price[40],totalprice=0,atp=0,ctp=0;
            int age, seatNumber;
            //initializing price to zero
            for(i=0;i<40;i++)
            {
                price[i]=0;
            }
            printf("enter no of tickets to be booked");
            scanf("%d",&ticket);
            if(ticket<=40){
            for(x=0;x<ticket;x++){
            //to print the visual of bus
            count=1;
            sc=0;
            for(i=0;i<8;i++)
            {
                for ( j = 0; j<5; j++)
                {
                    if(buses[busIndex].bookedseats[i][j]==1)
                    printf("*\t");
                else
                    printf("%d\t",count);
                count++;
                }
                printf("\n");

            }
            //to collect data of the user

            char name[50];
            printf("Enter name of passenger %d ",x+1);
		    scanf("%s", name);
		    printf("Enter age of passenger %d ",x+1);
		    scanf("%d",&age);
            //to select seats

            //creating a new node in linked list named newpassenger
            struct Passenger *newpassenger;
            newpassenger=(struct Passenger*)malloc(sizeof(struct Passenger));
            newpassenger->age=age;
            strcpy(newpassenger->name,name);
            newpassenger->busNumber=busNumber;
            newpassenger->userid=userId;
            printf("Enter seat number to be booked:");
            scanf("%d",&k);
            count=1;
            //to select the seats
            for(i=0;i<40;i++)
            {
                if(count==k)
                {
                    r=(count/5);
                    h=(count%5)-1;
                    if(h==-1)
                    h=4;
                    if(count%5==0)
                    r=r-1;
                    if(buses[busIndex].bookedseats[r][h]==1)
                    {
                        printf("seat is aldready booked.choose another seat\n");
                        sc=1;
                        x=x-1;
                        break;
                    }
                    else{
                    buses[busIndex].bookedseats[r][h]=1;
                    break;
                    }
               }
               count++;
            }

            printf("\n");
            //to print the selected seats
            if(sc==0){
            printf("booked seat is %d\n",k);
            newpassenger->seatNumber=k;
        printf("your booked seat numbers are :\n");
        printf("%d  \n",newpassenger->seatNumber);
        if(age>11)
        {
        price[pp]=0;
        pp=pp+1;
        ap=ap+1;
        }
        else{
            price[pp]= 1;
            pp=pp+1;
            cp=cp+1;
        }
		// Update available seats
		buses[busIndex].availableSeats--;
		printf("Ticket booked successfully!\n");
		if(start==NULL)
        {
		start=newpassenger;
		newpassenger->next=NULL;
		newpassenger->prev=NULL;
        }
        else
        {
        newpassenger->next=start;
        newpassenger->next->prev=newpassenger;
        newpassenger->prev=NULL;
        start=newpassenger;
        }
     }
     else{
        printf("\nFailed to book ticket.choose another seat\n");
     }
     }
	for(i=0;i<8;i++)
            {
                for ( j = 0; j<5; j++)
                {
                    if(buses[busIndex].bookedseats[i][j]==1)
                        printf("*\t");
                    else
                        printf("%d\t",count);
                    count++;
                }
                printf("\n");
            }

    for(pp=0;pp<ticket;pp++)
    {
        if(price[pp]==0)
        {
            atp=atp+buses[busIndex].fare;
        }
        else
        {
            ctp=ctp+buses[busIndex].childticket;
        }
    }
    printf("\n\t\t tickets booked \tprice\n");
    printf("child tickets:\t\t %d \t %.2f\n",cp,ctp);
    printf("adult tickets:\t\t %d \t %.2f\n",ap,atp);
    printf("total price  :\t\t %d \t %.2f\n",(cp+ap),(atp+ctp));
	}

	else{
        printf("%d seats cannot be booked",ticket);
	}}

}
// Function to cancel a ticket
void cancelTicket(struct Bus buses[], int numBuses, int userId)
{
    if(start==NULL)
    {
        printf("no passenger has registered yet");
    }
    else{
    int n,k,seat,r,i,count,h;
    struct Passenger *detpassenger;
    detpassenger=start;
    printf("enter no of seats to be canceled");
    scanf("%d",&n);
    for(k=0;k<n;k++)
    {
	printf("\nEnter Passenger Name: ");
	char name[50];
	scanf("%s", &name);
	printf("enter the ticket number");
	scanf("%d",&seat);
	int found = 0,i;
	int busIndex = -1,j;
	detpassenger=start;
	while(detpassenger!=NULL) {

        //printf("name %s age %d bus number %d",detpassenger->name,detpassenger->age,detpassenger->busNumber);
		if (strcmp(detpassenger->name,name) == 0 && detpassenger->seatNumber == seat) {
                if(detpassenger->userid!=userId)
                {
                    printf("\nThis ticket cannot be canceled , because this ticket has been booked by another passenger\n");
                    found=1;
                    break;
                }
			// Increase available seats
			for (j = 0; j < numBuses; j++) {
				if (buses[j].busNumber== detpassenger->busNumber) {
					busIndex = j;
					break;
				}
			}
			if(busIndex==-1)
			{
			    printf("bus not found");
			}
			else{
			buses[busIndex].availableSeats++;
			// Remove the passenger
			if(detpassenger->prev==NULL)
            {
                start = detpassenger->next;
                detpassenger->next=NULL;
            }
            else if(detpassenger->next==NULL)
            {
                detpassenger->prev->next=NULL;
                detpassenger->prev=NULL;
            }
            else
            {
			detpassenger->prev->next=detpassenger->next;
			detpassenger->next->prev = detpassenger->prev;
			}

			found = 1;
			free(detpassenger);
			printf("Ticket canceled successfully!\n");
			count=1;
            //to select the seats
            for(i=0;i<40;i++)
            {
                if(count==seat)
                {
                    r=(count/5);
                    h=(count%5)-1;
                    if(h==-1)
                    h=4;
                    if(count%5==0)
                    r=r-1;
                    buses[busIndex].bookedseats[r][h]=0;
               }
               count++;
            }
			break;
		}}
        /*printf("Try for next passenger or recheck passengers name. \n");
        printf("DO YOU WANT TO RECHECK THE PASSENGER \n");
        printf("\n1.yes,i want to recheck \n 2. no,i want to move to next passenger");
        scanf("%d",&r);
        switch(r)
        {
            case 1: k=k-1;break;
            case 2 : break;
            default: printf("please select valid option");
        }*/
        detpassenger=detpassenger->next;
	}

	if(found==0){
        printf("passenger with name %s not found",name);
	}
	}
	}
    }


// Function to check bus status
void checkBusStatus(struct Bus buses[], int numBuses,
					int userId)
{

    int i,count=1,j,busNumber;;
    printf("\nEnter Bus Number: ");
	scanf("%d", &busNumber);
	// Find the bus with the given busNumber
	int busIndex = -1,c=0;
	for (int i = 0; i < numBuses; i++) {
		if (buses[i].busNumber == busNumber) {
			busIndex = i;
			break;
		}
	}
	printf("%d\n",busIndex);
	printf("\nBus Number: %d\n", buses[busIndex].busNumber);
	printf("Source: %s\n", buses[busIndex].source);
	printf("Destination: %s\n", buses[busIndex].destination);
	printf("Total Seats: %d\n", buses[busIndex].totalSeats);
	printf("Available Seats: %d\n",buses[busIndex].availableSeats);
	printf("booked seat are : \n");
	for(i=0;i<8;i++)
    {
        for ( j = 0; j<5; j++)
        {
            if(buses[busIndex].bookedseats[i][j]==1)
            {
            printf("%d \n",count);
            c=1;
            }
            count++;
        }

    }
    if(c==0)
    {
        printf("all seats are free");
    }
	printf("adult ticket price is : %.2f\n", buses[busIndex].fare);
	printf("child ticket price is : %.2f\n", buses[busIndex].childticket);
}

int main()
{
	// Initialize user data
	struct User users[5] = {
		{ "user1", "password1" }, { "user2", "password2" },
		{ "user3", "password3" }, { "user4", "password4" },
		{ "user5", "password5" },
	};
	int numUsers = 5;

	// Initialize bus data
	struct Bus buses[5] = {
		{ 101, "huzurabad", "hyderabad", 50, 50, {0}, 180.0, 90.0},
		{ 102, "hanamkonda", "adilabad", 40, 40, {0}, 250.0, 90.0},
		{ 103, "karimnagar", "khammam", 30, 30, {0}, 200.0, 80.0}, {104, "warangal" , "delhi" ,40, 40, {0}, 1500.000, 300.0},{105, "hyderabad", "banglore", 30,30, 775.00, 250.0}
	};
	int numBuses = 5;

     //nul l// Array to store passenger
						// information
	int numPassengers = 0; // Number of passengers

	int loggedInUserId = -1; // Index of the logged-in user

	while (1) {
		if (loggedInUserId == -1) {
			displayMainMenu();
			int choice;
			scanf("%d", &choice);

			if (choice == 1) {
				char username[50];
				char password[50];

				printf("Enter Username: ");
				scanf("%s", username);
				printf("Enter Password: ");
				scanf("%s", password);

				loggedInUserId = loginUser(
					users, numUsers, username, password);
				if (loggedInUserId == -1) {
					printf("Login failed. Please check "
						"your username and password.\n");
				}
				else {
					printf(
						"Login successful. Welcome, %s!\n",
						username);
				}
			}
			else if (choice ==2)
			{
			    char entereduser[100];
			    char enteredpassword[100];
			    printf("enter the user name :");
			    scanf("%s",&entereduser);
			    printf("enter the user password :");
			    scanf("%s",&enteredpassword);
				loggedInUserId = signup(entereduser,enteredpassword,numUsers);
				if (loggedInUserId == -1) {
					printf("Login failed. Please check your username and password.\n");
				}
				else {
					printf("Login successful. Welcome, %s !\n",entereduser);
				}
			}

			else if (choice == 3) {
				printf("Exiting the program.\n");
				break;
			}
			else {
				printf(
					"Invalid choice. Please try again.\n");
			}
		}
		else {
			displayUserMenu();
			int userChoice;
			scanf("%d", &userChoice);

			switch (userChoice) {
			case 1:
				bookTicket(buses, numBuses, loggedInUserId);
				break;
			case 2:
				cancelTicket(buses, numBuses,loggedInUserId);

				break;
			case 3:
				checkBusStatus(buses, numBuses,
							loggedInUserId);
				break;
           case 4:
                viewdetails();
                break;
			case 7:
				printf("Logging out.\n");
				loggedInUserId = -1;
				break;
            case 5:
                viewallbuses(buses,numBuses);
                break;
            case 6:
                searchbus(buses,numBuses);
			default:
				printf(
					"Invalid choice. Please try again.\n");
			}
		}
	}

	return 0;
}
