#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

#include "../common/rawhid.h"
#include "../common/rawhid_defs.h"

typedef unsigned char u_char;

#define LSB(n) (u_char)((n) & 255)
#define MSB(n) (u_char)(((n) >> 8) & 255)

#define FILE_HEADER_LEN 2

#define WRITE_PACKET_HEADER_LEN 4
#define WRITE_PACKET_DATA_LEN (PACKET_LEN - WRITE_PACKET_HEADER_LEN)

#define EEPROM_HEADER_LEN 4
#define EEPROM_FOOTER_LEN 2

#define MAX_EEPROM_SIZE 8192

#define SETTINGS_HEADER_LEN 4

#define SETTINGS_MAX_LEN (MAX_EEPROM_SIZE - EEPROM_HEADER_LEN - EEPROM_FOOTER_LEN)

#define SETTINGS_FILE_MIN_LEN (FILE_HEADER_LEN + SETTINGS_HEADER_LEN)
#define SETTINGS_FILE_MAX_LEN (SETTINGS_MAX_LEN + FILE_HEADER_LEN)

#define FILE_BUF_LEN (SETTINGS_FILE_MAX_LEN + 1)

int do_compatibility_check(u_char ver_major, u_char ver_minor, int len)
{
	u_char hbuf[64];
	int err = 0;
	if ( !err ) {
		printf("scwr: sending info request: ");
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
		u_char settings_max_ver_major = 0;
		u_char settings_max_ver_minor = 0;
		u_char protocol_ver_major = 0;
		u_char protocol_ver_minor = 0;
		int max_len = 0;
		for ( int i = 1; i < 64; i += 3 ) {
			u_char ic = hbuf[i];
			if ( ic == IC_END ) {
				break;
			}
			switch ( ic ) {
			case IC_PROTOCOL_VERSION:
				protocol_ver_major = hbuf[i+1];
				protocol_ver_minor = hbuf[i+2];
				break;
			case IC_CONFIG_MAX_VERSION:
				settings_max_ver_major = hbuf[i+1];
				settings_max_ver_minor = hbuf[i+2];
				break;
			case IC_EEPROM_SIZE:
				max_len = hbuf[i+1] + 256 * hbuf[i+2] - EEPROM_HEADER_LEN - EEPROM_FOOTER_LEN;
				break;
			}
		}
		printf("protocol version check: converter=%d.%02d, scwr=%d.%02d: ", protocol_ver_major, protocol_ver_minor, PROTOCOL_VERSION_MAJOR, PROTOCOL_VERSION_MINOR);
		if ( protocol_ver_major != PROTOCOL_VERSION_MAJOR || protocol_ver_minor < PROTOCOL_VERSION_MINOR ) {
			err = 12;
			printf("failed\n");
		} else {
			printf("ok\n");
		}
		printf("settings version check: converter=%d.%02d, file=%d.%02d: ", settings_max_ver_major, settings_max_ver_minor, ver_major, ver_minor);
		if ( settings_max_ver_major != ver_major || settings_max_ver_minor < ver_minor ) {
			err = 12;
			printf("failed\n");
		} else {
			printf("ok\n");
		}
		printf("settings length check: max=%d, file=%d bytes: ", max_len, len);
		if ( len > max_len ) {
			err = 12;
			printf("failed\n");
		} else {
			printf("ok\n");
		}
	}
	return err;
}

int do_write(const char* fname)
{
	u_char fbuf[FILE_BUF_LEN];
	size_t fbuflen = 0;
	int err = 0;
	if ( !err ) {
		printf("scwr: reading file: ");
		FILE* f = fopen(fname, "rb");
		if ( f ) {
			fbuflen = fread(fbuf, 1, FILE_BUF_LEN, f);
			fclose(f);
			printf("%u bytes: ", fbuflen);
		} else {
			printf("failed\n");
		}
	}
	if ( !err ) {
		if ( fbuflen < SETTINGS_FILE_MIN_LEN ) {
			err = 1;
			printf("too short\n");
		}
		if ( fbuflen > SETTINGS_FILE_MAX_LEN ) {
			err = 1;
			printf("too long\n");
		}
	}
	if ( !err ) {
		if ( fbuf[0] != 'S' ) {
			err = 11;
		}
		if ( fbuf[1] != 'C' ) {
			err = 11;
		}
		if ( err ) {
			printf("bad signature\n");
		} else {
			printf("ok\n");
		}
	}
	size_t remaining = fbuflen - FILE_HEADER_LEN;
	if ( !err ) {
		err = do_compatibility_check(fbuf[2], fbuf[3], (int)remaining);
	}
	u_char hbuf[PACKET_LEN];
	if ( !err ) {
		printf("scwr: sending write request for %u bytes: ", remaining);
		hbuf[0] = RQ_WRITE;
		hbuf[1] = LSB(remaining);
		hbuf[2] = MSB(remaining);
		if ( PACKET_LEN != rawhid_send(0, hbuf, PACKET_LEN, 100) ) {
			err = 2;
			printf("failed\n");
		} else {
			printf("ok\n");
		}
	}
	if ( !err ) {
		printf("device: ");
		if ( PACKET_LEN != rawhid_recv(0, hbuf, PACKET_LEN, 220) ) {
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
	u_char* p = fbuf + FILE_HEADER_LEN;
	while ( !err && remaining ) {
		if ( !err ) {
			printf("device: ");
			if ( PACKET_LEN != rawhid_recv(0, hbuf, PACKET_LEN, 2000) ) {
				err = 5;
				printf("failed to respond\n");
			}
		}
		if ( !err ) {
			if ( hbuf[0] != RC_READY ) {
				err = 6;
				printf("not ready\n");
			} else {
				printf("ready\n");
			}
		}
		if ( !err ) {
// 			size_t len = remaining > 64 ? 64 : remaining;
			size_t len = remaining > WRITE_PACKET_DATA_LEN ? WRITE_PACKET_DATA_LEN : remaining;
			hbuf[0] = RQ_CONTINUATION | RQ_WRITE;
			hbuf[1] = (u_char)len;
			size_t ofs = p - fbuf + FILE_HEADER_LEN;
			hbuf[2] = LSB(ofs);
			hbuf[3] = MSB(ofs);
			for ( size_t i = 0; i < len; ++i ) {
				hbuf[i + WRITE_PACKET_HEADER_LEN] = p[i];
			}
			printf("scwr: sending %u bytes: ", len);
// 			if ( 64 != rawhid_send(0, p, 64, 100) ) {
			if ( PACKET_LEN != rawhid_send(0, hbuf, PACKET_LEN, 100) ) {
				err = 2;
				printf("failed\n");
			} else {
				remaining -= len;
				p += len;
				printf("ok\n");
			}
		}
		if ( !err ) {
			printf("device: ");
			if ( PACKET_LEN != rawhid_recv(0, hbuf, PACKET_LEN, 220) ) {
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
	}
	if ( !err ) {
		printf("device: ");
		if ( PACKET_LEN != rawhid_recv(0, hbuf, PACKET_LEN, 2000) ) {
			err = 5;
			printf("failed to respond\n");
		}
	}
	if ( !err ) {
		if ( hbuf[0] != RC_COMPLETED ) {
			err = 7;
			printf("not complete\n");
		} else {
			printf("complete\n");
		}
	}
	return err;
}

int main(int argc, char** argv)
{
	printf("scwr v1.10\n");

	if ( argc != 2 ) {
		fprintf(stderr, "usage: scwr <config_binary>\n");
		return 0;
	}

	printf("scwr: looking for Soarer\'s Converter: ");
	int r = rawhid_open(1, SC_VID, SC_PID, SC_USAGE_PAGE, SC_USAGE);
	if (r <= 0) {
		printf("not found\n");
		return -1;
	}
	printf("found\n");

	int err = do_write(argv[1]);

	if ( err ) {
		//printf("\nerror %d\n", err);
	}
	rawhid_close(0);
	return 0;
}
