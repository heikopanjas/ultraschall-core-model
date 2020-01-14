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

#include <CoreServiceManager.h>

#include "ServiceFactory.h"
#include "ServiceRegistry.h"

namespace Ultraschall { namespace Core {
struct ServiceManager::Impl
{
    Impl();

    ServiceStatus RegisterService(const String& serviceId, CREATE_SERVICE_FUNCTION factoryFunction);

    void UnregisterService(const String& serviceId);

    ServiceStatus AcquireService(const String& serviceId, IServiceCallback* serviceCallback, IService*& service);

private:
    ServiceRegistry serviceRegistry_;
    ServiceFactory  serviceFactory_;
};

ServiceManager::Impl::Impl() : serviceRegistry_(serviceFactory_) {}

ServiceStatus ServiceManager::Impl::RegisterService(const String& serviceId, CREATE_SERVICE_FUNCTION factoryFunction)
{
    return serviceFactory_.RegisterService(serviceId, factoryFunction);
}

void ServiceManager::Impl::UnregisterService(const String& serviceId)
{
    serviceFactory_.UnregisterService(serviceId);
}

ServiceStatus ServiceManager::Impl::AcquireService(
    const String& serviceId, IServiceCallback* serviceCallback, IService*& service)
{
    return serviceRegistry_.AcquireService(serviceId, serviceCallback, service);
}

ServiceManager::ServiceManager() : impl_(new Impl()) {}

ServiceManager::~ServiceManager()
{
    SafeDelete(impl_);
}

ServiceStatus ServiceManager::RegisterService(const String& serviceId, CREATE_SERVICE_FUNCTION factoryFunction)
{
    return impl_->RegisterService(serviceId, factoryFunction);
}

void ServiceManager::UnregisterService(const String& serviceId)
{
    impl_->UnregisterService(serviceId);
}

ServiceStatus ServiceManager::AcquireService(
    const String& serviceId, IServiceCallback* serviceCallback, IService*& service)
{
    return impl_->AcquireService(serviceId, serviceCallback, service);
}

}} // namespace Ultraschall::Core
