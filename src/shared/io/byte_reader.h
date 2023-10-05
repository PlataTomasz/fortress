#if !defined(BYTE_READER_INCLUDED)
#define BYTE_READER_INCLUDED

#include <core/io/marshalls.h>
#include <stdint.h>

/**
 * Class designed to simplify converting bytes to simple datatypes.
 * @note Unlike in byte buffer, no dynamic memory allocation nor copy is made
*/
class ByteReader
{
private:
protected:
    uint8_t *buffer;
    uint64_t read_offset = 0;
    uint64_t size;

    ByteReader(){};
public:
    uint8_t pop_uint8()
    {
		ERR_FAIL_COND_V(!(size > (read_offset + 1)), 0);
        read_offset+=1;
        return buffer[read_offset];
    }
    
    uint16_t pop_uint16()
    {
        ERR_FAIL_COND_V(!(size > (read_offset + 2)), 0);
        read_offset+=2;
        return decode_uint16(&buffer[read_offset]);
    }

    uint32_t pop_uint32()
    {
        ERR_FAIL_COND_V(!(size > (read_offset + 4)), 0);
        read_offset+=4;
        return decode_uint32(&buffer[read_offset]);
    }

    uint64_t pop_uint64()
    {
        ERR_FAIL_COND_V(!(size > (read_offset + 8)), 0);
        read_offset+=8;
        return decode_uint64(&buffer[read_offset]);
    }

    float pop_float()
    {
        ERR_FAIL_COND_V(!(size > (read_offset + 4)), 0);
        read_offset+=4;
		return decode_float(&buffer[read_offset]);
    }

    double pop_double()
    {
        ERR_FAIL_COND_V(!(size > (read_offset + 8)), 0);
        read_offset+=8;
		return decode_double(&buffer[read_offset]);
    }

    real_t pop_real()
    {
        #ifdef REAL_T_IS_DOUBLE
        return pop_double();
        #else
        return pop_float();
        #endif
    }

    operator String()
    {
        String str = "["
        ;

        for(int i = 0;i < size;i++)
        {
            str = str + " " + Variant(static_cast<int>(buffer[i])).operator String();
        }
        
        str+=" ]";
        return str;
    }

    ByteReader(uint8_t *p_buffer, uint64_t p_size)
    {
        buffer = p_buffer;
        size = p_size;
    }
};

#endif // BYTE_READER_INCLUDED
