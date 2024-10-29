; Define the target device
.DEVICE ATmega328P

.include "m328Pdef.inc"

.equ LCD_RS = 0  ; RS pin connected to PORTB0
.equ LCD_RW = 1  ; RW pin connected to PORTB1 (optional, can tie to ground)
.equ LCD_E  = 2  ; E pin connected to PORTB2

.equ LCD_D4 = 4  ; D4 pin connected to PORTD4
.equ LCD_D5 = 5  ; D5 pin connected to PORTD5
.equ LCD_D6 = 6  ; D6 pin connected to PORTD6
.equ LCD_D7 = 7  ; D7 pin connected to PORTD7

; Initialize stack pointer
ldi r16, low(RAMEND)
out SPL, r16
ldi r16, high(RAMEND)
out SPH, r16

; Initialize ports for LCD control and data
ldi r16, 0b11111100    ; Set PORTB pins 0, 1, 2 as output (RS, RW, E)
out DDRB, r16

ldi r16, 0b11110000    ; Set PORTD pins 4, 5, 6, 7 as output (D4-D7)
out DDRD, r16

; LCD Initialization sequence (4-bit mode)
rcall LCD_Init

; Display "Hello World" on the LCD
rcall LCD_Clear         ; Clear LCD

ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '0'
rcall LCD_Data
ldi r16, '0'
rcall LCD_Data
ldi r16, '1'
rcall LCD_Data
ldi r16, '0'
rcall LCD_Data
ldi r16, '0'
rcall LCD_Data
Start:
    rjmp Start

; Subroutine: LCD Initialization
LCD_Init:
    ldi r16, 0x02        ; Set 4-bit mode
    rcall LCD_Command

    ldi r16, 0x28        ; Function Set: 4-bit, 2-line, 5x7 dots
    rcall LCD_Command

    ldi r16, 0x0C        ; Display ON, Cursor OFF
    rcall LCD_Command

    ldi r16, 0x06        ; Entry mode: Increment cursor, No shift
    rcall LCD_Command
ret

; Subroutine: Send command to LCD
LCD_Command:
    cbi PORTB, LCD_RS    ; RS = 0 for command
    cbi PORTB, LCD_RW    ; RW = 0 for write
    rcall LCD_Nibble
    sbi PORTB, LCD_E     ; E = 1 (Enable)
    rcall LCD_Pulse
ret

; Subroutine: Send data to LCD
LCD_Data:
    sbi PORTB, LCD_RS    ; RS = 1 for data
    cbi PORTB, LCD_RW    ; RW = 0 for write
    rcall LCD_Nibble
    sbi PORTB, LCD_E     ; E = 1 (Enable)
    rcall LCD_Pulse
ret

; Subroutine: Send the higher nibble of r16 to the LCD
LCD_Nibble:
    mov r17, r16         ; Copy r16 to r17
    swap r17             ; Swap nibbles to send higher nibble first
    andi r17, 0xF0       ; Mask the higher nibble
    out PORTD, r17       ; Send it to PORTD (D4-D7)
ret

; Subroutine: Pulse the Enable pin
LCD_Pulse:
    sbi PORTB, LCD_E     ; E = 1
    nop
    cbi PORTB, LCD_E     ; E = 0
ret

; Subroutine: Clear LCD
LCD_Clear:
    ldi r16, 0x01        ; Command to clear display
    rcall LCD_Command
ret

; Delay subroutine (simple delay for timing purposes)
wait:
    ldi r18, 0xFF
    ldi r19, 0xFF
wloop:
    dec r19
    brne wloop
    dec r18
    brne wloop
ret
