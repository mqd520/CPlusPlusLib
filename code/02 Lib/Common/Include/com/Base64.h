#pragma once

#include <string>
using namespace std;


extern int Base64encode(char *encoded, const char *string, int len);
extern int Base64decode(char *bufplain, const char *bufcoded);

extern int Base64encode_len(int len);
extern int Base64decode_len(const char *bufcoded);

string base64_encode(unsigned char const*, unsigned int len);
string base64_decode(string const& s);