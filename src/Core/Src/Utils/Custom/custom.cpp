#include "custom.h"

namespace Custom {
float strToFloat(const char* str) {
    float result = 0.0f;
    float factor = 1.0f;
    bool negative = false;

    if (*str == '-') {
        negative = true;
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10.0f + (*str - '0');
        str++;
    }

    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            factor *= 0.1f;
            result += (*str - '0') * factor;
            str++;
        }
    }

    return negative ? -result : result;
}
};
