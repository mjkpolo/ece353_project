#include "serial_debug.h"
#include "circular_buffer.h"

// ADD CODE  - Copy this line after you #includes
Circular_Buffer* Tx_Buffer;

volatile char rxBuff[80];
volatile int rxCount;
volatile bool ALERT_STRING;
volatile uint16_t Rx_Char_Count = 0;
volatile char Rx_String[];

static void serial_debug_init_uart(void)
{
    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~(BIT2 | BIT3);

    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | EUSCI_B_CTLW0_SSEL__SMCLK;

    // Baud Rate calculation
    // 24000000 (clock) / (16 * 115200 (baud) = 13.02
    // Fractional portion = 0.02
    // UCBRFx = int ((13.02 -13) * 16) = 0
    EUSCI_A0->BRW = 13; // 24000000 / 16/ 115200

    // Set the fractional portion of the baud rate and turn on oversampling
    EUSCI_A0->MCTLW = (0 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;
    // Enable UART mode
    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

    // Clear any interrupts
    EUSCI_A0->IFG &= ~(EUSCI_A_IFG_RXIFG | EUSCI_A_IFG_TXIFG);

    // Enable Rx Interrupts
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;
    EUSCI_A0->IE |= EUSCI_A_IE_TXIE;
    NVIC_EnableIRQ(EUSCIA0_IRQn);

    // Prime the pump -- ADD CODE
    EUSCI_A0->TXBUF = 0;
}

void serial_debug_put_string(char* s)
{
    while (*s != 0) {
        // Wait until not busy
        while (EUSCI_A0->STATW & EUSCI_A_STATW_BUSY)
            ;
        EUSCI_A0->TXBUF = *s;

        s++; // advance to next char
    }
}

// static void serial_debug_init_3mhz_uart(void) {
//     // Baud rate of 9600 at 3MHz
//     P1->SEL0 |= BIT2 | BIT3;
//     P1->SEL1 &= ~(BIT2 | BIT3);
//
//     EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST;
//     EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | EUSCI_B_CTLW0_SSEL__SMCLK;
//
//     // Baud Rate calculation
//     // 3000000 (clock) / (16 * 9600 (baud) = 19.53125
//     // Fractional portion = 0.53125
//     // UCBRFx = (int) ((19.53125 -19) * 16) = 8
//     EUSCI_A0->BRW = 19; // 24000000 / 16/ 115200
//
//     // Set the fractional portion of the baud rate and turn on oversampling
//     EUSCI_A0->MCTLW = (8 << EUSCI_A_MCTLW_BRF_OFS) | EUSCI_A_MCTLW_OS16;
//     // Enable UART mode
//     EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;
//
//     // Clear any interrupts
//     EUSCI_A0->IFG &= ~(EUSCI_A_IFG_RXIFG | EUSCI_A_IFG_TXIFG);
//
//     // Enable Rx Interrupts
//     EUSCI_A0->IE |= EUSCI_A_IE_RXIE;
//     NVIC_EnableIRQ(EUSCIA0_IRQn);
// }

void serial_debug_init(void)
{
    // init uart
    serial_debug_init_uart();
    // ADD CODE that initializes a circular buffer of size 80 and sets it
    // equal to Tx_Buffer
    Tx_Buffer = circular_buffer_init(80);
}

//****************************************************************************
// This function is called from MicroLIB's stdio library.  By implementing
// this function, MicroLIB's putchar(), puts(), printf(), etc will now work.
// ****************************************************************************/
int fputc(int c, FILE* stream)
{
    // Busy wait while the circular buffer is full -- ADD CODE
    while (circular_buffer_full(Tx_Buffer)) { };

    // globally disable interrupts
    __disable_irq();

    // add the character to the circular buffer  -- ADD CODE
    circular_buffer_add(Tx_Buffer, c);

    // globally enable interrupts
    __enable_irq();

    // Enable Tx Empty Interrupts  -- ADD CODE
    EUSCI_A0->IE |= EUSCI_A_IE_TXIE;

    return 0;
}

//****************************************************************************
// UART interrupt service routine
// ****************************************************************************/
void EUSCIA0_IRQHandler(void)
{
    char c;

    // Check for Rx interrupts
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) {
        Rx_String[Rx_Char_Count] = EUSCI_A0->RXBUF;
        if (Rx_String[Rx_Char_Count] == 0x0A || Rx_String[Rx_Char_Count] == 0x0D)
            ALERT_STRING = true;
        Rx_Char_Count++;
    }

    // Check for Tx Interrupts
    if (EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG) {
        // Check to see if the Tx circular buffer is empty
        if (circular_buffer_empty(Tx_Buffer)) {
            // Disable Tx Interrupts -- ADD CODE
            EUSCI_A0->IE &= ~EUSCI_A_IE_TXIE;

        } else {
            // Get the next char from the circular buffer -- ADD CODE
            c = circular_buffer_remove(Tx_Buffer);

            // Transmit the character -- ADD CODE
            EUSCI_A0->TXBUF = c;
        }
    }
}
