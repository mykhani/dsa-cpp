/*
Given an unsigned 8-bit integer, swap its even and odd bits.
The 1st and 2nd bit should be swapped, the 3rd and 4th bit
should be swapped, and so on. For example:

x = 10101010
Output:
    01010101

x = 11100010
Output:
    11010001

Bonus if you can do this in one line?
*/

#include <gtest/gtest.h>

uint8_t SwapEvenOddBits(const uint8_t &x)
{
    // mask to extract odd bits  0x10101010 i.e. 0xAA
    // mask to extract even bits 0x01010101 i.e. 0x55
    // extract odd bits, shift to right
    // extract even bits, shift to left
    // swapped!
    return uint8_t((x & 0xAA) >> 1) | uint8_t((x & 0x55) << 1);
}

TEST(SwapEvenOddBits, TestCase1)
{
    // 0x10101010 becomes 0x01010101
    EXPECT_EQ(SwapEvenOddBits(0xAA), 0x55);
    EXPECT_EQ(SwapEvenOddBits(0xE2), 0xD1);
}