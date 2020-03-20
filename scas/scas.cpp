// scas.cpp - config file assembler for Soarer's Keyboard Converter.

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

#define SETTINGS_VERSION_MAJOR 1
#define SETTINGS_VERSION_MINOR 1

#define COMMENT_CHAR '#'

#define ERR_FILE_NOT_FOUND	1
#define ERR_INVALID_COMMAND	2
#define ERR_INVALID_ARGS	3
#define ERR_NOT_IMPLEMENTED	4
#define ERR_BLOCK_TOO_LARGE	5
#define ERR_MACRO_TOO_LONG	6
#define ERR_FILE_WRITE		7

void print_error(int err)
{
	switch ( err ) {
	case ERR_FILE_NOT_FOUND:	fprintf(stderr, "file not found\n");	break;
	case ERR_INVALID_COMMAND:	fprintf(stderr, "invalid command\n");	break;
	case ERR_INVALID_ARGS:		fprintf(stderr, "invalid argument\n");	break;
	case ERR_NOT_IMPLEMENTED:	fprintf(stderr, "not implemented\n");	break;
	case ERR_BLOCK_TOO_LARGE:	fprintf(stderr, "block too large\n");	break;
	case ERR_MACRO_TOO_LONG:	fprintf(stderr, "macro too long\n");	break;
	default:					fprintf(stderr, "unknown error\n");		break;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const char* skip_whitespace(const char* p)
{
	while ( isspace(*p) ) {
		++p;
	}
	return p;
}

const char* skip_non_whitespace(const char* p)
{
	while ( *p && !isspace(*p) ) {
		++p;
	}
	return p;
}

const char* skip_digit(const char* p)
{
	while ( isdigit(*p) ) {
		++p;
	}
	return p;
}

const char* match(const char* s1, const char* s2)
{
	size_t len = strlen(s1);
	if ( 0 == strnicmp(s1, s2, len) ) {
		return s2 + len;
	}
	return 0;
}

const char* skip_to_end_quote(const char* p)
{
	if ( *p == '\"' ) {
		return p;
	}
	while ( *p ) {
		if ( *p == '\"' && *(p-1) != '\\' ) {
			break;
		}
		++p;
	}
	return p;
}

const char* skip_token(const char* p)
{
	p = skip_whitespace(p);
	if ( *p == '\"' ) {
		++p;
		p = skip_to_end_quote(p);
		if ( *p == '\"' ) {
			++p;
		}
	} else {
		p = skip_non_whitespace(p);
	}
	p = skip_whitespace(p);
	return p;
}

string get_token(const char* p)
{
	p = skip_whitespace(p);
	const char* p2;
	if ( *p == '\"' ) {
		++p;
		p2 = skip_to_end_quote(p);
	} else {
		p2 = skip_non_whitespace(p);
	}
	return string(p, p2);
}

int parse_int(const char* args)
{
	args = skip_whitespace(args);
	if ( isdigit(*args) ) {
		return atoi(args);
	}
	return INVALID_NUMBER;
}

int parse_int(const char* args, int minval, int maxval)
{
	int v = parse_int(args);
	if ( minval <= v && v <= maxval ) {
		return v;
	}
	return INVALID_NUMBER;
}

int parse_hid(const char* args)
{
	string t = get_token(args);
	return lookup_hid_token(t.c_str());
/*

	const char* p2 = skip_non_whitespace(args);
	char c = *p2;
	if ( c ) {
		*p2 = 0;
	}
	int hid = lookup_hid_token(args);
	if ( c ) {
		*p2 = c;
	}
	return hid;
*/
}

bool parse_meta_match(const char* args, int& desired_meta, int& matched_meta)
{
	desired_meta = 0;
	matched_meta = 0;
	const char* p = args;
	while ( *p ) {
		bool inverted = false;
		if ( *p == '-' ) {
			inverted = true;
			++p;
		}
		string t = get_token(p);
		int meta = lookup_meta_token(t.c_str());
		if ( meta == INVALID_NUMBER ) {
			return false;
		}
		if ( inverted ) {
			desired_meta &= ~meta;
			matched_meta |= meta;
		} else {
			desired_meta |= meta;
			if ( is_meta_handed(meta) ) {
				matched_meta |= meta;
			} else {
				matched_meta |= (meta & 0x0F);
			}
		}
		p = skip_token(p);
	}
	return true;
}

int parse_meta_handed(const char* p)
{
	int val = 0;
	while ( *p ) {
		string t = get_token(p);
		int meta = lookup_meta_token(t.c_str());
		if ( meta == INVALID_NUMBER /*|| !is_meta_handed(meta)*/ ) {
			return INVALID_NUMBER;
		}
		val |= meta;
		p = skip_token(p);
	}
	return val;
}

bool parse_macro_cmd(const char* args, int& cmd, int& val)
{
	string t = get_token(args);
	cmd = lookup_macro_token(t.c_str());
	if ( cmd == INVALID_NUMBER ) {
		return false;
	}
	const char* p = skip_token(args);
	// todo: Q_PLAY
	if ( cmd == Q_PUSH_META ) {
		t = get_token(p);
		int q = lookup_macro_token(t.c_str());
		if ( q == INVALID_NUMBER ) {
			return false;
		}
		cmd |= q;
		p = skip_token(p);
	}
	t = get_token(p);
	//char* p2 = p;
	int argtype = get_macro_arg_type(cmd);
	switch ( argtype ) {
	case MACRO_ARG_HID:
		val = lookup_hid_token(t.c_str());
		//p2 = skip_token(p);
		break;
	case MACRO_ARG_META:
		val = parse_meta_handed(p);
		////p2 = next_token(p);
		break;
	case MACRO_ARG_DELAY:
		val = parse_int(t.c_str(), 0, 255);
		//p2 = skip_token(p);
		break;
	case MACRO_ARG_NONE:
		val = 0;
		break;
	}
	return val != INVALID_NUMBER;
}

int lookup_set_token(const char* t)
{
	if ( 0 == stricmp(t, "set1") ) {
		return 1;
	} else if ( 0 == stricmp(t, "set2") ) {
		return 2;
	} else if ( 0 == stricmp(t, "set3") ) {
		return 3;
	} else if ( 0 == stricmp(t, "set2ext") ) {
		return 4;
	} else if ( 0 == stricmp(t, "any") ) {
		return 0;
	}
	return INVALID_NUMBER;
}

int parse_single_set(const char* p)
{
	string t = get_token(p);
	int s = lookup_set_token(t.c_str());
	if ( s == INVALID_NUMBER ) {
		return INVALID_NUMBER;
	}
	return s;
}

int parse_multi_set(const char* p)
{
	int val = 0;
	while ( *p ) {
		string t = get_token(p);
		int s = lookup_set_token(t.c_str());
		if ( s == INVALID_NUMBER ) {
			return INVALID_NUMBER;
		}
		if ( s ) {
			val |= 1 << (s - 1);
		} else {
			val = 0;
		}
		p = skip_token(p);
	}
	return val;
}

int parse_function_n(const char* p)
{
	if ( 0 == strnicmp("fn", p, 2) ) {
		p += 2;
		if ( isdigit(*p) ) {
			int v = atoi(p);
			if ( 1 <= v && v <= 8 ) {
				return v;
			}
		}
	}
	return INVALID_NUMBER;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef int (*command_fn)(const char* args);

uint8_t current_force_flags = 0;
int cmd_force(const char* args)
{
	int set = parse_single_set(args);
	if ( set != INVALID_NUMBER ) {
		current_force_flags = (current_force_flags & 0xF0) | (uint8_t)set;
		return 0;
	}
	// todo: XT/AT force?
	return ERR_INVALID_ARGS;
}

uint8_t current_select = 0;
int cmd_select(const char* args)
{
	string t = get_token(args);
	int s;
	if ( 0 == stricmp(t.c_str(), "any") ) {
		s = 0;
	} else {
		s = parse_int(args, 1, 7);
	}
	if ( s != INVALID_NUMBER ) {
		current_select = (uint8_t)s;
		return 0;
	}
	return ERR_INVALID_ARGS;
}

uint8_t current_scanset = 0;
int cmd_scanset(const char* args)
{
	int s = parse_multi_set(args);
	if ( s != INVALID_NUMBER ) {
		current_scanset = (uint8_t)s;
		return 0;
	}
	return ERR_INVALID_ARGS;
}

bool is_hex(char c)
{
	c = (char)toupper(c);
	return isdigit(c) || ('A' <= c && c <= 'F');
}

int parse_hex(char c)
{
	c = (char)toupper(c);
	if ( isdigit(c) ) {
		return c - '0';
	} else if ( 'A' <= c && c <= 'F' ) {
		return c - 'A' + 10;
	} else {
		return INVALID_NUMBER;
	}
}

int parse_hex(const char* p)
{
	p = skip_whitespace(p);
	int val = 0;
	int digit = parse_hex(*p++);
	if ( digit == INVALID_NUMBER ) {
		return INVALID_NUMBER;
	}
	while ( digit != INVALID_NUMBER ) {
		val = (val << 4) | digit;
		digit = parse_hex(*p++);
	}
	return val;
}

int parse_hex(const char* p, int minval, int maxval)
{
	int v = parse_hex(p);
	if ( minval <= v && v <= maxval ) {
		return v;
	}
	return INVALID_NUMBER;
}

uint16_t current_keyboard_id = 0;
int cmd_keyboard_id(const char* args)
{
	string t = get_token(args);
	if ( 0 == stricmp(t.c_str(), "any") ) {
		current_keyboard_id = 0;
	} else {
		int v = parse_hex(args, 0, 0xFFFF);
		if ( v == INVALID_NUMBER ) {
			return ERR_INVALID_ARGS;
		}
		current_keyboard_id = (uint16_t)v;
	}
	return 0;
}

uint8_t current_layer = 0;
int cmd_layer(const char* args)
{
	int v = parse_int(args, 0, 255);
	if ( v != INVALID_NUMBER ) {
		current_layer = (uint8_t)v;
		return 0;
	}
	return ERR_INVALID_ARGS;
}

typedef pair<uint8_t, uint8_t> layerdef_pair;
typedef vector<layerdef_pair> layerdef_list_t;
layerdef_list_t layerdef_list;
int cmd_layerdef(const char* args)
{
	int fn_combo = 0;
	const char* p = skip_whitespace(args);
	for ( ; *p; p = skip_token(p) ) {
		int fn = parse_function_n(p);
		if ( fn == INVALID_NUMBER ) {
			break;
		}
		fn_combo |= 1 << (fn - 1);
	}
	if ( !fn_combo ) {
		return ERR_INVALID_ARGS;
	}
	int layer = parse_int(p, 1, 255); // layer id
	if ( layer == INVALID_NUMBER ) {
		return ERR_INVALID_ARGS;
	}
	layerdef_list.push_back(layerdef_pair((uint8_t)fn_combo, (uint8_t)layer));
	return 0;
}

typedef pair<uint8_t, uint8_t> remap_pair;
typedef vector<remap_pair> remap_list_t;
remap_list_t remap_list;
int cmd_remap(const char* args)
{
	args = skip_whitespace(args);
	int v1 = parse_hid(args);
	if ( v1 != INVALID_NUMBER ) {
		args = skip_token(args);
		int v2 = parse_hid(args);
		if ( v2 != INVALID_NUMBER ) {
			remap_list.push_back(remap_pair((uint8_t)v1, (uint8_t)v2));
			return 0;
		}
	}
	return ERR_INVALID_ARGS;
}

int current_macro_phase = -1; // -1 = invalid, 0 = make, 1 = break
uint8_t current_macro_release_meta = 1;
uint8_t current_hid_code = 0;
uint8_t current_desired_meta = 0;
uint8_t current_matched_meta = 0;
int cmd_macro(const char* args)
{
	string t = get_token(args);
	int hid_code = lookup_hid_token(t.c_str());
	if ( hid_code == INVALID_NUMBER ) {
		return ERR_INVALID_ARGS;
	}
	int desired_meta, matched_meta;
	if ( !parse_meta_match(skip_token(args), desired_meta, matched_meta) ) {
		return ERR_INVALID_ARGS;
	}
	current_macro_phase = 0;
	current_macro_release_meta = 1;
	current_hid_code = (uint8_t)hid_code;
	current_desired_meta = (uint8_t)desired_meta;
	current_matched_meta = (uint8_t)matched_meta;
	return 0;
}

/*
int cmd_meta(char* args)
{
	int v = parse_int(args, 0, 255);
	if ( v != INVALID_NUMBER ) {
		current_desired_meta = (uint8_t)v;
		return 0;
	}
	return ERR_INVALID_ARGS;
}
*/

/*
int cmd_ignore(char* args)
{
	int v = parse_int(args, 0, 255);
	if ( v != INVALID_NUMBER ) {
		current_matched_meta = (uint8_t)v;
		return 0;
	}
	return ERR_INVALID_ARGS;
}
*/

int cmd_onbreak(const char* args)
{
	if ( current_macro_phase != 0 ) {
		return ERR_INVALID_COMMAND;
	}
	current_macro_phase = 1;
	string t = get_token(args);
	if ( t == "" ) {
		current_macro_release_meta = 1;
	} else if ( 0 == stricmp(t.c_str(), "norestoremeta") ) {
		current_macro_release_meta = 0;
	} else {
		return ERR_INVALID_ARGS;
	}
	return 0;
}

typedef pair<uint8_t, uint8_t> mcommand_pair;
typedef vector<mcommand_pair> mcommand_list_t;
mcommand_list_t press_mcommand_list;
mcommand_list_t release_mcommand_list;
/*
int cmd_press(char* args)
{
	int cmd, val;
	if ( parse_macro_cmd(args, cmd, val) ) {
		press_mcommand_list.push_back(mcommand_pair((uint8_t)cmd, (uint8_t)val));
		return 0;
	}
	return ERR_INVALID_ARGS;
}

int cmd_release(char* args)
{
	int cmd, val;
	if ( parse_macro_cmd(args, cmd, val) ) {
		release_mcommand_list.push_back(mcommand_pair((uint8_t)cmd, (uint8_t)val));
		return 0;
	}
	return ERR_INVALID_ARGS;
}
*/

int cmd_macrostep(const char* args)
{
	int cmd, val;
	if ( parse_macro_cmd(args, cmd, val) ) {
		mcommand_pair mcp((uint8_t)cmd, (uint8_t)val);
		if ( current_macro_phase == 0 ) {
			press_mcommand_list.push_back(mcp);
		} else {
			release_mcommand_list.push_back(mcp);
		}
		return 0;
	}
	return ERR_INVALID_ARGS;
}



struct macro_t
{
	uint8_t hid_code;
	uint8_t desired_meta;
	uint8_t matched_meta;
	uint8_t press_flags;
	uint8_t release_flags;
	mcommand_list_t	commands;
};
typedef vector<macro_t> macro_list_t;
macro_list_t macro_list;
int cmd_endmacro(const char* /*args*/)
{
	if ( current_macro_phase == -1 ) {
		return ERR_INVALID_COMMAND;
	}
	current_macro_phase = -1;
	macro_t macro;
	macro.hid_code = current_hid_code;
	macro.desired_meta = current_desired_meta;
	macro.matched_meta = current_matched_meta;
	macro.press_flags = (uint8_t)press_mcommand_list.size();
	macro.release_flags = (uint8_t)release_mcommand_list.size();
	macro.release_flags |= current_macro_release_meta << 7;
	if ( press_mcommand_list.size() > 63 || release_mcommand_list.size() > 63 ) {
		return ERR_MACRO_TOO_LONG;
	}
	//macro.commands.push_back(press_mcommand_list);
	macro.commands.insert(macro.commands.end(), press_mcommand_list.begin(), press_mcommand_list.end());
	//macro.commands.push_back(release_mcommand_list);
	macro.commands.insert(macro.commands.end(), release_mcommand_list.begin(), release_mcommand_list.end());
	macro_list.push_back(macro);
	press_mcommand_list.clear();
	release_mcommand_list.clear();
	return 0;
}

int block_type = BLOCK_NONE;

int cmd_layerdefblock(const char* /*args*/)
{
	if ( block_type != BLOCK_NONE ) {
		return ERR_INVALID_COMMAND;
	}
	block_type = BLOCK_LAYERDEF;
	return 0;
}

int cmd_remapblock(const char* /*args*/)
{
	if ( block_type != BLOCK_NONE ) {
		return ERR_INVALID_COMMAND;
	}
	block_type = BLOCK_REMAP;
	return 0;
}

int cmd_macroblock(const char* /*args*/)
{
	if ( block_type != BLOCK_NONE ) {
		return ERR_INVALID_COMMAND;
	}
	block_type = BLOCK_MACRO;
	return 0;
}

int cmd_invalid(const char* args)
{
	switch ( block_type ) {
	case BLOCK_LAYERDEF:	return cmd_layerdef(args);
	case BLOCK_REMAP:		return cmd_remap(args);
	case BLOCK_MACRO:		return cmd_macrostep(args);
	default:				return ERR_INVALID_COMMAND;
	}
}

int process_file(const char* fname);

int cmd_include(const char* args)
{
	string fname = get_token(args);
	return process_file(fname.c_str());
}


typedef vector<uint8_t> block_t;
typedef vector<block_t> block_list_t;
block_list_t block_list;

void fill_block_header(block_t& block)
{
	// common block header stuff...
	block.push_back(0); // placeholder for size
	uint8_t flags = (uint8_t)block_type;
	flags |= current_select << 3;
	flags |= (current_scanset != 0) << 6;
	flags |= (current_keyboard_id != 0) << 7;
	block.push_back(flags);
	if ( current_scanset ) {
		block.push_back(current_scanset);
	}
	if ( current_keyboard_id ) {
		block.push_back((uint8_t)(current_keyboard_id & 0xFF));
		block.push_back((uint8_t)((current_keyboard_id >> 8) & 0xFF));
	}
}

int cmd_endlayerdefblock(const char* /*args*/)
{
	block_t block;
	fill_block_header(block);
	block.push_back((uint8_t)layerdef_list.size());
	for ( int i = 0; i < (int)layerdef_list.size(); ++i ) {
		block.push_back(layerdef_list[i].first);
		block.push_back(layerdef_list[i].second);
	}
	if ( block.size() > 255 ) {
		return ERR_BLOCK_TOO_LARGE;
	}
	block[0] = (uint8_t)block.size();
	block_list.push_back(block);
	layerdef_list.clear();
	block_type = BLOCK_NONE;
	return 0;
}

int cmd_endremapblock(const char* /*args*/)
{
	block_t block;
	fill_block_header(block);
	block.push_back(current_layer);
	block.push_back((uint8_t)remap_list.size());
	for ( int i = 0; i < (int)remap_list.size(); ++i ) {
		block.push_back(remap_list[i].first);
		block.push_back(remap_list[i].second);
	}
	if ( block.size() > 255 ) {
		return ERR_BLOCK_TOO_LARGE;
	}
	block[0] = (uint8_t)block.size();
	block_list.push_back(block);
	remap_list.clear();
	current_layer = 0;
	block_type = BLOCK_NONE;
	return 0;
}

int cmd_endmacroblock(const char* /*args*/)
{
	block_t block;
	fill_block_header(block);
	block.push_back((uint8_t)macro_list.size());
	for ( int i = 0; i < (int)macro_list.size(); ++i ) {
		block.push_back(macro_list[i].hid_code);
		block.push_back(macro_list[i].desired_meta);
		block.push_back(macro_list[i].matched_meta);
		block.push_back(macro_list[i].press_flags);
		block.push_back(macro_list[i].release_flags);
		for ( int j = 0; j < (int)macro_list[i].commands.size(); ++j ) {
			block.push_back(macro_list[i].commands[j].first);
			block.push_back(macro_list[i].commands[j].second);
		}
	}
	if ( block.size() > 255 ) {
		return ERR_BLOCK_TOO_LARGE;
	}
	block[0] = (uint8_t)block.size();
	block_list.push_back(block);
	macro_list.clear();
	block_type = BLOCK_NONE;
	return 0;
}

int cmd_endblock(const char* args)
{
	switch ( block_type ) {
	case BLOCK_LAYERDEF:	return cmd_endlayerdefblock(args);
	case BLOCK_REMAP:		return cmd_endremapblock(args);
	case BLOCK_MACRO:		return cmd_endmacroblock(args);
	default:				return ERR_INVALID_COMMAND;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

struct command_map_t
{
	const char*	cmd;
	command_fn	fn;
};

command_map_t command_map[] =
{
	{ "force",			cmd_force },

	{ "ifselect",		cmd_select },
	{ "ifset",			cmd_scanset },
	{ "ifkeyboard",		cmd_keyboard_id },

	{ "layerblock",		cmd_layerdefblock },

	{ "remapblock",		cmd_remapblock },
	{ "layer",			cmd_layer },

	{ "macroblock",		cmd_macroblock },
	{ "macro",			cmd_macro },
	{ "onbreak",		cmd_onbreak },
	{ "endmacro",		cmd_endmacro },

	{ "endblock",		cmd_endblock },

	{ "include",		cmd_include },
};

command_fn find_command(const char* cmd)
{
	int n = sizeof(command_map) / sizeof(command_map_t);
	for ( int i = 0; i < n; ++i ) {
		if ( 0 == stricmp(cmd, command_map[i].cmd) ) {
			return command_map[i].fn;
		}
	}
	return cmd_invalid;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int process_line(char* linebuf)
{
	char* pcomment = strchr(linebuf, COMMENT_CHAR);
	if ( pcomment ) {
		*pcomment = 0;
	}
	string t = get_token(linebuf);
	if ( t.size() ) {
		const char* p;
		command_fn fn = find_command(t.c_str());
		if ( fn != cmd_invalid ) {
			p = skip_token(linebuf);
		} else {
			p = linebuf;
		}
		if ( int err = fn(p) ) {
			return err;
		}
	}
// 	p = skip_whitespace(linebuf);
// 	char* p2 = skip_non_whitespace(p);
// 	if ( *p2 ) {
// 		*p2++ = 0;
// 		p2 = skip_whitespace(p2);
// 		if ( int err = find_command(p)(p2) ) {
// 			return err;
// 		}
// 	}
	return 0;
}

int process_file(FILE* f)
{
	int linenum = 0;
	char linebuf[256];
	while ( fgets(linebuf, sizeof(linebuf), f) ) {
		++linenum;
		if ( int err = process_line(linebuf) ) {
			fprintf(stderr, "error at line %d: ", linenum);
			return err;
		}
	}
	return 0;
}

int process_file(const char* fname)
{
	FILE* f = fopen(fname, "rt");
	if ( f ) {
		int retval = process_file(f);
		fclose(f);
		return retval;
	}
	return ERR_FILE_NOT_FOUND;
}

int write_target(FILE* f)
{
	// Header...
	fputc('S', f); // signature...
	fputc('C', f);
	fputc(SETTINGS_VERSION_MAJOR, f);
	fputc(SETTINGS_VERSION_MINOR, f);
	fputc(current_force_flags, f);
	fputc(0, f); // reserved

	// Blocks...
	for ( int i = 0; i < (int)block_list.size(); ++i ) {
		if ( !fwrite(&(block_list[i][0]), block_list[i].size(), 1, f) ) {
			return ERR_FILE_WRITE;
		}
	}
	return 0;
}

int write_target(const char* fname)
{
	FILE* f = fopen(fname, "wb");
	if ( f ) {
		int retval = write_target(f);
		fclose(f);
		return retval;
	}
	return ERR_FILE_WRITE;
}

int main(int argc, char** argv)
{
	printf("scas v1.10\n");

	int err = 0;
	if ( argc < 3 ) {
		fprintf(stderr, "usage: scas <text_config> [<text_config> ...] <binary_config>\n");
		err = 1;
	}
	for ( int i = 1; i < argc - 1; ++i ) {
		err = process_file(argv[i]);
		if ( err ) {
			print_error(err);
		}
	}
	if ( !err ) {
		err = write_target(argv[argc - 1]);
		if ( err ) {
			fprintf(stderr, "unable to write to file: %s\n", argv[argc - 1]);
		}
	}
	if ( !err ) {
		fprintf(stderr, "No errors. Wrote: %s\n", argv[argc - 1]);
	}
	return err ? 1 : 0;
}
