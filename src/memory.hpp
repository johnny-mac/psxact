#ifndef __psxact_memory_hpp__
#define __psxact_memory_hpp__


#include <cstdint>
#include <cstring>
#include <cstdio>
#include "memory-component.hpp"


constexpr uint32_t kib(uint32_t x) { return 1024 * x; }
constexpr uint32_t mib(uint32_t x) { return 1024 * kib(x); }
constexpr uint32_t gib(uint32_t x) { return 1024 * mib(x); }


template<uint32_t size>
struct memory_t : public memory_component_t {

  static constexpr int mask = size - 1;

  union {
    uint8_t  b[size];
    uint16_t h[size / 2];
    uint32_t w[size / 4];
  };

  memory_t(const char *name)
    : memory_component_t(name) {

    memset(b, 0, size_t(size));
  }

  void *get_pointer(uint32_t address) {
    return &b[address];
  }

  uint32_t io_read_byte(uint32_t address) {
    return b[(address & mask) / 1];
  }

  uint32_t io_read_half(uint32_t address) {
    return h[(address & mask) / 2];
  }

  uint32_t io_read_word(uint32_t address) {
    return w[(address & mask) / 4];
  }

  void io_write_byte(uint32_t address, uint32_t data) {
    b[(address & mask) / 1] = uint8_t(data);
  }

  void io_write_half(uint32_t address, uint32_t data) {
    h[(address & mask) / 2] = uint16_t(data);
  }

  void io_write_word(uint32_t address, uint32_t data) {
    w[(address & mask) / 4] = data;
  }

  bool load_blob(const char *filename) {
    if (FILE* file = fopen(filename, "rb+")) {
      fread(b, sizeof(uint8_t), size, file);
      fclose(file);
      return true;
    }
    else {
      printf("unable to load '%s'\n", filename);

      return false;
    }
  }
};


#endif // __psxact_memory_hpp__
