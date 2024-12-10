#include<stdio.h>
#include<string.h>  //this header file is included to do operations regarding the string 
#include<malloc.h>  //this header file is included to to use the malloc funtion for memory allocation  
//#include<stdlib.h>

//creating a struct of passenger type to store the information of passenger 
struct Passanger{
    char aadhar_number[12];  // aadhar number is taken as character for furtheer implementations
    char passanger_name[50];  //character string for passanger name 
    int age; //age of the passenger
    char gender[2]; //gender information of passenger
    struct Passanger * next;  //pointer to Passanger to hold the address of next linked list node
    int seat_number;
};

int array_size;  //globally declaring the array_size varibale to use this same notation throught the program


//hash function the heart of hashing technique is declared here this function takes aadhar number as unique id in the form of character and total seats available in the flight
int Hash_Function(char unique_id[], int total_seats) {
    int first=0, second=0, third=0, fourth=0;  //here in the hash function we have used the folding method by deviding the 12 digit aadhar number into 4 parts to perform folding method 
    for(int i=0; i<12; i++){   //iterating through a loop till 12 iterations as we know that the aadhar numbeer only consist of 12 numberrs
        int num = unique_id[i] - '0';  //the aadhar number we accepted as a character value to iterate now typecasting it into the integer
        if (i <= 3) first = first * 10 + num;  //breaking the number in 3 parts the first three digit will be stored in the first variable
        else if (i <= 6) second = second * 10 + num;// next three value will be stored in the second part 
        else if (i <= 9) third = third * 10 + num;  //next will b ein the third part
        else fourth = fourth * 10 + num; // similarly the last three digits willn be stored in this 
    }
    int hash_value = (first + second + third + fourth) % total_seats;  // the hash value is generated by adding all the parts and finding the modulo by the total setas in the flight in order to keep the hash value index with in the required range 
    return hash_value;
}

//this function is dedciated to book tickets functionality 
int Book_Ticket(struct Passanger * arr[array_size]) {  //this function take the array array of type struct passanger as a argument 
    struct Passanger *temp = NULL;  // initialising and declaring the temp pointer to ease out the traversing work
    printf("\n\t\t\t\t<=<=<=<=<=<= TICKET BOOKING WINDOW =>=>=>=>=>=>=>=>");
    printf("\n\nProvide the Required Details");
    

    //asking for passanger name by declaring the pname varibale of char datatupe and for flexibilty the size of character string is set up to 50 characters
    char Pname[50];
    printf("\nEnter the Passenger Name:");
    scanf("%s", Pname);  //%s for format specifier as we are accepting the string of charatcers
    

    //asking for aadhar number as character for furtheer hashing implementation function
    char aadhar[12];
    printf("\nEnter the Aadhar Number:");
    scanf("%s", aadhar);
    

    //varibale is initialised for passangers age 
    int p_age;
    printf("\nEnter the age of the passenger:");
    while (scanf("%d", &p_age) != 1) {  // here validations was given if the age of the passanger if the input is invalid then again user have to enter the age 
        printf("Invalid input! Please enter a valid age (numeric value): ");
        while(getchar() != '\n');  // for clearing the buffer values
    }
    //the varibale initialising and declaration for passangers gender
    char p_gender;
    printf("\nEnter the gender of the passenger:");
    scanf(" %c", &p_gender);  // Added space before %c for reading single character

    //allocated the memory for the node for passangeer by type casting it into struct passanger type
    struct Passanger *Passanger_node = (struct Passanger *)malloc(sizeof(struct Passanger));
    strcpy(Passanger_node->passanger_name, Pname);  //strcpy function is used to deal with the string and passanger_name varibale in the struct Passanger node is initialised with the value taken in the function
    strcpy(Passanger_node->aadhar_number, aadhar);  //same for aadhar number 
    Passanger_node->age = p_age; //assigning the value of age to the age varibale in the struct passanger 
    Passanger_node->gender[0] = p_gender;  // Storing gender as a single character
    Passanger_node->gender[1] = '\0';      // Null-terminate the string
    Passanger_node->next = NULL;

    int hash_value = Hash_Function(aadhar, array_size);  //storing the value returned by hash_function into the hash_value variable 
    int i = 0, isemptyindex = 0, newindex;  //declaring and initialising i for probe count 

    if (arr[hash_value] == NULL) {  //comparing that the arr index value returned by hash value is null or not for ex. arr[5]==NUll 
        arr[hash_value] = Passanger_node; //if it is NULL then simply insert the address of the passanger node to the index position as index is pf type struct passanger pointer
        printf("Dear, %s", Pname); // as the tickeet is booked 
        printf("\nYour Seat Is Successfully Booked!!!"); //confirmation message is popedup
        printf("\nYour Seat Number for the flight is: %d", hash_value);  //showing the seat number to the passanger
        printf("\nThank you for using Data Structure Airlines");
        Passanger_node->seat_number=hash_value;
        return 0;
    } else {  // if the hash value generated is not null means that thr value is already existing at that index means the seat is already reserved
        while (i < array_size) {  //iterrating through a loop till the size of array means the total number of seats available 
            newindex = (hash_value + i * i) % array_size;  //as the collision occurs we ahve used the quadratic probe technique to resolve the esolution as it will give cluster free values
            if (arr[newindex] == NULL) {  //again checking if the index of the newindex value generated by is null or not or seat is avialable or not
                arr[newindex] = Passanger_node; // as the seat is available then assign the passenger node to that index
                isemptyindex = 1; //setting it to 1 as true
                printf("Dear, %s", Pname); //again success message with seat number
                printf("\nYour Seat Is Successfully Booked!!!");
                printf("\nYour Seat Number for the flight is: %d", newindex);
                printf("\nThank you for using Data Structure Airlines");
                Passanger_node->seat_number=newindex;
                break;  //breaking the loop as the seat booking is done for the given passsenger
            }
            i=i+1; // inrementing the value of i or probe  by 1
        }
        //checking if the empty index is not found that means that all the seats are reserved then
        if (!isemptyindex) {
            temp = arr[hash_value];
            while (temp != NULL) {
                temp = temp->next;
            }
            temp->next = Passanger_node;  //linking the passenger node in chain in waiting list 
            printf("Your Booking is in WAITING LIST!!");
            printf("You will be informed Soon about the final confirmations!!");
            printf("THANKYOU FOR USING DATA STRUCTURE AIRLINES");
        }
    }
}


//here the this function is used to initialise the array with null 
void array_initialisation(struct Passanger * arr[array_size]) {
    for(int i = 0; i < array_size; i++) {
        arr[i] = NULL;
    }
}


//this function is declared to know the details of all the passengers who have successfully booked theri reservations
void Booked_Passenger_Details(struct Passanger * arr[array_size]) {
    printf("\nDETAILS OF PASSENGER BOOKED SUCCESSFULLY FOR THE FLIGHT!\n");
    printf("\n->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>->>");
    int found=0;
    
    int i = 0;
    while (i < array_size) {
        if (arr[i] != NULL) {
            struct Passanger *holder = arr[i];
            printf("\nSeat Number:%d\n",holder->seat_number);
            printf("Name: %s\n", holder->passanger_name);
            printf("Aadhar: %s\n", holder->aadhar_number);
            printf("Age: %d\n", holder->age);
            printf("-----------------------------------------------");
            found=1;
        }
        i++;
    }
    if(!found){
        printf("No Booking for Now all the seats are non reserved!!");
    }
}


//this function is to cancel the reservation
void Cancel_Booking(struct Passanger * arr[array_size]) {
    char aadhar_to_cancel[12];  //this function takes aadhar number to cancel the ticket 
    printf("\nEnter the Aadhar number of the passenger to cancel the booking: ");
    scanf("%s", aadhar_to_cancel);
    
    //accessing the hash value as the hash value is generated for the aadhar number 
    int hash_value = Hash_Function(aadhar_to_cancel, array_size);
    struct Passanger *temp = arr[hash_value];
    struct Passanger *prev = NULL;

    // Searching  for the passenger with the matching Aadhar number
    while (temp != NULL && strcmp(temp->aadhar_number, aadhar_to_cancel) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nNo passenger found with Aadhar number %s\n", aadhar_to_cancel);
        return;
    }

    // If the passenger is found
    if (prev == NULL) {
        // The passenger is the first node in the list
        arr[hash_value] = temp->next;
    } else {
        // The passenger is not the first node, so link the previous node to the next node
        prev->next = temp->next;
    }

    // Free the memory allocated for the passenger node
    free(temp);

    printf("\nBooking cancelled for Aadhar number: %s\n", aadhar_to_cancel);

    // Handling the case where there is another node linked (waiting booking)
    if (prev != NULL && prev->next != NULL) {
        printf("\nThe next booking in the queue has been linked.\n");
    }
}

int main() {
    printf("\t\t\t\t\t<<-<<-<<-<<-<<-<<-<<- WELCOME TO DATA STRUCTURE AIRLINES ->>->>->>->>->>->>->>");
    printf("\n\t\t\t\t_______________________________________________________________________________________________");
    printf("\n\nEnter the Total Number of Seats in the flight:");
    scanf("%d", &array_size);

    struct Passanger *Flight_Tickets[array_size];
    int option_choose;
    
    array_initialisation(Flight_Tickets); // 

    while (1) {
        printf("\n\nWhat would you like to do?");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n\n1.->>Book Ticket");
        printf("\n2.->>Show All Booked Seats");
        printf("\n3.->>Search Passenger");
        printf("\n4.->>Cancel Booking");
        printf("\n5.->>Exit");
        printf("\n\n ENTER YOUR CHOICE: ");
        scanf("%d", &option_choose);

        switch (option_choose) {
            case 1:
                Book_Ticket(Flight_Tickets);
                break;
            case 2:
                Booked_Passenger_Details(Flight_Tickets);
                break;
            case 4:
                Cancel_Booking(Flight_Tickets);
                break;
            case 5:
                printf("\nExiting the system. Thank you for using Data Structure Airlines!\n");
                exit(0);
                break;
            default:
                printf("\nInvalid option! Please select a valid option.\n");
                break;
        }
    }

    return 0;
}
