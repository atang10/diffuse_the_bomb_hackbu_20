/*
 * Lab3.c
 *
 * Created: 2/8/2020 1:02:58 PM
 * Author : Jacob
 */ 

#define F_CPU 1600000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <util/delay.h>

 
#define SW4_LOC 7
#define SW3_LOC 4
#define SW2_LOC 5
#define SW1_LOC 3
#define SW0_LOC 2

#define LED7_LOC 7
#define LED6_LOC 0
#define LED5_LOC 1
#define LED4_LOC 4
#define LED3_LOC 6

#define DOWN_BUTTON 3
#define UP_BUTTON 2
#define LEFT_BUTTON 1
#define RIGHT_BUTTON 0

/***** PART 1 ******/

void configure_switches() {
	DDRD &= ~((1<<SW4_LOC) | (1<<SW1_LOC) | (1<<SW0_LOC));
	PORTD &= ~((1<<SW4_LOC) | (1<<SW1_LOC) | (1<<SW0_LOC));
	
	DDRB &= ~((1<<SW3_LOC) | (1<<SW2_LOC));
	PORTB &= ~((1<<SW3_LOC) | (1<<SW2_LOC));
	
}


int8_t get_switches() {
	int8_t result = 0;
	if (PIND & (1<<SW0_LOC))
	result |= (1<<0);
	if (PIND & (1<<SW1_LOC))
	result |= (1<<1);
	if (PINB & (1<<SW2_LOC))
	result |= (1<<2);
	if (PINB & (1<<SW3_LOC))
	result |= (1<<3);
	if (PIND & (1<<SW4_LOC))
	result |= (1<<4);
	
	return result;
}

void configure_leds() {
	DDRB |= (1<<LED7_LOC);
	DDRD |= ((1<<LED6_LOC) | (1<<LED5_LOC) | (1<<LED4_LOC) | (1<<LED3_LOC));
	
}

void output_to_leds(int8_t value) {
	if (value & (1<<4))
	PORTB |= (1<<LED7_LOC);
	else
	PORTB &= ~(1<<LED7_LOC);
	if (value & (1<<3))
	PORTD |= (1<<LED6_LOC);
	else
	PORTD &= ~(1<<LED6_LOC);
	if (value & (1<<2))
	PORTD |= (1<<LED5_LOC);
	else
	PORTD &= ~(1<<LED5_LOC);
	if (value & (1<<1))
	PORTD |= (1<<LED4_LOC);
	else
	PORTD &= ~(1<<LED4_LOC);
	if (value & (1<<0))
	PORTD |= (1<<LED3_LOC);
	else
	PORTD &= ~(1<<LED3_LOC);
	
}

/****** PART 2 *******/



// down button driver

void configure_down_button()
{
	DDRB &=~(1<<DOWN_BUTTON);//Set the pin for DOWN as an input with no pull-up
}
_Bool down_button_is_pressed()
{
	return (PINB&(1<<DOWN_BUTTON));//return true only if the down button is pressed
}
_Bool down_button_is_released()
{
	return !down_button_is_pressed();//return true only if the down button is released
}

//up button driver

void configure_up_button()
{
	DDRB &=~(1<<UP_BUTTON);//Set the pin for DOWN as an input with no pull-up
}
_Bool up_button_is_pressed()
{
	return (PINB&(1<<UP_BUTTON));//return true only if the down button is pressed
}
_Bool up_button_is_released()
{
	return !up_button_is_pressed();//return true only if the down button is released
}

//right button driver

void configure_right_button()
{
	DDRB &=~(1<<RIGHT_BUTTON);//Set the pin for DOWN as an input with no pull-up
}
_Bool right_button_is_pressed()
{
	return (PINB&(1<<RIGHT_BUTTON));//return true only if the down button is pressed
}
_Bool right_button_is_released()
{
	return !right_button_is_pressed();//return true only if the down button is released
}

void wait_for_right_button_press()
{
	while(right_button_is_released());//returns back to caller only when down button is pressed
}


//left button driver

void configure_left_button()
{
	DDRB &=~(1<<LEFT_BUTTON);//Set the pin for DOWN as an input with no pull-up
}
_Bool left_button_is_pressed()
{
	return (PINB&(1<<LEFT_BUTTON));//return true only if the down button is pressed
}
_Bool left_button_is_released()
{
	return !left_button_is_pressed();//return true only if the down button is released
}

_Bool wait_for_down_button_press() {
	
	static int8_t state_down = 0;
	_Bool result = false;
	if (state_down==0) {
		if (down_button_is_pressed()){ 
			state_down = 1;
			result = true;
		} 
	}
	else if (state_down == 1) {
		if (down_button_is_released()){ 
			state_down = 0;
		}
	}
	else {
		state_down = 0;
	}
	return result;
}

_Bool wait_for_up_button_press() {
	
	static int8_t state_up = 0;
	_Bool result = false;
	if (state_up==0) {
		if (up_button_is_pressed()){
			state_up = 1;
			result = true;
		}
	}
	else if (state_up == 1) {
		if (up_button_is_released()){
			state_up = 0;
		}
	}
	else {
		state_up = 0;
	}
	return result;
}


_Bool wait_for_left_button_press() {
	
	static int8_t state_left = 0;
	_Bool result = false;
	if (state_left==0) {
		if (left_button_is_pressed()){
			state_left = 1;
			result = true;
		}
	}
	else if (state_left == 1) {
		if (left_button_is_released()){
			state_left = 0;
		}
	}
	else {
		state_left = 0;
	}
	return result;
}

int8_t dec_to_bin(int8_t dec_num) {
	
	int8_t binaryNum[8];
	int8_t i = 0;
	while (dec_num > 0) {
		binaryNum[i] = dec_num % 2;
		dec_num /= 2;
		i++;
	}
	
	
	return (int8_t)binaryNum;

}

void wrong() {
	
	while(1) {
		_delay_ms(500);
		output_to_leds(31);
		_delay_ms(500);
		output_to_leds(0);
		if (wait_for_left_button_press()) {
			return;
		}
	}
	
}


int main(void)
{
	configure_leds();
	configure_switches();
	configure_down_button();
	configure_left_button();
	configure_up_button();
	configure_right_button();
	
	
	int8_t array[] = {31, 4, 15, 9, 26, 5, 3, 5, 8, 9, 7, 9, 3, 23, 8, 4, 6, 26, 4, 3, 3, 8, 3, 27, 9, 5, 28, 8, 4, 19, 7, 16, 9, 3, 9, 9, 3, 7, 5, 10, 5, 8, 20, 9, 7 };
	int i= 0;
		while (1)
		{
			if (wait_for_down_button_press()){
				break;
			}
			
			
		
			
			output_to_leds(array[i]);
			_delay_ms(10000);
			output_to_leds(0);
			wait_for_right_button_press();
			if (get_switches() != array[i]){
				wrong();
				i=0;
			}
			else {
				output_to_leds(31);
				_delay_ms(10000);
				i++;
			}
				
			//printf("%d", VALUE);
	
			
			
		}
		output_to_leds(0);
	
}



	