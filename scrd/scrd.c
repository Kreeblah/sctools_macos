#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include "../common/rawhid.h"
#include "../common/rawhid_defs.h"

typedef unsigned char u_char;

int do_read(const char* fname)
{
	u_char fbuf[8192];
	size_t n = 0;
	int err = 0;
	size_t remaining = 0;
	u_char hbuf[64];
	if ( !err ) {
		printf("scrd: sending read request: ");
		hbuf[0] = RQ_READ;
		if ( 64 != rawhid_send(0, hbuf, 64, 100) ) {
			err = 1;
			printf("failed\n");
		} else {
			printf("ok\n");
		}
	}
	if ( !err ) {
		printf("device: ");
		if ( 64 != rawhid_recv(0, hbuf, 64, 220) ) {
			err = 2;
			printf("failed to respond\n");
		}
	}
	if ( !err ) {
		if ( hbuf[0] != RC_OK ) {
			err = 3;
			printf("not ok\n");
		} else {
			n = (size_t)hbuf[2] << 8 | hbuf[1];
			remaining = n;
			printf("has %u bytes: ok\n", n);
		}
	}
	u_char* p = fbuf;
	while ( !err && remaining ) {
		if ( !err ) {
			printf("scrd: ");
			hbuf[0] = RC_READY;
			if ( 64 != rawhid_send(0, hbuf, 64, 100) ) {
				err = 4;
				printf("failed to send 'ready' response\n");
			} else {
				printf("ready\n");
			}
		}
		if ( !err ) {
			printf("device: ");
			if ( 64 != rawhid_recv(0, hbuf, 64, 2000) ) {
				err = 5;
				printf("failed to respond\n");
			}
		}
		if ( !err ) {
			size_t len = remaining > 64 ? 64 : remaining;
			memcpy(p, hbuf, len);
			remaining -= len;
			p += len;
			printf("sent %u bytes: ok\n", len);
		}
		if ( !err ) {
			printf("scrd: ");
			hbuf[0] = RC_OK;
			if ( 64 != rawhid_send(0, hbuf, 64, 100) ) {
				err = 6;
				printf("failed to send 'ok' response\n");
			} else {
				printf("ok\n");
			}
		}
	}
	if ( !err ) {
		printf("scrd: ");
		hbuf[0] = RC_COMPLETED;
		if ( 64 != rawhid_send(0, hbuf, 64, 100) ) {
			err = 7;
			printf("failed to send 'complete' response\n");
		} else {
			printf("complete\n");
		}
	}
	if ( !err ) {
		printf("scrd: writing file: ");
		FILE* f = fopen(fname, "wb");
		if ( f ) {
			fputc('S', f);
			fputc('C', f);
			size_t n2 = fwrite(fbuf, 1, n, f);
			fclose(f);
			printf("%u bytes: ", n2 + 2);
			printf("ok\n");
		} else {
			err = 8;
			printf("failed\n");
		}
	}
	return err;
}

int main(int argc, char** argv)
{
	printf("scrd v1.10\n");

	if ( argc != 2 ) {
		fprintf(stderr, "usage: scrd <config_binary>\n");
		return 0;
	}

	printf("scrd: looking for Soarer\'s Converter: ");
	int r = rawhid_open(1, SC_VID, SC_PID, SC_USAGE_PAGE, SC_USAGE);
	if (r <= 0) {
		printf("not found\n");
		return -1;
	}
	printf("found\n");

	int err = do_read(argv[1]);

	if ( err ) {
		//printf("\nerror %d\n", err);
	}
	rawhid_close(0);
	return 0;
}
