#include <assert.h>
#include <stdio.h>

int mystrpunktcmp(const char *str1, const char *str2) {
    while (42) {
        if (*str1 && (*str1 == '.'
                    || *str1 == ','
                    || *str1 == ':'
                    || *str1 == ';'
                    || *str1 == '!'
                    || *str1 == '?')) {
            ++str1;
            continue;
        }
        if (*str2 && (*str2 == '.'
                    || *str2 == ','
                    || *str2 == ':'
                    || *str2 == ';'
                    || *str2 == '!'
                    || *str2 == '?')) {
            ++str2;
            continue;
        }
        if (*str1 && *str2 && *str1 == *str2) {
            ++str1;
            ++str2;
            continue;
        } else {
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
    }
}

/*
void test_mystrpunktcmp() {
    assert(mystrpunktcmp("", "") == 0);
    assert(mystrpunktcmp("", "a") < 0);
    assert(mystrpunktcmp("a", "") > 0);
    assert(mystrpunktcmp("a", "b") < 0);
    assert(mystrpunktcmp("b", "a") > 0);
    assert(mystrpunktcmp("abc", "abc") == 0);
    assert(mystrpunktcmp("ABC", "ABCD") < 0);
    assert(mystrpunktcmp("ABCD", "ABC") > 0);

    assert(mystrpunktcmp("", ".") == 0);
    assert(mystrpunktcmp("", ",") == 0);
    assert(mystrpunktcmp("", ":") == 0);
    assert(mystrpunktcmp("", ";") == 0);
    assert(mystrpunktcmp("", "!") == 0);
    assert(mystrpunktcmp("", "?") == 0);
    assert(mystrpunktcmp(".", "") == 0);
    assert(mystrpunktcmp(",", "") == 0);
    assert(mystrpunktcmp(":", "") == 0);
    assert(mystrpunktcmp(";", "") == 0);
    assert(mystrpunktcmp("?", "") == 0);
    assert(mystrpunktcmp("!", "") == 0);
    assert(mystrpunktcmp("", "a") < 0);
    assert(mystrpunktcmp("a", "") > 0);
    assert(mystrpunktcmp("a", "b") < 0);
    assert(mystrpunktcmp("b", "a") > 0);
    assert(mystrpunktcmp("abc", "abc") == 0);
    assert(mystrpunktcmp("ABC", "ABCD") < 0);
    assert(mystrpunktcmp("!ABCD", "ABC") > 0);
    assert(mystrpunktcmp("ABCD", "!ABC") > 0);
    assert(mystrpunktcmp("!ABCD", "?ABC") > 0);
    assert(mystrpunktcmp("?ABCD", "!ABC") > 0);
    fprintf(stderr, "OK\n");
}

int main() {
    test_mystrpunktcmp();
}
*/
