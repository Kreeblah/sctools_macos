#include "hid_tokens.h"
#include "global.h"
#include <string.h>

token_t meta_token_list[] =
{
	{ "LCTRL",               0x01 }, //  Left Control
    { "MACOS_LCONTROL",      0x01 }, //  macOS Left Control
	{ "LSHIFT",              0x02 }, //  Left Shift
    { "MACOS_LSHIFT",        0x02 }, //  macOS Left Shift
	{ "LALT",                0x04 }, //  Left Alt
    { "MACOS_LOPTION",       0x04 }, //  macOS Left Alt/Option
	{ "LGUI",                0x08 }, //  Left GUI
    { "MACOS_LCOMMAND",      0x08 }, //  macOS Left Command

	{ "RCTRL",               0x10 }, //  Right Control
    { "MACOS_RCONTROL",      0x10 }, //  macOS Right Control
	{ "RSHIFT",              0x20 }, //  Right Shift
    { "MACOS_RSHIFT",        0x20 }, //  macOS Right Shift
	{ "RALT",                0x40 }, //  Right Alt
    { "MACOS_ROPTION",       0x40 }, //  macOS Right Alt/Option
	{ "RGUI",                0x80 }, //  Right GUI
    { "MACOS_RCOMMAND",      0x80 }, //  macOS Right Command

	{ "CTRL",                0x11 }, //  Either/Both Control
    { "MACOS_CONTROL",       0x11 }, //  Either/Both macOS Control
	{ "SHIFT",               0x22 }, //  Either/Both Shift
    { "MACOS_SHFIT",         0x22 }, //  Either/Both macOS Shift
	{ "ALT",                 0x44 }, //  Either/Both Alt
    { "MACOS_OPTION",        0x44 }, //  Either/Both macOS Alt/Option
	{ "GUI",                 0x88 }, //  Either/Both GUI
    { "MACOS_COMMAND",       0x88 }, //  Either/Both macOS Command

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
    { "MACOS_VIEW_DESKTOP",      0x44 }, //  macOS View Desktop
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
    { "MACOS_BRIGHTNESS_DOWN",   0x69 }, //  macOS Screen Brightness Down
    { "F15",                     0x6A }, //  F15
    { "MACOS_BRIGHTNESS_UP",     0x6A }, //  macOS Screen Brightness Up
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
    { "MACOS_VOLUME_MUTE",       0x7F }, //  macOS Volume Mute
    { "VOLUME_UP",               0x80 }, //  Keyboard Volume Up
    { "MACOS_VOLUME_UP",         0x80 }, //  macOS Volume Up
    { "VOLUME_DOWN",             0x81 }, //  Keyboard Volume Dn
    { "MACOS_VOLUME_DOWN",       0x81 }, //  macOS Volume Down
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
    { "MACOS_POWER",             0xA8 }, //  macOS System Power
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
    { "MACOS_LCONTROL",          0xE0 }, //  macOS Left Control
    { "LSHIFT",                  0xE1 }, //  Left Shift
    { "MACOS_LSHIFT",            0xE1 }, //  macOS Left Shift
    { "LALT",                    0xE2 }, //  Left Alt
    { "MACOS_LOPTION",           0xE2 }, //  macOS Left Alt/Option
    { "LGUI",                    0xE3 }, //  Left GUI
    { "MACOS_LCOMMAND",          0xE3 }, //  macOS Left Command
    { "RCTRL",                   0xE4 }, //  Right Control
    { "MACOS_RCONTROL",          0xE4 }, //  macOS Right Control
    { "RSHIFT",                  0xE5 }, //  Right Shift
    { "MACOS_RSHIFT",            0xE5 }, //  macOS Right Shift
    { "RALT",                    0xE6 }, //  Right Alt
    { "MACOS_ROPTION",           0xE6 }, //  macOS Right Alt/Option
    { "RGUI",                    0xE7 }, //  Right GUI
    { "MACOS_RCOMMAND",          0xE8 }, //  macOS Right Command
    { "MEDIA_NEXT_TRACK",        0xE8 }, //  Scan Next Track
    { "MACOS_NEXT_TRACK",        0xE8 }, //  macOS Next Track
    { "MEDIA_PREV_TRACK",        0xE9 }, //  Scan Previous Track
    { "MACOS_PREV_TRACK",        0xE9 }, //  macOS Previous Track
    { "MEDIA_STOP",              0xEA }, //  Stop
    { "MEDIA_PLAY_PAUSE",        0xEB }, //  Play/Pause
    { "MACOS_PLAY_PAUSE",        0xEB }, //  macOS Play/Pause
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
    { "HID_CODE_00",             0x00 }, //  Raw HID code for 0x00
    { "HID_CODE_01",             0x01 }, //  Raw HID code for 0x01
    { "HID_CODE_02",             0x02 }, //  Raw HID code for 0x02
    { "HID_CODE_03",             0x03 }, //  Raw HID code for 0x03
    { "HID_CODE_04",             0x04 }, //  Raw HID code for 0x04
    { "HID_CODE_05",             0x05 }, //  Raw HID code for 0x05
    { "HID_CODE_06",             0x06 }, //  Raw HID code for 0x06
    { "HID_CODE_07",             0x07 }, //  Raw HID code for 0x07
    { "HID_CODE_08",             0x08 }, //  Raw HID code for 0x08
    { "HID_CODE_09",             0x09 }, //  Raw HID code for 0x09
    { "HID_CODE_0A",             0x0A }, //  Raw HID code for 0x0A
    { "HID_CODE_0B",             0x0B }, //  Raw HID code for 0x0B
    { "HID_CODE_0C",             0x0C }, //  Raw HID code for 0x0C
    { "HID_CODE_0D",             0x0D }, //  Raw HID code for 0x0D
    { "HID_CODE_0E",             0x0E }, //  Raw HID code for 0x0E
    { "HID_CODE_0F",             0x0F }, //  Raw HID code for 0x0F
    { "HID_CODE_10",             0x10 }, //  Raw HID code for 0x10
    { "HID_CODE_11",             0x11 }, //  Raw HID code for 0x11
    { "HID_CODE_12",             0x12 }, //  Raw HID code for 0x12
    { "HID_CODE_13",             0x13 }, //  Raw HID code for 0x13
    { "HID_CODE_14",             0x14 }, //  Raw HID code for 0x14
    { "HID_CODE_15",             0x15 }, //  Raw HID code for 0x15
    { "HID_CODE_16",             0x16 }, //  Raw HID code for 0x16
    { "HID_CODE_17",             0x17 }, //  Raw HID code for 0x17
    { "HID_CODE_18",             0x18 }, //  Raw HID code for 0x18
    { "HID_CODE_19",             0x19 }, //  Raw HID code for 0x19
    { "HID_CODE_1A",             0x1A }, //  Raw HID code for 0x1A
    { "HID_CODE_1B",             0x1B }, //  Raw HID code for 0x1B
    { "HID_CODE_1C",             0x1C }, //  Raw HID code for 0x1C
    { "HID_CODE_1D",             0x1D }, //  Raw HID code for 0x1D
    { "HID_CODE_1E",             0x1E }, //  Raw HID code for 0x1E
    { "HID_CODE_1F",             0x1F }, //  Raw HID code for 0x1F
    { "HID_CODE_20",             0x20 }, //  Raw HID code for 0x20
    { "HID_CODE_21",             0x21 }, //  Raw HID code for 0x21
    { "HID_CODE_22",             0x22 }, //  Raw HID code for 0x22
    { "HID_CODE_23",             0x23 }, //  Raw HID code for 0x23
    { "HID_CODE_24",             0x24 }, //  Raw HID code for 0x24
    { "HID_CODE_25",             0x25 }, //  Raw HID code for 0x25
    { "HID_CODE_26",             0x26 }, //  Raw HID code for 0x26
    { "HID_CODE_27",             0x27 }, //  Raw HID code for 0x27
    { "HID_CODE_28",             0x28 }, //  Raw HID code for 0x28
    { "HID_CODE_29",             0x29 }, //  Raw HID code for 0x29
    { "HID_CODE_2A",             0x2A }, //  Raw HID code for 0x2A
    { "HID_CODE_2B",             0x2B }, //  Raw HID code for 0x2B
    { "HID_CODE_2C",             0x2C }, //  Raw HID code for 0x2C
    { "HID_CODE_2D",             0x2D }, //  Raw HID code for 0x2D
    { "HID_CODE_2E",             0x2E }, //  Raw HID code for 0x2E
    { "HID_CODE_2F",             0x2F }, //  Raw HID code for 0x2F
    { "HID_CODE_30",             0x30 }, //  Raw HID code for 0x30
    { "HID_CODE_31",             0x31 }, //  Raw HID code for 0x31
    { "HID_CODE_32",             0x32 }, //  Raw HID code for 0x32
    { "HID_CODE_33",             0x33 }, //  Raw HID code for 0x33
    { "HID_CODE_34",             0x34 }, //  Raw HID code for 0x34
    { "HID_CODE_35",             0x35 }, //  Raw HID code for 0x35
    { "HID_CODE_36",             0x36 }, //  Raw HID code for 0x36
    { "HID_CODE_37",             0x37 }, //  Raw HID code for 0x37
    { "HID_CODE_38",             0x38 }, //  Raw HID code for 0x38
    { "HID_CODE_39",             0x39 }, //  Raw HID code for 0x39
    { "HID_CODE_3A",             0x3A }, //  Raw HID code for 0x3A
    { "HID_CODE_3B",             0x3B }, //  Raw HID code for 0x3B
    { "HID_CODE_3C",             0x3C }, //  Raw HID code for 0x3C
    { "HID_CODE_3D",             0x3D }, //  Raw HID code for 0x3D
    { "HID_CODE_3E",             0x3E }, //  Raw HID code for 0x3E
    { "HID_CODE_3F",             0x3F }, //  Raw HID code for 0x3F
    { "HID_CODE_40",             0x40 }, //  Raw HID code for 0x40
    { "HID_CODE_41",             0x41 }, //  Raw HID code for 0x41
    { "HID_CODE_42",             0x42 }, //  Raw HID code for 0x42
    { "HID_CODE_43",             0x43 }, //  Raw HID code for 0x43
    { "HID_CODE_44",             0x44 }, //  Raw HID code for 0x44
    { "HID_CODE_45",             0x45 }, //  Raw HID code for 0x45
    { "HID_CODE_46",             0x46 }, //  Raw HID code for 0x46
    { "HID_CODE_47",             0x47 }, //  Raw HID code for 0x47
    { "HID_CODE_48",             0x48 }, //  Raw HID code for 0x48
    { "HID_CODE_49",             0x49 }, //  Raw HID code for 0x49
    { "HID_CODE_4A",             0x4A }, //  Raw HID code for 0x4A
    { "HID_CODE_4B",             0x4B }, //  Raw HID code for 0x4B
    { "HID_CODE_4C",             0x4C }, //  Raw HID code for 0x4C
    { "HID_CODE_4D",             0x4D }, //  Raw HID code for 0x4D
    { "HID_CODE_4E",             0x4E }, //  Raw HID code for 0x4E
    { "HID_CODE_4F",             0x4F }, //  Raw HID code for 0x4F
    { "HID_CODE_50",             0x50 }, //  Raw HID code for 0x50
    { "HID_CODE_51",             0x51 }, //  Raw HID code for 0x51
    { "HID_CODE_52",             0x52 }, //  Raw HID code for 0x52
    { "HID_CODE_53",             0x53 }, //  Raw HID code for 0x53
    { "HID_CODE_54",             0x54 }, //  Raw HID code for 0x54
    { "HID_CODE_55",             0x55 }, //  Raw HID code for 0x55
    { "HID_CODE_56",             0x56 }, //  Raw HID code for 0x56
    { "HID_CODE_57",             0x57 }, //  Raw HID code for 0x57
    { "HID_CODE_58",             0x58 }, //  Raw HID code for 0x58
    { "HID_CODE_59",             0x59 }, //  Raw HID code for 0x59
    { "HID_CODE_5A",             0x5A }, //  Raw HID code for 0x5A
    { "HID_CODE_5B",             0x5B }, //  Raw HID code for 0x5B
    { "HID_CODE_5C",             0x5C }, //  Raw HID code for 0x5C
    { "HID_CODE_5D",             0x5D }, //  Raw HID code for 0x5D
    { "HID_CODE_5E",             0x5E }, //  Raw HID code for 0x5E
    { "HID_CODE_5F",             0x5F }, //  Raw HID code for 0x5F
    { "HID_CODE_60",             0x60 }, //  Raw HID code for 0x60
    { "HID_CODE_61",             0x61 }, //  Raw HID code for 0x61
    { "HID_CODE_62",             0x62 }, //  Raw HID code for 0x62
    { "HID_CODE_63",             0x63 }, //  Raw HID code for 0x63
    { "HID_CODE_64",             0x64 }, //  Raw HID code for 0x64
    { "HID_CODE_65",             0x65 }, //  Raw HID code for 0x65
    { "HID_CODE_66",             0x66 }, //  Raw HID code for 0x66
    { "HID_CODE_67",             0x67 }, //  Raw HID code for 0x67
    { "HID_CODE_68",             0x68 }, //  Raw HID code for 0x68
    { "HID_CODE_69",             0x69 }, //  Raw HID code for 0x69
    { "HID_CODE_6A",             0x6A }, //  Raw HID code for 0x6A
    { "HID_CODE_6B",             0x6B }, //  Raw HID code for 0x6B
    { "HID_CODE_6C",             0x6C }, //  Raw HID code for 0x6C
    { "HID_CODE_6D",             0x6D }, //  Raw HID code for 0x6D
    { "HID_CODE_6E",             0x6E }, //  Raw HID code for 0x6E
    { "HID_CODE_6F",             0x6F }, //  Raw HID code for 0x6F
    { "HID_CODE_70",             0x70 }, //  Raw HID code for 0x70
    { "HID_CODE_71",             0x71 }, //  Raw HID code for 0x71
    { "HID_CODE_72",             0x72 }, //  Raw HID code for 0x72
    { "HID_CODE_73",             0x73 }, //  Raw HID code for 0x73
    { "HID_CODE_74",             0x74 }, //  Raw HID code for 0x74
    { "HID_CODE_75",             0x75 }, //  Raw HID code for 0x75
    { "HID_CODE_76",             0x76 }, //  Raw HID code for 0x76
    { "HID_CODE_77",             0x77 }, //  Raw HID code for 0x77
    { "HID_CODE_78",             0x78 }, //  Raw HID code for 0x78
    { "HID_CODE_79",             0x79 }, //  Raw HID code for 0x79
    { "HID_CODE_7A",             0x7A }, //  Raw HID code for 0x7A
    { "HID_CODE_7B",             0x7B }, //  Raw HID code for 0x7B
    { "HID_CODE_7C",             0x7C }, //  Raw HID code for 0x7C
    { "HID_CODE_7D",             0x7D }, //  Raw HID code for 0x7D
    { "HID_CODE_7E",             0x7E }, //  Raw HID code for 0x7E
    { "HID_CODE_7F",             0x7F }, //  Raw HID code for 0x7F
    { "HID_CODE_80",             0x80 }, //  Raw HID code for 0x80
    { "HID_CODE_81",             0x81 }, //  Raw HID code for 0x81
    { "HID_CODE_82",             0x82 }, //  Raw HID code for 0x82
    { "HID_CODE_83",             0x83 }, //  Raw HID code for 0x83
    { "HID_CODE_84",             0x84 }, //  Raw HID code for 0x84
    { "HID_CODE_85",             0x85 }, //  Raw HID code for 0x85
    { "HID_CODE_86",             0x86 }, //  Raw HID code for 0x86
    { "HID_CODE_87",             0x87 }, //  Raw HID code for 0x87
    { "HID_CODE_88",             0x88 }, //  Raw HID code for 0x88
    { "HID_CODE_89",             0x89 }, //  Raw HID code for 0x89
    { "HID_CODE_8A",             0x8A }, //  Raw HID code for 0x8A
    { "HID_CODE_8B",             0x8B }, //  Raw HID code for 0x8B
    { "HID_CODE_8C",             0x8C }, //  Raw HID code for 0x8C
    { "HID_CODE_8D",             0x8D }, //  Raw HID code for 0x8D
    { "HID_CODE_8E",             0x8E }, //  Raw HID code for 0x8E
    { "HID_CODE_8F",             0x8F }, //  Raw HID code for 0x8F
    { "HID_CODE_90",             0x90 }, //  Raw HID code for 0x90
    { "HID_CODE_91",             0x91 }, //  Raw HID code for 0x91
    { "HID_CODE_92",             0x92 }, //  Raw HID code for 0x92
    { "HID_CODE_93",             0x93 }, //  Raw HID code for 0x93
    { "HID_CODE_94",             0x94 }, //  Raw HID code for 0x94
    { "HID_CODE_95",             0x95 }, //  Raw HID code for 0x95
    { "HID_CODE_96",             0x96 }, //  Raw HID code for 0x96
    { "HID_CODE_97",             0x97 }, //  Raw HID code for 0x97
    { "HID_CODE_98",             0x98 }, //  Raw HID code for 0x98
    { "HID_CODE_99",             0x99 }, //  Raw HID code for 0x99
    { "HID_CODE_9A",             0x9A }, //  Raw HID code for 0x9A
    { "HID_CODE_9B",             0x9B }, //  Raw HID code for 0x9B
    { "HID_CODE_9C",             0x9C }, //  Raw HID code for 0x9C
    { "HID_CODE_9D",             0x9D }, //  Raw HID code for 0x9D
    { "HID_CODE_9E",             0x9E }, //  Raw HID code for 0x9E
    { "HID_CODE_9F",             0x9F }, //  Raw HID code for 0x9F
    { "HID_CODE_A0",             0xA0 }, //  Raw HID code for 0xA0
    { "HID_CODE_A1",             0xA1 }, //  Raw HID code for 0xA1
    { "HID_CODE_A2",             0xA2 }, //  Raw HID code for 0xA2
    { "HID_CODE_A3",             0xA3 }, //  Raw HID code for 0xA3
    { "HID_CODE_A4",             0xA4 }, //  Raw HID code for 0xA4
    { "HID_CODE_A5",             0xA5 }, //  Raw HID code for 0xA5
    { "HID_CODE_A6",             0xA6 }, //  Raw HID code for 0xA6
    { "HID_CODE_A7",             0xA7 }, //  Raw HID code for 0xA7
    { "HID_CODE_A8",             0xA8 }, //  Raw HID code for 0xA8
    { "HID_CODE_A9",             0xA9 }, //  Raw HID code for 0xA9
    { "HID_CODE_AA",             0xAA }, //  Raw HID code for 0xAA
    { "HID_CODE_AB",             0xAB }, //  Raw HID code for 0xAB
    { "HID_CODE_AC",             0xAC }, //  Raw HID code for 0xAC
    { "HID_CODE_AD",             0xAD }, //  Raw HID code for 0xAD
    { "HID_CODE_AE",             0xAE }, //  Raw HID code for 0xAE
    { "HID_CODE_AF",             0xAF }, //  Raw HID code for 0xAF
    { "HID_CODE_B0",             0xB0 }, //  Raw HID code for 0xB0
    { "HID_CODE_B1",             0xB1 }, //  Raw HID code for 0xB1
    { "HID_CODE_B2",             0xB2 }, //  Raw HID code for 0xB2
    { "HID_CODE_B3",             0xB3 }, //  Raw HID code for 0xB3
    { "HID_CODE_B4",             0xB4 }, //  Raw HID code for 0xB4
    { "HID_CODE_B5",             0xB5 }, //  Raw HID code for 0xB5
    { "HID_CODE_B6",             0xB6 }, //  Raw HID code for 0xB6
    { "HID_CODE_B7",             0xB7 }, //  Raw HID code for 0xB7
    { "HID_CODE_B8",             0xB8 }, //  Raw HID code for 0xB8
    { "HID_CODE_B9",             0xB9 }, //  Raw HID code for 0xB9
    { "HID_CODE_BA",             0xBA }, //  Raw HID code for 0xBA
    { "HID_CODE_BB",             0xBB }, //  Raw HID code for 0xBB
    { "HID_CODE_BC",             0xBC }, //  Raw HID code for 0xBC
    { "HID_CODE_BD",             0xBD }, //  Raw HID code for 0xBD
    { "HID_CODE_BE",             0xBE }, //  Raw HID code for 0xBE
    { "HID_CODE_BF",             0xBF }, //  Raw HID code for 0xBF
    { "HID_CODE_C0",             0xC0 }, //  Raw HID code for 0xC0
    { "HID_CODE_C1",             0xC1 }, //  Raw HID code for 0xC1
    { "HID_CODE_C2",             0xC2 }, //  Raw HID code for 0xC2
    { "HID_CODE_C3",             0xC3 }, //  Raw HID code for 0xC3
    { "HID_CODE_C4",             0xC4 }, //  Raw HID code for 0xC4
    { "HID_CODE_C5",             0xC5 }, //  Raw HID code for 0xC5
    { "HID_CODE_C6",             0xC6 }, //  Raw HID code for 0xC6
    { "HID_CODE_C7",             0xC7 }, //  Raw HID code for 0xC7
    { "HID_CODE_C8",             0xC8 }, //  Raw HID code for 0xC8
    { "HID_CODE_C9",             0xC9 }, //  Raw HID code for 0xC9
    { "HID_CODE_CA",             0xCA }, //  Raw HID code for 0xCA
    { "HID_CODE_CB",             0xCB }, //  Raw HID code for 0xCB
    { "HID_CODE_CC",             0xCC }, //  Raw HID code for 0xCC
    { "HID_CODE_CD",             0xCD }, //  Raw HID code for 0xCD
    { "HID_CODE_CE",             0xCE }, //  Raw HID code for 0xCE
    { "HID_CODE_CF",             0xCF }, //  Raw HID code for 0xCF
    { "HID_CODE_D0",             0xD0 }, //  Raw HID code for 0xD0
    { "HID_CODE_D1",             0xD1 }, //  Raw HID code for 0xD1
    { "HID_CODE_D2",             0xD2 }, //  Raw HID code for 0xD2
    { "HID_CODE_D3",             0xD3 }, //  Raw HID code for 0xD3
    { "HID_CODE_D4",             0xD4 }, //  Raw HID code for 0xD4
    { "HID_CODE_D5",             0xD5 }, //  Raw HID code for 0xD5
    { "HID_CODE_D6",             0xD6 }, //  Raw HID code for 0xD6
    { "HID_CODE_D7",             0xD7 }, //  Raw HID code for 0xD7
    { "HID_CODE_D8",             0xD8 }, //  Raw HID code for 0xD8
    { "HID_CODE_D9",             0xD9 }, //  Raw HID code for 0xD9
    { "HID_CODE_DA",             0xDA }, //  Raw HID code for 0xDA
    { "HID_CODE_DB",             0xDB }, //  Raw HID code for 0xDB
    { "HID_CODE_DC",             0xDC }, //  Raw HID code for 0xDC
    { "HID_CODE_DD",             0xDD }, //  Raw HID code for 0xDD
    { "HID_CODE_DE",             0xDE }, //  Raw HID code for 0xDE
    { "HID_CODE_DF",             0xDF }, //  Raw HID code for 0xDF
    { "HID_CODE_E0",             0xE0 }, //  Raw HID code for 0xE0
    { "HID_CODE_E1",             0xE1 }, //  Raw HID code for 0xE1
    { "HID_CODE_E2",             0xE2 }, //  Raw HID code for 0xE2
    { "HID_CODE_E3",             0xE3 }, //  Raw HID code for 0xE3
    { "HID_CODE_E4",             0xE4 }, //  Raw HID code for 0xE4
    { "HID_CODE_E5",             0xE5 }, //  Raw HID code for 0xE5
    { "HID_CODE_E6",             0xE6 }, //  Raw HID code for 0xE6
    { "HID_CODE_E7",             0xE7 }, //  Raw HID code for 0xE7
    { "HID_CODE_E8",             0xE8 }, //  Raw HID code for 0xE8
    { "HID_CODE_E9",             0xE9 }, //  Raw HID code for 0xE9
    { "HID_CODE_EA",             0xEA }, //  Raw HID code for 0xEA
    { "HID_CODE_EB",             0xEB }, //  Raw HID code for 0xEB
    { "HID_CODE_EC",             0xEC }, //  Raw HID code for 0xEC
    { "HID_CODE_ED",             0xED }, //  Raw HID code for 0xED
    { "HID_CODE_EE",             0xEE }, //  Raw HID code for 0xEE
    { "HID_CODE_EF",             0xEF }, //  Raw HID code for 0xEF
    { "HID_CODE_F0",             0xF0 }, //  Raw HID code for 0xF0
    { "HID_CODE_F1",             0xF1 }, //  Raw HID code for 0xF1
    { "HID_CODE_F2",             0xF2 }, //  Raw HID code for 0xF2
    { "HID_CODE_F3",             0xF3 }, //  Raw HID code for 0xF3
    { "HID_CODE_F4",             0xF4 }, //  Raw HID code for 0xF4
    { "HID_CODE_F5",             0xF5 }, //  Raw HID code for 0xF5
    { "HID_CODE_F6",             0xF6 }, //  Raw HID code for 0xF6
    { "HID_CODE_F7",             0xF7 }, //  Raw HID code for 0xF7
    { "HID_CODE_F8",             0xF8 }, //  Raw HID code for 0xF8
    { "HID_CODE_F9",             0xF9 }, //  Raw HID code for 0xF9
    { "HID_CODE_FA",             0xFA }, //  Raw HID code for 0xFA
    { "HID_CODE_FB",             0xFB }, //  Raw HID code for 0xFB
    { "HID_CODE_FC",             0xFC }, //  Raw HID code for 0xFC
    { "HID_CODE_FD",             0xFD }, //  Raw HID code for 0xFD
    { "HID_CODE_FE",             0xFE }, //  Raw HID code for 0xFE
    { "HID_CODE_FF",             0xFF }, //  Raw HID code for 0xFF
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
