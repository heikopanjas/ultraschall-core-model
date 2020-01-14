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

#include <CoreGuid.h>

#include "Common.h"

#ifdef _WIN32
#include <rpc.h>
#include <windows.h>

void InitializeGUID(uint8_t* data, const size_t dataSize)
{
    PRECONDITION(data != nullptr);
    PRECONDITION(dataSize >= sizeof(UUID));

    UUID       uuid   = {0};
    RPC_STATUS status = UuidCreate(&uuid);
    if(RPC_S_OK == status)
    {
        memcpy(data, &uuid, dataSize);
    }
}

#endif // #ifdef _WIN32

namespace Ultraschall { namespace Core {

struct Guid::Impl
{
public:
    static constexpr size_t GUID_DATA_SIZE = 16;

    Impl();
    virtual ~Impl();

    Impl(const Impl& rhs);

    bool operator==(const Impl& rhs) const;
    bool operator<(const Impl& rhs) const;

    uint8_t data_[GUID_DATA_SIZE];
};

Guid::Impl::Impl() : data_{0} {}

Guid::Impl::~Impl()
{
    memset(data_, 0, sizeof(uint8_t) * GUID_DATA_SIZE);
}

Guid::Impl::Impl(const Guid::Impl& rhs) : data_{0}
{
    *this = rhs;
}

bool Guid::Impl::operator==(const Impl& rhs) const
{
    return memcmp(data_, rhs.data_, sizeof(uint8_t) * GUID_DATA_SIZE) == 0;
}

bool Guid::Impl::operator<(const Impl& rhs) const
{
    return memcmp(data_, rhs.data_, sizeof(uint8_t) * GUID_DATA_SIZE) < 0;
}

Guid::Guid() : impl_(nullptr) {}

Guid::~Guid()
{
    SafeDelete(impl_);
}

Guid::Guid(const Guid& rhs) : impl_(nullptr)
{
    *this = rhs;
}

Guid& Guid::operator=(const Guid& rhs)
{
    memcpy(impl_->data_, rhs.impl_->data_, Impl::GUID_DATA_SIZE);
    return *this;
}

bool Guid::operator==(const Guid& rhs) const
{
    return impl_->operator==(*rhs.impl_);
}

bool Guid::operator<(const Guid& rhs) const
{
    return impl_->operator<(*rhs.impl_);
}

Guid Guid::New()
{
    return Guid();
}

const Guid& Guid::Null()
{
    static Guid* pGuid = nullptr;

    if(nullptr == pGuid)
    {
        pGuid = new Guid();
        memset(pGuid->impl_->data_, 0, Impl::GUID_DATA_SIZE);
    }

    return *pGuid;
}

}} // namespace Ultraschall::Core
