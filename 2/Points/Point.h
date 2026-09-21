#pragma once

class Point
{
public:
    Point();
    Point(const double p_x, const double p_y, const double p_z);

    double get_x() const;
    void set_x(const double real);
    double get_y() const;
    void set_y(const double real);
    double get_z() const;
    void set_z(const double real);

    void set_point(const double, const double, const double);
    void input();

    void plane() const;
    bool octant(const Point& other) const;
private:
    double x, y, z;

};