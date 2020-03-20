#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include "../common/rawhid.h"
#include "../common/rawhid_defs.h"

typedef unsigned char u_char;

int do_boot()
{
	u_char hbuf[64];
	int err = 0;
	if ( !err ) {
		printf("scboot: sending boot request: ");
		hbuf[0] = RQ_BOOT;
		if ( 64 != rawhid_send(0, hbuf, 64, 100) ) {
			err = 2;
			printf("failed\n");
		} else {
			printf("ok\n");
		}
	}
	if ( !err ) {
		printf("device: ");
		if ( 64 != rawhid_recv(0, hbuf, 64, 220) ) {
			err = 3;
			printf("failed to respond\n");
		}
	}
	if ( !err ) {
		if ( hbuf[0] != RC_OK ) {
			err = 4;
			printf("not ok\n");
		} else {
			printf("ok\n");
		}
	}
	return err;
}

int main(int argc, char** argv)
{
	printf("scboot v1.10\n");

	if ( argc != 1 ) {
		fprintf(stderr, "usage: scboot\n");
		return 0;
	}

	printf("scboot: looking for Soarer\'s Converter: ");
	int r = rawhid_open(1, SC_VID, SC_PID, SC_USAGE_PAGE, SC_USAGE);
	if (r <= 0) {
		printf("not found\n");
		return -1;
	}
	printf("found\n");

	int err = do_boot();

	if ( err ) {
		//printf("\nerror %d\n", err);
	}
	rawhid_close(0);
	return 0;
}
