#pragma once

#include "rtweekend.h"

class camera
{
    public:
        const double ASPECT_RATIO = 16.0 / 9.0;
        const double VIEWPORT_HEIGHT = 2.0;
        const double VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
        const double FOCAL_LENGTH = 1.0;

        camera() : 
            origin_(point3(0,0,0)),
            horizontal_(vec3(VIEWPORT_WIDTH,0.0,0.0)),
            vertical_(vec3(0.0, VIEWPORT_HEIGHT, 0.0))
        {
            lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - vec3(0,0,FOCAL_LENGTH);
        }

        ray get_ray(double u, double v) const 
        {
            return ray(origin_, lower_left_corner_ + u*horizontal_ + v*vertical_ - origin_);
        }

    private:
        point3  origin_;
        point3  lower_left_corner_;
        vec3    horizontal_;
        vec3    vertical_;
};
