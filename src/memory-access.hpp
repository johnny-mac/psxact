#ifndef __psxact_memory_access__
#define __psxact_memory_access__


#include <cstdint>


class memory_access_t {
public:

  virtual uint32_t read_byte(uint32_t address) = 0;

  virtual uint32_t read_half(uint32_t address) = 0;

  virtual uint32_t read_word(uint32_t address) = 0;

  virtual void write_byte(uint32_t address, uint32_t data) = 0;

  virtual void write_half(uint32_t address, uint32_t data) = 0;

  virtual void write_word(uint32_t address, uint32_t data) = 0;
};


#endif // __psxact_memory_access__
