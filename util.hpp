/*!
 *  (C) 2010 Tom Brinkman
 *
 * Use, modification and distribution is subject to the accompanying license file LICENSE_1_0.txt, Version 1.0.
 * (See http://www.reportbase.com/LICENSE_1_0.txt)
 *
 * \file   util.hpp
 * \brief  C Utility functions
 */

#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <stdarg.h>
#include <cmath>
#include <stdint.h>
#include <limits>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <algorithm>
#include <memory>
#include <fnmatch.h>
#include <functional>
#include <map>

static const char                ASCII_BEGIN = ' ';
static const char                ASCII_END = '~';
static const int                 LETTERSIZE = 'Z' - 'A' + 1; //26
static const unsigned int        OPTION_STRING_SIZE = 0x1 << 8; //256
static const unsigned short      LABEL_SIZE = 0x1 << 7; //128
static const unsigned short      TITLE_SIZE = 0x1 << 6; //64
static const unsigned short      FULL_NAME_SIZE = 0x1 << 6; //64
static const unsigned short      OPTION_NAME = 0x1 << 5; //32
static const unsigned int        MAX_PATH = 0x1 << 8; //256
static const unsigned int        MAX_EXCHANGE_SYMBOLS = 0x1 << 15; //32768
static const unsigned int        LARGE_TEXT_BUFFER = 0x1 << 10; //1024
static const unsigned int        ASCII_COUNT = ASCII_END - ASCII_BEGIN + 1;
static const unsigned int        TEXT_BUFFER = 0x1 << 8; //256
static const unsigned int        NAME_SIZE = 0x1 << 4; //16
static const unsigned int        HISTORY_SIZE = 256; //256
static const unsigned int        BEKCHARTCOLS = 160;

struct message
{
    int domain;
    int code;
    char file[MAX_PATH];
    char function[MAX_PATH];
    int line;
    int fatal;
    char* message;
};

template <typename type_t>
struct node
{
    type_t data;
    node<type_t>* next;
};

inline void push_message(node<message*>** head, int domain, int code, int fatal,
                         const char* file, const char* function, int line, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    node<message*>* oldhead = *head;
    message* error = (message*)calloc(1, sizeof(message));
    *head = (node<message*>*)calloc(1, sizeof(node<message*>));
    error->domain = domain;
    error->code = code;
    error->fatal = fatal;
    if(function)
        strcpy(error->function, function);
    if(file)
        strcpy(error->file, file);
    error->line = line;
    vasprintf(&error->message, format, args);
    va_end(args);
    (*head)->data = error;
    (*head)->next = oldhead;
}

inline char* get_string_from_file(FILE* file = stdin)
{
    static const int inputBufSize = 1024;
    char* msg = NULL;
    int msgBytes = 0;
    int inputMsgBufSize = 0;
    char inputBuffer[inputBufSize];
    int bytesRead = 0;
    int n = 0;
    while((bytesRead = fread(
                           inputBuffer,            // target buffer
                           1,                      // number of buffer-sized elements to read
                           sizeof(inputBuffer),    // number of bytes in buffer
                           file)) > 0)
    {
        char* tmp = (char*) realloc(msg, inputMsgBufSize + bytesRead + 1);
        msg = tmp;
        memmove(&msg[inputMsgBufSize], inputBuffer, bytesRead);
        inputMsgBufSize += bytesRead;
    }

    if(inputMsgBufSize)
        msg[inputMsgBufSize] = '\0';
    return msg;
}

inline char* get_string_from_file(char* path, node<message*>** errors)
{
    FILE* file = fopen(path, "r");
    if(!file)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "invalid path: %s", path);
        return 0;
    }

    char* str;
    if(!(str = get_string_from_file(file)))
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "invalid path: %s", path);
        return 0;
    }

    fclose(file);
    return str;
}

inline char* get_safe_name(char* str)
{
    int size = strlen(str);
    for(int n = 0; n < strlen(str); ++n)
        if(!isalnum(str[n]))
            str[n] = ' ';
    return str;
}

inline int get_safe_size(const float* a, int size)
{
    int m = 0;
    for(; m < size; ++m)
        if(isnan(a[m]) || isinf(a[m]))
            break;
    return m;
}

inline int echo_messages(node<message*>* head, FILE* file = stderr)
{
    int messagesn = 0;
    char** messages = NULL;

    node<message*>* hsave = head;
    while(head)
    {
        node<message*>* next = head->next;
        int n = 0;
        for(; n < messagesn; ++n)
            if(!strcmp(head->data->message, messages[n]))
                break;

        if(n == messagesn)
        {
            messages = (char**)realloc(messages, (messagesn + 1) * sizeof(char*));
            int isize = strlen(head->data->message) + 1;
            messages[messagesn] = (char*)malloc(isize * sizeof(char));
            strcpy(messages[messagesn], head->data->message);
            fprintf(file, "%s %s,%s,%d\n", messages[messagesn], head->data->file,
                    head->data->function, head->data->line);
            messagesn++;
        }

        head = next;
    }

    int n = 0;
    for(; n < messagesn; ++n)
        free(messages[n]);
    free(messages);
    return messagesn;
}

inline char* remove_slash(char* str)
{
    int size = strlen(str);
    for(int n = 0; n < strlen(str); ++n)
        if(str[n] == '/')
            str[n] = '-';
    return str;
}


template <typename type_t>
struct pod
{
    type_t operator()()
    {
        type_t type;
        memset(&type, 0, sizeof(type_t));
        return type;
    }

    template <typename T1>
    type_t operator()(T1 t1)
    {
        type_t type = {t1};
        return type;
    }

    template <typename T1, typename T2>
    type_t operator()(T1 t1, T2 t2)
    {
        type_t type = {t1, t2};
        return type;
    }

    template <typename T1, typename T2, typename T3>
    type_t operator()(T1 t1, T2 t2, T3 t3)
    {
        type_t type = {t1, t2, t3};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4)
    {
        type_t type = {t1, t2, t3, t4};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
    {
        type_t type = {t1, t2, t3, t4, t5};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
    {
        type_t type = {t1, t2, t3, t4, t5, t6};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
    {
        type_t type = {t1, t2, t3, t4, t5, t6, t7};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
    {
        type_t type = {t1, t2, t3, t4, t5, t6, t7, t8};
        return type;
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    type_t operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
    {
        type_t type = {t1, t2, t3, t4, t5, t6, t7, t8, t9};
        return type;
    }
};

struct echo
{
    void operator()(const float* a, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f\n", n, a[n]);
    }

    void operator()(const float* a, const float* b, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f%15.5f\n", n, a[n], b[n]);
    }

    void operator()(const float* a, const float* b, const float* c, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f%15.5f%15.5f\n", n, a[n], b[n], c[n]);
    }

    void operator()(const float* a, const float* b, const float* c, const float* d, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f%15.5f%15.5f%15.5f\n", n, a[n], b[n], c[n], d[n]);
    }

    void operator()(const float* a, const float* b, const float* c, const float* d, const float* e, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f%15.5f%15.5f%15.5f%15.5f\n", n, a[n], b[n], c[n], d[n], e[n]);
    }

    void operator()(const float* a, const float* b, const float* c, const float* d,
                    const float* e, const float* f, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f%15.5f%15.5f%15.5f%15.5f%15.5f\n", n, a[n], b[n], c[n], d[n], e[n], f[n]);
    }

    void operator()(const float* a, const float* b, const float* c, const float* d,
                    const float* e, const float* f, const float* g, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f%15.5f%15.5f%15.5f%15.5f%15.5f%15.5f\n", n, a[n], b[n], c[n], d[n], e[n], f[n], g[n]);
    }

    void operator()(const float* a, const float* b, const float* c, const float* d,
                    const float* e, const float* f, const float* g, const float* h, int size)
    {
        for(int n = 0; n < size; ++n)
            printf("%15d%15.5f%15.5f%15.5f%15.5f%15.5f%15.5f%15.5f%15.5f\n",
                   n, a[n], b[n], c[n], d[n], e[n], f[n], g[n], h[n]);
    }
};

#endif
