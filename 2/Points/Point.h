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
    bool symmetry(const Point& other) const;
    void symmetryAxis(const Point& other) const;

    double operator -(const Point& other) const;

    double abs() const;
    bool operator >(const Point& other) const;

    Point operator *(const double A) const;

    double distanceX() const;
    double distanceY() const;
    double distanceZ() const;

    bool triangle (const Point& second,const Point& third) const;

    double square (const Point& second, const Point& third) const;

private:
    double x, y, z;

};