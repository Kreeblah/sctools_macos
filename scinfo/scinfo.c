#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include "../common/rawhid.h"
#include "../common/rawhid_defs.h"

typedef unsigned char u_char;

#define LSN(n) ((n) & 15)
#define MSN(n) (((n) >> 4) & 15)

void print_version(const char* s, u_char ver_hi, u_char ver_lo)
{
	//printf("%s: v%d.%d%d%d\n", s, MSN(ver_hi), LSN(ver_hi), MSN(ver_lo), LSN(ver_lo));
	printf("%s: v%d.%02d\n", s, ver_hi, ver_lo);
}


int do_info()
{
	u_char hbuf[64];
	int err = 0;
	if ( !err ) {
		printf("scinfo: sending info request: ");
		hbuf[0] = RQ_INFO;
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
	if ( !err ) {
		putchar('\n');
		for ( int i = 1; i < 64; i += 3 ) {
			u_char ic = hbuf[i];
			if ( ic == IC_END ) {
				break;
			}
			switch ( ic ) {
			case IC_CODE_VERSION:
				print_version("Code Version", hbuf[i+1], hbuf[i+2]);
				break;
			case IC_PROTOCOL_VERSION:
				print_version("Protocol Version", hbuf[i+1], hbuf[i+2]);
				break;
			case IC_CONFIG_MAX_VERSION:
				print_version("Max Settings Version", hbuf[i+1], hbuf[i+2]);
				break;
			case IC_CONFIG_VERSION:
				print_version("Current Settings Version", hbuf[i+1], hbuf[i+2]);
				break;
			case IC_RAM_SIZE:
				printf("SRAM Size: %d bytes\n", hbuf[i+1] + 256 * hbuf[i+2]);
				break;
			case IC_RAM_FREE:
				printf("SRAM Free: %d bytes\n", hbuf[i+1] + 256 * hbuf[i+2]);
				break;
			case IC_EEPROM_SIZE:
				printf("EEPROM Size: %d bytes\n", hbuf[i+1] + 256 * hbuf[i+2]);
				break;
			case IC_EEPROM_FREE:
				printf("EEPROM Free: %d bytes\n", hbuf[i+1] + 256 * hbuf[i+2]);
				break;
			}
		}
	}
	return err;
}

int main(int argc, char** argv)
{
	printf("scinfo v1.10\n");

	if ( argc != 1 ) {
		fprintf(stderr, "usage: scinfo\n");
		return 0;
	}

	printf("scinfo: looking for Soarer\'s Converter: ");
	int r = rawhid_open(1, SC_VID, SC_PID, SC_USAGE_PAGE, SC_USAGE);
	if (r <= 0) {
		printf("not found\n");
		return -1;
	}
	printf("found\n");

	int err = do_info();

	if ( err ) {
		//printf("\nerror %d\n", err);
	}
	rawhid_close(0);
	return 0;
}
