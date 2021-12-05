/**
 * @file TimeUtil.h
 * @brief Time unit conversion functions
 * 
 * Copyright (c) 2021 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#pragma once

namespace time_util {

constexpr unsigned long MILLIS_PER_SECOND = 1000;
constexpr unsigned long SECONDS_PER_MINUTE = 60;
constexpr unsigned long MINUTES_PER_HOUR = 60;

class Seconds {
  public:
    inline __attribute__((always_inline)) constexpr static unsigned long toMillis(const unsigned long seconds) {
      return 1UL * seconds * time_util::MILLIS_PER_SECOND;
    }
};

class Minutes {
  public:
    inline __attribute__((always_inline)) constexpr static unsigned long toMillis(const unsigned long minutes) {
      return time_util::Seconds::toMillis(time_util::Minutes::toSeconds(minutes));
    }
    inline __attribute__((always_inline)) constexpr static unsigned long toSeconds(const unsigned long minutes) {
      return 1UL * minutes * time_util::SECONDS_PER_MINUTE;
    }
};

class Hours {
  public:
    inline __attribute__((always_inline)) constexpr static unsigned long toMillis(const unsigned long hours) {
      return time_util::Seconds::toMillis(time_util::Minutes::toSeconds(time_util::Hours::toMinutes(hours)));
    }
    inline __attribute__((always_inline)) constexpr static unsigned long toSeconds(const unsigned long hours) {
      return time_util::Minutes::toSeconds(time_util::Hours::toMinutes(hours));
    }
    inline __attribute__((always_inline)) constexpr static unsigned long toMinutes(const unsigned long hours) {
      return 1UL * hours * time_util::MINUTES_PER_HOUR;
    }
};

}
