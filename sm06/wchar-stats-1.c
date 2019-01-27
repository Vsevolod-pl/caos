#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdio.h>

int main() {
    wchar_t c;
    int digit_count = 0, lower_count = 0, upper_count = 0;
    setlocale(LC_ALL, "");
    while ((c = fgetwc(stdin)) != EOF) {
        if (iswdigit(c)) {
            ++digit_count;
        }
        if (iswlower(c)) {
            ++lower_count;
        }
        if (iswupper(c)) {
            ++upper_count;
        }
    }
    printf("%d\n%d\n%d\n", digit_count, upper_count, lower_count);
}
