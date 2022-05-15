//
// Created by Benedikt on 26.04.2022.
// Copyright 2022, Laminoid.com (Muessig & Muessig GbR).
// Licensed under the terms and conditions of the GPLv3.
//

#ifndef SPRINTPCB_TOKEN_H
#define SPRINTPCB_TOKEN_H

#include "stringbuilder.h"
#include "errors.h"

#include <stdio.h>
#include <stdbool.h>

// true, false, 123, 123/456, TEXT, |string|
typedef enum sprint_tokenizer_state {
    SPRINT_SLICER_STATE_SCANNING,
    SPRINT_SLICER_STATE_INVALID,
    SPRINT_SLICER_STATE_COMMENT,
    SPRINT_SLICER_STATE_WORD,
    SPRINT_SLICER_STATE_NUMBER,
    SPRINT_SLICER_STATE_STRING_START,
    SPRINT_SLICER_STATE_STRING,
    SPRINT_SLICER_STATE_STRING_END,
    SPRINT_SLICER_STATE_VALUE_SEPARATOR,
    SPRINT_SLICER_STATE_TUPLE_SEPARATOR,
    SPRINT_SLICER_STATE_STATEMENT_SEPARATOR,
    SPRINT_SLICER_STATE_STATEMENT_TERMINATOR
} sprint_tokenizer_state;
extern const char* SPRINT_TOKENIZER_STATE_NAMES[];

typedef enum sprint_token_type {
    SPRINT_TOKEN_TYPE_NONE,
    SPRINT_TOKEN_TYPE_INVALID,
    SPRINT_TOKEN_TYPE_WORD,
    SPRINT_TOKEN_TYPE_NUMBER,
    SPRINT_TOKEN_TYPE_STRING,
    SPRINT_TOKEN_TYPE_VALUE_SEPARATOR,
    SPRINT_TOKEN_TYPE_TUPLE_SEPARATOR,
    SPRINT_TOKEN_TYPE_STATEMENT_SEPARATOR,
    SPRINT_TOKEN_TYPE_STATEMENT_TERMINATOR
} sprint_token_type;
extern const char* SPRINT_TOKEN_TYPE_NAMES[];

bool sprint_tokenizer_state_valid(sprint_tokenizer_state state);
sprint_tokenizer_state sprint_tokenizer_state_first(char first_chr);
sprint_tokenizer_state sprint_tokenizer_state_next(sprint_tokenizer_state current_state, char next_chr);
bool sprint_tokenizer_state_idle(sprint_tokenizer_state state);
bool sprint_tokenizer_state_recorded(sprint_tokenizer_state state);
bool sprint_tokenizer_state_complete(sprint_tokenizer_state current_state, sprint_tokenizer_state next_state);
sprint_token_type sprint_tokenizer_state_type(sprint_tokenizer_state state);

extern const char SPRINT_COMMENT_PREFIX;
extern const char SPRINT_STATEMENT_SEPARATOR;
extern const char SPRINT_STATEMENT_TERMINATOR;
extern const char SPRINT_VALUE_SEPARATOR;
extern const char SPRINT_TUPLE_SEPARATOR;
extern const char SPRINT_STRING_DELIMITER;
extern const char* SPRINT_TRUE_VALUE;
extern const char* SPRINT_FALSE_VALUE;

typedef struct sprint_source_origin {
    int line;
    int pos;
    const char* source;
} sprint_source_origin;

typedef struct sprint_token {
    sprint_token_type type;
    sprint_source_origin origin;
} sprint_token;

typedef struct sprint_tokenizer sprint_tokenizer;

struct sprint_tokenizer {
    sprint_source_origin origin;
    bool preloaded;
    bool last_cr;
    bool last_lf;
    bool last_eof;
    char next_chr;
    sprint_tokenizer_state next_state;
    bool (*read)(sprint_tokenizer* tokenizer);
    bool (*close)(sprint_tokenizer* tokenizer);
    union {
        const char* str;
        FILE* file;
    };
};

sprint_tokenizer* sprint_tokenizer_from_str(const char* str, bool free);
sprint_tokenizer* sprint_tokenizer_from_file(const char* path);
sprint_error sprint_tokenizer_next(sprint_tokenizer* tokenizer, sprint_token* output, sprint_stringbuilder* builder);
sprint_error sprint_tokenizer_destroy(sprint_tokenizer* tokenizer);

#endif //SPRINTPCB_TOKEN_H
