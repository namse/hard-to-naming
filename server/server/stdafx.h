#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <chrono>
#include <memory>
#include <set>
#include <functional>
#include <queue>
#include <iostream>
#include <tchar.h>

#define ASIO_STANDALONE
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS
#define ASIO_HAS_MOVE
#include <asio.hpp>

using asio::ip::tcp;

#include "config.h"