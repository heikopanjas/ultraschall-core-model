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

#ifndef __SERVICE_REGISTRY_H_INCL__
#define __SERVICE_REGISTRY_H_INCL__

#include <CoreService.h>
#include <CoreString.h>

#include "Common.h"

namespace Ultraschall { namespace Core {

class ServiceFactory;

class ServiceRegistry
{
public:
    ServiceRegistry(ServiceFactory& serviceFactory);
    virtual ~ServiceRegistry();

    ServiceStatus AcquireService(const String& serviceId, IServiceCallback* serviceCallback, IService*& service);
    ServiceStatus ReleaseService(const String& serviceId);

private:
    ServiceFactory& serviceFactory_;

    typedef std::map<String, IService*> ServiceDictionary;
    ServiceDictionary                   services_;
    std::recursive_mutex                servicesLock_;
};

}} // namespace Ultraschall::Core

#endif // #ifndef __SERVICE_REGISTRY_H_INCL__
