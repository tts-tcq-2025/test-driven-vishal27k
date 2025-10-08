#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#define MAX_DELIMITERS 10
#define MAX_DELIM_LEN 10
#define MAX_NEGATIVES 50

typedef struct {
    char delimiters[MAX_DELIMITERS][MAX_DELIM_LEN];
    int count;
} Delimiters;

typedef struct {
    int sum;
    int negatives[MAX_NEGATIVES];
    int negative_count;
} AddResult;

const char* parse_delimiters(const char* input, Delimiters* delimiters);

AddResult add(const char* input);

#endif // STRING_CALCULATOR_H
