/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Ryan Cleminson
 * Student ID: 13555089
 * Date of submission: 
 * A brief statement on what you could achieve (less than 50 words):
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/

#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"
#define MAX_ARRIVECODE_LEN 100

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/

struct date_time { 
    int month; 
    int day; 
    int hour; 
    int minute;
}; 
typedef struct date_time date_time_t; 

struct flights { 
    char flightcode[MAX_FLIGHTCODE_LEN+1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN+1];
    date_time_t arrival_dt;
}; 
typedef struct flights flight_t; 

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void print_menu (void);
int addFlight(flight_t flights[], int flightCount);
void displayFlightsToDest(flight_t flights[], int flightCount);
void saveFlights(flight_t flights[MAX_NUM_FLIGHTS], int flightCount);
int loadFlights(flight_t flights[MAX_NUM_FLIGHTS], int flightCount);

/*******************************************************************************
 * Main
*******************************************************************************/

int main(void)
{
    
    
    int option;
    flight_t flights[MAX_NUM_FLIGHTS];
    int flightCount;
    flightCount = 0;
    _Bool check;
    
    do
    {   
        option = 0;
        check = 1;
        do
        {

            print_menu();
            scanf("%d", &option);
            
            if (option < 1 || option > 5)
            {
                check = 1;
                printf("Invalid choice\n");
            }
            else 
            {
                check = 0;
            }

        } while (check == 1);
        
        switch (option)
        {
            case 1:
                flightCount = addFlight(flights, flightCount);
                break;
            case 2:
                displayFlightsToDest(flights, flightCount);
                break;
            case 3:
                saveFlights(flights, flightCount);
                break;
            case 4:
                flightCount = loadFlights(flights, flightCount);
                break;
            case 5:
                break;
        }
    } while (option != 5);

    return 0;
    
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_menu (void)
{
    printf("\n"
    "1. add a flight\n"
    "2. display all flights to a destination\n"
    "3. save the flights to the database file\n"
    "4. load the flights from the database file\n"
    "5. exit the program\n"
    "Enter choice (number between 1-5)>\n");
}
/*******************************************************************************
 * This function adds a new flight to the flights through the terminal. 
 * inputs:
 * - flights(Current), flightCount
 * outputs:
 * - flights(Updated)
*******************************************************************************/
int addFlight(flight_t flights[MAX_NUM_FLIGHTS], int flightCount)
{

    _Bool check;
    check = 0;

    /******************************************************************************
     * Flight Code    
    *******************************************************************************/
    if (flightCount <= MAX_NUM_FLIGHTS-1) {
        
        do
        {
            printf("Enter flight code>\n");
            scanf("%s", flights[flightCount].flightcode);
            
            if (strlen(flights[flightCount].flightcode) <= 6 && strlen(flights[flightCount].flightcode) >= 3)
            {     
                if (flights[flightCount].flightcode[0] >= 'A' && flights[flightCount].flightcode[0] <= 'Z') 
                { 
                    if (flights[flightCount].flightcode[1] >= 'A' && flights[flightCount].flightcode[1] <= 'Z') 
                    {    
                        if (flights[flightCount].flightcode[2] >= '0' && flights[flightCount].flightcode[2] <= '9'){
                            check = 1;
                        }
                        else
                        {
                            check = 0;
                            printf("Invalid input\n");
                        }
                    }
                    else 
                    {
                        check = 0;
                        printf("Invalid input\n");
                    }
                }
                else 
                {
                    check = 0;
                    printf("Invalid input\n");
                }
            }
            else 
            {
                check = 0;
                printf("Invalid input\n");
            }

        } while (check == 0);

        /******************************************************************************
         * Depart Info  
        *******************************************************************************/
       
        check = 0;
        printf("Enter departure info for the flight leaving SYD.\n");

        do
        {

            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &flights[flightCount].departure_dt.month, &flights[flightCount].departure_dt.day, &flights[flightCount].departure_dt.hour, &flights[flightCount].departure_dt.minute);

            if (flights[flightCount].departure_dt.month >= 1 && flights[flightCount].departure_dt.month <= 12) {
                if (flights[flightCount].departure_dt.day >= 1 && flights[flightCount].departure_dt.day <= 31) {
                    if (flights[flightCount].departure_dt.hour >= 0 && flights[flightCount].departure_dt.hour <= 23) {
                        if (flights[flightCount].departure_dt.minute >= 0 && flights[flightCount].departure_dt.minute <= 59) {
                            check = 1;
                        }
                        else
                        {
                            check = 0;
                            printf("Invalid input\n");                        
                        }
                    }
                    else
                    {
                        check = 0;
                        printf("Invalid input\n");
                    }
                } 
                else
                {
                    check = 0;
                    printf("Invalid input\n");
                } 
            }
            else
            {
                check = 0;
                printf("Invalid input\n");
            }
            
        } while (check == 0);

        /******************************************************************************
         * Arrival City Code 
        *******************************************************************************/
        
        char arrival_code[100];
        printf("Enter arrival city code>\n");
        scanf("%s", arrival_code);
        strcpy(flights[flightCount].arrival_city, arrival_code);
        flights[flightCount].arrival_city[strlen(flights[flightCount].arrival_city)+1] = '\0';
        
        /******************************************************************************
         * Arrival Info
        *******************************************************************************/

        check = 0;
        printf("Enter arrival info.\n");

        do
        {

            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &flights[flightCount].arrival_dt.month, &flights[flightCount].arrival_dt.day, &flights[flightCount].arrival_dt.hour, &flights[flightCount].arrival_dt.minute);
            
            if (flights[flightCount].arrival_dt.month >= 1 && flights[flightCount].arrival_dt.month <= 12) {
                if (flights[flightCount].arrival_dt.day >= 1 && flights[flightCount].arrival_dt.day <= 31) {
                    if (flights[flightCount].arrival_dt.hour >= 0 && flights[flightCount].arrival_dt.hour <= 23) {
                        if (flights[flightCount].arrival_dt.minute >= 0 && flights[flightCount].arrival_dt.minute <= 59) {
                            check = 1;
                            flightCount = flightCount + 1;
                        }
                        else
                        {
                            check = 0;
                            printf("Invalid input\n");
                        }
                    }
                    else
                    {
                        check = 0;
                        printf("Invalid input\n");
                    }
                }
                else
                {
                    check = 0;
                    printf("Invalid input\n");
                }  
            }
            else
            {
                check = 0;
                printf("Invalid input\n");
            }
        } while(check == 0);
    }
    else
    {
        printf("Cannot add more flights - memory full\n");
    }

    return flightCount;

}

/*******************************************************************************
 * This function adds a new flight to the flights through the terminal. 
 * inputs:
 * - flights, flightcount
 * outputs:
 * - A print of all the data stored in flights
*******************************************************************************/
void displayFlightsToDest(flight_t flights[MAX_NUM_FLIGHTS], int flightCount)
{

    char searchArrivalCity[20];
    int i,i2;
    int space;
    _Bool check;
    _Bool check2;
   
    check2 = 0;
    printf("Enter arrival city code or enter * to show all destinations>\n");
    scanf("%s", searchArrivalCity);
    
    if (flightCount >= 0) 
    {

        if (strcmp(searchArrivalCity, "*")== 0) 
        {

            printf("Flight Origin          Destination\n");
            printf("------ --------------- ---------------\n");

            for(i = 0; i < flightCount; i++)
            {
                printf("%s", flights[i].flightcode);
                
                space = MAX_FLIGHTCODE_LEN - strlen(flights[i].flightcode);
            
                for( i2 = 0; i2 <= space; i2++)
                {
                    printf(" ");
                }
                printf("SYD %.2d-%.2d %.2d:%.2d %.3s",flights[i].departure_dt.month, flights[i].departure_dt.day, flights[i].departure_dt.hour, flights[i].departure_dt.minute, flights[i].arrival_city); 
                
                if (strlen(flights[i].arrival_city)> 3)
                {
                    space = MAX_CITYCODE_LEN - 3;
                }
                else
                {
                    space = MAX_CITYCODE_LEN - strlen(flights[i].arrival_city);
                }
                
                for( i2 = 0; i2 <= space; i2++)
                {
                    printf(" ");
                }
                printf("%.2d-%.2d %.2d:%.2d\n", flights[i].arrival_dt.month, flights[i].arrival_dt.day, flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
                check = 0;
            }
        }
        else 
        {
            
            for( i = 0; i < flightCount; i++)
            {
                
                if (strcmp(searchArrivalCity, flights[i].arrival_city)== 0) 
                {
                    if (check2 == 0) 
                    {
                        printf("Flight Origin          Destination\n");
                        printf("------ --------------- ---------------\n");
                        check2 = 1;
                    }
                    
                    printf("%s", flights[i].flightcode);
                    space = MAX_FLIGHTCODE_LEN - strlen(flights[i].flightcode);

                    for( i2 = 0; i2 <= space; i2++)
                    {
                        printf(" ");
                    }

                    printf("SYD %.2d-%.2d %.2d:%.2d %.3s",flights[i].departure_dt.month, flights[i].departure_dt.day, flights[i].departure_dt.hour, flights[i].departure_dt.minute, flights[i].arrival_city); 
                    space = MAX_CITYCODE_LEN - strlen(flights[i].arrival_city);

                    for( i2 = 0; i2 <= space; i2++)
                    {
                        printf(" ");
                    }

                    printf("%.2d-%.2d %.2d:%.2d\n", flights[i].arrival_dt.month, flights[i].arrival_dt.day, flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
                    check = 0;

                }
                else
                {
                    check = 1;
                }
            }
        }
    }
    else
    {
        check = 1;
    }
    
    if (check == 1) 
    {
        printf("No flights\n");
    }
    
}

/*******************************************************************************
 * This function adds a new flight to the flights through the terminal. 
 * inputs:
 * - flights, flightCount
 * outputs:
 * - file containing flightCount and the array of structures: flights
*******************************************************************************/
void saveFlights(flight_t flights[MAX_NUM_FLIGHTS], int flightCount)
{
    
    FILE *fp=NULL;
    int i;
    fp = fopen("database.txt", "w");

    if (fp==NULL) 
    {
        printf("Write error\n");
        return;
    }

    fprintf(fp,"%d\n",flightCount);
    for( i = 0; i < flightCount; i++)
    {
        fprintf(fp,"%s\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%d\t%d\n", flights[i].flightcode, flights[i].departure_dt.month, flights[i].departure_dt.day, flights[i].departure_dt.hour, flights[i].departure_dt.minute, flights[i].arrival_city, flights[i].arrival_dt.month, flights[i].arrival_dt.day, flights[i].arrival_dt.hour, flights[i].arrival_dt.minute);
    }

    fclose(fp);

}

/*******************************************************************************
 * This function adds a new flight to the flights through the terminal. 
 * inputs:
 * - flights, fLightCount
 * outputs:
 * - flights(Loaded), fLightCount(Loaded)
*******************************************************************************/
int loadFlights(flight_t flights[MAX_NUM_FLIGHTS], int flightCount)
{

    FILE *fp;
    int i;
    fp = fopen("database.txt", "r");

    if (fp==NULL) 
    {
        printf("Read error\n");
        return flightCount;
    }

    fscanf(fp,"%d\n", &flightCount);
    
    for( i = 0; i <= flightCount; i++)
    {
        if (i > MAX_NUM_FLIGHTS) 
        {
            printf("Read error\n");
            fclose(fp);
            return flightCount;
        }
        fscanf(fp,"%s\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%d\t%d\n", &*flights[i].flightcode, &flights[i].departure_dt.month, &flights[i].departure_dt.day, &flights[i].departure_dt.hour, &flights[i].departure_dt.minute, &*flights[i].arrival_city, &flights[i].arrival_dt.month, &flights[i].arrival_dt.day, &flights[i].arrival_dt.hour, &flights[i].arrival_dt.minute);
    }

    fclose(fp);
    return flightCount;
}