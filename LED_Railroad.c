/* ========================================
 *
 * Harold Araya, Projects October, 2026
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // 8 bits used to hold values from [0-255]
    uint8 isBlinking4 = 0;
    uint8 isBlinking3 = 0;
    uint8 SW2_tally = 0;
    uint8 SW3_tally = 0;
    uint8 showDash = 0;
    
    // 16 bits used to measure time, delays, high-speed counts
    uint16 timeCount = 0;
    uint16 SW2_debounce = 0;
    uint16 SW3_debounce = 0;
    uint16 scrollTimer = 0;
    
    
    LCD_Start();
    LED4_Write(1);
    LED3_Write(0);
    
    LCD_Position(0,1);
    LCD_PrintString("Testing Blinking LEDs!!");
    LCD_Position(1,0);
    LCD_PrintString("Click SW2 to begin!");
    
    for(;;)
    {
        /* Place your application code here. */ 
        if(scrollTimer >= 250 && showDash == 0)
        {
            LCD_WriteControl(LCD_DISPLAY_SCRL_LEFT);
            scrollTimer = 0;
        }
        
        if(SW2_Read() == 0 && SW2_debounce >= 250)
        {
            //Set condition for showDash disappears after first click on SW2
            if(showDash == 0)
            {
                LCD_ClearDisplay();
                showDash = 1;
            }
            
            if(isBlinking4 == 0 && isBlinking3 == 0)
            {
                LED4_Write(1);
                LED3_Write(0);
            }
            
            isBlinking4 = !isBlinking4;
            //CyDelay(250);
            
            isBlinking3 = !isBlinking3;
            //CyDelay(500);
            SW2_debounce = 0; //resets the alternative route (allows processor to keep running)
            
            SW2_tally++;
            
            LCD_Position(0,0);
            LCD_PrintString("SW2 Pressed: ");
            
            LCD_Position(0,13);
            LCD_PrintNumber(SW2_tally);

            showDash = 1;
            
        }
        
         if(SW3_Read() == 0 && SW3_debounce >= 250)
        {
            isBlinking3 = 0;
            //CyDelay(500);
            
            isBlinking4 = 0;
            //CyDelay(250);
            SW3_debounce = 0;
            
            LED4_Write(0);
            LED3_Write(0);
            
            SW3_tally++;
            
            LCD_Position(1,0);
            LCD_PrintString("SW3 Pressed: ");
            
            LCD_Position(1,13);
            LCD_PrintNumber(SW3_tally);
        }
        
        
        // A time check, so every 250ms toggle LEDs
        if (timeCount >= 250)
        {
            if(isBlinking4 == 1)
            {
                LED4_Write(!LED4_ReadDataReg());
            }
            if(isBlinking3 == 1)
            {
                LED3_Write(!LED3_ReadDataReg());
            }
            
            timeCount = 0;
        }
        CyDelay(1);
        timeCount++;
        SW2_debounce++;
        SW3_debounce++;
        scrollTimer++;
    }
   
}

/* [] END OF FILE */
