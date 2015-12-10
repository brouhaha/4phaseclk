Four-Phase non-overlapping clock generator using PIC microcontroller

In the 1970s, some microprocessors and support chips used four-phase
MOS logic. Some, including the Rockwell PPS-4 and PPS-8, generated the
four non-overlapping clock phases on-chip based on two external clock
inputs, while others, including the TI TMS9900, the Western Digital
CP1600 chip set (used in DEC LSI-11 and Alpha Micro AM100), and the
WD9000 chipset (used in Pascal Microengine), required an external
four-phase clock generator. The four-phase clock inputs usually
required a voltage swing close to the Vss and Vdd supply rails,
typically 0V to +12V for NMOS. TI and Western Digital offered support
chips to generate the four-phase clock, although it was often done
with a crystal, 74S logic, and MOS drivers such as the National
Semiconductor MH0026 dual MOS driver or the Intel 3245 quad MOS
driver.

I've recently had occasion to work on interfacing to some of these old
chips, and wanted a modern four-phase clock generator. I've just
written and tested code to use a Microchip PIC16F1575 as a clock
generator, though it only has 5V outputs, so it will require external
gate drivers, such as a Microchip TC4469 quad gate driver, to obtain
the 12V swing.

The PIC16F1575 is a fairly new part using Microchip's enhanced
midrange core. It is in a 14-pin package, has an internal oscillator,
PLL, and four 16-bit PWM modules. The PWM modules can operate
independently, but for this purpose it was convenient that they can be
synchronized.

I've configured the PIC to use the 8 MHz internal oscillator, with a
4x PLL for a 32 MHz clock going into the processor and the PWM
modules. The CPU speed doesn't matter, but that gives timing
resolution of around 31ns for the PWM.  I've configured the PWMs for a
period of 16 clock cycles (500 ns, 2 MHz), clock high pulses of three
clock cycles (93ns), and delay between phases of one clock cycle
(31ns). This could be trivially changed to a 2.67 MHz clock by
reducing the period to 12 cycles and the clock high pulses to two
clock cycles (62ns).  Either set of timings is within the
specifications of the TI and Western Digital parts.

A word of caution: when using gate drivers to drive old MOS parts, I
recommend the use of series resistors of at least 10 ohms and schottky
diode clamps to Vss and Vdd, to ensure that undershoot, overshoot, and
ringing are limited to 0.3V.
