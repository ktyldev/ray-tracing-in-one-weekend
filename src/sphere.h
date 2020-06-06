#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
    public:
        sphere() {}
        sphere(point3 centre, double r, shared_ptr<material> m) : 
            centre_(centre), 
            radius_(r),
            mat_ptr_(m)
    {};

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

    private:
        point3                  centre_;
        double                  radius_;
        shared_ptr<material>    mat_ptr_;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
    vec3 oc = r.origin() - centre_;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius_*radius_;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0)
    {
        auto root = sqrt(discriminant);

        auto temp = (-half_b - root)/a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);

            vec3 outward_normal = (rec.p - centre_) / radius_;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr_;

            return true;
        }

        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            
            vec3 outward_normal = (rec.p - centre_) / radius_;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr_;
            
            return true;
        }
    }

    return false;
}
