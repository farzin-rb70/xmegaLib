// title: PersianReshaper.h
// by: Amir Soutehkeshan
// when: 2022-01-24 01:44:44
// If all you have is a hammer, everything looks like a nail.

#ifndef __PERSIANRESHAPER_H__
#define __PERSIANRESHAPER_H__
#include <string.h>
#include <stdint.h>
#include "WString.h"
//----------------------------------------------------------------------------
//#define DEBUG
#define LCDWidth lcdDriver.getDisplayWidth()
#define ALINE_CENTER(t) ((LCDWidth - (lcdDriver.getUTF8Width(t))) / 2)
#define ALINE_RIGHT(t) (LCDWidth - lcdDriver.getUTF8Width(t))
#define ALINE_LEFT 0
#define N_DISTINCT_CHARACTERS 91
#define IS_UNICODE(c) (((c)&0xc0) == 0xc0)
//----------------------------------------------------------------------------
struct prGlyph
{
  int AsciiCode;
  const char *codeGlyph;
  const char *isoGlyph;
  const char *iniGlyph;
  const char *midGlyph;
  const char *endGlyph;
};

const prGlyph prForms[] = {
    // Ascii Code, Code, Isolated, Initial, Medial, Final
    {193, "\u0621", "\uFE80", "\uFE80", "\uFE80", "\uFE80"}, // 1 HAMZA ء	[*]
    {194, "\u0622", "\uFE81", "\uFE81", "\uFE82", "\uFE82"}, // 2 ALEF_MADDA آ [*]
    {195, "\u0623", "\uFE83", "\uFE83", "\uFE84", "\uFE84"}, // 3 ALEF_HAMZA_ABOVE أ [*]
    {196, "\u0624", "\uFE85", "\uFE85", "\uFE86", "\uFE86"}, // 4 WAW_HAMZA ؤ [*]
    {197, "\u0625", "\uFE87", "\uFE87", "\uFE88", "\uFE88"}, // 5 ALEF_HAMZA_BELOW إ [*]
    {198, "\u0626", "\uFE89", "\uFE8B", "\uFE8C", "\uFE8A"}, // 6 YEH_HAMZA ئ [*]
    {199, "\u0627", "\uFE8D", "\uFE8D", "\uFE8E", "\uFE8E"}, // 7 ALEF ا [*]
    {200, "\u0628", "\uFE8F", "\uFE91", "\uFE92", "\uFE90"}, // 8 BEH ب
    {555, "\u0629", "\uFE93", "\uFE93", "\uFE94", "\uFE94"}, // 9 TEH_MARBUTA ة [*]
    {202, "\u062A", "\uFE95", "\uFE97", "\uFE98", "\uFE96"}, // 10 TEH ت
    {203, "\u062B", "\uFE99", "\uFE9B", "\uFE9C", "\uFE9A"}, // 11 THEH ث
    {204, "\u062C", "\uFE9D", "\uFE9F", "\uFEA0", "\uFE9E"}, // 12 JEEM ج
    {205, "\u062D", "\uFEA1", "\uFEA3", "\uFEA4", "\uFEA2"}, // 13 HAH ح
    {206, "\u062E", "\uFEA5", "\uFEA7", "\uFEA8", "\uFEA6"}, // 14 KHAH خ
    {207, "\u062F", "\uFEA9", "\uFEA9", "\uFEAA", "\uFEAA"}, // 15 DAL د [*]
    {208, "\u0630", "\uFEAB", "\uFEAB", "\uFEAC", "\uFEAC"}, // 16 THAL ذ [*]
    {209, "\u0631", "\uFEAD", "\uFEAD", "\uFEAE", "\uFEAE"}, // 17 REH ر [*]
    {210, "\u0632", "\uFEAF", "\uFEAF", "\uFEB0", "\uFEB0"}, // 18 ZAIN ز [*]
    {184, "\u0698", "\uFB8A", "\uFB8A", "\uFB8B", "\uFB8B"}, // 19 ZHEH ژ [*]
    {211, "\u0633", "\uFEB1", "\uFEB3", "\uFEB4", "\uFEB2"}, // 20 SEEN
    {212, "\u0634", "\uFEB5", "\uFEB7", "\uFEB8", "\uFEB6"}, // 21 SHEEN
    {213, "\u0635", "\uFEB9", "\uFEBB", "\uFEBC", "\uFEBA"}, // 22 SAD ص
    {214, "\u0636", "\uFEBD", "\uFEBF", "\uFEC0", "\uFEBE"}, // 23 DAD ض
    {215, "\u0637", "\uFEC1", "\uFEC3", "\uFEC4", "\uFEC2"}, // 24 TAH ط
    {216, "\u0638", "\uFEC5", "\uFEC7", "\uFEC8", "\uFEC6"}, // 25 ZAH ظ
    {217, "\u0639", "\uFEC9", "\uFECB", "\uFECC", "\uFECA"}, // 26 AIN ع
    {218, "\u063A", "\uFECD", "\uFECF", "\uFED0", "\uFECE"}, // 27 GHAIN غ
    {160, "\u0640", "\u0640", "\u0640", "\u0640", "\u0640"}, // 28 TATWEEL ـ
    {161, "\u0641", "\uFED1", "\uFED3", "\uFED4", "\uFED2"}, // 29 FEH ف
    {162, "\u0642", "\uFED5", "\uFED7", "\uFED8", "\uFED6"}, // 30 QAF ق
    {163, "\u0643", "\uFED9", "\uFEDB", "\uFEDC", "\uFEDA"}, // 31 KAF Arabic ك
    {164, "\u0644", "\uFEDD", "\uFEDF", "\uFEE0", "\uFEDE"}, // 32 LAM ل
    {165, "\u0645", "\uFEE1", "\uFEE3", "\uFEE4", "\uFEE2"}, // 33 MEEM م
    {228, "\u0646", "\uFEE5", "\uFEE7", "\uFEE8", "\uFEE6"}, // 34 NOON ن
    {167, "\u0647", "\uFEE9", "\uFEEB", "\uFEEC", "\uFEEA"}, // 35 HEH ه
    {168, "\u0648", "\uFEED", "\uFEED", "\uFEEE", "\uFEEE"}, // 36 WAW و [*]
    {169, "\u0649", "\uFEEF", "\uFEEF", "\uFEF0", "\uFEF0"}, // 37 ALEF_MAKSURA [*]
    {170, "\u064A", "\uFEF1", "\uFEF3", "\uFEF4", "\uFEF2"}, // 38 YEH Arabic ي
    {172, "\u06CC", "\uFBFC", "\uFBFE", "\uFBFF", "\uFBFD"}, // 39 YEH Farsi ی
    {141, "\u0686", "\uFB7A", "\uFB7C", "\uFB7D", "\uFB7B"}, // 40 CHEH چ
    {222, "\u067E", "\uFB56", "\uFB58", "\uFB59", "\uFB57"}, // 41 Peh پ
    {144, "\u06AF", "\uFB92", "\uFB94", "\uFB95", "\uFB93"}, // 42 Gaf گ
    {201, "\u06A9", "\uFB8E", "\uFB90", "\uFB91", "\uFB8F"}, // 43 Kaf ک
    {32, "\u0020", "\u0020", "\u0020", "\u0020", "\u0020"},  // 44 Space
    {44, "\u060C", "\u060C", "\u060C", "\u060C", "\u060C"},  // 45 Kama
    {20, "\u200C", "\u200C", "\u200C", "\u200C", "\u200C"},  // 46 half-space
    {58, "\u003A", "\u003A", "\u003A", "\u003A", "\u003A"},  // 47 :
    {187, "\u061B", "\u061B", "\u061B", "\u061B", "\u061B"}, // 48 ؛
    {46, "\u002E", "\u002E", "\u002E", "\u002E", "\u002E"},  // 49 .
    {191, "\u061F", "\u061F", "\u061F", "\u061F", "\u061F"}, // 50 ؟
    {48, "\u06F0", "\u06F0", "\u06F0", "\u06F0", "\u06F0"},  // 51 0
    {49, "\u06F1", "\u06F1", "\u06F1", "\u06F1", "\u06F1"},  // 52 1
    {50, "\u06F2", "\u06F2", "\u06F2", "\u06F2", "\u06F2"},  // 53 2
    {51, "\u06F3", "\u06F3", "\u06F3", "\u06F3", "\u06F3"},  // 54 3
    {52, "\u06F4", "\u06F4", "\u06F4", "\u06F4", "\u06F4"},  // 55 4
    {53, "\u06F5", "\u06F5", "\u06F5", "\u06F5", "\u06F5"},  // 56 5
    {54, "\u06F6", "\u06F6", "\u06F6", "\u06F6", "\u06F6"},  // 57 6
    {55, "\u06F7", "\u06F7", "\u06F7", "\u06F7", "\u06F7"},  // 58 7
    {56, "\u06F8", "\u06F8", "\u06F8", "\u06F8", "\u06F8"},  // 59 8
    {57, "\u06F9", "\u06F9", "\u06F9", "\u06F9", "\u06F9"},  // 60 9
    {41, "\u0028", "\u0028", "\u0028", "\u0028", "\u0028"},  // 61 (
    {40, "\u0029", "\u0029", "\u0029", "\u0029", "\u0029"},  // 62 )
    {33, "\u0021", "\u0021", "\u0021", "\u0021", "\u0021"},  // 63 !
    {10, "\u000A", "\u000A", "\u000A", "\u000A", "\u000A"},  // 64 line
    {45, "\u002D", "\u002D", "\u002D", "\u002D", "\u002D"},  // 65 -
    {35, "\u0023", "\u0023", "\u0023", "\u0023", "\u0023"},  // 66 #
    {43, "\u002B", "\u002B", "\u002B", "\u002B", "\u002B"},  // 67 +
    {34, "\u0022", "\u0022", "\u0022", "\u0022", "\u0022"},  // 68 "
    {39, "\u0027", "\u0027", "\u0027", "\u0027", "\u0027"},  // 69 '
    {37, "\u0025", "\u0025", "\u0025", "\u0025", "\u0025"},  // 70 %
    {42, "\u002A", "\u002A", "\u002A", "\u002A", "\u002A"},  // 71 *
    {95, "\u005F", "\u005F", "\u005F", "\u005F", "\u005F"},  // 72 _
    {64, "\u0040", "\u0040", "\u0040", "\u0040", "\u0040"},  // 73 @
    {36, "\u0024", "\u0024", "\u0024", "\u0024", "\u0024"},  // 74 $
    {94, "\u005E", "\u005E", "\u005E", "\u005E", "\u005E"},  // 75 ^
    {38, "\u0026", "\u0026", "\u0026", "\u0026", "\u0026"},  // 76 & von hier
    {44, "\u002C", "\u002C", "\u002C", "\u002C", "\u002C"},  // 77 ,
    {47, "\u002F", "\u002F", "\u002F", "\u002F", "\u002F"},  // 78 /
    {59, "\u003B", "\u003B", "\u003B", "\u003B", "\u003B"},  // 79 ;
    {60, "\u003C", "\u003C", "\u003C", "\u003C", "\u003C"},  // 80 <
    {62, "\u003E", "\u003E", "\u003E", "\u003E", "\u003E"},  // 81 >
    {61, "\u003D", "\u003D", "\u003D", "\u003D", "\u003D"},  // 82 =
    {63, "\u003F", "\u003F", "\u003F", "\u003F", "\u003F"},  // 83 ?
    {91, "\u005B", "\u005B", "\u005B", "\u005B", "\u005B"},  // 84 [
    {93, "\u005D", "\u005D", "\u005D", "\u005D", "\u005D"},  // 85 ]
    {92, "\u005C", "\u005C", "\u005C", "\u005C", "\u005C"},  // 86 BACKSLASH
    {96, "\u0060", "\u0060", "\u0060", "\u0060", "\u0060"},  // 87 `
    {123, "\u007B", "\u007B", "\u007B", "\u007B", "\u007B"},  // 88 {
    {125, "\u007D", "\u007D", "\u007D", "\u007D", "\u007D"},  // 89 }
    {126, "\u007E", "\u007E", "\u007E", "\u007E", "\u007E"},  // 90 ~
    {124, "\u007C", "\u007C", "\u007C", "\u007C", "\u007C"},  // 91 |
};

bool isFromTheSet1(unsigned char ch);
bool isFromTheSet2(unsigned char ch);
int FindGlyph(unsigned char chFind);
String prReshaper(const char *Text);

void utf8rev(char *str);
String utf8rev(String utf8String);

int strlen_utf8(char *s);

#endif // __PERSIANRESHAPER_H__
