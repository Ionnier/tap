//
// Created by Dragos BAHRIM on 12.04.2024.
//

#ifndef TAP_TIMEMEASUREMENTUTIL_H
#define TAP_TIMEMEASUREMENTUTIL_H
#include <chrono>
class TimeMeasurementUtil {
    std::chrono::steady_clock::time_point bg;
public:
    void begin();

    long end();
};
#endif //TAP_TIMEMEASUREMENTUTIL_H
