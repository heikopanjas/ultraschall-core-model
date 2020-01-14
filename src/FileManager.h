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

#ifndef __ULTRASCHALL_CORE_FILE_MANAGER_H_INCL__
#define __ULTRASCHALL_CORE_FILE_MANAGER_H_INCL__

#include <CoreStream.h>
#include <CoreString.h>

namespace Ultraschall { namespace Core {

class FileManager
{
public:
    static String      AppendPath(const String& prefix, const String& appendix);
    static String      StripPath(const String& path);
    static StringArray SplitPath(const String& path);

    static bool   FileExists(const String& path);
    static size_t FileExists(const StringArray& paths);

    static String QueryFileDirectory(const String& filename);

    enum class FILE_TYPE { MP4CHAPS, MP3, JPEG, PNG, UNKNOWN_FILE_TYPE, MAX_FILE_TYPE = UNKNOWN_FILE_TYPE };
    static FILE_TYPE QueryFileType(const String& filename);

    static size_t QueryFileSize(const String& filename);
    static bool   IsDiskSpaceAvailable(const String& filename, const size_t requiredBytes);

    static BinaryStream* ReadBinaryFile(const String& filename);
    static StringArray   ReadTextFile(const String& filename);

    static bool WriteTextFile(const String& filename, const String& str);

private:
    static String NormalizeFileName(const String& targetName);
};

}} // namespace Ultraschall::Core

#endif // #ifndef __ULTRASCHALL_CORE_FILE_MANAGER_H_INCL__
