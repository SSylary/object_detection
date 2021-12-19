/**
 * @file point2d.h
 * @author SSylary.xzc@gmail.com
 * @brief 
 *  simple class for Point2D
 * @version 1.0
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <iostream>
#include <cmath>

class Point2D
{
public:
    Point2D();
    Point2D(double x, double y);
    ~Point2D() = default;

    double DistanceTo(Point2D &other_point) const;
    double SquareDistanceTo(Point2D &other_point) const;

private:
    double x_;
    double y_;
};