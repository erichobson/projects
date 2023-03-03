#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apps.h"

int cmp_ret(const void *aptr, const void *bptr);
int cmp_rev(const void *aptr, const void *bptr);
int cmp_rev_review(const void *aptr, const void *bptr);

int main(int argc, char *argv[]) {
    FILE *fid;
    int i;
    int rc;


    fid = fopen("googlePlayStore.bin", "r");
    if(!fid){
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    unsigned short count;
    fread(&count, sizeof(unsigned short), 1, fid);
    
    struct App app[count];
    fread(app, sizeof(app), 1, fid);

    int free = 0;
    int paid = 0;

    for(int i = 0; i < count; i++){
        if(app[i].type == 0){
            free++;
        }if(app[i].type == 1){
            paid++;
        }
    }

    float requestRating = 4.8;

    printf("\n");
    printf("Percentage of Paid Apps: %5.02f%%\n", (paid / (float)count) * 100);
    printf("Percentage of Free Apps: %5.02f%%\n", (free / (float) count) * 100);

    printf("\n");
    printf("Apps for 'Everyone' that are 'free' and rating of '%.01f' or more:\n", requestRating);
    for(int i = 0; i < count; i++){
        if(app[i].contentRating == 0){
            if(app[i].type == 0){
                if(app[i].rating >= requestRating){
                    printf("[%.01f] %s\n", app[i].rating, app[i].name);
                }
            }
        }
    }

    int z = 0;
    for (int i = 0; i < count; i++){
        if(app[i].category == GAME){
            z++;
        }
    }

    struct App games[z];
    int x = 0;
    for (int i = 0; i < count; i++) {
        if(app[i].category == GAME){
            games[x] = app[i];
            x++;
        }
    }
    qsort(games, z, sizeof(App), cmp_ret);
    printf("\n");
    printf("Game category apps in 'increasing' order of 'size':");
    for (int i = 0; i < z; i++)
    {
        printf("[%d] %s\n", games[i].size, games[i].name);
    }


    z = 0;
    for (int i = 0; i < count; i++){
        if(app[i].category == WEATHER){
            z++;
        }
    }
    struct App weather[z];
    x = 0;
    for (int i = 0; i < count; i++) {
        if(app[i].category == WEATHER){
            weather[x] = app[i];
            x++;
        }
    }
    qsort(weather, z, sizeof(App), cmp_rev);
    printf("\n");
    printf("Weather category apps in 'decreasing' order of 'installs':\n");
    for (int i = 0; i < z; i++)
    {
        printf("[%d] %s\n", weather[i].installs, weather[i].name);
    }

    struct App reviews[count];
    for (int i = 0; i < count; i++) {
        reviews[i] = app[i];
    }
    qsort(reviews, count, sizeof(App), cmp_rev_review);
    printf("\n");
    printf("Top 10 reviewed apps:\n");
    for (int i = 0; i < 10; i++){
        printf("[%d] %s\n", reviews[i].reviews, reviews[i].name);
    }

    int CategoryTotals[NUM_CATEGORIES + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


    for(int i = 0; i < count; i++){
        if(app[i].category >= 0 && app[i].category < NUM_CATEGORIES+1){
            CategoryTotals[app[i].category]++;
        }
    }
    printf("\n");
    printf("Number of apps in each category:\n");
    for (int i = 0; i < NUM_CATEGORIES + 1; i++)
    {
        printf("[%d] %s\n", CategoryTotals[i], CategoryNames[i]);
    }

    fclose(fid);
    return 0;
}

int cmp_ret(const void *aptr, const void *bptr)
{
    int a = ((App *)aptr)->size, b = ((App *)bptr)->size;
    return (a > b) - (a < b);
}

int cmp_rev(const void *aptr, const void *bptr)
{
    int a = ((App *)aptr)->installs, b = ((App *)bptr)->installs;
    return (a < b) - (a > b);
}

int cmp_rev_review(const void *aptr, const void *bptr)
{
    int a = ((App *)aptr)->reviews, b = ((App *)bptr)->reviews;
    return (a < b) - (a > b);
}