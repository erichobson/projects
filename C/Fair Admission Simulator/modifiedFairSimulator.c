#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// constant variables
#define ADMISSION_COST      15.26
#define RIDE_COST            1.13  
#define PASS_COST           43.51
#define TOTAL_GUESTS          300
#define AVAILABLE_TICKETS    5000
#define AVAILABLE_PASSES      200
#define TOTAL_RIDES            10
#define PURCHASE_LOOPS         20

// typedef structs
typedef struct TicketBooth{
  int tickets;
  int passes;
  float sales;
} TicketBooth;

typedef struct Ride{
  char *name;
  int  ticketCost;
  int  heightRequirement;
  int  guestsAdmitted;
  int  guestsRejected;
} Ride;

typedef struct Guest{
  int age;
  int height;
  float money;
  int ticketsOwned;
  int passOwned;
  int numberOfRides;
  int admitted;
} Guest;

typedef struct Fair{
  TicketBooth fairBooth;
  Ride        fairRides[TOTAL_RIDES];    
} Fair;

// forward declarations
void populateGuest(struct Guest *Guest);
void populateRide(struct Ride *Ride, int k);
int admitGuest(struct Guest *Guest, struct Fair *Fair);
int purchaseTickets(struct Guest *Guest, struct Fair *Fair, int t);
int purchasePass(struct Guest *Guest, struct Fair *Fair);
void attemptRide(struct Guest *Guest, struct Ride *Ride);

// main
int main(){

  // create rand() seed
  srand(time(NULL));

  // initialize local variables
  int i, q; // iterators
  int r, s; // rand() variables
  int g;    // flag
  int ticketBundles[7] = {10, 15, 20, 25, 30, 35, 40};
  int h = PURCHASE_LOOPS;

  // create initial fair struct
  struct Fair   myFair;
  struct Fair   *FairPtr = &myFair;

  // initialize struct variables using pointers
  FairPtr->fairBooth.tickets = AVAILABLE_TICKETS;
  FairPtr->fairBooth.passes  = AVAILABLE_PASSES;
  FairPtr->fairBooth.sales   = 0;

  // dynamically create array of pointers for guests and rides
  struct Guest **guests = (struct Guest **) malloc(TOTAL_GUESTS * sizeof(Guest *));
  struct Ride **rides = (struct Ride **) malloc(TOTAL_GUESTS * sizeof(Ride *));
  
  // dynamically allocate memory for guests and rides
  for(i = 0; i < TOTAL_GUESTS; i++) guests[i] = (struct Guest *) malloc(TOTAL_GUESTS * sizeof(Guest));
  for(i = 0; i < TOTAL_RIDES; i++) rides[i] = (struct Ride *) malloc(TOTAL_RIDES* sizeof(Ride));

  // initialize each element of rides to point to corresponding element of myFair.
  for(i = 0; i < TOTAL_RIDES; i++) rides[i] = &(myFair.fairRides[i]);

  // populate guests using populateGuest() function
  for(i = 0; i < TOTAL_GUESTS; i++) populateGuest(guests[i]);

  // populate rides using populateRide() function
  for(i = 0; i < TOTAL_RIDES; i++) populateRide(rides[i], i);

  // simulate admitting guest to the fair using admitGuest() function
  for(i = 0; i < TOTAL_GUESTS; i++) guests[i]->admitted = admitGuest(guests[i], FairPtr);
  
  // simulate the purchase of either a pass or tickets per guest randomly
  for(i = 0; i < TOTAL_GUESTS; i++){
    g = 0;            // flag used to determine whether purchase was sucessful or not
    r = rand() % 10;  // random variable between 0-9 used to calculate 50/50 probability

    // 50% chance to purchase tickets
    if(r < 5){
      s = rand() % 7;   // random variable between 0-6 used to select amount of tickets 
                        // to buy from ticketBundles {10, 15, 20, 25, 30, 35, 40}

      // loop used to iterate down from initial value of ticketBundles if guest cannot afford tickets                    
      while(s >= 0){
        g = purchaseTickets(guests[i], FairPtr, ticketBundles[s]);
        s -= 1;
        if(g == 1){
          break;    // breaks if user successfully purchases tickets
        }else{
          continue;
        }
      }

      // loop used if guest fails to purchase tickets
      if(g == 0){
        q = 5;          // final amount of tickets to attempt to purchase
        while(q > 0){   // iterates down by 1 until guest successfully purchases q ticket(s)
          g = purchaseTickets(guests[i], FairPtr, q);
          if(g == 1){
            break;
          }else{
            q -= 1;
          }
        }
      }

    // 50% chance to purchase pass
    }else if(r >= 5){
      // guest attemps to purchase pass
      g = purchasePass(guests[i], FairPtr);
      if(g != 1){               // is purchase of pass unsuccessful
        q = 40;                 // increments down by 5, starting at 40 and attemps to purchase q tickets
        while(q >= 0){
          g = purchaseTickets(guests[i], FairPtr, q);
          if(g == 1 || q == 1){ // if purchase successful OR if guest fails to purchase 1 ticket
            break;
          }else if(q <= 5){     // if q equal <= 5, decrements by 1 until final loop
            q -= 1;
          }else{
            q -= 5;             // else decrements by 5
          }
        }
      }else if(g == 1){         // purchase of pass was successful
        continue;
      }
    }
  }

  // printf all of the guests and their purchases
  printf("Guests after purchases:\n");
  for(i = 0; i < TOTAL_GUESTS; i++){
    if(guests[i]->admitted == 0){
      printf("Guest #%3d: NOT ADMITTED\n", i);
    }else{
      if(guests[i]->passOwned == 1){
        printf("Guest #%3d, Age: %2d, Height: %3dcm, Money: $%6.02f, Tickets:PASS, Rides:%3d\n", 
              i, guests[i]->age, guests[i]->height, guests[i]->money, guests[i]->numberOfRides);
      }else{
      printf("Guest #%3d, Age: %2d, Height: %3dcm, Money: $%6.02f, Tickets:%4d, Rides:%3d\n", 
              i, guests[i]->age, guests[i]->height, guests[i]->money, guests[i]->ticketsOwned, guests[i]->numberOfRides);
      }
    }
  }

  // loop that repeats h times (20)
  while(h > 0){
    for(i = 0; i < TOTAL_GUESTS; i++){
      s = rand() % 5;   // random variable used to choose from rides
      if(guests[i]->age <= 12){
        // guest is < 13 years old, so selects random ride from first 5 elements 
        // of rides using initial random variable between 0-4

        // if guest has no ticekts and no pass - skip
        if(guests[i]->ticketsOwned == 0 && guests[i]->passOwned == 0){
          continue;
        
        // else run attemptRide()
        }else attemptRide(guests[i], rides[s]);  

      }else if(guests[i]->age > 12){
        // guest is > 12 years old, so selects random ride from last 5 elements
        // of rides using initial random variable (+5) between 5-9
        s += 5;

        // if guest has no ticekts and no pass skip
        if(guests[i]->ticketsOwned == 0 && guests[i]->passOwned == 0){
          continue;

        // else run attemptRide()
        }else attemptRide(guests[i], rides[s]);
      }
    }
    h--;
  }
  
  // printf all of the guests and their stats
  printf("\nGuests after rides:\n");
  for(i = 0; i < TOTAL_GUESTS; i++){
    if(guests[i]->passOwned == 1){
      printf("Guest #%3d, Age: %2d, Height: %3dcm, Money: $%6.02f, Tickets:PASS, Rides:%3d\n", 
              i, guests[i]->age, guests[i]->height, guests[i]->money, guests[i]->numberOfRides);
    }else{
      printf("Guest #%3d, Age: %2d, Height: %3dcm, Money: $%6.02f, Tickets:%4d, Rides:%3d\n", 
              i, guests[i]->age, guests[i]->height, guests[i]->money, guests[i]->ticketsOwned, guests[i]->numberOfRides);
    }
  }

  // printf the results of the fair
  printf("\n\nHere are the fair results:\n\n$ %5.02f has been earned.%4d passes and %d tickets were not sold.\n\nHere are the ride statistics:\n\n", 
          FairPtr->fairBooth.sales, FairPtr->fairBooth.passes, FairPtr->fairBooth.tickets);

  // printf the results of the rides
  for(i = 0; i < TOTAL_RIDES; i++){
    printf("%14s allowed %3d guests on but turned away %3d guests\n", 
            FairPtr->fairRides[i].name, FairPtr->fairRides[i].guestsAdmitted, FairPtr->fairRides[i].guestsRejected);
  }
  printf("\n");

  free(guests);
  free(rides);

  return 0;
}
// end

// functions
/***********************************************************************************
populateGuest(struct Guest *Guest)

Purpose: Populate a guest passed in by reference
Assumption: Guest has been previously allocated

Input
Guest - Pointer to a guest to be initialized

Output
None

Return
Void
***********************************************************************************/
void populateGuest(struct Guest *Guest){

  // minimum value to be chosen at random for initial money
  int minMoney[5] = {20, 22, 24, 26, 28};

  // values to be chosen at random for aditional money and age calculation
  int randMoney[6] = {20, 25, 30, 35, 40, 45};

  // age arrays split based on 50/50 chance
  int ageFirst[7] = {13, 14, 15, 16, 17, 18, 19};
  int ageSecond[54] = { 5,  6,  7,  8,  9, 10, 11, 12,
                       20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
                       30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
                       40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
                       50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
                       60, 61, 62, 63, 64, 65};

  // initialize zero structures
  Guest->passOwned = 0;
  Guest->ticketsOwned = 0;
  Guest->numberOfRides = 0;

  // randomly select initial money
  int j = rand() % 5;
  Guest->money = minMoney[j];

  // randomaly select age 
  j = rand() % 100;
  // 50% chance between 13-19 
  if(j < 50){ 
    j = rand() % 7;
    Guest->age = ageFirst[j];

  // 50% chance between 5-12 or 20-65
  }else{      
    j = rand() % 54;
    Guest->age = ageSecond[j];
  }

  // adds more money based on decades alive * randomly selected value
  if(Guest->age >= 10){
    Guest->money += ((Guest->age / 10) * randMoney[rand() % 6]);
  }

  // randomly assigns height based on age
  // if guest 12 or younger, height is (age * 6) + (random number between 72-81)
  if(Guest->age <= 12){
    Guest->height = (Guest->age * 6) + ((rand() % 10) + 72);

  // if guest 13 or older, height is randomly assigned between 149-280
  }else{
    Guest->height = (rand() % 132) + 149;
  }
}

/***********************************************************************************
populateRide(struct Ride *Ride, int k)

Purpose: Populate a ride passed in by reference
Assumption: Ride has been previously allocated

Input
Ride - Pointer to a ride to be initialized
k    - iterator to determine which values of array to use

Output
None

Return
Void
***********************************************************************************/
void populateRide(struct Ride *Ride, int k){

  char *rides[TOTAL_RIDES] = {"Fun House", "Merry-Go-Round", "Calm Train", 
                              "Tea Cups", "Ferris Wheel", "Back Destroyer", 
                              "Pirate Ship", "Drop To Death", "Roller Coaster",
                              "Tummy Tosser"};

  int reqiredTickets[TOTAL_RIDES] = {1, 2, 3, 3, 4, 4, 4, 5, 5, 5};

  int requiredHeight[TOTAL_RIDES] = {60, 60, 105, 108, 110, 150, 152, 154, 156, 160};

  Ride->name = rides[k];
  Ride->ticketCost = reqiredTickets[k];
  Ride->heightRequirement = requiredHeight[k];
  Ride->guestsAdmitted = 0;
  Ride->guestsRejected = 0;
}

/***********************************************************************************
admitGuest(struct Guest *Guest, struct Fair *Fair)

Purpose: Guest attemps to purchase admission to fair

Assumption: Guest has been previously allocated
            Fair has been previously allocated

Input
Guest - Pointer to a guest to have structures updated
Fair  - Pointer to a fair to have structures updated

Output
Guest - money updated accordingly
Fair  - sales updated accordingly

Return
0 - guest was not admitted
1 - guest was admitted
***********************************************************************************/
int admitGuest(struct Guest *Guest, struct Fair *Fair){
  int a = 0;

  // guest is 6 or younger - free admission
  if(Guest->age <= 6){
    a = 1;

  // guest is between 7 and 12 - half-priced admission
  }else if(Guest->age > 6 && Guest->age < 13){

    // guest not enough money - unsuccessful
    if(Guest->money - (ADMISSION_COST/2) < 0){
      a = 0;

    //guest has enough money - successful
    }else{
      Guest->money -= (ADMISSION_COST/2);
      Fair->fairBooth.sales += (ADMISSION_COST/2);
      a = 1;
    }

  // guest is 13 or older - full-priced admission
  }else if(Guest->age >= 13){

    // guest not enough money - unsuccessful
    if(Guest->money - ADMISSION_COST < 0){
      a = 0;

    // guest has enough money - successful
    }else{
      Guest->money -= ADMISSION_COST;
      Fair->fairBooth.sales += ADMISSION_COST;
      a = 1;
    }
  }
  return a;
}

/***********************************************************************************
purchaseTickets(struct Guest *Guest, struct Fair *Fair, int t)

Purpose: Guest attemps to purchase t amount of tickets 

Assumption: Guest has been previously allocated
            Fair has been previously allocated
            t is a valid positive integer

Input
Guest - Pointer to a guest to have structures updated
Fair  - Pointer to a fair to have structures updated
t     - Number of tickets requested

Output
Guest - money / ticketsOwned updated accordingly
Fair  - sales / tickets updated accordingly

Return
0 - purchase of tickets unsuccessful
1 - purchase of tickets successful
***********************************************************************************/
int purchaseTickets(struct Guest *Guest, struct Fair *Fair, int t){
  int a = 0;
  float c = 0;

  // guest not admitted / fair out of tickets - unsuccessful
  if(Guest->admitted == 0 || Fair->fairBooth.tickets - t < 0){
    a = 0;
  
  }else{
    // determines cost of tickets requested
    c = t * RIDE_COST;

    // guest has enough money - successful
    if(Guest->money - c >= 0){
      Guest->money -= c;
      Guest->ticketsOwned += t;
      Fair->fairBooth.sales += c;
      Fair->fairBooth.tickets -= t;
      a = 1;

    // guest not enough money - unsuccessful
    }else{
      a = 0;
    }
  }
  return a;
}

/***********************************************************************************
purchasePass(struct Guest *Guest, struct Fair *Fair)

Purpose: Guest attempts to purchase pass

Assumption: Guest has been previously allocated
            Fair has been previously allocated

Input
Guest - Pointer to a guest to have structures updated
Fair  - Pointer to a fair to have structures updated

Output
Guest - money / passOwned updated accordingly
Fair  - sales / passes updated accordingly

Return
0 - purchase of pass unsuccessful
1 - purchase of pass successful
***********************************************************************************/
int purchasePass(struct Guest *Guest, struct Fair *Fair){
  int a = 0;

  // guest not admitted / fair out of passes / guest not enough money - unsuccessful
  if(Guest->admitted == 0 || Fair->fairBooth.passes == 0 || (Guest->money - PASS_COST) < 0){
    a = 0;

  // guest has enough money - successful
  }else{
    Guest->money -= PASS_COST;
    Guest->passOwned = 1;
    Fair->fairBooth.sales += PASS_COST;
    Fair->fairBooth.passes -= 1;

    a = 1;
  }
  return a;
}

/***********************************************************************************
attemptRide(struct Guest *Guest, struct Ride *Ride)

Purpose: 1) Determine whether guest is correct height to go on ride
         2) Determine whether guest has pass or enough tickets
         3) Rejects or Admits accordingly 
        
Assumption: Guest has been previously allocated
            Ride has been previously allocated

Input
Guest - Pointer to a guest to have structures updated
Ride  - Pointer to a ride to have structures updated

Output
Guest - numberOfRides / ticketsOwned updated accordingly
Ride  - guestsAdmitted / guestsRejected updated accordingly

Return
Void
***********************************************************************************/
void attemptRide(struct Guest *Guest, struct Ride *Ride){
  // checks if guest meets heightRequirement
  if(Guest->height >= Ride->heightRequirement){

    // guest meets heightRequirement and has pass - admit
    if(Guest->passOwned == 1){
      Guest->numberOfRides += 1;
      Ride->guestsAdmitted += 1;

    // guest meets heightRequirement and has enough tickets - admit
    }else if(Guest->passOwned == 0 && Guest->ticketsOwned >= Ride->ticketCost){
      Guest->ticketsOwned -= Ride->ticketCost;
      Guest->numberOfRides += 1;
      Ride->guestsAdmitted += 1;
    }
  // guest does not meet heighRequirement - reject
  }else if(Guest->height < Ride->heightRequirement){
    Ride->guestsRejected += 1;
  }
}
