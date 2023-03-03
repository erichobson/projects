#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apps.h"

// forward declaration
int compareIncreasing(const void *pointerA, const void *pointerB);
int compareDecreasing(const void *pointerA, const void *pointerB);
int compareDecreasingReviews(const void *pointerA, const void *pointerB);

// main
int main() {
    FILE *fid;  // binary file to read

    // open bin and check for error
    fid = fopen("googlePlayStore.bin", "r");
    if(!fid){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    // reads two bytes for number of records
    unsigned short count;
    fread(&count, sizeof(unsigned short), 1, fid);

    // struct to stores apps
    struct App app[count];

    // loop through the lines and store the app information accordingly
    for(int i = 0; i < count; i++) {
        unsigned char nameLen;
        fread(&nameLen,              sizeof(unsigned char), 1, fid);
        fread(&app[i].name,          sizeof(char), nameLen, fid);
        fread(&app[i].category,      sizeof(unsigned char), 1, fid);
        fread(&app[i].rating,        sizeof(float), 1, fid);
        fread(&app[i].reviews,       sizeof(unsigned int), 1, fid);
        fread(&app[i].size,          sizeof(unsigned int), 1, fid);
        fread(&app[i].installs,      sizeof(unsigned int), 1, fid);
        fread(&app[i].type,          sizeof(unsigned char), 1, fid);
        fread(&app[i].price,         sizeof(float), 1, fid);
        fread(&app[i].contentRating, sizeof(unsigned char), 1, fid);
        fread(&app[i].year,          sizeof(unsigned short), 1, fid);
        fread(&app[i].month,         sizeof(unsigned char), 1, fid);
        fread(&app[i].day,           sizeof(unsigned char), 1, fid);
    }


    // calculate %paid and %free
    int free = 0;
    int paid = 0;
    for(int i = 0; i < count; i++){
        if(app[i].type == FREE){
            free++;
        }if(app[i].type == PAID){
            paid++;
        }
    }
    printf("\n");
    printf("Percentage of Paid Apps: %5.02f%%\n", (paid / (float)count) * 100);
    printf("Percentage of Free Apps: %5.02f%%\n", (free / (float) count) * 100);


    // calculate ratings >= 4.8
    float requestRating = 4.8;
    printf("\n");
    printf("Apps for 'Everyone' that are 'free' and rating of '%.01f' or more:\n", requestRating);
    for(int i = 0; i < count; i++){
        if(app[i].contentRating == EVERYONE){
            if(app[i].type == FREE){
                if(app[i].rating >= requestRating){
                    printf("[%.01f] %s\n", app[i].rating, app[i].name);
                }
            }
        }
    }


    // calculate game apps and sort in increasing order
    int z = 0;
    for (int i = 0; i < count; i++) {
        if(app[i].category == GAME) {
            z++;
        }
    }
    struct App games[z];
    int x = 0;
    for (int i = 0; i < count; i++) {
        if(app[i].category == GAME) {
            games[x] = app[i];
            x++;
        }
    }
    qsort(games, z, sizeof(App), compareIncreasing);
    printf("\n");
    printf("Game category apps in 'increasing' order of 'size':\n");
    for (int i = 0; i < z; i++) {
        printf("[%d] %s\n", games[i].size, games[i].name);
    }


    // calculate weather apps and sort in decreasing order
    z = 0;
    for (int i = 0; i < count; i++) {
        if(app[i].category == WEATHER) {
            z++;
        }
    }
    struct App weather[z];
    x = 0;
    for (int i = 0; i < count; i++) {
        if(app[i].category == WEATHER) {
            weather[x] = app[i];
            x++;
        }
    }
    qsort(weather, z, sizeof(App), compareDecreasing);
    printf("\n");
    printf("Weather category apps in 'decreasing' order of 'installs':\n");
    for (int i = 0; i < z; i++) {
        printf("[%d] %s\n", weather[i].installs, weather[i].name);
    }


    // calculate top10 reviewed apps and sort in decreasing order
    struct App reviews[count];
    for (int i = 0; i < count; i++) {
        reviews[i] = app[i];
    }
    qsort(reviews, count, sizeof(App), compareDecreasingReviews);
    printf("\n");
    printf("Top 10 reviewed apps:\n");
    for (int i = 0; i < 10; i++) {
        printf("[%d] %s\n", reviews[i].reviews, reviews[i].name);
    }


    // calculate the number of apps of each of the 34 categories
    int CategoryTotals[NUM_CATEGORIES + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < count; i++) {
        if(app[i].category >= 0 && app[i].category < NUM_CATEGORIES+1) {
            CategoryTotals[app[i].category]++;
        }
    }
    printf("\n");
    printf("Number of apps in each category:\n");
    for (int i = 0; i < NUM_CATEGORIES + 1; i++) {
        printf("[%d] %s\n", CategoryTotals[i], CategoryNames[i]);
    }

    // close file
    fclose(fid);    
    return 0;
}

// compare increasing size
int compareIncreasing(const void *pointerA, const void *pointerB) {
    int a = ((App *)pointerA)->size;
    int b = ((App *)pointerB)->size;
    return (a > b) - (a < b);
}

// compare decreasing installs
int compareDecreasing(const void *pointerA, const void *pointerB) {
    int a = ((App *)pointerA)->installs;
    int b = ((App *)pointerB)->installs;
    return (a < b) - (a > b);
}

// compare decreasing reviews
int compareDecreasingReviews(const void *pointerA, const void *pointerB) {
    int a = ((App *)pointerA)->reviews;
    int b = ((App *)pointerB)->reviews;
    return (a < b) - (a > b);
}