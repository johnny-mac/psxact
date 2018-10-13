#ifndef __psxact_utility__
#define __psxact_utility__


#include <cstdio>
#include <cstdint>


#define likely(n) __builtin_expect(!!(n), 1)
#define unlikely(n) __builtin_expect(!!(n), 0)


#define expand(...) , ## __VA_ARGS__


#define logger(n, s, ...) \
  printf("[" n "] " s "\n" expand(__VA_ARGS__))

#define log_cpu(s, ...) \
  logger("cpu", s, __VA_ARGS__)

#define log_dma(s, ...) \
  logger("dma", s, __VA_ARGS__)

#define log_gpu(s, ...) \
  logger("gpu", s, __VA_ARGS__)

#define log_spu(s, ...) \
  logger("spu", s, __VA_ARGS__)

#define log_cdrom(s, ...) \
  logger("cdrom", s, __VA_ARGS__)

#define log_input(s, ...) \
  logger("input", s, __VA_ARGS__)

#define log_timer(s, ...) \
  logger("timer", s, __VA_ARGS__)


namespace utility {
  template<int bits>
  inline uint32_t sclip(uint32_t value) {
    const int mask = (1 << bits) - 1;
    const int sign = 1 << (bits - 1);

    return ((value & mask) ^ sign) - sign;
  }

  template<int bits>
  inline uint32_t uclip(uint32_t value) {
    const int mask = (1 << bits) - 1;

    return value & mask;
  }

  inline uint8_t dec_to_bcd(uint8_t value) {
    return uint8_t(((value / 10) * 16) + (value % 10));
  }

  inline uint8_t bcd_to_dec(uint8_t value) {
    return uint8_t(((value / 16) * 10) + (value % 16));
  }

  template<int bits>
  inline int clz(uint32_t value) {
    enum {
      mask = 1 << (bits - 1)
    };

    uint32_t count = 0;

    while (!(value & mask) && count < bits) {
      value = value << 1;
      count = count + 1;
    }

    return count;
  }
}


#endif // __psxact_utility__
