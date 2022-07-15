#include <stdarg.h>
#include <string>
#include "util.h"
#include "animation.h"

std::string cal::string_format(const std::string fmt, ...) {
    int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
    std::string str;
    va_list ap;
    while (1) {     // Maximum two passes on a POSIX system...
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {  // Everything worked
            str.resize(n);
            return str;
        }
        if (n > -1)  // Needed size returned
            size = n + 1;   // For null char
        else
            size *= 2;      // Guess at a larger size (OS specific)
    }
    return str;
}

float cal::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

cal::Transform cal::lerp(Transform a, Transform b,float t) {
    return {
        a.pos + t * (b.pos - a.pos),
        a.scale + t * (b.scale - a.scale),
        a.rotation + t * (b.rotation - a.rotation),
    };
}