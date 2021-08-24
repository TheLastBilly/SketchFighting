#pragma once

#include <chrono>

#include "utilities/exceptions.hpp"

#define throw_out_of_bounds_error(allocation, index) \
    throw_exception_with_msg(utilities::index_out_of_bounds_error, "index of size \"" + std::to_string(index) + "\" is too large for allocation " #allocation);

namespace utilities
{
    register_exception(index_out_of_bounds_error, "requested index is out of bounds");
    register_exception(null_callback_error, "attempting to use null callback");

    inline size_t get_current_time_in_milliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}