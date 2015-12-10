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

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

#if 0
    
    /* TODO Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if(<Interrupt Flag 1>)
    {
        <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
    }
    else if (<Interrupt Flag 2>)
    {
        <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
    }
    else
    {
        /* Unhandled interrupts */
    }

#endif

}

void pwm_init(void)
{
// Note that the following PWM initialization, with all four PWMs in
// independent run mode, winds up with them synchronized, but only by
// accident. We should use an offset mode for PWM2..4.
    PWM1CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM1PR     = 15;
    PWM1PH     = 0;
    PWM1DC     = 3;
    
    PWM1INTE   = 0x00;  // no interrupts enabled
    PWM1INTF   = 0x00;  // clear interrupt flag
    
    PWM1LDCON  = 0x80;  // load armed
    PWM1OFCON  = 0x00;  // independent run mode
    PWM1CON    = 0x80;  // enable, standard PWM mode, active high output
 
    RC0PPS     = PPSO_PWM1;

    PWM2CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM2PR     = 15;
    PWM2PH     = 4;
    PWM2DC     = 7;
    
    PWM2INTE   = 0x00;  // no interrupts enabled
    PWM2INTF   = 0x00;  // clear interrupt flag
    
    PWM2LDCON  = 0x80;  // load armed
    PWM2OFCON  = 0x00;  // independent run mode
    PWM2CON    = 0x80;  // enable, standard PWM mode, active high output
 
    RC1PPS     = PPSO_PWM2;

    PWM3CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM3PR     = 15;
    PWM3PH     = 8;
    PWM3DC     = 11;
    
    PWM3INTE   = 0x00;  // no interrupts enabled
    PWM3INTF   = 0x00;  // clear interrupt flag
    
    PWM3LDCON  = 0x80;  // load armed
    PWM3OFCON  = 0x00;  // independent run mode
    PWM3CON    = 0x80;  // enable, standard PWM mode, active high output
 
    RC2PPS     = PPSO_PWM3;

    PWM4CLKCON = 0x00;  // From Fosc w/o prescaler
    
    PWM4PR     = 15;
    PWM4PH     = 12;
    PWM4DC     = 15;
    
    PWM4INTE   = 0x00;  // no interrupts enabled
    PWM4INTF   = 0x00;  // clear interrupt flag
    
    PWM4LDCON  = 0x80;  // load armed
    PWM4OFCON  = 0x00;  // independent run mode
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
        //PWM1CONbits.OUT = 1;
        LATC = (LATC & 0xf0) | count;
        count = (count + 1) & 0x0f;
        //PWM1CONbits.OUT = 0;
        _delay(800000);
    }
}

