/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * Test Application for the XADC
 *
 */
#include "xsysmon.h"
#include "xparameters.h"
#include "xstatus.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xil_io.h"
#include "xadc_driver.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "errno.h"



#define XPAR_AXI_XADC_0_DEVICE_ID 0
#define C_BASEADDR 0x43C10000
#define DELAY_COUNT 100000000 // Adjust this value as needed for your environment
#define BUFFER_SIZE 1000 // Define a buffer size for storing samples

//void delay(int count) {
//    for (int i = 0; i < count; i++) {
//        asm("nop"); // No-operation instruction to create a delay
//    }
//}

int main()
{
	u16 vaux[16];
//	u16 data_buffer[BUFFER_SIZE];
//	int buffer_index = 0;
	//init_platform();

	Xil_Out32(C_BASEADDR + 0x300 , 0x9103); //40
	Xil_Out32(C_BASEADDR + 0x304 , 0x3F0F); //41
	Xil_Out32(C_BASEADDR + 0x308 , 0x0400); //42
	Xil_Out32(C_BASEADDR + 0x320 , 0x0800); //40
	for (int counter = 0; counter < 10; counter++)
	{
		vaux[0] = Xil_In32(C_BASEADDR + 0x20C);
		vaux[1] = Xil_In32(C_BASEADDR + 0x240);
		vaux[2] = Xil_In32(C_BASEADDR + 0x244);
		vaux[3] = Xil_In32(C_BASEADDR + 0x248);
		vaux[4] = Xil_In32(C_BASEADDR + 0x24C);
		vaux[5] = Xil_In32(C_BASEADDR + 0x254);
		vaux[6] = Xil_In32(C_BASEADDR + 0x258);
		vaux[7] = Xil_In32(C_BASEADDR + 0x25C);
		vaux[8] = Xil_In32(C_BASEADDR + 0x260);
		vaux[9] = Xil_In32(C_BASEADDR + 0x264);
		vaux[10] = Xil_In32(C_BASEADDR + 0x268);
		vaux[11] = Xil_In32(C_BASEADDR + 0x26C);
		vaux[12] = Xil_In32(C_BASEADDR + 0x270);
		vaux[13] = Xil_In32(C_BASEADDR + 0x274);
		vaux[14] = Xil_In32(C_BASEADDR + 0x278);
		vaux[15] = Xil_In32(C_BASEADDR + 0x27C);
//		xil_printf("data1 = %03dmv\n\r", vaux[0]);
//		xil_printf("data2 = %03dmv\n\r", vaux[1]);
//		xil_printf("data3 = %03dmv\n\r", vaux[2]);
//		xil_printf("data4 = %03dmv\n\r", vaux[3]);
//		xil_printf("data5 = %03dmv\n\r", vaux[4]);
//		xil_printf("data6 = %03dmv\n\r", vaux[5]);


//		xil_printf("data9 = %03dmv\n\r", vaux[8]);
//		xil_printf("data10 = %03dmv\n\r", vaux[9]);
//		xil_printf("data11 = %03dmv\n\r", vaux[10]);
//		xil_printf("data12 = %03dmv\n\r", vaux[11]);
//		xil_printf("data13 = %03dmv\n\r", vaux[12]);
//		xil_printf("data14 = %03dmv\n\r", vaux[13]);

// R2 = 19.76 KOhm, R1 = 0 - 8.89 KOhm
		vaux[14] = vaux[14] >> 4;
		vaux[14] = vaux[14] * 0.246;
		vaux[7] = vaux[7] >> 4;
		vaux[7] = vaux[7] * 0.246;
		vaux[15] = vaux[15] >> 4;
		vaux[15] = vaux[15] * 0.246;
		vaux[6] = vaux[6] >> 4;
		vaux[6] = vaux[6] * 0.246;

		data_buffer[buffer_index++] = vaux[14];
		data_buffer[buffer_index++] = vaux[7];
		data_buffer[buffer_index++] = vaux[15];
		data_buffer[buffer_index++] = vaux[6];

		xil_printf("PIN 1/PIN 7 = %03dmv\n\r", vaux[14]);
		xil_printf("PIN 2/PIN 8 = %03dmv\n\r", vaux[7]);
		xil_printf("PIN 3/PIN 9 = %03dmv\n\r", vaux[15]);
		xil_printf("PIN 4/PIN 10 = %03dmv\n\r", vaux[6]);
		//sleep(2);
		delay(DELAY_COUNT / BUFFER_SIZE);

	}
	//cleanup_platform();
	return 0;
}
