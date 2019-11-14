#pragma once

#ifndef GBase64_h__
#define GBase64_h__

extern int Base64decode_len(const char *bufcoded);
extern int Base64decode(char *bufplain, const char *bufcoded);
extern int Base64encode_len(int len);
extern int Base64encode(char *encoded, const char *string, int len);

#endif // GBase64_h__
