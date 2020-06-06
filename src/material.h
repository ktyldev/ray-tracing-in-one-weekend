#pragma once

#include "rtweekend.h"
#include "hittable.h"

class material
{
    public:
        virtual bool scatter(
            const ray& r_in,
            const hit_record& rec,
            colour& attenuation,
            ray& scattered) const = 0;
};

class lambertian : public material
{
    public:
        lambertian(const colour& a) : albedo_(a) {}

        virtual bool scatter(
            const ray& r_in, 
            const hit_record& rec, 
            colour& attenuation, 
            ray& scattered) const 
        {
            vec3 scatter_direction = rec.normal + random_unit_vector();
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo_;
            return true;
        }

    private:
        colour albedo_;
};

class metal : public material
{
    public:
        metal(const colour& a) : albedo_(a) {}

    virtual bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        colour& attenuation, 
        ray& scattered) const 
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo_;
        return dot(scattered.direction(), rec.normal) > 0;
    }

    private:
        colour albedo_;
};
