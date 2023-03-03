#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "apps.h"

const char *removeClutter(char *str);

int main (){
    FILE *fd;
    FILE *fb;

    int bufferLength = MAX_LINE_SIZE;
    char buffer[bufferLength];
    const char *delim = "\t\n";
    char *s;
    char *toks;
    char *p;

    unsigned char lineSkip[1] = "\n";
    unsigned char lineTab[1] = "\t";

    unsigned short count = 0;
    unsigned short j = 0;
    unsigned short k;
    char c;

    int i = 0;

    fd = fopen("googlePlayStore.tsv", "r");
    if(!fd){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    fb = fopen("googlePlayStore.bin", "wb+");
    if(!fb){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    for (c = getc(fd); c != EOF; c = getc(fd)){
        if (c == '\n'){
            count++;
        }     
    }

    printf("%d\n", count);
    fclose(fd);

    fwrite(&count, sizeof(unsigned short), 1, fb);

    fd = fopen("googlePlayStore.tsv", "r");
    if(!fd){
        printf("ERROR: Could not open file\n");
        exit(1);
    }
    struct App app[count];

    //rewind(fd);

    while(fgets(buffer, bufferLength, fd)) {
        char             name;
        unsigned char    category;
        float            rating;
        unsigned int     reviews;
        unsigned int     size;
        unsigned int     installs;
        unsigned char    type;
        float			 price;
        unsigned char	 contentRating;
        unsigned short   year;
        unsigned char	 month;
        unsigned char    day;

        k = 0;
        s = strdup(buffer);
        toks = s;
        while ((p = strsep(&toks, delim)))
        {
            // app
            if(k == 0){ 
                unsigned char numChar = strlen(p);
                char pName[numChar];
                strcpy(pName, p);
                strcpy(app[i].name, pName);
                k++;

            // category
            }else if(k == 1){
                unsigned char z = 0;
                while(Categories[z]) {
                    if(strcmp(Categories[z], p) == 0) {
                        break;
                    }
                z++;
                }
                app[i].category = z;
                k++;

            // rating
            }else if(k == 2){
                float rating;
                float NaN = -1;                          // changed from char
                if (strcmp("NaN", p) == 0) {
                    app[i].rating = NaN;  // changed from char
                } else {
                    rating = atof(p);
                    app[i].rating = rating;
                }
                k++;

            //reviews
            }else if(k == 3){
                unsigned int reviews = atoi(p);
                app[i].reviews = reviews;
                k++;

            // size
            }else if(k == 4){
                unsigned int size;
                unsigned int zero = 0;                          // changed from char
                if (strcmp("Varies with device", p) == 0) {
                    app[i].size = zero;
                    //fwrite(&zero, sizeof(unsigned int), 1, fb); // changed from char
                } else if (strcmp("k", &p[strlen(p) - 1]) == 0) {
                    p[strlen(p)-1] = '\0';
                    size = atoi(p);
                    app[i].size = size;
                } else if (strcmp("M", &p[strlen(p) - 1]) == 0) {
                    p[strlen(p)-1] = '\0';
                    float pSize = atof(p);
                    size = pSize * 1024;
                    app[i].size = size;
                }
                k++;

            // installs
            }else if(k == 5){
                unsigned int installs;
                removeClutter(p);
                installs = atoi(p);
                app[i].installs = installs;
                k++;
            
            // type
            }else if(k == 6){
                unsigned char type;
                if(strcmp("Free", p) == 0){
                    type = 0;
                }else if(strcmp("Paid", p) == 0){
                    type = 1;
                }
                app[i].type = type;
                k++;

            // price
            }else if(k == 7){
                float price;
                if(strcmp("0", p) == 1){
                    removeClutter(p);
                    price = atof(p);
                    app[i].price = price;
                }
                k++;

            // content rating
            }else if(k == 8){
                unsigned char x = 0;
                while(ContentRatings[x]) {
                    if(strcmp(ContentRatings[x], p) == 0) {
                        break;
                    }
                    x++;
                }
                app[i].contentRating = x;
                k++;

            // genres
            }else if(k == 9){
                k++;

            //last update
            }else if(k == 10){
                unsigned char day;
                unsigned char month = 0;
                unsigned short year;
                char monthC[3];

                sscanf(p, "%hhd-%[^-]-%hd", &day, monthC, &year);

                while(Months[month]) {
                    if(strcmp(Months[month], monthC) == 0) {
                        break;
                    }
                    month++;
                }
                month += 1;
                year += 2000;
                
                app[i].year = year;
                app[i].month = month;
                app[i].day = day;
                k++;

                // current version
            }else if(k == 11){
                k++;

            // android version
            }else if(k == 12){
                k++;

            // end move to next line
            }else if(k == 13){
                break;
            }
        }
        i++;
    }
    fwrite(&app, sizeof(app), 1, fb);
    fclose(fd);
    fclose(fb);
}

const char *removeClutter(char *str){
    int i,j;
    i = 0;
    while(i<strlen(str))
    {
        if (str[i]==',' || str[i]=='"' || str[i]=='+' || str[i]=='$')
        {
            for (j=i; j<strlen(str); j++)
                str[j]=str[j+1];
        }
        else i++;
    }
    return str;
}