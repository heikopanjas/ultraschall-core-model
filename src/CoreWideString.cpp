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

#include <CoreWideString.h>

#include "Common.h"

namespace Ultraschall { namespace Core {

struct WideString::Impl
{
    static constexpr size_t NPOS = std::basic_string<char16_t>::npos;
    std::basic_string<char16_t> str_;
};

const size_t WideString::NPOS = WideString::Impl::NPOS;

WideString::WideString() {}

WideString::~WideString() {}

WideString& WideString::operator=(const char16_t* str) 
{
  impl_->str_ = str;
  return *this;
}

WideString& WideString::operator+=(const char16_t* str)
{
    impl_->str_ += str;
    return *this;
}

bool WideString::operator==(const char16_t* str) const
{
    return impl_->str_ == str;
}

bool WideString::empty() const 
{
    return impl_->str_.empty();
}

size_t WideString::size() const
{
    return impl_->str_.size();
}

const char16_t* WideString::data() const
{
    return impl_->str_.data();
}

WideString WideString::substr(const size_t offset, const size_t count)
{
    WideString str;
    str.impl_->str_ = impl_->str_.substr(offset, count);
    return str;
}

}} // namespace Ultraschall::Core
