#include <msp430.h>      
#include "temperatura.h"
#include "queue.h"

static int32_t  adcval;
static char*    flag;
static func_ptr_t temp_callback;

void set_callback_temp(func_ptr_t func_temp){
    temp_callback = func_temp;
}
void initTemp(){

  /* Temp Sensor ADC10CLK/4 */
    ADC10CTL1 = INCH_10 + ADC10DIV_3;         //
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;

  /* Espero que se estabilice la Ref del ADC */
    __delay_cycles(1000);
}

void setFlagTemp(char* flag_main){
    /*Set flag*/
    flag = flag_main;
}

void runTemp(){

  /* Start samppling and conversionb*/
    ADC10CTL0 |= ENC + ADC10SC;

}


int32_t getTemp(){
    int32_t  temp;
  /* Convert ADC value to celsius degrees*/
    temp = (((adcval - 673) * 423)/1024);

    *flag = 0;

    return temp;

}

/* ISR */

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    *flag = 1;
    adcval = ADC10MEM;
    enqueue(temp_callback);
}

