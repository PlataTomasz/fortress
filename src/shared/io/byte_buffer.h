#if !defined(BYTE_BUFFER_INCLUDED)
#define BYTE_BUFFER_INCLUDED

#include "byte_reader.h"
#include  <core/math/math_defs.h>

/**
 * Wrapper class for byte conversions
*/
class ByteBuffer : public ByteReader
{
    const static uint64_t DEFAULT_BYTEBUFFER_SIZE = 1024;
private:
protected:
    uint64_t write_offset = 0;
public:
    void push_uint8(uint8_t value)
    {
        ERR_FAIL_COND(!(size > (write_offset + 1)));
        buffer[write_offset] = value;
        write_offset+=1;
    }
    
    void push_uint16(uint16_t value)
    {
        ERR_FAIL_COND(!(size > (write_offset + 2)));
		encode_uint16(value, &buffer[write_offset]);
        write_offset+=2;
    }

    void push_uint32(uint32_t value)
    {
        ERR_FAIL_COND(!(size > (write_offset + 4)));
		encode_uint32(value, &buffer[write_offset]);
        write_offset+=4;
    }

    void push_uint64(uint64_t value)
    {
        ERR_FAIL_COND(!(size > (write_offset + 8)));
		encode_uint64(value, &buffer[write_offset]);
        write_offset+=8;
    }

    void push_float(float value)
    {
        ERR_FAIL_COND(!(size > (write_offset + 4)));
		encode_float(value, &buffer[write_offset]);
        write_offset+=4;
    }

    void push_double(double value)
    {
        ERR_FAIL_COND(!(size > (write_offset + 8)));
		encode_double(value, &buffer[write_offset]);
        write_offset+=8;
    }

    void push_real(real_t value)
    {
        #ifdef REAL_T_IS_DOUBLE
        push_double(value);
        #else
        push_float(value);
        #endif
    }

    ByteBuffer(uint64_t p_size = ByteBuffer::DEFAULT_BYTEBUFFER_SIZE)
    {
        size = p_size;
        buffer = new uint8_t[size];
    }

    virtual ~ByteBuffer()
    {
        delete[] buffer;
    }
};

#endif // BYTE_BUFFER_INCLUDED
