/*
 * ServoMotor_code.c
 *
 * Created: 18/11/2021 09:05:06
 * Author : Default
 */ 

#define F_CPU 8000000UL 
#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <util/delay.h> 
#include "LCD.h" /* Computation variables */ 


volatile uint16_t position = 0; 
int PWM; 
char buffer[20]; 
char buffer1[20];


/* Function that does the pin definitions and setup for GPI0 and PWM */
 void setup(){ /* GPIO setup */ 
	 DDRB |= (1<<PB3); // Make OC0 pin as Output 
	 /* PWM setup */ 
	 TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS02); // Set Fast PWM with Fosc/256 Timer0 clock 
	 
}
	 
	 
int main(void){ 
	setup(); // Initialize PWM 
	ADC_Init(); // Initialize ADC 
	LCD_Init(); // Initialize LCD 
	while(1){
	position = (ADC_Read(0)); // Obtain ADC reading 
	PWM = 31.25 + (position*31.25)/1024; // Scale the ADC value to the correct PWM values 
	OCR0 = PWM; // Send the PWM value to control the ON time 
	/* Displaying the ADC value and the PWM */ 
	LCD_Cmd(0x80); 
	itoa(position, buffer, 10); 
	LCD_String("ADC Value= "); 
	LCD_String(buffer); 
	LCD_String(" "); 
	LCD_Cmd(0xC0); 
	itoa(PWM, buffer1, 10); 
	LCD_String("Servo Value= "); 
	LCD_String(buffer1); 
	LCD_String(" "); }
}
