#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define INVALID_NUMBER -9999

struct token_t
{
	const char*	token;
	int			value;
};

#define BLOCK_NONE -1
#define BLOCK_LAYERDEF 0
#define BLOCK_REMAP 1
#define BLOCK_MACRO 2

#ifndef _MSC_VER
#define strnicmp strncasecmp
#define stricmp strcasecmp
#endif

#endif // __GLOBAL_H__
