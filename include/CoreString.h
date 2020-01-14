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

#ifndef __ULTRASCHALL_CORE_STRING_H_INCL__
#define __ULTRASCHALL_CORE_STRING_H_INCL__

#include <CoreCommon.h>

namespace Ultraschall { namespace Core {

class ULTRASCHALL_CORE_API String
{
public:
    static const size_t NPOS;

    String();
    String(const char* str);
    virtual ~String();

    String& operator=(const char* str);
    String& operator+=(const char* str);

    operator const char*() const;

    bool operator==(const char* str) const;
    bool operator<(const String& str) const;

    bool   empty() const;
    size_t size() const;
    size_t length() const;

    const char* c_str() const;
    const char* data() const;

    String substr(const size_t offset = 0, const size_t count = NPOS) const;
    void   replace(const String& source, const String& target);
    String& append(const char* str);

    void trim_left();
    void trim_right();
    void trim();

    static String trim_left(String str);
    static String trim_right(String str);
    static String trim(String str);

    // StringArray split(const char delimiter) const;

    String to_lower();
    String to_upper();

    static int    to_int(const String& str);
    static String from_int(const int value);

private:
    struct Impl;
    Impl* impl_;
};

}} // namespace Ultraschall::Core

#endif // #ifndef __ULTRASCHALL_CORE_UNICODE_STRING_H_INCL__
