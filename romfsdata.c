#include <picoos.h>
#include <picoos-u.h>

#ifndef unix
// test.py
static const unsigned char file_1[] = {

0x63,0x6c,0x61,0x73,0x73,0x20,0x54,0x65,0x73,0x74,0x3a,0x0a,0x20,0x20,0x64,
0x65,0x66,0x20,0x5f,0x5f,0x69,0x6e,0x69,0x74,0x5f,0x5f,0x28,0x73,0x65,0x6c,
0x66,0x29,0x3a,0x0a,0x20,0x20,0x20,0x20,0x73,0x65,0x6c,0x66,0x2e,0x76,0x61,
0x6c,0x20,0x3d,0x20,0x31,0x0a,0x0a,0x20,0x20,0x64,0x65,0x66,0x20,0x61,0x64,
0x64,0x28,0x73,0x65,0x6c,0x66,0x2c,0x20,0x76,0x61,0x6c,0x29,0x3a,0x0a,0x20,
0x20,0x20,0x20,0x73,0x65,0x6c,0x66,0x2e,0x76,0x61,0x6c,0x20,0x3d,0x20,0x73,
0x65,0x6c,0x66,0x2e,0x76,0x61,0x6c,0x20,0x2b,0x20,0x76,0x61,0x6c,0x0a,0x20,
0x20,0x20,0x20,0x70,0x72,0x69,0x6e,0x74,0x28,0x22,0x56,0x61,0x6c,0x75,0x65,
0x20,0x6e,0x6f,0x77,0x22,0x2c,0x20,0x73,0x65,0x6c,0x66,0x2e,0x76,0x61,0x6c,
0x29,0x0a
};


const UosRomFile uosRomFiles[] = {
{ "test.py",  file_1, sizeof(file_1) },
{ "__init__.py",  "", 0 },
{ NULL,  NULL, 0 }
};
#endif
