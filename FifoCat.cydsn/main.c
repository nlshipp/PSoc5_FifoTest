/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

char buffer[1024];

uint8 f0, f1;
uint16 f01;
uint8 concat = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    UART_Start();
    
    for(;;)
    {
        int i;
        UART_PutStringConst("Clearing FIFOs\n\r");
        DualFifo_DP_F0_CLEAR;
        DualFifo_DP_F1_CLEAR;
        
        if (concat & 0x01)
            UART_PutStringConst("Filling fifos using 16 bit word\n\r");
            
        if (concat & 0x02)
            UART_PutStringConst("Read fifos using 16 bit word\n\r");
            
        UART_PutStringConst("Filling FIFOs\n\r");
        for (i = 0; i < 4; i++)
        {
            if (concat & 0x01)
            {
                *DualFifo_F0_F1_Word = i | (0x10 + i) << 8;
            }
            else
            {
                DualFifo_DP_F0_REG = i;
                DualFifo_DP_F1_REG = 0x10 + i;
            }
        }
        
        UART_PutStringConst("Printing FIFOs\n\r");
        for (i = 0; i < 4; i++)
        {
            if (concat & 0x02)
            {
                f01 = *DualFifo_F0_F1_Word;
            }
            else
            {
                f0 = DualFifo_DP_F0_REG;
                f1 = DualFifo_DP_F1_REG;
                f01 = f0 | (f1 << 8);
            }
            
            sprintf(buffer, "F0=%02x F1=%02x\n\r", f01 & 0xFF, f01 >> 8);
            UART_PutString(buffer);
        }
        
        UART_PutStringConst("Filling FIFOs\n\r");
        for (i = 0; i < 4; i++)
        {
            if (concat & 0x01)
            {
                *DualFifo_F0_F1_Word = (0x20 + i) | (0x30 + i) << 8;
            }
            else
            {
                DualFifo_DP_F0_REG = 0x20 + i;
                DualFifo_DP_F1_REG = 0x30 + i;
            }
        }
        
        UART_PutStringConst("Printing FIFOs\n\r");
        for (i = 0; i < 4; i++)
        {
            if (concat & 0x02)
            {
                f01 = *DualFifo_F0_F1_Word;
            }
            else
            {
                f0 = DualFifo_DP_F0_REG;
                f1 = DualFifo_DP_F1_REG;
                f01 = f0 | (f1 << 8);
            }
            
            sprintf(buffer, "F0=%02x F1=%02x\n\r", f01 & 0xFF, f01 >> 8);
            UART_PutString(buffer);
        }
        
        concat ++;
    }
}

/* [] END OF FILE */
