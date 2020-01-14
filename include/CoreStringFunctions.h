////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (https://ultraschall.fm)
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __ULTRASCHALL_CORE_STRING_FUNCTIONS_H_INCL__
#define __ULTRASCHALL_CORE_STRING_FUNCTIONS_H_INCL__

#include <CoreCommon.h>
#include <CoreString.h>
#include <CoreStringArray.h>
#include <CoreWideString.h>

namespace Ultraschall { namespace Core {

enum class CHAR_ENCODING { UTF8, UTF16 };

enum class UTF16_BOM_SPEC { NO_UTF16_BOM = 0, WITH_UTF16_BOM_LE = 1, WITH_UTF16_BOM_BE = 2 };
static const char16_t* UTF16_BOM_LE = u"\xfffe"; // intel
static const char16_t* UTF16_BOM_BE = u"\xfeff";

ULTRASCHALL_CORE_API WideString
    StringToWideString(const String& uncodeString, const UTF16_BOM_SPEC bomSpec = UTF16_BOM_SPEC::NO_UTF16_BOM);

enum class UTF8_BOM_SPEC { NO_UTF8_BOM = 0, WITH_UTF8_BOM = 1 };
static const char* UTF8_BOM = "\xef\xbb\xbf";

ULTRASCHALL_CORE_API String
    WideStringToString(const WideString& wideUnicodeString, const UTF8_BOM_SPEC bomSpec = UTF8_BOM_SPEC::NO_UTF8_BOM);

ULTRASCHALL_CORE_API String HostStringToString(
    const char* pInputString, const size_t stringSize, const UTF8_BOM_SPEC bomSpec = UTF8_BOM_SPEC::NO_UTF8_BOM);

ULTRASCHALL_CORE_API size_t StringToHostString(const String& str, char** ppString, const size_t stringSize);

#define _MAKE_TEXT(str) #str
#define MAKE_TEXT(str) _MAKE_TEXT(str)

StringArray StringTokenize(const String& input, const char delimiter);

String   MillisecondsToString(const uint32_t milliseconds, const bool roundSeconds = false);
uint32_t StringToMilliseconds(const String& str);
String   SecondsToString(const double seconds, const bool roundSeconds = false);
double   StringToSeconds(const String& str);

#define H2U(a) HostStringToUnicodeString((a))
#define H2WU(a) HostStringToWideUnicodeString((a))

#define U2H(a) UnicodeStringToHostString((a))
#define WU2H(a) WideUnicodeStringToHostString((a))

#define U2WU(a) UnicodeStringToWideUnicodeString((a))
#define WU2U(a) WideUnicodeStringToUnicodeString((a))

}} // namespace Ultraschall::Core

#endif // #ifndef __ULTRASCHALL_CORE_STRING_FUNCTIONS_H_INCL__
