////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_CORE_COMMON_H_INCL__
#define __ULTRASCHALL_CORE_COMMON_H_INCL__

#ifdef _MSC_VER
#ifdef ULTRASCHALL_CORE_SHARED
#define ULTRASCHALL_CORE_API __declspec(dllexport)
#else // #ifdef ULTRASCHALL_FRAMEWORK_DYNAMIC
#define ULTRASCHALL_CORE_API
#endif // #ifdef ULTRASCHALL_FRAMEWORK_DYNAMIC
#else  // #ifdef _MSC_VER
#ifdef __GNUC__
#ifdef ULTRASCHALL_CORE_SHARED
#define ULTRASCHALL_CORE_API __attribute__((visibility("default")))
#else // #ifdef ULTRASCHALL_FRAMEWORK_DYNAMIC
#define ULTRASCHALL_CORE_API
#endif // #ifdef ULTRASCHALL_FRAMEWORK_DYNAMIC
#endif // #ifdef __GNUC__
#endif // #ifdef _MSC_VER

#include <cstdint>

namespace Ultraschall { namespace Core {

template<class T> inline static T* SafeAlloc()
{
    T* ptr = new T();
    if(ptr != nullptr)
    {
        memset(ptr, 0, sizeof(T));
    }

    return ptr;
}

template<class T> inline static T* SafeAllocArray(const size_t itemCount)
{
    T* ptr = nullptr;
    if(itemCount > 0)
    {
        ptr = new T[itemCount]();
        if(ptr != nullptr)
        {
            memset(ptr, 0, sizeof(T) * itemCount);
        }
    }

    return ptr;
}

template<class T> inline static void SafeDelete(T*& ptr)
{
    delete ptr;
    ptr = nullptr;
}

template<class T> inline static void SafeDeleteArray(T*& ptr)
{
    delete[] ptr;
    ptr = nullptr;
}

template<class T> inline static void SafeRelease(T*& ptr)
{
    if(ptr != nullptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}

}} // namespace Ultraschall::Core

#endif // #ifndef __ULTRASCHALL_CORE_COMMON_H_INCL__
