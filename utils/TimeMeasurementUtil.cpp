//
// Created by Dragos BAHRIM on 12.04.2024.
//
#include <chrono>
#include <TimeMeasurementUtil.h>

void TimeMeasurementUtil::begin() {
    bg = std::chrono::steady_clock::now();
}

long TimeMeasurementUtil::end() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - bg).count();
}