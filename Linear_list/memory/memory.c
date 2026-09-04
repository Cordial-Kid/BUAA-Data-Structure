#include<stdio.h>
#include<stdlib.h>

int isPalindrome(int x) {
    int reversed = 0;
    while (x > reversed) {
        reversed = reversed * 10 + x %  10;
        x /= 10;
    }
    return x == reversed || x == reversed / 10;
}