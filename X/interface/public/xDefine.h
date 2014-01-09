#pragma once

typedef struct ObjectInfo
{
    GUID* guid;
    char* strPath;
    char* progid;
}OBJINFO, *LPOBJINFO;

#define STR(x) #x
#define STR2(y) STR(\x##y)

#define DEFGUID(g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12,g13,g14,g15,g16) \
    STR2(g4) STR2(g3) STR2(g2) STR2(g1) STR2(g6) STR2(g5) STR2(g8) STR2(g7) STR2(g9) STR2(g10) STR2(g11) STR2(g12) STR2(g13) STR2(g14) STR2(g15) STR2(g16)

#define DEFITEM(iid, clsid, filename, interface) \
    {(GUID*)iid clsid, filename, interface},