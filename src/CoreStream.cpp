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

#include <CoreStream.h>
#include <CoreGlobals.h>

#include "Common.h"

namespace Ultraschall { namespace Core {

const size_t Stream::INVALID_DATA_SIZE = Globals::INVALID_DATA_SIZE;

Stream::Stream(const size_t dataSize) : size_(dataSize), data_(new uint8_t[dataSize]) {}

Stream::~Stream()
{
    size_ = INVALID_DATA_SIZE;
    SafeDeleteArray(data_);
}

size_t Stream::Size() const
{
    return size_;
}

const uint8_t* Stream::Data() const
{
    return data_;
}

bool Stream::Write(const size_t offset, const uint8_t* data, const size_t size)
{
    PRECONDITION_RETURN(data_ != nullptr, false);
    PRECONDITION_RETURN((offset + size) <= size_, false);
    PRECONDITION_RETURN(data != nullptr, false);

    const size_t itemSize = sizeof(uint8_t);
    memmove(&data_[offset * itemSize], data, size * itemSize);
    return true;
}

bool Stream::Read(const size_t offset, uint8_t* data, const size_t size)
{
    PRECONDITION_RETURN(data_ != nullptr, false);
    PRECONDITION_RETURN((offset + size) < size_, false);
    PRECONDITION_RETURN(data != nullptr, false);

    const size_t itemSize = sizeof(uint8_t);
    memmove(data, &data_[offset * itemSize], size * itemSize);
    return true;
}

}} // namespace Ultraschall::Core
