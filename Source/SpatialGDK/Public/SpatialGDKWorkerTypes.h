// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#pragma once

#ifdef SPATIALOS_WORKER_SDK_MOCK_ENABLED

#include "SpatialOSMockWorkerTypes.h"

#else

#include <improbable/worker.h>

using SpatialOSConnection = worker::Connection;
using SpatialOSLocator = worker::Locator;
using SpatialOSOpList = worker::OpList;
using SpatialOSDispatcher = worker::Dispatcher;
template <class T>
using SpatialOSFuture = worker::Future<T>;

#endif
