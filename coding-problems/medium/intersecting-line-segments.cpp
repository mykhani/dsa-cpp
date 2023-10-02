#include <gtest/gtest.h>
#include <utility>

/*

Use the idea if orientation of 3-points
https://www.geeksforgeeks.org/orientation-3-ordered-points/

And
https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

Let's explain how the orientation based check works to see if two segments
are intersecting.

Image there are two segments,
PQ: consisting of points p and q
RS: consisting of points r and s

whereas each point consists of two x, y coordinates. Two line segments intersect if:
1. They cross-each other completely (at certain angle)
2. An end-point of one segment lies on the other segment i.e. they might not cross each
other completely.

This discusses finding the orientation using vector cross-product:
https://algorithmtutor.com/Computational-Geometry/Check-if-two-line-segment-intersect/
https://algorithmtutor.com/Computational-Geometry/Determining-if-two-consecutive-segments-turn-left-or-right/

Since it uses vector-cross product (instead of slopes to find orientation), there is a standardized
convention for determining clockwise vs counter-clockwose orientation.

*/

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

using namespace std;

// checks whether point r lies within the seqment pq
static bool OnSegment(Point p, Point q, Point r)
{
    const auto [x1, y1] = p;
    const auto [x2, y2] = q;
    const auto [x3, y3] = r;

    if (x3 >= std::min(x1, x2) && x3 <= std::max(x1, x2) &&
        y3 > std::min(y1, y2) && y3 < std::max(y1, y2))
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
    return 0: collinear
    return 1: clockwise
    return 2: counter-clockwise
*/
int Orientation(Point p, Point q, Point r)
{
    const auto [x1, y1] = p;
    const auto [x2, y2] = q;
    const auto [x3, y3] = r;

    /*
        slope of p and q (y2-y1)/(x2-x1)
        slope of q and r (y3-y2)/(x3-x2)
        Orientation of p,q, and r considering their slopes
        if slope of p and q is greater than slope of q and r -> orientation clockwise
        if slope of p and q is less than slope of q and r -> orientation counter-clockwise
        if slope of p and q is equal to slope of q and r -> collinear

        For same slopes
        (y2-y1)/(x2-x1) = (y3-y2)/(x3-x2)
        Getting rid of denominators (to avoid division by 0 incase x3==x2 or x2==x1)
        (y2-y1)*(x3-x2) = (y3-y2)(x2-x1)
        (y2-y1)*(x3-x2) - (y3-y2)(x2-x1) = 0 // for same slope
        Similarly,
        (y2-y1)*(x3-x2) - (y3-y2)(x2-x1) > 0 // for slope pq > slope qr (clockwise)
        (y2-y1)*(x3-x2) - (y3-y2)(x2-x1) < 0 // for slope pq < slope qr (counter-clockwise)
    */
    int result = (y2 - y1) * (x3 - x2) - (y3 - y2) * (x2 - x1);
    if (result == 0)
        return 0;
    else if (result > 0)
        return 1;
    else
        return 2;
}

/*
Segment 1 is defined by points p and q.
Segment 2 is defined by points r and s.
Each point has x, y coordinates
*/
bool SegmentsIntersectUsingOrientation(Point p, Point q, Point r, Point s)
{
    int o1 = Orientation(p, q, r);
    int o2 = Orientation(p, q, s);
    int o3 = Orientation(r, s, p);
    int o4 = Orientation(r, s, q);

    // first case
    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && OnSegment(p, q, r))
        return true;

    if (o2 == 0 && OnSegment(p, q, s))
        return true;

    if (o3 == 0 && OnSegment(r, s, p))
        return true;

    if (o4 == 0 && OnSegment(r, s, q))
        return true;

    return false;
}

bool SegmentsIntersectUsingCrossProduct(Point p, Point q, Point r, Point s)
{
    int pqr = CrossProduct(Vector{p, q}, Vector{p, r});
    int pqs = CrossProduct(Vector{p, q}, Vector{p, s});
    int rsp = CrossProduct(Vector{r, s}, Vector{r, p});
    int rsq = CrossProduct(Vector{r, s}, Vector{r, q});

    // cross-products are in opposite directions i.e. negative
    // or product of clockwise and counter-clockwise vectors
    if ((pqr * pqs < 0) && (rsp * rsq < 0))
    {
        return true;
    }

    // if one of the endpoint lies on the other segment
    // i.e cross-product is 0 and it exists on the segment

    /*
    For example vector pq and pr are collinear and r exists on segment pq

                 s
                 .
                 .
                 .
         p . . . q,r
    */
    if (pqr == 0 && OnSegment(p, q, r))
        return true;

    /*
    For example vector pq and ps are collinear and s exists on segment pq

         p . . . q,s
                 .
                 .
                 .
                 r
    */
    if (pqs == 0 && OnSegment(p, q, s))
        return true;

    /*
    For example vector rs and rp are collinear and p exists on segment rs

        s,p . . . q
          .
          .
          .
          r
   */
    if (rsp == 0 && OnSegment(r, s, p))
        return true;
    /*
    For example vector rs and rq are collinear and q exists on segment rs

          p . . . q, s
                  .
                  .
                  .
                  r
   */
    if (rsq == 0 && OnSegment(r, s, q))
        return true;

    return false;
}

TEST(SegmentsIntersectUsingOrientation, TestCase1)
{
    Point p{1, 1};
    Point q{10, 1};
    Point r{1, 2};
    Point s{10, 2};
    EXPECT_EQ(SegmentsIntersectUsingOrientation(p, q, r, s), false);

    p = Point{10, 0};
    q = Point{0, 10};
    r = {0, 0};
    s = {10, 10};
    EXPECT_EQ(SegmentsIntersectUsingOrientation(p, q, r, s), true);

    p = Point{-5, -5};
    q = Point{0, 0};
    r = Point{1, 1};
    s = Point{10, 10};
    EXPECT_EQ(SegmentsIntersectUsingOrientation(p, q, r, s), false);
}

TEST(SegmentsIntersectUsingCrossProduct, TestCase1)
{
    Point p{1, 1};
    Point q{10, 1};
    Point r{1, 2};
    Point s{10, 2};
    EXPECT_EQ(SegmentsIntersectUsingCrossProduct(p, q, r, s), false);

    p = Point{10, 0};
    q = Point{0, 10};
    r = {0, 0};
    s = {10, 10};
    EXPECT_EQ(SegmentsIntersectUsingCrossProduct(p, q, r, s), true);

    p = Point{-5, -5};
    q = Point{0, 0};
    r = Point{1, 1};
    s = Point{10, 10};
    EXPECT_EQ(SegmentsIntersectUsingCrossProduct(p, q, r, s), false);
}