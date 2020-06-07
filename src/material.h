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

double schlick(double cosine, double refraction_index)
{
    auto r0 = (1-refraction_index) / (1+refraction_index);
    r0 = r0*r0;
    return r0 + (1-r0)*pow(1-cosine, 5);
}

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
        metal(const colour& a, double f) : 
            albedo_(a),
            fuzz_(f < 1 ? f : 1) {}

    virtual bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        colour& attenuation, 
        ray& scattered) const 
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz_*random_in_unit_sphere());
        attenuation = albedo_;
        return dot(scattered.direction(), rec.normal) > 0;
    }

    private:
        colour albedo_;
        double fuzz_;
};

class dielectric : public material
{
    public:
        dielectric(double ri) : refraction_index_(ri) {}

    virtual bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        colour& attenuation, 
        ray& scattered) const 
    {
        attenuation = colour(1.0,1.0,1.0);
        double etai_over_etat = rec.front_face ? (1.0 / refraction_index_) : refraction_index_;

        vec3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
        if (etai_over_etat * sin_theta > 1.0)
        {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob)
        {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);

        return true;
    }

    private:
        double refraction_index_;
};
