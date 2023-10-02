
#include <gtest/gtest.h>

/*
Currying is the transformation of a function with multiple arguments
into a sequence of single-argument functions. That means converting a
function like this f(a, b, c, ...) into a function like this f(a)(b)(c)

Currying helps you avoid passing the same variable multiple times,
and it helps you create a higher order function

Write a function, add_subtract, which alternately adds and subtracts
curried arguments. Here are some sample operations:

add_subtract(7) -> 7

add_subtract(1)(2)(3) -> 1 + 2 - 3 -> 0

add_subtract(-5)(10)(3)(9) -> -5 + 10 - 3 + 9 -> 11

*/

class AddSubtractFunctor
{
private:
    int result{0};
    bool isAdd{true};

public:
    void Reset(int i)
    {
        result = i;
        isAdd = true;
    }
    AddSubtractFunctor &operator()(int i)
    {

        if (isAdd)
        {
            result += i;
        }
        else
        {
            result -= i;
        }

        isAdd = !isAdd;

        return *this;
    }

    operator int()
    {
        return result;
    }
};

/* Limitation: not thread-safe */
AddSubtractFunctor &add_subtract(int i)
{
    static AddSubtractFunctor functor;
    functor.Reset(i);
    return functor;
}

TEST(AddSubtractCurrying, TestCase1)
{
    int result = add_subtract(7)(1);
    EXPECT_EQ(result, 8);
}
