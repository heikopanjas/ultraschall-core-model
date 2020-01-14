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
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif // #ifdef _WIN32
#include <codecvt>
#ifdef _WIN32
#undef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif // #ifdef _WIN32

#include <CoreStringFunctions.h>
#include <CoreStringBuilder.h>
#include <CoreGlobals.h>
#include "Common.h"

namespace Ultraschall { namespace Core {

#ifdef _WIN32
#include <windows.h>

String HostStringToString(const char* pString, const size_t stringSize, const UTF8_BOM_SPEC bomSpec)
{
    PRECONDITION_RETURN(pString != nullptr, String());
    PRECONDITION_RETURN(stringSize > 0, String());

    String str;

    if(bomSpec == UTF8_BOM_SPEC::WITH_UTF8_BOM)
    {
        str.append(UTF8_BOM);
    }

    const int wideStringBufferLength = MultiByteToWideChar(0, 0, pString, (int)stringSize, 0, 0);
    if(wideStringBufferLength > 0)
    {
        WCHAR* wideStringBuffer = (WCHAR*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
        if(wideStringBuffer != 0)
        {
            int convertedBytes
                = MultiByteToWideChar(0, 0, pString, (int)stringSize, wideStringBuffer, wideStringBufferLength);
            if(convertedBytes > 0)
            {
                const int narrowStringBufferLength
                    = WideCharToMultiByte(65001, 0, wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                if(narrowStringBufferLength > 0)
                {
                    CHAR* narrowStringBuffer = (CHAR*)calloc(sizeof(CHAR), narrowStringBufferLength + 1);
                    if(narrowStringBuffer != 0)
                    {
                        convertedBytes = WideCharToMultiByte(
                            65001, 0, wideStringBuffer, wideStringBufferLength, narrowStringBuffer,
                            narrowStringBufferLength, 0, 0);
                        if(convertedBytes > 0)
                        {
                            str += narrowStringBuffer;
                        }

                        free(narrowStringBuffer);
                        narrowStringBuffer = 0;
                    }
                }
            }

            free(wideStringBuffer);
            wideStringBuffer = 0;
        }
    }

    return str;
}

// WideString HostStringToWideString(const std::string& hostString, const UTF16_BOM_SPEC bomSpec)
//{
//    PRECONDITION_RETURN(hostString.empty() == false, WideString());
//
//    WideString wideUnicodeString;
//
//    if(bomSpec == UTF16_BOM_SPEC::WITH_UTF16_BOM_LE)
//    {
//        wideUnicodeString = UTF16_BOM_LE;
//    }
//    else if(bomSpec == UTF16_BOM_SPEC::WITH_UTF16_BOM_BE)
//    {
//        wideUnicodeString = UTF16_BOM_BE;
//        // TODO swap
//    }
//
//    const int wideStringBufferLength = MultiByteToWideChar(0, 0, hostString.c_str(), (int)hostString.length(), 0, 0);
//    if(wideStringBufferLength > 0)
//    {
//        char16_t* wideStringBuffer = (char16_t*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
//        if(wideStringBuffer != 0)
//        {
//            int convertedBytes = MultiByteToWideChar(
//                0, 0, hostString.c_str(), (int)hostString.length(), (LPWSTR)wideStringBuffer, wideStringBufferLength);
//            if(convertedBytes > 0)
//            {
//                wideUnicodeString += wideStringBuffer;
//            }
//
//            free(wideStringBuffer);
//            wideStringBuffer = 0;
//        }
//    }
//
//    return wideUnicodeString;
//}

size_t StringToHostString(const String& str, char** ppString, const size_t stringSize)
{
    PRECONDITION_RETURN(str.empty() == false, Globals::INVALID_DATA_SIZE);
    PRECONDITION_RETURN(ppString != nullptr, Globals::INVALID_DATA_SIZE);
    PRECONDITION_RETURN(stringSize > 0, Globals::INVALID_DATA_SIZE)

    *ppString = nullptr;

    char*  pResult    = nullptr;
    size_t resultSize = Globals::INVALID_DATA_SIZE;

    std::string hostString;

    size_t      unicodeStringBufferLength = str.size();
    const char* unicodeStringBuffer       = str.data();
    if(str.size() >= 3)
    {
        if(strncmp(unicodeStringBuffer, UTF8_BOM, sizeof(char) * 3) == 0)
        {
            unicodeStringBufferLength -= sizeof(char) * 3;
            unicodeStringBuffer = &(unicodeStringBuffer[3]);
        }
    }

    const int wideStringBufferLength
        = MultiByteToWideChar(65001, 0, unicodeStringBuffer, (int)unicodeStringBufferLength, 0, 0);
    if(wideStringBufferLength > 0)
    {
        char16_t* wideStringBuffer = (char16_t*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
        if(wideStringBuffer != 0)
        {
            int convertedBytes = MultiByteToWideChar(
                65001, 0, unicodeStringBuffer, (int)unicodeStringBufferLength, (LPWSTR)wideStringBuffer,
                wideStringBufferLength);
            if(convertedBytes > 0)
            {
                const int hostStringBufferLength
                    = WideCharToMultiByte(0, 0, (LPWCH)wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                if(hostStringBufferLength > 0)
                {
                    CHAR* hostStringBuffer = (CHAR*)calloc(sizeof(CHAR), hostStringBufferLength + 1);
                    if(hostStringBuffer != 0)
                    {
                        convertedBytes = WideCharToMultiByte(
                            0, 0, (LPWCH)wideStringBuffer, wideStringBufferLength, hostStringBuffer,
                            hostStringBufferLength, 0, 0);
                        if(convertedBytes > 0)
                        {
                            hostString = hostStringBuffer;
                        }

                        free(hostStringBuffer);
                        hostStringBuffer = 0;
                    }
                }
            }

            free(wideStringBuffer);
            wideStringBuffer = 0;
        }
    }

    if(hostString.empty() == false)
    {
        pResult = new char[hostString.size() + 1]();
        if(pResult != nullptr)
        {
            memset(pResult, 0, (hostString.size() + 1) * sizeof(char));
            memcpy(pResult, hostString.data(), hostString.size());

            *ppString = pResult;
            resultSize = hostString.size();
        }
    }

    return resultSize;
}

// std::string WideStringToHostString(const WideString& wideUnicodeString)
//{
//    PRECONDITION_RETURN(wideUnicodeString.empty() == false, std::string());
//
//    std::string hostString;
//
//    size_t          wideUnicodeStringBufferLength = wideUnicodeString.size();
//    const char16_t* wideUnicodeStringBuffer       = wideUnicodeString.data();
//    if(wideUnicodeString.size() >= 3)
//    {
//        if(memcmp(wideUnicodeStringBuffer, UTF16_BOM_LE, sizeof(char16_t)) == 0)
//        {
//            wideUnicodeStringBufferLength -= 1;
//            wideUnicodeStringBuffer = &(wideUnicodeStringBuffer[1]);
//        }
//        else if(memcmp(wideUnicodeStringBuffer, UTF16_BOM_BE, sizeof(char16_t)) == 0)
//        {
//            wideUnicodeStringBufferLength -= 1;
//            wideUnicodeStringBuffer = &(wideUnicodeStringBuffer[1]);
//            // TODO swap
//        }
//    }
//
//    const int hostStringBufferLength
//        = WideCharToMultiByte(0, 0, (LPWCH)wideUnicodeStringBuffer, (int)wideUnicodeStringBufferLength, 0, 0, 0, 0);
//    if(hostStringBufferLength > 0)
//    {
//        CHAR* hostStringBuffer = (CHAR*)calloc(sizeof(CHAR), hostStringBufferLength + 1);
//        if(hostStringBuffer != 0)
//        {
//            const int convertedBytes = WideCharToMultiByte(
//                0, 0, (LPWCH)wideUnicodeStringBuffer, (int)wideUnicodeStringBufferLength, hostStringBuffer,
//                hostStringBufferLength, 0, 0);
//            if(convertedBytes > 0)
//            {
//                hostString = hostStringBuffer;
//            }
//
//            free(hostStringBuffer);
//            hostStringBuffer = 0;
//        }
//    }
//
//    return hostString;
//}

#else // #ifdef _WIN32

String HostStringToUnicodeString(const std::string& hostString, const UTF8_BOM_SPEC bomSpec)
{
    String unicodeString;

    if(bomSpec == WITH_UTF8_BOM)
    {
        unicodeString = UTF8_BOM;
    }
    return unicodeString + hostString;
}

WideUnicodeString HostStringToWideUnicodeString(const std::string& hostString, const UTF16_BOM_SPEC bomSpec)
{
    return UnicodeStringToWideUnicodeString(hostString, bomSpec);
}

std::string UnicodeStringToHostString(const String& unicodeString)
{
    return unicodeString;
}

std::string WideUnicodeStringToHostString(const WideUnicodeString& wideUnicodeString)
{
    return WideUnicodeStringToUnicodeString(wideUnicodeString);
}

#endif // #ifdef _WIN32

WideString StringToWideString(const String& unicodeString, const UTF16_BOM_SPEC bomSpec)
{
    PRECONDITION_RETURN(unicodeString.empty() == false, WideString());

    WideString wideUnicodeString;

    String unicodeData = unicodeString;
    if(unicodeData.size() >= 3)
    {
        if(unicodeData.substr(0, 3) == UTF8_BOM)
        {
            unicodeData = unicodeData.substr(3);
        }
    }

    if(bomSpec == UTF16_BOM_SPEC::WITH_UTF16_BOM_LE)
    {
        wideUnicodeString = UTF16_BOM_LE;
    }
    else if(bomSpec == UTF16_BOM_SPEC::WITH_UTF16_BOM_BE)
    {
        wideUnicodeString = UTF16_BOM_BE;
    }

#if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> converter;
    const char* p = reinterpret_cast<const char*>(unicodeData.data());
    wideUnicodeString += (char16_t*)converter.from_bytes(p, p + unicodeData.size()).data();
#else  // #if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    wideUnicodeString += converter.from_bytes(unicodeData);
#endif // #if _WIN32

    return wideUnicodeString;
}

String WideStringToString(const WideString& wideUnicodeString, const UTF8_BOM_SPEC bomSpec)
{
    PRECONDITION_RETURN(wideUnicodeString.empty() == false, String());

    String unicodeString;

    WideString wideUnicodeData = wideUnicodeString;
    if(wideUnicodeData.size() >= 2)
    {
        if(wideUnicodeData.substr(0, 3) == UTF16_BOM_LE)
        {
            wideUnicodeData = wideUnicodeData.substr(3);
        }
        else if(wideUnicodeData.substr(0, 3) == UTF16_BOM_BE)
        {
            wideUnicodeData = wideUnicodeData.substr(3);
        }
    }

    if(bomSpec == UTF8_BOM_SPEC::WITH_UTF8_BOM)
    {
        unicodeString = UTF8_BOM;
    }

#if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
    const int16_t* p = reinterpret_cast<const int16_t*>(wideUnicodeData.data());
    unicodeString += convert.to_bytes(p, p + wideUnicodeData.size()).data();
#else  // #if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    unicodeString += converter.to_bytes(wideUnicodeData);
#endif // #if _WIN32

    return unicodeString;
}

StringArray StringTokenize(const String& input, const char delimiter)
{
    StringArray tokens;

    std::stringstream stream(static_cast<const char*>(input));
    std::string       token;
    while(std::getline(stream, token, delimiter))
    {
        tokens.push_back(String(token.c_str()));
    }

    return tokens;
}

}} // namespace Ultraschall::Core
