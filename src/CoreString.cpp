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

#include <CoreString.h>

#include "Common.h"

namespace Ultraschall { namespace Core {

struct String::Impl
{
    static constexpr size_t NPOS = std::string::npos;
    std::string             str_;
};

const size_t String::NPOS = String::Impl::NPOS;

String::String() : impl_(new Impl()) {}

String::String(const char* str) : impl_(new Impl())
{
    impl_->str_ = str;
}

String::~String() {}

String& String::operator=(const char* str)
{
    impl_->str_ = str;
    return *this;
}

String& String::operator+=(const char* str)
{
    impl_->str_ = str;
    return *this;
}

String::operator const char*() const
{
    return impl_->str_.c_str();
}

bool String::operator==(const char* str) const
{
    return impl_->str_ == str;
}

bool String::operator<(const String& str) const
{
    return impl_->str_ < str.impl_->str_;
}

bool String::empty() const
{
    return impl_->str_.empty();
}

size_t String::size() const
{
    return impl_->str_.size();
}

size_t String::length() const
{
    return impl_->str_.length();
}

const char* String::c_str() const
{
    return impl_->str_.c_str();
}

const char* String::data() const
{
    return impl_->str_.data();
}

String String::substr(const size_t offset, const size_t count) const
{
    String str;
    str.impl_->str_ = impl_->str_.substr(offset, count);
    return str;
}

void String::replace(const String& source, const String& target)
{
    size_t start_pos = 0;
    while((start_pos = impl_->str_.find(source.impl_->str_, start_pos)) != String::NPOS)
    {
        impl_->str_.replace(start_pos, source.length(), target.impl_->str_);
        start_pos += target.length();
    }
}

String& String::append(const char* str) 
{
  impl_->str_.append(str);
  return *this;
}

void String::trim_left()
{
    impl_->str_.erase(
        impl_->str_.begin(), std::find_if(impl_->str_.begin(), impl_->str_.end(), [](int ch) { return (ch != ' '); }));
}

void String::trim_right()
{
    impl_->str_.erase(
        std::find_if(impl_->str_.rbegin(), impl_->str_.rend(), [](int ch) { return (ch != ' '); }).base(),
        impl_->str_.end());
}

void String::trim()
{
    trim_left();
    trim_right();
}

String String::trim_left(String str)
{
    str.trim_left();
    return str;
}

String String::trim_right(String str)
{
    str.trim_right();
    return str;
}

String String::trim(String str)
{
    str.trim();
    return str;
}

// StringArray String::split(const char delimiter) const
// {
//     StringArray tokens;

//     std::stringstream stream(static_cast<const char*>(impl_->str_.c_str()));
//     std::string       token;
//     while(std::getline(stream, token, delimiter))
//     {
//         tokens.push_back(String(token.c_str()));
//     }

//     return tokens;
// }

String String::to_lower()
{
    String str(impl_->str_.c_str());
    if(str.empty() == false)
    {
        std::transform(str.impl_->str_.begin(), str.impl_->str_.end(), str.impl_->str_.begin(), ::tolower);
    }

    return str;
}

String String::to_upper()
{
    String str(impl_->str_.c_str());
    if(str.empty() == false)
    {
        std::transform(str.impl_->str_.begin(), str.impl_->str_.end(), str.impl_->str_.begin(), ::toupper);
    }

    return str;
}

int String::to_int(const String& str)
{
    int result = -1;

    if(str.empty() == false)
    {
        std::istringstream is(str.impl_->str_);
        is >> result;
    }

    return result;
}

String String::from_int(const int value)
{
    std::ostringstream os;
    os << value;
    return String(os.str().c_str());
}

}} // namespace Ultraschall::Core
