#include "macro_tokens.h"
#include "global.h"
#include <string.h>

token_t macro_token_list[] = 
{
	{ "NOP",			Q_NOP },			// value = ignored
	{ "PRESS",			Q_KEY_PRESS },		// value = hid code
	{ "MAKE",			Q_KEY_MAKE },		// value = hid code
	{ "BREAK",			Q_KEY_RELEASE },	// value = hid code
	{ "ASSIGN_META",	Q_ASSIGN_META },	// value = metas
	{ "SET_META",		Q_SET_META },		// value = metas
	{ "CLEAR_META",		Q_CLEAR_META },		// value = metas
	{ "TOGGLE_META",	Q_TOGGLE_META },	// value = metas
	{ "POP_META",		Q_POP_META },		// value = ignored
	{ "POP_ALL_META",	Q_POP_ALL_META },	// value = ignored
	{ "DELAY",			Q_DELAY_MS },		// value = delay count
	{ "CLEAR_ALL",		Q_CLEAR_ALL },		// value = ignored		// internal use
	{ "BOOT",			Q_BOOT },			// value = ignored
	{ "PUSH_META",		Q_PUSH_META },		// can be combined with any other command. value = value for other command
};

const char* lookup_macro_token(int value)
{
	int n = sizeof(macro_token_list) / sizeof(token_t);
	for ( int i = 0; i < n; ++i ) {
		if ( macro_token_list[i].value == value ) {
			return macro_token_list[i].token;
		}
	}
	return "INVALID";
}


int lookup_macro_token(const char* s)
{
	int n = sizeof(macro_token_list) / sizeof(token_t);
	for ( int i = 0; i < n; ++i ) {
		if ( 0 == stricmp(macro_token_list[i].token, s) ) {
			return macro_token_list[i].value;
		}
	}
	return INVALID_NUMBER;
}

int get_macro_arg_type(int cmd)
{
	switch ( cmd & ~Q_PUSH_META ) {
	case Q_KEY_PRESS:
	case Q_KEY_MAKE:
	case Q_KEY_RELEASE:
		return MACRO_ARG_HID;
	case Q_ASSIGN_META:
	case Q_SET_META:
	case Q_CLEAR_META:
	case Q_TOGGLE_META:
		return MACRO_ARG_META;
	case Q_DELAY_MS:
		return MACRO_ARG_DELAY;
	case Q_NOP:
	case Q_POP_META:
	case Q_POP_ALL_META:
	case Q_CLEAR_ALL:
	case Q_BOOT:
		return MACRO_ARG_NONE;
	default:
		return INVALID_NUMBER;
	}
}
