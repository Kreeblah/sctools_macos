#include "hid_tokens.h"
#include "global.h"
#include <string.h>

token_t meta_token_list[] =
{
	{ "LCTRL",               0x01 }, //  Left Control
	{ "LSHIFT",              0x02 }, //  Left Shift
	{ "LALT",                0x04 }, //  Left Alt
	{ "LGUI",                0x08 }, //  Left GUI

	{ "RCTRL",               0x10 }, //  Right Control
	{ "RSHIFT",              0x20 }, //  Right Shift
	{ "RALT",                0x40 }, //  Right Alt
	{ "RGUI",                0x80 }, //  Right GUI

	{ "CTRL",                0x11 }, //  Either/Both Control
	{ "SHIFT",               0x22 }, //  Either/Both Shift
	{ "ALT",                 0x44 }, //  Either/Both Alt
	{ "GUI",                 0x88 }, //  Either/Both GUI

	{ "ALL",                 0xFF }, //  Any/All
};

token_t hid_token_list[] =
{
    { "UNASSIGNED",              0x00 }, //  No Event
    { "OVERRUN_ERROR",           0x01 }, //  Overrun Error
    { "POST_FAIL",               0x02 }, //  POST Fail
    { "ERROR_UNDEFINED",         0x03 }, //  ErrorUndefined
    { "A",                       0x04 }, //  a A
    { "B",                       0x05 }, //  b B
    { "C",                       0x06 }, //  c C
    { "D",                       0x07 }, //  d D
    { "E",                       0x08 }, //  e E
    { "F",                       0x09 }, //  f F
    { "G",                       0x0A }, //  g G
    { "H",                       0x0B }, //  h H
    { "I",                       0x0C }, //  i I
    { "J",                       0x0D }, //  j J
    { "K",                       0x0E }, //  k K
    { "L",                       0x0F }, //  l L
    { "M",                       0x10 }, //  m M
    { "N",                       0x11 }, //  n N
    { "O",                       0x12 }, //  o O
    { "P",                       0x13 }, //  p P
    { "Q",                       0x14 }, //  q Q
    { "R",                       0x15 }, //  r R
    { "S",                       0x16 }, //  s S
    { "T",                       0x17 }, //  t T
    { "U",                       0x18 }, //  u U
    { "V",                       0x19 }, //  v V
    { "W",                       0x1A }, //  w W
    { "X",                       0x1B }, //  x X
    { "Y",                       0x1C }, //  y Y
    { "Z",                       0x1D }, //  z Z
    { "1",                       0x1E }, //  1 !
    { "2",                       0x1F }, //  2 @
    { "3",                       0x20 }, //  3 #
    { "4",                       0x21 }, //  4 $
    { "5",                       0x22 }, //  5 %
    { "6",                       0x23 }, //  6 ^
    { "7",                       0x24 }, //  7 &
    { "8",                       0x25 }, //  8 *
    { "9",                       0x26 }, //  9 (
    { "0",                       0x27 }, //  0 )
    { "ENTER",                   0x28 }, //  Return
    { "ESC",                     0x29 }, //  Escape
    { "BACKSPACE",               0x2A }, //  Backspace
    { "TAB",                     0x2B }, //  Tab
    { "SPACE",                   0x2C }, //  Space
    { "MINUS",                   0x2D }, //  minus _
    { "EQUAL",                   0x2E }, //  = +
    { "LEFT_BRACE",              0x2F }, //  [ {
    { "RIGHT_BRACE",             0x30 }, //  ] }
    { "BACKSLASH",               0x31 }, //  \ |  
    { "EUROPE_1",                0x32 }, //  Europe 1
    { "SEMICOLON",               0x33 }, //  ; :
    { "QUOTE",                   0x34 }, //  quotes
    { "BACK_QUOTE",              0x35 }, //  ` ~
    { "COMMA",                   0x36 }, //  comma <
    { "PERIOD",                  0x37 }, //  . >
    { "SLASH",                   0x38 }, //  / ?
    { "CAPS_LOCK",               0x39 }, //  Caps Lock
    { "F1",                      0x3A }, //  F1
    { "F2",                      0x3B }, //  F2
    { "F3",                      0x3C }, //  F3
    { "F4",                      0x3D }, //  F4
    { "F5",                      0x3E }, //  F5
    { "F6",                      0x3F }, //  F6
    { "F7",                      0x40 }, //  F7
    { "F8",                      0x41 }, //  F8
    { "F9",                      0x42 }, //  F9
    { "F10",                     0x43 }, //  F10
    { "F11",                     0x44 }, //  F11
    { "F12",                     0x45 }, //  F12
    { "PRINTSCREEN",             0x46 }, //  Print Screen
    { "SCROLL_LOCK",             0x47 }, //  Scroll Lock
    { "PAUSE",                   0x48 }, //  Pause
    { "INSERT",                  0x49 }, //  Insert
    { "HOME",                    0x4A }, //  Home
    { "PAGE_UP",                 0x4B }, //  Page Up
    { "DELETE",                  0x4C }, //  Delete
    { "END",                     0x4D }, //  End
    { "PAGE_DOWN",               0x4E }, //  Page Down
    { "RIGHT",                   0x4F }, //  Right Arrow
    { "LEFT",                    0x50 }, //  Left Arrow
    { "DOWN",                    0x51 }, //  Down Arrow
    { "UP",                      0x52 }, //  Up Arrow
    { "NUM_LOCK",                0x53 }, //  Num Lock
    { "PAD_SLASH",               0x54 }, //  Keypad /
    { "PAD_ASTERIX",             0x55 }, //  Keypad *
    { "PAD_MINUS",               0x56 }, //  Keypad -
    { "PAD_PLUS",                0x57 }, //  Keypad +
    { "PAD_ENTER",               0x58 }, //  Keypad Enter
    { "PAD_1",                   0x59 }, //  Keypad 1 End
    { "PAD_2",                   0x5A }, //  Keypad 2 Down
    { "PAD_3",                   0x5B }, //  Keypad 3 PageDn
    { "PAD_4",                   0x5C }, //  Keypad 4 Left
    { "PAD_5",                   0x5D }, //  Keypad 5
    { "PAD_6",                   0x5E }, //  Keypad 6 Right
    { "PAD_7",                   0x5F }, //  Keypad 7 Home
    { "PAD_8",                   0x60 }, //  Keypad 8 Up
    { "PAD_9",                   0x61 }, //  Keypad 9 PageUp
    { "PAD_0",                   0x62 }, //  Keypad 0 Insert
    { "PAD_PERIOD",              0x63 }, //  Keypad . Delete
    { "EUROPE_2",                0x64 }, //  Europe 2
    { "APP",                     0x65 }, //  App
    { "POWER",                   0x66 }, //  Keyboard Power
    { "PAD_EQUALS",              0x67 }, //  Keypad =
    { "F13",                     0x68 }, //  F13
    { "F14",                     0x69 }, //  F14
    { "F15",                     0x6A }, //  F15
    { "F16",                     0x6B }, //  F16
    { "F17",                     0x6C }, //  F17
    { "F18",                     0x6D }, //  F18
    { "F19",                     0x6E }, //  F19
    { "F20",                     0x6F }, //  F20
    { "F21",                     0x70 }, //  F21
    { "F22",                     0x71 }, //  F22
    { "F23",                     0x72 }, //  F23
    { "F24",                     0x73 }, //  F24
    { "EXECUTE",                 0x74 }, //  Keyboard Execute
    { "HELP",                    0x75 }, //  Keyboard Help
    { "MENU",                    0x76 }, //  Keyboard Menu
    { "SELECT",                  0x77 }, //  Keyboard Select
    { "STOP",                    0x78 }, //  Keyboard Stop
    { "AGAIN",                   0x79 }, //  Keyboard Again
    { "UNDO",                    0x7A }, //  Keyboard Undo
    { "CUT",                     0x7B }, //  Keyboard Cut
    { "COPY",                    0x7C }, //  Keyboard Copy
    { "PASTE",                   0x7D }, //  Keyboard Paste
    { "FIND",                    0x7E }, //  Keyboard Find
    { "MUTE",                    0x7F }, //  Keyboard Mute
    { "VOLUME_UP",               0x80 }, //  Keyboard Volume Up
    { "VOLUME_DOWN",             0x81 }, //  Keyboard Volume Dn
    { "LOCKING_CAPS_LOCK",       0x82 }, //  Keyboard Locking Caps Lock
    { "LOCKING_NUM_LOCK",        0x83 }, //  Keyboard Locking Num Lock
    { "LOCKING_SCROLL_LOCK",     0x84 }, //  Keyboard Locking Scroll Lock
    { "PAD_COMMA",               0x85 }, //  Keypad comma (Brazilian Keypad .)
    { "EQUAL_SIGN",              0x86 }, //  Keyboard Equal Sign
    { "INTERNATIONAL_1",         0x87 }, //  Keyboard Int'l 1 (Ro)
    { "INTERNATIONAL_2",         0x88 }, //  Keyboard Intl'2 (Katakana/Hiragana)
    { "INTERNATIONAL_3",         0x89 }, //  Keyboard Int'l 2 (Yen)
    { "INTERNATIONAL_4",         0x8A }, //  Keyboard Int'l 4 (Henkan)
    { "INTERNATIONAL_5",         0x8B }, //  Keyboard Int'l 5 (Muhenkan)
    { "INTERNATIONAL_6",         0x8C }, //  Keyboard Int'l 6 (PC9800 Keypad comma)
    { "INTERNATIONAL_7",         0x8D }, //  Keyboard Int'l 7
    { "INTERNATIONAL_8",         0x8E }, //  Keyboard Int'l 8
    { "INTERNATIONAL_9",         0x8F }, //  Keyboard Int'l 9
    { "LANG_1",                  0x90 }, //  Keyboard Lang 1 (Hanguel/English)
    { "LANG_2",                  0x91 }, //  Keyboard Lang 2 (Hanja)
    { "LANG_3",                  0x92 }, //  Keyboard Lang 3 (Katakana)
    { "LANG_4",                  0x93 }, //  Keyboard Lang 4 (Hiragana)
    { "LANG_5",                  0x94 }, //  Keyboard Lang 5 (Zenkaku/Hankaku)
    { "LANG_6",                  0x95 }, //  Keyboard Lang 6
    { "LANG_7",                  0x96 }, //  Keyboard Lang 7
    { "LANG_8",                  0x97 }, //  Keyboard Lang 8
    { "LANG_9",                  0x98 }, //  Keyboard Lang 9
    { "ALTERNATE_ERASE",         0x99 }, //  Keyboard Alternate Erase
    { "SYSREQ_ATTN",             0x9A }, //  Keyboard SysReq/Attention
    { "CANCEL",                  0x9B }, //  Keyboard Cancel
    { "CLEAR",                   0x9C }, //  Keyboard Clear
    { "PRIOR",                   0x9D }, //  Keyboard Prior
    { "RETURN",                  0x9E }, //  Keyboard Return
    { "SEPARATOR",               0x9F }, //  Keyboard Separator
    { "OUT",                     0xA0 }, //  Keyboard Out
    { "OPER",                    0xA1 }, //  Keyboard Oper
    { "CLEAR_AGAIN",             0xA2 }, //  Keyboard Clear/Again
    { "CRSEL_PROPS",             0xA3 }, //  Keyboard CrSel/Props
    { "EXSEL",                   0xA4 }, //  Keyboard ExSel
    { "SYSTEM_POWER",            0xA8 }, //  System Power
    { "SYSTEM_SLEEP",            0xA9 }, //  System Sleep
    { "SYSTEM_WAKE",             0xAA }, //  System Wake
	{ "AUX1",                    0xAB }, //  Auxiliary key 1
	{ "AUX2",                    0xAC }, //  Auxiliary key 2
	{ "AUX3",                    0xAD }, //  Auxiliary key 3
	{ "AUX4",                    0xAE }, //  Auxiliary key 4
	{ "AUX5",                    0xAF }, //  Auxiliary key 5
	//{ "EXTRA_UNUSED_1",          0xB0 }, //  extra
	{ "EXTRA_LALT",              0xB1 }, //  AT-F extra pad lhs of space
	{ "EXTRA_PAD_PLUS",          0xB2 }, //  Term extra pad bottom of keypad +
	{ "EXTRA_RALT",              0xB3 }, //  AT-F extra pad rhs of space
	{ "EXTRA_EUROPE_2",          0xB4 }, //  AT-F extra pad lhs of enter
	{ "EXTRA_BACKSLASH",         0xB5 }, //  AT-F extra pad top of enter
	{ "EXTRA_INSERT",            0xB6 }, //  AT-F extra pad lhs of Insert
	{ "EXTRA_F1",                0xB7 }, //  Term F1
	{ "EXTRA_F2",                0xB8 }, //  Term F2
	{ "EXTRA_F3",                0xB9 }, //  Term F3
	{ "EXTRA_F4",                0xBA }, //  Term F4
	{ "EXTRA_F5",                0xBB }, //  Term F5
	{ "EXTRA_F6",                0xBC }, //  Term F6
	{ "EXTRA_F7",                0xBD }, //  Term F7
	{ "EXTRA_F8",                0xBE }, //  Term F8
	{ "EXTRA_F9",                0xBF }, //  Term F9
	{ "EXTRA_F10",               0xC0 }, //  Term F10
	//{ "EXTRA_UNUSED_2",          0xC1 }, //  extra
	{ "EXTRA_SYSRQ",             0xC2 }, //  Sys Req (AT 84-key)
    { "FAKE_01",                 0xB0 }, //  extra
    { "FAKE_02",                 0xB1 }, //  AT-F extra pad lhs of space
    { "FAKE_03",                 0xB2 }, //  Term extra pad bottom of keypad +
    { "FAKE_04",                 0xB3 }, //  AT-F extra pad rhs of space
    { "FAKE_05",                 0xB4 }, //  AT-F extra pad lhs of enter
    { "FAKE_06",                 0xB5 }, //  AT-F extra pad top of enter
    { "FAKE_07",                 0xB6 }, //  AT-F extra pad lhs of Insert
    { "FAKE_08",                 0xB7 }, //  Term F1
    { "FAKE_09",                 0xB8 }, //  Term F2
    { "FAKE_10",                 0xB9 }, //  Term F3
    { "FAKE_11",                 0xBA }, //  Term F4
    { "FAKE_12",                 0xBB }, //  Term F5
    { "FAKE_13",                 0xBC }, //  Term F6
    { "FAKE_14",                 0xBD }, //  Term F7
    { "FAKE_15",                 0xBE }, //  Term F8
    { "FAKE_16",                 0xBF }, //  Term F9
    { "FAKE_17",                 0xC0 }, //  Term F10
    { "FAKE_18",                 0xC1 }, //  extra
    { "FAKE_19",                 0xC2 }, //  Sys Req (AT 84-key)
    { "FN1",                     0xD0 }, //  Function layer key 1
    { "FN2",                     0xD1 }, //  Function layer key 2
    { "FN3",                     0xD2 }, //  Function layer key 3
    { "FN4",                     0xD3 }, //  Function layer key 4
    { "FN5",                     0xD4 }, //  Function layer key 5
    { "FN6",                     0xD5 }, //  Function layer key 6
    { "FN7",                     0xD6 }, //  Function layer key 7
    { "FN8",                     0xD7 }, //  Function layer key 8
    { "SELECT_0",                0xD8 }, //  Select reset
    { "SELECT_1",                0xD9 }, //  Select 1
    { "SELECT_2",                0xDA }, //  Select 2
    { "SELECT_3",                0xDB }, //  Select 3
    { "SELECT_4",                0xDC }, //  Select 4
    { "SELECT_5",                0xDD }, //  Select 5
    { "SELECT_6",                0xDE }, //  Select 6
    { "SELECT_7",                0xDF }, //  Select 7
    { "LCTRL",                   0xE0 }, //  Left Control
    { "LSHIFT",                  0xE1 }, //  Left Shift
    { "LALT",                    0xE2 }, //  Left Alt
    { "LGUI",                    0xE3 }, //  Left GUI
    { "RCTRL",                   0xE4 }, //  Right Control
    { "RSHIFT",                  0xE5 }, //  Right Shift
    { "RALT",                    0xE6 }, //  Right Alt
    { "RGUI",                    0xE7 }, //  Right GUI
    { "MEDIA_NEXT_TRACK",        0xE8 }, //  Scan Next Track
    { "MEDIA_PREV_TRACK",        0xE9 }, //  Scan Previous Track
    { "MEDIA_STOP",              0xEA }, //  Stop
    { "MEDIA_PLAY_PAUSE",        0xEB }, //  Play/ Pause
    { "MEDIA_MUTE",              0xEC }, //  Mute
    { "MEDIA_BASS_BOOST",        0xED }, //  Bass Boost
    { "MEDIA_LOUDNESS",          0xEE }, //  Loudness
    { "MEDIA_VOLUME_UP",         0xEF }, //  Volume Up
    { "MEDIA_VOLUME_DOWN",       0xF0 }, //  Volume Down
    { "MEDIA_BASS_UP",           0xF1 }, //  Bass Up
    { "MEDIA_BASS_DOWN",         0xF2 }, //  Bass Down
    { "MEDIA_TREBLE_UP",         0xF3 }, //  Treble Up
    { "MEDIA_TREBLE_DOWN",       0xF4 }, //  Treble Down
    { "MEDIA_MEDIA_SELECT",      0xF5 }, //  Media Select
    { "MEDIA_MAIL",              0xF6 }, //  Mail
    { "MEDIA_CALCULATOR",        0xF7 }, //  Calculator
    { "MEDIA_MY_COMPUTER",       0xF8 }, //  My Computer
    { "MEDIA_WWW_SEARCH",        0xF9 }, //  WWW Search
    { "MEDIA_WWW_HOME",          0xFA }, //  WWW Home
    { "MEDIA_WWW_BACK",          0xFB }, //  WWW Back
    { "MEDIA_WWW_FORWARD",       0xFC }, //  WWW Forward
    { "MEDIA_WWW_STOP",          0xFD }, //  WWW Stop
    { "MEDIA_WWW_REFRESH",       0xFE }, //  WWW Refresh
    { "MEDIA_WWW_FAVORITES",     0xFF }, //  WWW Favorites
};

const char* lookup_hid_token(int value)
{
	int n = sizeof(hid_token_list) / sizeof(token_t);
	for ( int i = 0; i < n; ++i ) {
		if ( hid_token_list[i].value == value ) {
			return hid_token_list[i].token;
		}
	}
	return "INVALID";
}

int lookup_hid_token(const char* s)
{
	int n = sizeof(hid_token_list) / sizeof(token_t);
	for ( int i = 0; i < n; ++i ) {
		if ( 0 == stricmp(hid_token_list[i].token, s) ) {
			return hid_token_list[i].value;
		}
	}
	return INVALID_NUMBER;
}

int lookup_meta_token(const char* s)
{
	int n = sizeof(meta_token_list) / sizeof(token_t);
	for ( int i = 0; i < n; ++i ) {
		if ( 0 == stricmp(meta_token_list[i].token, s) ) {
			return meta_token_list[i].value;
		}
	}
	return INVALID_NUMBER;
}
