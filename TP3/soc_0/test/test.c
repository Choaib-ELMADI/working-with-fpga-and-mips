#include "nios2_ctrl_reg_macros.h"

#define SW (volatile int *) 0x21010
//#define G_LEDS (volatile int *) 0x11020
#define R_LEDS (volatile int *) 0x00021020

#define flag (volatile int *) 0x00021000

void the_reset (void)__attribute__((section(".reset")));
void the_reset (void)
{
	asm (".set noat");
	asm (".set nobreak");
	asm ("movia r2, _start");	/* Go to the start of  */
	asm ("jmp r2");		  	/*   the program.      */
}

void the_exception (void)__attribute__((section(".exceptions")));
void the_exception (void)
{
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


volatile unsigned int sum;
int b;

void INT_HANDLER()
{
	int int_pending;
	NIOS2_READ_IPENDING(int_pending);

	if (int_pending & 0x2)
		{
			*(flag + 3) = 0;
			b = *SW;
			sum=sum+b;
			*R_LEDS= sum;

		};
	return;
}

main()
{
	*(flag + 2) = 0x1;		
	NIOS2_WRITE_IENABLE(0x2);	
						
	NIOS2_WRITE_STATUS(0x1);
	sum = 0;
	while(1);

}

