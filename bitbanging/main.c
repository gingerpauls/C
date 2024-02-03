#include "stdio.h"

int main(void) {

    unsigned int register1, value1;

    /* HSE PLL CONFIG AND ENABLE */
    /* PLL 		M-8 	| N-192 	| P-4 	| Q-8
     * PLLI2S	M-10	| N-200		| R-2
     * AHB		1
     * APB1		4
     * APB2		1
     */

    register1 = 0x24003010; // reset value 

    register1 |= 0x8 << 24;
    register1 &= ~(0x7 << 24); => ~ => 0xF8FFFFFF

    register1 = 0x28003004; // reset value 


    register1 |= 0x8<<24;

    return 0;
}