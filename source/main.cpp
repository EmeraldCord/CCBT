#include <stdio.h>
#include <cstdlib>
#include <gccore.h>
#include <asndlib.h>
#include <wiiuse/wpad.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

int main (int argc, char **argv) {
    
	VIDEO_Init();

	WPAD_Init();

	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(rmode);

	VIDEO_SetNextFramebuffer(xfb);

	VIDEO_SetBlack(FALSE);

	VIDEO_Flush();

	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

    printf("\x1b[30;0m\x1b[47;1m");
    printf("Classic Controller Button Tester\n Press HOME on a Wii Remote to Exit");

while (1) {

	WPAD_ScanPads();

	u32 pressed = WPAD_ButtonsDown(0);

	if ( pressed & WPAD_BUTTON_HOME ) exit (0); 

	if ( pressed & WPAD_CLASSIC_BUTTON_A ) printf("A Button is Working!");

	if ( pressed & WPAD_CLASSIC_BUTTON_B ) printf("B Button is Working!");

}

    VIDEO_WaitVSync();

return 0;
}
