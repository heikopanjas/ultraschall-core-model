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

#include <CoreSharedObject.h>

#include "Common.h"

namespace Ultraschall { namespace Core {

struct SharedObject::Impl
{
    std::atomic<uint32_t> refCount_ = 1;

    Impl() {}

    const uint32_t AddRef()
    {
        return ++refCount_;
    }

    const uint32_t Release()
    {
        const uint32_t refCount = --refCount_;
        if(refCount == 0)
        {
            delete this;
        }

        return refCount;
    }
};

SharedObject::SharedObject() : impl_(new Impl()) {}

SharedObject::~SharedObject()
{
    SafeDelete(impl_);
}

uint32_t SharedObject::AddRef() const
{
    return impl_->AddRef();
}

uint32_t SharedObject::Release() const
{
    return impl_->Release();
}

}} // namespace Ultraschall::Core
