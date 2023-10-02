#include <gtest/gtest.h>

/*

You are going on a road trip, and would like to create a suitable music playlist.
The trip will require N songs, though you only have M songs downloaded,
where M < N. A valid playlist should select each song at least once, and guarantee a
buffer of B songs between repeats.

Given N, M, and B, determine the number of valid playlists.

*/

/*
Solution:

This seems like a combination problem

We have N slots and we have to fill them with M objects
A song can only be repeated after B positions. For example
let N=8, M=4 and B=2. Let songs be represented by numbers starting from 0.

0, 1, 2, 3 , 0, 1, 2, 3 is valid as song 0 is repeated after 3 songs
0, 1, 2, 0 , 1, 2, 0, 1 is valid as each song is repeated after 2 songs
So once you select the first song, there should be B songs available
to fill the next B slots.

*/

int ValidPlaylists(int N, int M, int B)
{
    if (M <= B)
    { //
        return 0;
    }
}