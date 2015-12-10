// Four-phase non-overlapping clock generator
// Copyright 2015 Eric Smith <spacewar@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 3
// as published by the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#define SYS_FREQ        32000000L
#define FCY             SYS_FREQ/4

#include <xc.h>

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

// PIC16F1575 Configuration Bit Settings

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY = OFF    // PPSLOCK bit One-Way Set Enable bit (PPSLOCKED Bit Can Be Cleared & Set Repeatedly)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled, can be enabled by SPLLEN bit in OSCCON)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)


// Constants used in the RxxPPS registers for peripheral output selection
#define PPSO_LAT        0x0
#define PPSO_SYNC_C1OUT 0x1
#define PPSO_SYNC_C2OUT 0x2
#define PPSO_PWM1       0x3
#define PPSO_PWM2       0x4
#define PPSO_PWM3       0x5
#define PPSO_PWM4       0x6
#define PPSO_CWG1OUTA   0x7
#define PPSO_CWG1OUTB   0x8
#define PPSO_TX_CK      0x9
#define PPSO_DT         0xa

// PWM1 is used in independent run mode, and PWMn, for n in 2..4, are in
// continuous slave run mode, at an offset from PWMn-1.
void pwm_init(void)
{
    PWM1CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM1PR     = 15;
    PWM1PH     = 0;
    PWM1DC     = 3;
    PWM1OF     = 4;
    
    PWM1INTE   = 0x00;  // no interrupts enabled
    PWM1INTF   = 0x00;  // clear interrupt flag
    
    PWM1LDCON  = 0x80;  // load armed
    PWM1OFCON  = 0x00;  // independent run mode
    PWM1CON    = 0x80;  // enable, standard PWM mode, active high output
 
    RC0PPS     = PPSO_PWM1;

    PWM2CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM2PR     = 15;
    PWM2PH     = 0;
    PWM2DC     = 3;
    PWM2OF     = 4;
    
    PWM2INTE   = 0x00;  // no interrupts enabled
    PWM2INTF   = 0x00;  // clear interrupt flag
    
    PWM2LDCON  = 0x80;  // load armed
    PWM2OFCON  = 0x20;  // continuous slave run mode, OF1 match
    PWM2CON    = 0x80;  // enable, standard PWM mode, active high output
 
    RC1PPS     = PPSO_PWM2;

    PWM3CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM3PR     = 15;
    PWM3PH     = 0;
    PWM3DC     = 3;
    PWM3OF     = 4;
    
    PWM3INTE   = 0x00;  // no interrupts enabled
    PWM3INTF   = 0x00;  // clear interrupt flag
    
    PWM3LDCON  = 0x80;  // load armed
    PWM3OFCON  = 0x21;  // continuous slave run mode, OF2 match
    PWM3CON    = 0x80;  // enable, standard PWM mode, active high output
 
    RC2PPS     = PPSO_PWM3;

    PWM4CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM4PR     = 15;
    PWM4PH     = 0;
    PWM4DC     = 3;
    PWM4OF     = 4;
    
    PWM4INTE   = 0x00;  // no interrupts enabled
    PWM4INTF   = 0x00;  // clear interrupt flag
    
    PWM4LDCON  = 0x80;  // load armed
    PWM4OFCON  = 0x22;  // continuous slave run mode, OF3 match
    PWM4CON    = 0x80;  // enable, standard PWM mode, active high output
 
    RC3PPS     = PPSO_PWM4;
}

void main(void)
{
    uint8_t count;
    
    OSCCON = 0xf0;  // SPLLEN = 1, IRCF = 8 MHz, SCS = 0
    
    ANSELA = 0x04;
    LATA   = 0x00;
    TRISA  = 0x1c;  // RA4 = button, RA3 = /MCLR, RA2 = ADC
    
    LATC = 0x00;
    TRISC = 0x00;  // C3..C0 = LEDs
    
    pwm_init();
    
    count = 0;
    
    while(1)
    {
        ;
    }
}

