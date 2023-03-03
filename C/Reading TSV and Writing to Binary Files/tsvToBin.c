#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "apps.h"

// forward declaration
const char *removeClutter(char *str);

// main
int main (){
    FILE *fd;       // tsv file
    FILE *fb;       // binary file

    int bufferLength = MAX_LINE_SIZE;
    char buffer[bufferLength];
    const char *breaker = "\t\n";
    char *line;
    char *token;
    char *part;

    int header = 0;                 // ignore the header
    unsigned short k;               // counter for each column

    // open tsv and check for error
    fd = fopen("googlePlayStore.tsv", "r");    
    if(!fd){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    // open bin and check for error
    fb = fopen("googlePlayStore.bin", "wb+");  
    if(!fb){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    // count the lines in tsv file
    char c;
    unsigned short count = 0;
    for (c = getc(fd); c != EOF; c = getc(fd)) {
        if (c == '\n'){
            count++;
        }     
    }

    // write two bytes count to binary file
    fwrite(&count, sizeof(unsigned short), 1, fb);

    // loops through each line, separating each element by \t\n
    rewind(fd);
    while(fgets(buffer, bufferLength, fd)) {    // loop until end of file
        k = 0;
        line = strdup(buffer);                  // save the line
        token = line;                           // duplicate line

        // only run once to ignore the header line
        if(header == 0){
            while ((part = strsep(&token, breaker))) {  // seperate token by breaker (new tab)
                k++;
                if (k == 13) {      // final column     
                    header = 1;     // sets header flag
                    break;
                }
            }
        }

        while ((part = strsep(&token, breaker))) {      // seperate token by breaker (new tab)

            // name
            if(k == 0){
                unsigned char numChar = strlen(part);           // length of name
                char pName[numChar];                            // store name
                strcpy(pName, part);                            // copy name
                fwrite(&numChar, sizeof(unsigned char), 1, fb); // write length of name to bin
                fwrite(&pName, sizeof(char), numChar, fb);      // write name to bin using length of name
                k++;                                            // next column

            // category
            }else if(k == 1){
                unsigned char z = 0;                            // store category index                         
                while(Categories[z]) {                          // loop through categories
                    if(strcmp(Categories[z], part) == 0) {      // if index == part break
                        break;
                        }
                    z++;
                    }
                fwrite(&z, sizeof(unsigned char), 1, fb);       // write category index to bin
                k++;                                            // next column

            // rating
            }else if(k == 2){
                float rating;                                   // store rating
                float NaN = -1;                                 /* this should be char, but had to change
                                                                   to float because I could not get fread()
                                                                   to work properly. binary file is larger
                                                                   then intended                          */                                           
                if (strcmp("NaN", part) == 0) {                 
                    fwrite(&NaN, sizeof(float), 1, fb);         // if NaN, writes float -1 to bin
                } else {
                    rating = atof(part);                        // store rating with atof()
                    fwrite(&rating, sizeof(float), 1, fb);      // write rating to bin
                }
                k++;                                            // next column

            //reviews
            }else if(k == 3){
                unsigned int reviews = atoi(part);              // store review with atoi()
                fwrite(&reviews, sizeof(unsigned int), 1, fb);  // write review to bin
                k++;                                            // next column

            // size
            }else if(k == 4){
                unsigned int size;                                      // store size
                unsigned int zero = 0;                                  /* this should be char, but had to change
                                                                           to int because I could not get fread()
                                                                           to work properly. binary file is larger
                                                                           then intended                         */                      
                if (strcmp("Varies with device", part) == 0) {
                    fwrite(&zero, sizeof(unsigned int), 1, fb);         // write 'zero' to bin if "varies with device"
                } else if (strcmp("k", &part[strlen(part) - 1]) == 0) { 
                    part[strlen(part)-1] = '\0';                        // if size is in kilobytes, remove 'k' from end
                    size = atoi(part);                                  // store size with atoi()
                    fwrite(&size, sizeof(unsigned int), 1, fb);         // write size to bin
                } else if (strcmp("M", &part[strlen(part) - 1]) == 0) {
                    part[strlen(part)-1] = '\0';                        // if size is in megabytes, remove 'M' from end
                    float pSize = atof(part);                           // store size with atof() in pSize
                    size = pSize * 1024;                                // calculate size in kilobytes
                    fwrite(&size, sizeof(unsigned int), 1, fb);         // write size to bin
                }
                k++;                                                    // next column

            // installs
            }else if(k == 5){
                unsigned int installs;                          // store installs
                removeClutter(part);                            // call removeClutter() to delete ',' and '+' and '"'
                installs = atoi(part);                          // store installs with atoi()
                fwrite(&installs, sizeof(unsigned int), 1, fb); // write installs to bin
                k++;                                            // next column
            
            // type
            }else if(k == 6){
                unsigned char type;                             // store type
                if(strcmp("Free", part) == 0){
                    type = 0;                                   /* if free, set type to '0'. this should not be needed
                                                                   but had to add because I could not get fread() to
                                                                   work properly without it. binary file is larger
                                                                   then intended */
                }else if(strcmp("Paid", part) == 0){
                    type = 1;                                   // if paid set type to '1'
                }
                fwrite(&type, sizeof(unsigned char), 1, fb);    // write type to bin
                k++;                                            // next column

            // price
            }else if(k == 7){
                float price;                                // store price
                if(strcmp("0", part) == 1){                 // if type is 'Paid'
                    removeClutter(part);                    // call removeClutter() to delete '$'
                    price = atof(part);                     // store price with atof()
                    fwrite(&price, sizeof(float), 1, fb);   // write price to bin
                }else{
                    price = 0;                              // if type is 'Free'
                    fwrite(&price, sizeof(float), 1, fb);   /* if free, write price '0' to bin. this should not be 
                                                               needed but had to add because I could not get fread() to
                                                               work properly without it. binary file is larger
                                                               then intended */
                }
                k++;                                        // next column

            // content rating
            }else if(k == 8){
                unsigned char x = 0;                            // store contentRating index
                while(ContentRatings[x]) {                      // loop through ContentRatings
                    if(strcmp(ContentRatings[x], part) == 0) {  // if index == part break
                        break;
                    }
                    x++;
                }
                fwrite(&x, sizeof(unsigned char), 1, fb);       // write contentRating index to bin
                k++;                                            // next column

            // genres
            }else if(k == 9){                       // skip genres
                k++;                                // next column                    

            //last update
            }else if(k == 10){
                unsigned char day;                                      // store day
                unsigned char month = 0;                                // store month index
                unsigned short year;                                    // store year
                char monthC[3];                                         // store 3 character month string

                sscanf(part, "%hhd-%[^-]-%hd", &day, monthC, &year);    // sscanf date into variables

                while(Months[month]) {                                  // loop through Months 
                    if(strcmp(Months[month], monthC) == 0) {            // if month string == Months index break
                        break;
                    }
                    month++;
                }
                month += 1;                                             // add 1 because 0 index
                year += 2000;                                           /* add 2000 for the year
                                                                           NOTE: there could be a 19xx year, but did not
                                                                                 see when writing, this could be an incorrect
                                                                                 assumption on my part*/
                
                fwrite(&year, sizeof(unsigned short), 1, fb);   // write year to bin
                fwrite(&month, sizeof(unsigned char), 1, fb);   // write month to bin
                fwrite(&day, sizeof(unsigned char), 1, fb);     // write day to bin
                k++;                                            // next column

                // current version
            }else if(k == 11){          // skip current version
                k++;                    // next column  

            // android version
            }else if(k == 12){          // skip android version 
                k++;                    // next column

            // end move to next line
            }else if(k == 13){          // end of the columns
                break;                  // break to move to next line
            }
        }
        free(line); // free line to pass leak-check and error-checking valgrind
    }
    fclose(fd); // close file
    fclose(fb); // close file

    return 0;
}

// helper function to remove unnecessary characters from string
// deletes ',' '"' '+' '$'
const char *removeClutter(char *str){
    int i,j;
    i = 0;
    while(i < strlen(str)) {
        if (str[i]==',' || str[i]=='"' || str[i]=='+' || str[i]=='$') {
            for (j = i; j < strlen(str); j++){
                str[j] = str[j+1];
            }
        }else{
            i++;
        } 
    }
    return str;
}