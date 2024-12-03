#include "nios2_ctrl_reg_macros.h"

#define RED_LEDS (volatile int *) 0xFF200000
#define Timer (volatile int *) 0xFF202000
int count=0;

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

	if ( ipending & 0x1 ) {				// Interruption générée par TIMER
		*(Timer) = 0; 										
		count ^= 0x1;
		*RED_LEDS = count;
	}

	return;
}

main() {
	*(Timer + 2) = 0xF080;  		// COUNTER START VALUE (LOW)
	*(Timer + 3) = 0x2FA;   		// COUNTER START VALUE (HIGH)
	*(Timer + 1) = 7;				// ..... STOP START COUNT IT0

	NIOS2_WRITE_IENABLE(0x3);

	NIOS2_WRITE_STATUS(0x1);

	while(1);
}
