#pragma once

#include <cstdint>
#include <string.h>

namespace narechi
{
    struct buffer
    {
        uint8_t* data = nullptr;
        uint64_t size = 0;

        buffer() = default;
        buffer(const buffer&) = default;

        buffer(uint64_t size) {}

        static buffer clone(const buffer& other)
        {
            buffer temp(other.size);
            memcpy(temp.data, other.data, other.size);
            return temp;
        }

        void allocate(uint64_t size)
        {
            release();

            data = new uint8_t[size];
            this->size = size;
        }

        void release()
        {
            delete[] data;

            // Reset values to default
            data = nullptr;
            size = 0;
        }

        operator bool() const
        {
            return (bool)data;
        }
    };
}