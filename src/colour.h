#pragma once

#include "vec3.h"

#include <iostream>

void writeColour(std::ostream &out, colour pixelColour)
{
    // write the translated [0,255] value of each colour component.
    out << static_cast<int>(255.999 * pixelColour.x()) << ' '
        << static_cast<int>(255.999 * pixelColour.y()) << ' '
        << static_cast<int>(255.999 * pixelColour.z()) << '\n';
}
