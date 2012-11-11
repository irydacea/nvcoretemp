/*
 * nvcoretemp - Read NVIDIA graphics core temperature on the command line.
 *
 * by Iris Morelle <shadowm2006@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <NVCtrl/NVCtrlLib.h>

#define DEFAULT_DISPLAY		":0"

int main(int argc, char **argv)
{
	int res;
	int core_temp;

	char **arg;

	Display *disp;
	const char *disp_id;

	disp_id = getenv("DISPLAY");

	if(!disp_id || !*disp_id) {
		disp_id = DEFAULT_DISPLAY;
	}

	disp = XOpenDisplay(disp_id);
	if(!disp) {
		fprintf(stderr, "Could not open display %s!\n", disp_id);
		return 1;
	}

	res = XNVCTRLQueryAttribute(disp, 0, 0, NV_CTRL_GPU_CORE_TEMPERATURE, &core_temp);
	XCloseDisplay(disp);

	if(!res) {
		fprintf(stderr, "Could not query NV_CTRL_GPU_CORE_TEMPERATURE attribute!\n");
		return 1;
	}

	for(arg = &argv[1]; *arg; ++arg) {
		if(strcmp(*arg, "--batch") == 0 || strcmp(*arg, "-b") == 0) {
			printf("%d\n", core_temp);
			return 0;
		}
	}

	printf("Core temperature is %d\n", core_temp);

	return 0;
}
