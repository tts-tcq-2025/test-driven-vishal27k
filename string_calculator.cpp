#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_calculator.h"

int starts_with(const char* str, const char* prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void set_default_delimiters(Delimiters* d) {
    strcpy(d->delimiters[0], ",");
    strcpy(d->delimiters[1], "\n");
    d->count = 2;
}


int parse_single_delimiter(const char* ptr, Delimiters* delimiters) {
    delimiters->count = 1;
    delimiters->delimiters[0][0] = ptr[0];
    delimiters->delimiters[0][1] = '\0';
    return 1;
}


int parse_multi_delimiters(const char* ptr, Delimiters* delimiters) {
    int read_chars = 0;
    delimiters->count = 0;

    while (*ptr == '[' && delimiters->count < MAX_DELIMITERS) {
        ptr++; read_chars++;
        int i = 0;
        while (*ptr != ']' && *ptr != '\0' && i < MAX_DELIM_LEN - 1) {
            delimiters->delimiters[delimiters->count][i++] = *ptr++;
            read_chars++;
        }
        if (*ptr != ']') {
            return -1; // malformed
        }
        delimiters->delimiters[delimiters->count][i] = '\0';
        delimiters->count++;
        ptr++; read_chars++;
    }
    return read_chars;
}

const char* parse_delimiters(const char* input, Delimiters* delimiters) {
    if (!starts_with(input, "//")) {
        set_default_delimiters(delimiters);
        return input;
    }
    const char* ptr = input + 2;

    if (*ptr == '[') {
        int chars_read = parse_multi_delimiters(ptr, delimiters);
        if (chars_read < 0) {
            set_default_delimiters(delimiters);
            return input;
        }
        ptr += chars_read;
    } else {
        parse_single_delimiter(ptr, delimiters);
        ptr++;
    }

    if (*ptr == '\n') {
        return ptr + 1;
    }
    set_default_delimiters(delimiters);
    return input;
}

int matches_delimiter(const char* str, const char* delimiter) {
    return strncmp(str, delimiter, strlen(delimiter)) == 0;
}

void process_token(const char* token, AddResult* result) {
    if (*token == '\0') return;

    int num = atoi(token);
    if (num < 0) {
        if (result->negative_count < MAX_NEGATIVES) {
            result->negatives[result->negative_count++] = num;
        }
    } else if (num <= 1000) {
        result->sum += num;
    }
}

AddResult add(const char* input) {
    AddResult result = {0};
    Delimiters delimiters;
    const char* numbers = parse_delimiters(input, &delimiters);

    char buffer[20];
    int buf_index = 0;

    while (*numbers != '\0') {
        int found_delim = 0;
        for (int i = 0; i < delimiters.count; i++) {
            if (matches_delimiter(numbers, delimiters.delimiters[i])) {
                buffer[buf_index] = '\0';
                process_token(buffer, &result);
                buf_index = 0;
                numbers += strlen(delimiters.delimiters[i]);
                found_delim = 1;
                break;
            }
        }
        if (!found_delim) {
            if (isdigit(*numbers) || (*numbers == '-' && buf_index == 0)) {
                buffer[buf_index++] = *numbers++;
            } else {
                // ignore invalid chars like spaces or unexpected symbols
                numbers++;
            }
        }
    }
    buffer[buf_index] = '\0';
    process_token(buffer, &result);

    return result;
}

void print_result(AddResult res) {
    if (res.negative_count > 0) {
        printf("Exception: negatives not allowed: ");
        for (int i = 0; i < res.negative_count; i++) {
            printf("%d", res.negatives[i]);
            if (i != res.negative_count - 1) printf(", ");
        }
        printf("\n");
    } else {
        printf("Sum: %d\n", res.sum);
    }
}
