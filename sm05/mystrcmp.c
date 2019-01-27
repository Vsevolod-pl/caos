#include <assert.h>
#include <stdio.h>

int mystrcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

/*
void test_mystrcmp() {
    assert(mystrcmp("", "") == 0);
    assert(mystrcmp("", "a") < 0);
    assert(mystrcmp("a", "") > 0);
    assert(mystrcmp("a", "b") < 0);
    assert(mystrcmp("b", "a") > 0);
    assert(mystrcmp("abc", "abc") == 0);
    assert(mystrcmp("ABC", "ABCD") < 0);
    assert(mystrcmp("ABCD", "ABC") > 0);
    fprintf(stderr, "OK\n");
}

int main() {
    test_mystrcmp();
}
*/

