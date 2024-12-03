#include "nios2_ctrl_reg_macros.h"

volatile int * KEY_ptr = (int *) 0xFF200050;
volatile int * HEX3_HEX0_ptr = (int *) 0xFF200020;
int KEY_hold = 0;

void the_reset (void)__attribute__((section(".reset")));
void the_reset (void) {
	asm ("movia r2, _start");	/* Go to the start of  */
	asm ("jmp r2");		  	/*   the program.      */
}

void the_exception (void)__attribute__((section(".exceptions")));
void the_exception (void) {
	asm ("subi sp, sp, 4");		/* Save the contents of  */ 
	asm ("stw et, (sp)");	  	/*   the et register.    */
	asm ("rdctl et, ipending");	   /* If external interrupt, */ 	
	asm ("beq et, r0, SKIP_EA_DEC"); /*   then decrement et    */ 
	asm ("subi ea, ea, 4");		   /*   by 4.                */ 
	asm ("SKIP_EA_DEC:");
	asm ("subi sp, sp, 116"); /* Save all registers except r0 and et. */
	asm ("stw r1, 0(sp)");
	asm ("stw r2, 4(sp)");
	asm ("stw r3, 8(sp)");
	asm ("stw r4, 12(sp)");
	asm ("stw r5, 16(sp)");
	asm ("stw r6, 20(sp)");
	asm ("stw r7, 24(sp)");
	asm ("stw r8, 28(sp)");
	asm ("stw r9, 32(sp)");
	asm ("stw r10, 36(sp)");
	asm ("stw r11, 40(sp)");
	asm ("stw r12, 44(sp)");
	asm ("stw r13, 48(sp)");
	asm ("stw r14, 52(sp)");
	asm ("stw r15, 56(sp)");
	asm ("stw r16, 60(sp)");
	asm ("stw r17, 64(sp)");
	asm ("stw r18, 68(sp)");
	asm ("stw r19, 72(sp)");
	asm ("stw r20, 76(sp)");
	asm ("stw r21, 80(sp)");
	asm ("stw r22, 84(sp)");
	asm ("stw r23, 88(sp)");
	asm ("stw bt, 92(sp)");
	asm ("stw gp, 96(sp)");
	asm ("stw fp, 100(sp)");
	asm ("stw ea, 104(sp)");
	asm ("stw ba, 108(sp)");
	asm ("stw ra, 112(sp)");

	asm ("call INT_HANDLER");

	asm ("ldw r1, 0(sp)");	   /* Restore all registers except sp. */
	asm ("ldw r2, 4(sp)");
	asm ("ldw r3, 8(sp)");
	asm ("ldw r4, 12(sp)");
	asm ("ldw r5, 16(sp)");
	asm ("ldw r6, 20(sp)");
	asm ("ldw r7, 24(sp)");
	asm ("ldw r8, 28(sp)");
	asm ("ldw r9, 32(sp)");
	asm ("ldw r10, 36(sp)");
	asm ("ldw r11, 40(sp)");
	asm ("ldw r12, 44(sp)");
	asm ("ldw r13, 48(sp)");
	asm ("ldw r14, 52(sp)");
	asm ("ldw r15, 56(sp)");
	asm ("ldw r16, 60(sp)");
	asm ("ldw r17, 64(sp)");
	asm ("ldw r18, 68(sp)");
	asm ("ldw r19, 72(sp)");
	asm ("ldw r20, 76(sp)");
	asm ("ldw r21, 80(sp)");
	asm ("ldw r22, 84(sp)");
	asm ("ldw r23, 88(sp)");
	asm ("ldw bt, 92(sp)");
	asm ("ldw gp, 96(sp)");
	asm ("ldw fp, 100(sp)");
	asm ("ldw ea, 104(sp)");
	asm ("ldw ba, 108(sp)");
	asm ("ldw ra, 112(sp)");
	asm ("ldw et, 116(sp)");
	asm ("addi sp, sp, 120");
	asm ("eret");		    /* Return from exception. */
}

void INT_HANDLER() {
	int ipending;
	NIOS2_READ_IPENDING(ipending);
	
	if ( ipending & 0x2 ) {					// Interruption générée par KEYS			
		int press, HEX_bits;

		press = *(KEY_ptr + 3);				// Quel KEY exactement			
		*(KEY_ptr + 3) = press;				// Mise à 0 du registre EDGE BITS			

		press ^= KEY_hold;					//					
		KEY_hold = press;					// Pour toggler le bit pressé						

		HEX_bits = 0;
							
		if (press & 0x1)
			HEX_bits = 0b00111111; 			// Ecrire dans HEX0

		if (press & 0x2)
			HEX_bits |= 0b00000110 << 8;	// Ecrire dans HEX1

		if (press & 0x4)
			HEX_bits |= 0b01011011 << 16;	// Ecrire dans HEX2

		if (press & 0x8)
			HEX_bits |= 0b01001111 << 24;	// Ecrire dans HEX3

		*HEX3_HEX0_ptr = HEX_bits; 			// Registre à 32 bits - HEX3 HEX2 HEX1 HEX0
	}

	return;
}

main() {
	*(KEY_ptr + 2) = 0xF;					// Enable KEYS interruption

	NIOS2_WRITE_IENABLE(0x2);

	NIOS2_WRITE_STATUS(1);

	while(1);
}
