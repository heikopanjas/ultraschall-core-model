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

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>

#include <CoreString.h>

#include "Common.h"
#include "Platform.h"

namespace Ultraschall { namespace Core {

char Platform::QueryPathSeparator()
{
    return '\\';
}

size_t Platform::QueryAvailableDiskSpace(const String& directory)
{
    PRECONDITION_RETURN(directory.empty() == false, -1);

    size_t         availableSpace           = -1;
    ULARGE_INTEGER freeBytesAvailableToUser = {0};
    if(GetDiskFreeSpaceEx(directory.c_str(), &freeBytesAvailableToUser, nullptr, nullptr) != FALSE)
    {
        availableSpace = freeBytesAvailableToUser.QuadPart;
    }

    return availableSpace;
}

}} // namespace Ultraschall::Core

#endif // #ifdef _WIN32
