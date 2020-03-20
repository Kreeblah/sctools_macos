// scdis.cpp - config file disassembler for Soarer's Keyboard Converter.

#include "../common/global.h"
#include "../common/hid_tokens.h"
#include "../common/macro_tokens.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <utility>
#include <string>

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

FILE* fout = stdout;

const char* get_force_set(uint8_t force)
{
	static const char* sets[] = { "set1", "set2", "set3", "set2ext" };
	uint8_t force_set = force & 0x0F;
	if ( 1 <= force_set && force_set <= 4 ) {
		return sets[force_set - 1];
	}
	return "ERROR";
}

const char* get_force_protocol(uint8_t force)
{
	static const char* protocols[] = { "xt", "at" };
	uint8_t force_protocol = (force & 0xF0) >> 4;
	if ( 1 <= force_protocol && force_protocol <= 2 ) {
		return protocols[force_protocol - 1];
	}
	return "ERROR";
}

const char* get_block_type(uint8_t blk_type)
{
	static const char* blk_types[] = { "layerblock", "remapblock", "macroblock" };
	if ( 0 <= blk_type && blk_type <= 2 ) {
		return blk_types[blk_type];
	}
	return "ERROR";
}

string get_ifset(uint8_t ifset)
{
	static const char* sets[8] = { "set1", "set2", "set3", "set2ext", "INVALIDSET", "INVALIDSET", "INVALIDSET", "INVALIDSET" };
	if ( !ifset ) {
		return string("any");
	} else {
		string s;
		for ( int i = 0; i < 8; ++i ) {
			if ( ifset & 1 ) {
				s += sets[i];
				s += " ";
			}
			ifset = ifset >> 1;
		}
		return s;
	}
}

string get_macro_match_metas(uint8_t desired_meta, uint8_t matched_meta)
{
	static const char* metas[4] = { "control", "shift", "alt", "gui" };
	static const char* hmetas[8] = { "lcontrol", "lshift", "lalt", "lgui", "rcontrol", "rshift", "ralt", "rgui" };
	uint8_t unhanded_meta = (desired_meta & ~matched_meta) & 0xF0;
	string s;
	for ( int i = 0; i < 4; ++i ) {
		uint8_t mask = (uint8_t)((1 << (i + 4)) | (1 << i));
		if ( unhanded_meta & mask ) {
			s += metas[i];
			s += " ";
			desired_meta &= ~mask;
			matched_meta &= ~mask;
		}
	}
	for ( int i = 0; i < 8; ++i ) {
		uint8_t mask = (uint8_t)(1 << i);
		if ( matched_meta & mask ) {
			if ( !(desired_meta & mask) ) {
				s += "-";
			}
			s += hmetas[i];
			s += " ";
		}
	}
	return s;
}

string get_macrostep_metas(int val)
{
	static const char* metas[8] = { "lcontrol", "lshift", "lalt", "lgui", "rcontrol", "rshift", "ralt", "rgui" };
	string s;
	for ( int i = 0; i < 8; ++i ) {
		if ( val & 1 ) {
			s += metas[i];
			s += " ";
		}
		val = val >> 1;
	}
	return s;
}

string get_macrostep(int cmd, int val)
{
	//fprintf(fout, "\t%s %d\n", lookup_macro_token(cmd), val);
	string s;
	if ( cmd & Q_PUSH_META ) {
		s = "PUSH_META ";
	}
	s += lookup_macro_token(cmd & ~Q_PUSH_META);
	s += " ";
	int argtype = get_macro_arg_type(cmd);
	char buffer[64];
	switch ( argtype ) {
	case MACRO_ARG_NONE:
		break;
	case MACRO_ARG_HID:
		s += lookup_hid_token(val);
		break;
	case MACRO_ARG_META:
		s += get_macrostep_metas(val);
		break;
	case MACRO_ARG_DELAY:
		//s += itoa(val, buffer, 10);
		sprintf(buffer, "%d", val);
		s += string(buffer);
		break;
	default:
		s += "INVALID";
		break;
	}
	return s;
}

int process_layerblock(const uint8_t* buf, const uint8_t* bufend)
{
	const uint8_t* p = buf;
	fprintf(fout, "layerblock\n");
	if ( bufend - p < 1 ) {
		fprintf(fout, "# ERROR: block truncated\n");
		return 1;
	}
	uint8_t n = *p++;
	fprintf(fout, "# count: %d\n", n);
	if ( bufend - p != (int)n * 2 ) {
		fprintf(fout, "# ERROR: block size mismatch\n");
		return 1;
	}
	for ( int i = 0; i < n; ++i ) {
		uint8_t fn = *p++;
		uint8_t layer = *p++;
		fprintf(fout, "\t");
		int b = 1;
		while ( fn ) {
			if ( fn & 1 ) {
				fprintf(fout, "fn%d ", b);
			}
			++b;
			fn = fn >> 1;
		}
		fprintf(fout, "%d\n", layer);
	}
	return 0;
}

int process_remapblock(const uint8_t* buf, const uint8_t* bufend)
{
	const uint8_t* p = buf;
	fprintf(fout, "remapblock\n");
	if ( bufend - p < 2 ) {
		fprintf(fout, "# ERROR: block truncated\n");
		return 1;
	}
	uint8_t layer = *p++;
	fprintf(fout, "layer %d\n", layer);
	uint8_t n = *p++;
	fprintf(fout, "# count: %d\n", n);
	if ( bufend - p != (int)n * 2 ) {
		fprintf(fout, "# ERROR: block size mismatch\n");
		return 1;
	}
	for ( int i = 0; i < n; ++i ) {
		uint8_t from_hid = *p++;
		uint8_t to_hid = *p++;
		fprintf(fout, "\t%s %s\n", lookup_hid_token(from_hid), lookup_hid_token(to_hid));
	}
	return 0;
}

int process_macro(const uint8_t* buf, const uint8_t* /*bufend*/)
{
	// todo: use bufend to check length
	const uint8_t* p = buf;
	uint8_t hid_code = *p++;
	uint8_t desired_meta = *p++;
	uint8_t matched_meta = *p++;
	uint8_t press_flags = *p++;
	uint8_t release_flags = *p++;
	size_t press_length = press_flags & 0x3F;
	size_t release_length = release_flags & 0x3F;
	string s = get_macro_match_metas(desired_meta, matched_meta);
	fprintf(fout, "macro %s %s # %02X %02X\n", lookup_hid_token(hid_code), s.c_str(), desired_meta, matched_meta);
	for ( int i = 0; i < (int)press_length; ++i ) {
		uint8_t cmd = *p++;
		uint8_t val = *p++;
		fprintf(fout, "\t%s\n", get_macrostep(cmd, val).c_str());
	}
	if ( release_length ) {
		fprintf(fout, "onbreak%s\n", (release_flags & 0x40) ? "" : " norestoremeta");
		for ( int i = 0; i < (int)release_length; ++i ) {
			uint8_t cmd = *p++;
			uint8_t val = *p++;
			fprintf(fout, "\t%s\n", get_macrostep(cmd, val).c_str());
		}
	}
	fprintf(fout, "endmacro\n");
	return 0;
}

int process_macroblock(const uint8_t* buf, const uint8_t* bufend)
{
	const uint8_t* p = buf;
	fprintf(fout, "macroblock\n");
	if ( bufend - p < 1 ) {
		fprintf(fout, "# ERROR: block truncated\n");
		return 1;
	}
	uint8_t n = *p++;
	fprintf(fout, "# macro count: %d\n", n);
	for ( int i = 0; i < n; ++i ) {
		if ( bufend - p < 5 ) {
			fprintf(fout, "# ERROR: block truncated\n");
			return 1;
		}
		int press_length = p[3] & 0x3F;
		int release_length = p[4] & 0x3F;
		int macro_length = 5 + 2 * (press_length + release_length);
		if ( bufend - p < macro_length ) {
			fprintf(fout, "# ERROR: block truncated\n");
			return 1;
		}
		process_macro(p, p + macro_length);
		p += macro_length;
	}
	return 0;
}

int process_block(const uint8_t* buf, size_t buflen)
{
	const uint8_t* p = buf;
	const uint8_t* bufend = buf + buflen;
	if ( bufend - p < 2 ) {
		fprintf(fout, "# ERROR: block truncated\n");
		return 1;
	}
	fprintf(fout, "\n# block length: %d\n", *p++);
	uint8_t blktype = *p & 0x07;
	uint8_t blksel = (*p >> 3) & 0x07;
	uint8_t has_set = (*p & 0x40) ? 1 : 0;
	uint8_t has_id = (*p & 0x80) ? 2 : 0;
	++p;
	if ( bufend - p < has_set + has_id ) {
		fprintf(fout, "# ERROR: block truncated\n");
		return 1;
	}
	uint8_t blkset = 0;
	if ( has_set ) {
		blkset = *p++;
	}
	uint16_t blkid = 0;
	if ( has_id ) {
		blkid = (uint16_t)(*p++);
		blkid |= ((uint16_t)(*p++) << 8);
	}
	fprintf(fout, "ifset %s\n", get_ifset(blkset).c_str());
	if ( has_id ) {
		fprintf(fout, "ifkeyboard %04X\n", blkid);
	} else {
		fprintf(fout, "ifkeyboard any\n");
	}
	if ( blksel ) {
		fprintf(fout, "ifselect %d\n", blksel);
	} else {
		fprintf(fout, "ifselect any\n");
	}
// 	fprintf(fout, "%s\n", get_block_type(blktype));
	int retval = 1;
	switch ( blktype ) {
	case BLOCK_LAYERDEF:	retval = process_layerblock(p, bufend); break;
	case BLOCK_REMAP:		retval = process_remapblock(p, bufend); break;
	case BLOCK_MACRO:		retval = process_macroblock(p, bufend); break;
	}
	fprintf(fout, "endblock\n");
	return retval;
}

int process_file(const uint8_t* buf, size_t buflen)
{
	const uint8_t* p = buf;

	fprintf(fout, "# length: %u\n", buflen);

	// header...
	uint8_t sig1 = *p++;
	uint8_t sig2 = *p++;
	fprintf(fout, "# signature: %c %c\n", sig1, sig2);
	uint8_t ver1 = *p++;
	uint8_t ver2 = *p++;
	fprintf(fout, "# version: %d %d\n", ver1, ver2);
	if ( *p & 0x0F ) {
		fprintf(fout, "force %s\n", get_force_set(*p));
	}
	if ( *p & 0xF0 ) {
		fprintf(fout, "force %s\n", get_force_protocol(*p));
	}
	++p; // force
	++p; // reserved

	// blocks...
	int err = 0;
	const uint8_t* pend = buf + buflen;
	while ( p < pend ) {
		uint8_t blklen = *p;
		if ( !blklen ) {
			fprintf(fout, "ERROR: block length is zero!\n");
			return 1;
		}
		err |= process_block(p, blklen);
		p += blklen;
	}

	return err;
}

int main(int argc, char** argv)
{
	printf("scdis v1.10\n");

	if ( argc != 2 && argc != 3 ) {
		fprintf(stderr, "usage: scdis <binary_config> [<text_config>]\n");
		return 1;
	}
	const size_t bufsize = 16384;
	static uint8_t buf[bufsize];
	FILE* f = fopen(argv[1], "rb");
	if ( !f ) {
		fprintf(stderr, "error: could not open input file %s\n", argv[1]);
		return 1;
	}
	size_t buflen = fread(buf, 1, bufsize, f);
	fclose(f);
	if ( argc == 3 ) {
		fout = fopen(argv[2], "wt");
		if ( !fout ) {
			fprintf(stderr, "error: could not open output file %s\n", argv[2]);
			return 1;
		}
	}
	int err = process_file(buf, buflen);
	if ( fout != stdout ) {
		fclose(fout);
	}
	if ( err ) {
		fprintf(stderr, "errors encountered, see output file\n");
		return 1;
	}
	return 0;
}
