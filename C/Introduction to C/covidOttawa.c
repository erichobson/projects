#include <stdio.h>
#include <locale.h>

// initialize constant variables
#define STAR_COUNT 0.022737608  // value used to calculate number of stars
#define AVERAGE 5               // how many times averageArray() is run
#define WEEKS 63

// functions used in main
void printer(short int *array);
void averageArray(short int *array);
int maxValue(short int *array);
int getPeaks(short int *array);
float sumArray(short int *array);

// main function
int main(int argc, char* argv[]){

    short int weeklyCases[] =   {9, 20, 104, 223, 223, 268, 281, 363, 149, 134, 105, 64, 56, 35, 22, 29, 29, 40, 74, 200,
                                129, 76, 63, 128, 118, 127, 234, 323, 454, 645, 721, 609, 501, 571, 394, 396, 253, 281, 291,
                                315, 281, 364, 668, 987, 909, 644, 408, 348, 289, 384, 362, 390, 461, 550, 709, 1216, 1543, 
                                2199, 1600, 1160, 854, 683, 552};

    setlocale(LC_NUMERIC, "");

    printf("\nThere were %'d cases in total over the %d weeks.\n", (int) sumArray(weeklyCases), WEEKS);
    printf("The average is %0.1f cases per week.\n", sumArray(weeklyCases)/WEEKS);
    printf("The worst week had %d cases.\n\n", maxValue(weeklyCases));

    printf("Here is the weekly cases histogram:\n");
    printer(weeklyCases);
    printf("\n");

    averageArray(weeklyCases);
    printf("Here is the weekly cases histogram after averaging:\n");
    printer(weeklyCases);

    printf("\nThe number of waves during the %d weeks was %d\n\n", WEEKS, getPeaks(weeklyCases));
    return 0;     
}

// procedure used to print the histogram
void printer(short int *array){
    int count = 0;
    for(int i = 0; i < WEEKS; i++){
        count += 1;
        float star = array[i] * STAR_COUNT;
        printf("Week %3d: ", count);
        while(star >= 0){
            printf("*");
            star -= 1;
        }
        printf("\n");
    }
}

// function to return the max element in the array
int maxValue(short int *array){
    int maxValue = 0;
    for(int i = 0; i < WEEKS; i++){
        if(maxValue < array[i]){
            maxValue = array[i];
        }      
    }
    return maxValue;
}

// function to return the sum of all elements in the array
float sumArray(short int *array){
    float sum = 0;
    for(int i = 0; i < WEEKS; i++){
        sum += array[i];
    }
    return sum;
}

// function to return the number of peaks in the array
int getPeaks(short int *array){
    int peaks = 0;
    int bool = 0;
    for(int i = 0; i < WEEKS; i++){
    	if(i == 0){
            if(array[i+1] < array[i]){
                peaks += 1;
            }
    	}else if(i == (WEEKS - 1)){
            if(array[i] > array[i-1]){
                peaks += 1;
            }
    	}else{
            if(array[i+1] > array[i]){
                bool = 1;
            }else if(array[i+1] == array[i]){
                bool = 1;
            }else if(array[i+1] < array[i]){
                if(bool == 1){
                    peaks += 1;
                    bool = 0;
                }else{
                    bool =0;
                }
            }
        }
    }
    return peaks;
}

// procedure to average and smooth the array
void averageArray(short int *array){
    int count = AVERAGE;
    while(count > 0){
        for(int i = 0; i < WEEKS; i++) {
            int average = 0;
            if(i == 0){
                average += array[i];
                average += array[i+1];
                average = average / 2;
            }else if(i == (WEEKS - 1)){
                average += array[i];
                average += array[i-1];
                average = average / 2;
            }else{
                average += array[i+1];
                average += array[i];
                average += array[i-1];
                average = average / 3;
            }
            array[i] = average;
        }
        count -= 1;
    }
}