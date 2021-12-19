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

#include "point2d.h"

Point2D::Point2D() : x_(0.0), y_(0.0) {}

Point2D::Point2D(double x, double y) : x_(x), y_(y) {}

double Point2D::DistanceTo(Point2D &other_point) const
{
    return std::hypot(x_ - other_point.x_, y_ - other_point.y_);
}
