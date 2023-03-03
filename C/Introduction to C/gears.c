#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// initialize constant variables
#define _USE_MATH_DEFINES

//// functions used in main
float ratioCalc(float, float);

// main function
int main(int argc, char* argv[]){
	float motor;
	float wheel;
	float diameter;
	float motor_rpm;
	float wheel_rpm;

	printf("Enter number of teeth in the motor gear: ");
	scanf("%f", &motor);
	while(getchar() != '\n');

	printf("Enter number of teeth in the wheel gear: ");
	scanf("%f", &wheel);
	while(getchar() != '\n');

	printf("Enter the wheel diameter (in cm): ");
    scanf("%f", &diameter);
	while(getchar() != '\n');

	printf("Enter the motor speed as rotations per minute (rpm): ");
    scanf("%f", &motor_rpm);
	while(getchar() != '\n');

	if(motor > wheel){
		wheel_rpm = motor_rpm * ratioCalc(motor, wheel);
		printf("\nThe gear ratio is 1:%.1f\n", ratioCalc(motor, wheel));
		printf("At a motor speed of %drpm, the speed of a %0.2fcm diameter wheel is %0.2frpm.\n", (int) motor_rpm, diameter, wheel_rpm);
		
	}else if(motor < wheel){
		wheel_rpm = motor_rpm / ratioCalc(motor, wheel);
		printf("\nThe gear ratio is %0.1f:1\n", ratioCalc(motor, wheel));
		printf("At a motor speed of %drpm, the speed of a %0.2fcm diameter wheel is %0.2frpm.\n", (int) motor_rpm, diameter, wheel_rpm);
		
	}else{
		wheel_rpm = motor_rpm * ratioCalc(motor, wheel);
		printf("\nThe gear ratio is 1:1\n");
		printf("At a motor speed of %0.frpm, the speed of a %0.2fcm diameter wheel is %0.2frpm.\n", motor_rpm, diameter, motor_rpm);
	}

	float circle = diameter * M_PI;
	printf("The wheel will move at %0.2fcm per second (i.e., %0.2fkm/h).\n\n", circle*(wheel_rpm / 60), (circle*(wheel_rpm / 60)) * 0.036);
	return 0;
}

// function used to calculate the gear ratio
float ratioCalc(float x, float y) {
	float ratio;
	if(x > y){
		ratio = x/y;
	}else if(x < y){
		ratio = y/x;
	}else{
		ratio = 1;
	}
	return(ratio);	
}
