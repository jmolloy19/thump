#include "stockwatch/candle.h"

#include <algorithm>

#include "glog/logging.h"

namespace stockwatch {

float AverageClose(std::vector<Candle>::const_iterator first, std::vector<Candle>::const_iterator last) {
    if (first >= last) {
        DLOG_IF(WARNING, first > last);
        return 0;
    }

    double total = 0;
    for (auto itr = first; itr != last; itr++) {
        total += itr->close;
    }

    return total / std::distance(first, last);
}

std::vector<Candle>::const_iterator MinClose(std::vector<Candle>::const_iterator first,
                                             std::vector<Candle>::const_iterator last) {
    return std::min_element(first, last, [](const Candle& a, const Candle& b) { return a.close < b.close; });
}

std::vector<Candle>::const_iterator MaxClose(std::vector<Candle>::const_iterator first,
                                             std::vector<Candle>::const_iterator last) {
    return std::max_element(first, last, [](const Candle& a, const Candle& b) { return a.close < b.close; });
}

float AverageOpen(std::vector<Candle>::const_iterator first, std::vector<Candle>::const_iterator last) {
    if (first >= last) {
        DLOG_IF(WARNING, first > last);
        return 0;
    }

    double total = 0;
    for (auto itr = first; itr != last; itr++) {
        total += itr->open;
    }

    return total / std::distance(first, last);
}

std::vector<Candle>::const_iterator MinOpen(std::vector<Candle>::const_iterator first,
                                            std::vector<Candle>::const_iterator last) {
    return std::min_element(first, last, [](const Candle& a, const Candle& b) { return a.open < b.open; });
}

std::vector<Candle>::const_iterator MaxOpen(std::vector<Candle>::const_iterator first,
                                            std::vector<Candle>::const_iterator last) {
    return std::max_element(first, last, [](const Candle& a, const Candle& b) { return a.open < b.open; });
}

float AverageHigh(std::vector<Candle>::const_iterator first, std::vector<Candle>::const_iterator last) {
    if (first >= last) {
        DLOG_IF(WARNING, first > last);
        return 0;
    }

    double total = 0;
    for (auto itr = first; itr != last; itr++) {
        total += itr->high;
    }

    return total / std::distance(first, last);
}

std::vector<Candle>::const_iterator MinHigh(std::vector<Candle>::const_iterator first,
                                            std::vector<Candle>::const_iterator last) {
    return std::min_element(first, last, [](const Candle& a, const Candle& b) { return a.high < b.high; });
}

std::vector<Candle>::const_iterator MaxHigh(std::vector<Candle>::const_iterator first,
                                            std::vector<Candle>::const_iterator last) {
    return std::max_element(first, last, [](const Candle& a, const Candle& b) { return a.high < b.high; });
}

float AverageLow(std::vector<Candle>::const_iterator first, std::vector<Candle>::const_iterator last) {
    if (first >= last) {
        DLOG_IF(WARNING, first > last);
        return 0;
    }

    double total = 0;
    for (auto itr = first; itr != last; itr++) {
        total += itr->low;
    }

    return total / std::distance(first, last);
}

std::vector<Candle>::const_iterator MinLow(std::vector<Candle>::const_iterator first,
                                           std::vector<Candle>::const_iterator last) {
    return std::min_element(first, last, [](const Candle& a, const Candle& b) { return a.low < b.low; });
}
std::vector<Candle>::const_iterator MaxLow(std::vector<Candle>::const_iterator first,
                                           std::vector<Candle>::const_iterator last) {
    return std::max_element(first, last, [](const Candle& a, const Candle& b) { return a.low < b.low; });
}

int AverageVolume(std::vector<Candle>::const_iterator first, std::vector<Candle>::const_iterator last) {
    if (first >= last) {
        DLOG_IF(WARNING, first > last);
        return 0;
    }

    int64_t total = 0;
    for (auto itr = first; itr != last; itr++) {
        total += itr->volume;
    }

    return total / std::distance(first, last);
}

std::vector<Candle>::const_iterator MinVolume(std::vector<Candle>::const_iterator first,
                                              std::vector<Candle>::const_iterator last) {
    return std::min_element(first, last, [](const Candle& a, const Candle& b) { return a.volume < b.volume; });
}

std::vector<Candle>::const_iterator MaxVolume(std::vector<Candle>::const_iterator first,
                                              std::vector<Candle>::const_iterator last) {
    return std::max_element(first, last, [](const Candle& a, const Candle& b) { return a.volume < b.volume; });
}

}  // namespace stockwatch
