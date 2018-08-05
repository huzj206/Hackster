#include "xil_cache.h"
#include "xparameters.h"
#include <stdio.h>
#include <MyDisp.h>
#include <mtds.h>
#include "sleep.h"

extern "C" {
#include "PmodMAXSONAR.h "
#include "xparameters.h"
}

#define PMOD_MAXSONAR_BASEADDR XPAR_PMODMAXSONAR_0_AXI_LITE_GPIO_BASEADDR
#define CLK_FREQ 100000000

PmodMAXSONAR sonar;

void EraseImageBox(bool fill, int x1, int y1, int x2, int y2);

int main()
{
	char c[50];
	MAXSONAR_begin(&sonar, PMOD_MAXSONAR_BASEADDR, CLK_FREQ);

	printf("www.adiuvoengineering.com Presents\n\r");
	printf("Sonar Distance Measuring Example\n\r");


    mydisp.begin();
    mydisp.clearDisplay(clrBlack);
    mydisp.setForeground(clrWhite);
    mydisp.setPen(penSolid);
    mydisp.setForeground(clrBlue);

    //mydisp.drawImage((char*) "Images/IMG_0100.BMP", 20, 20);
    mydisp.drawImage((char*) "Images/logo_large.BMP", 70, 20);
    mydisp.drawText((char*) "www.adiuvoengineering.com", 20, 160);
    mydisp.drawText((char*) "Hexapod Robot Controller", 40, 170);
    mydisp.drawText((char*) "Distance To Object", 60, 190);
    print("\n\r");
    u32 dist;
    while (1) {
	  dist = MAXSONAR_getDistance(&sonar);
	  xil_printf("dist (in) = %3d\r", dist);
	  sprintf(c, "%d", dist);
	  EraseImageBox(true, 120, 200, 240, 220);
	  mydisp.drawText(c, 120, 200);
	  usleep(200000);
    }
	return 0;
}

void EraseImageBox(bool fill, int x1, int y1, int x2, int y2) {
   mydisp.setForeground(clrBlack);
   mydisp.setPen(penNull);
   mydisp.drawRectangle(fill, x1, y1, x2, y2);
}


