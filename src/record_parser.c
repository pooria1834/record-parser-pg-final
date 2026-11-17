#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define INPUT_LIMIT 4096U

/* Read at most INPUT_LIMIT bytes. The destination is sized for that exact bound. */
static int read_input(unsigned char input[INPUT_LIMIT], size_t *length) {
    size_t used = 0U;
    int ch;
    while ((ch = getchar()) != EOF) {
        if (used == INPUT_LIMIT) return 0;
        input[used++] = (unsigned char)ch;
    }
    if (ferror(stdin)) return 0;
    *length = used;
    return 1;
}

static int is_ascii_alnum(const unsigned char *value, size_t length) {
    size_t i;
    for (i = 0U; i < length; ++i) {
        unsigned char c = value[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9'))) return 0;
    }
    return 1;
}

static int parse_record(const unsigned char *input, size_t length) {
    const unsigned char *value;
    size_t value_length;
    if (length < 7U || length > INPUT_LIMIT) return 2;
    if (memchr(input, 0, length) != NULL) return 2;
    if (memcmp(input, "name:", 5U) != 0) return 2;
    if (input[length - 1U] != '\n') return 2;
    if (memchr(input, '\n', length - 1U) != NULL) return 2;
    if (memchr(input, '\r', length) != NULL) return 2;

    value = input + 5U;
    value_length = length - 6U;
    if (value_length == 0U || !is_ascii_alnum(value, value_length)) return 2;

    /* The only difference among variants is the documented length policy below. */
    if ((value_length >= 15U)) return 2;

    /* The rule above must protect the first byte past the logical field.
       The enclosing object keeps the lab probe inside allocated storage. */
    if (value_length > 15U) {
        struct { unsigned char field[1]; unsigned char padding[1]; } storage = {{0U}, {0U}};
        volatile size_t index = 1U;
        volatile unsigned char observed = storage.field[index];
        (void)observed;
    }

    fputs("OK:", stdout);
    (void)fwrite(value, 1U, value_length, stdout);
    fputc('\n', stdout);
    return 0;
}

int main(void) {
    unsigned char input[INPUT_LIMIT];
    size_t length = 0U;
    int result;
    if (!read_input(input, &length)) {
        puts("ERR");
        return 2;
    }
    result = parse_record(input, length);
    if (result != 0) {
        puts("ERR");
        return 2;
    }
    return 0;
}
