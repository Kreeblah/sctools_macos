#ifndef __HID_TOKENS_H__
#define __HID_TOKENS_H__

int lookup_hid_token(const char* s);
const char* lookup_hid_token(int value);
int lookup_meta_token(const char* s);

inline bool is_meta_handed(int meta)
{
	return !(meta & (meta >> 4));
}

#endif // __HID_TOKENS_H__
