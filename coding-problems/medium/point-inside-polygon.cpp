#include <gtest/gtest.h>
#include <iostream>
#include <utility>

using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, pair<T1, T2> p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

struct Point
{
    int x;
    int y;
};

struct Vector
{
    int x;
    int y;

    explicit Vector(Point a, Point b)
    {
        x = b.x - a.x;
        y = b.y - a.y;
    };
};

/*

You are given a list of N points (x1, y1), (x2, y2), ..., (xN, yN)
representing a polygon. You can assume these points are given in order;
that is, you can construct the polygon by connecting point 1 to point 2,
point 2 to point 3, and so on, finally looping around to connect point N to point 1.

Determine if a new point p lies inside this polygon. (If p is on the boundary
of the polygon, you should return False).

Note: is the polygon self-intersecting meaning an edge can cross another edge?

A polygon is an enclosed structure meaning it must have at least 3 edges.

*/

/*

Idea 1: For non-self-intersecting polygon, like a rectange, a point will be inside if?
    it must lie within the min_x and max_x
    it must lie within the min_y and max_y
    Doesn't work for a triangle

Idea 2: See if the point is bounded by at least 3 edges? Works for both self-intersecting and
non-self-intersecting.

    Then the problem is how to identify if the point has been enclosed? It may lie either
    above or below a certain edge


    Solution: https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
    Use the idea of intersecting segments
*/

// checks whether point r lies within the seqment pq
static bool OnSegment(Point p, Point q, Point r)
{
    const auto [x1, y1] = p;
    const auto [x2, y2] = q;
    const auto [x3, y3] = r;

    int x_min = std::min(x1, x2);
    int x_max = std::max(x1, x2);
    int y_min = std::min(y1, y2);
    int y_max = std::max(y1, y2);

    if ((x3 >= x_min && x3 <= x_max) && (y3 >= y_min && y3 <= y_max))
        return true;

    return false;
}

/*
    Return 0 if cross-product is 0
    Return 1 if cross-product is +ive i.e. b lies counter-clockwise to a
    Return -1 if cross-product is -ive i.e. b lies clockwise to a
*/
static int CrossProduct(Vector a, Vector b)
{
    /*
        a = (x1, y1);
        b = (x2, y2);
        a x b = x1y2 - x2y1
    */
    int result = a.x * b.y - b.x * a.y;
    /* where result is a vector perpendicular to both a and b
       the direction of the result is could either be out-of-the-screen (positive)
       i.e. towards you or into the screen (negative). It is determined
       using the right hand rule i.e. join the tails of two vectors,
       put the heel of the right hand over the joined tails, and curl the
       fingers in the direction of shortest rotation that would make a
       reach b. Then the thumb will point in the direction of cross-product.
       For info, tail is the starting point of the vector.

       thumb towards you (or out of screen): positive cross-product
       thumb away from you (in to the screen): negative cross-product

       if both vectors are parallel, then the cross-product is zero.
    */
    if (result == 0)
        return 0;

    return result > 0 ? 1 : -1;
}

/*
Segment 1 is defined by points p and q.
Segment 2 is defined by points r and s.
Each point has x, y coordinates
See medium/intersecting-line-segments for more explanation
*/
static bool SegmentsIntersect(Point p, Point q, Point r, Point s)
{

    int pqr = CrossProduct(Vector{p, q}, Vector{p, r});
    int pqs = CrossProduct(Vector{p, q}, Vector{p, s});
    int rsp = CrossProduct(Vector{r, s}, Vector{r, p});
    int rsq = CrossProduct(Vector{r, s}, Vector{r, q});

    if ((pqr * pqs < 0) && (rsp * rsq < 0))
        return true;

    if (pqr == 0 && OnSegment(p, q, r))
        return true;

    if (pqs == 0 && OnSegment(p, q, s))
        return true;

    if (rsp == 0 && OnSegment(r, s, p))
        return true;

    if (rsq == 0 && OnSegment(r, s, q))
        return true;

    return false;
}

// O(n)
bool IsPointInsidePolygon(vector<Point> points, Point r)
{
    int intersectionCount = 0;
    for (int i = 1; i < points.size(); i++)
    {
        auto p = points[i - 1];
        auto q = points[i];

        Point s{INT_MAX, r.y}; // endpoint for a horizontal line rs

        // TODO: handle case where point lies on the boundary
        if (CrossProduct(Vector{p, q}, Vector{p, r}) == 0 &&
            OnSegment(p, q, r))
        {
            return false;
        }
        // see if the horizontal line rs intersect the edge
        if (SegmentsIntersect(p, q, r, s))
        {
            intersectionCount++;
        }
    }

    // if count of intersection odd, return true
    return intersectionCount % 2 != 0 ? true : false;
}

TEST(IsPointInsidePolygon, TestCase1)
{
    vector<Point> points{
        {0, 0}, {2, 4}, {4, 0}};

    EXPECT_EQ(IsPointInsidePolygon(points, {0, 1}), false);
    EXPECT_EQ(IsPointInsidePolygon(points, {2, 4}), false);
    EXPECT_EQ(IsPointInsidePolygon(points, {2, 3}), true);
}