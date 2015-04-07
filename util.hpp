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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
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
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <libgen.h>
#include <functional>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <syslog.h>
#include <algorithm>
#include <float.h>
#include <memory>
#include <fnmatch.h>
#include <functional>
#include <map>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

static const char* const COPYRIGHT = "copyright (c) 2013 Tom Brinkman";
static const char* const REFERENCENAME = "Reportbase";
static const char* const WEBNAME = "reportbase.net";

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
static const unsigned int        HISTORY_SIZE = 0x1 << 8; //256
static const unsigned int        BEKCHARTCOLS = 40;
static const unsigned int        OPTION_FLAG_DEFAULT = 0x1 << 0; //1
static const unsigned int        OPTION_FLAG_IN_MAIN = 0x1 << 1; //2
static const unsigned int        OPTION_FLAG_REVERSE = 0x1 << 2; //4
static const unsigned int        OPTION_FLAG_NO_ARG = 0x1 << 3; //8
static const unsigned int        OPTION_FLAG_FILENAME = 0x1 << 4; //16
static const unsigned int        OPTION_FLAG_OPTIONAL_ARG = 0x1 << 5; //32
static const unsigned int        OPTION_FLAG_NOALIAS = 0x1 << 6; //64
static const unsigned int        OPTION_FLAG_DUAL_ARG = 0x1 << 7; //128
static const unsigned int        OPTION_FLAG_TRIP_ARG = 0x1 << 8; //256
static const unsigned int        OPTION_FLAG_HIDDEN = 0x1 << 9; //512
extern const char*               APPLICATION;
extern const char*               WEBSITE;
extern const char*               SUMMARY;
extern const char*               EXAMPLE;
extern const char*               USAGE;
extern const int                 MAJORVERSION;
extern const int                 MINORVERSION;
extern const int                 PATCHVERSION;
extern int*                      VERBOSE;

enum class option_type
{
    none,
    string,
    integer,
    flag,
    callback,
    system,
    filename,
    string_array,
    filename_array,
    decimal,
    integer64,
};

struct point
{
    int x;
    int y;
};

struct color
{
    char name[LABEL_SIZE];
    int red;
    int green;
    int blue;
    int hue;
    int sat;
    int val;
};

struct rectangle
{
    short x;
    short y;
    short width;
    short height;
};

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

struct image
{
    int width;
    int height;
    int channels;
    int left;
    int right;
    int top;
    int bottom;
    unsigned char* data;
};

template <typename type_t>
struct array
{
    type_t* data;
    int size;
};

template <typename type_t>
struct node
{
    type_t data;
    node<type_t>* next;
};

template <typename type_t>
struct queue
{
    node<type_t>* head;
    node<type_t>* tail;
};

struct option
{
    char name[OPTION_NAME];
    char short_name;
    int flags;
    option_type arg;
    void* arg_data;
    void* user_data;
    const char* description;
    const char* arg_description;
    const char* dflt;
    void* unused2;
    const char* arg1;
    const char* arg2;
    const char* arg3;
};

typedef array<option> options_t;

struct font
{
    char path[MAX_PATH];
    int size;
};

struct market
{
    char name[NAME_SIZE];
    char title[TITLE_SIZE];
    char url[TITLE_SIZE];
    char url2[TITLE_SIZE];
};

struct application
{
    unsigned char** symbols;
    int symbolsn;
    image** fonts;
    char* name;
    char* title;
    char* describe;
};

struct option_user
{
    option* options;
    int optionsn;
    void* user_data;
};

typedef void (*option_callback2)(const char*, const char*, void*, node<message*>**);
typedef void (*option_callback3)(const char*, const char*, const char*, void*, node<message*>**);

inline void push_tail(node<char*>** a, const char* format, ...)
{
    node<char*>* n = (node<char*>*)calloc(1, sizeof(node<char*>));
    if(*a)
        (*a)->next = n;
    va_list args;
    va_start(args, format);
    vasprintf(&n->data, format, args);
    va_end(args);
    *a = n;
}

inline void push_head(node<char*>** a, const char* format, ...)
{
    node<char*>* n = (node<char*>*)malloc(sizeof(node<char*>));
    n->next = *a;
    va_list args;
    va_start(args, format);
    vasprintf(&n->data, format, args);
    va_end(args);
    *a = n;
}

inline int writef(int fd, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char* str = 0;
    vasprintf(&str, format, args);
    va_end(args);
    return write(fd, str, strlen(str));
}

inline int compare_namelst(const void* _a, const void* _b)
{
    const market* a = (market*) _a;
    const market* b = (market*) _b;
    return strcmp(a->name, b->name);
}

template <typename type_t, typename key_t> inline
type_t binary_search(type_t begin, int size, key_t key, int (funct)(key_t, type_t))
{
    type_t end = begin + size;
    while(begin < end)
    {
        int n = (end - begin) / 2.0;
        const type_t type = begin + n;
        int result = funct(key, type);
        if(result == 0)
            return type;
        else if(result > 0)
            begin = type + 1;
        else
            end = type;
    }
    return 0;
}

inline void push_tail(queue<char*>* q, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char* str = 0;
    vasprintf(&str, format, args);
    va_end(args);
    if(!q->head)
    {
        push_tail(&q->head, str);
        q->tail = q->head;
    }
    else
    {
        push_tail(&q->tail, str);
    }
}

template <typename type_t>
inline node<type_t>* push_tail(queue<type_t>* q)
{
    node<type_t>* n = (node<type_t>*)calloc(1, sizeof(node<type_t>));
    if(!q->tail)
    {
        q->head = n;
        q->tail = n;
    }
    else
    {
        q->tail->next = n;
        q->tail = n;
    }
    return n;
}

inline char* combstr(const char* format, ...)
{
    char* str = NULL;
    va_list args;
    va_start(args, format);
    vasprintf(&str, format, args);
    va_end(args);
    int size = strlen(str);
    char* buffer = 0;
    if(!(buffer = (char*)malloc(size + 1)))
        return NULL;
    memcpy(buffer, str, size);
    buffer[size] = 0;
    return buffer;
}

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

inline void echo_string(node<char*>* head, FILE* file = stderr)
{
    while(head)
    {
        node<char*>* next = head->next;
        fprintf(file, "%s\n", head->data);
        head = next;
    }
}

inline void echo_string(node<char*>* head, int fd)
{
    static const char* eol = "\n";

    while(head)
    {
        node<char*>* next = head->next;
        write(fd, head->data, strlen(head->data));
        write(fd, eol, strlen(eol));
        head = next;
    }
}

inline int free_messages(node<message*>* head)
{
    int messagesn = 0;
    for(node<message*>* msg = head; msg; ++messagesn)
    {
        node<message*>* save = msg;
        msg = msg->next;
        free(save->data->message);
        free(save->data);
        free(save);
    }

    return messagesn;
}

int echo_messages(node<message*>* head, FILE* file = stderr);


static const unsigned int               PARSE_SKIPBLANKS = 0x1 << 1;//2
static const unsigned int               PARSE_SKIPCOMMENTS = 0x1 << 2;//4

inline int next_token(const char** start, const char** end, char delim)
{
    if(!*end)
        *end = *start;
    else if(!** end)
        return 0;
    else
        *start = ++*end;
    while(**end &&** end != delim)
        ++*end;
    return 1;
}

inline char** tokenizer(const char* string, char delim, int& size, int options = 0)
{
    const char* start = string;
    const char* end = NULL;
    char** data = 0;
    size = 0;
    int n = 0;
    while(next_token(&start, &end, delim))
    {
        int ts = end - start;

        if(options & PARSE_SKIPBLANKS && ts == 0)
            continue;

        if(options & PARSE_SKIPCOMMENTS && start[0] == '#')
            continue;

        data = (char**) realloc(data, sizeof(char*) * (size + 1));
        data[size] = (char*) malloc(sizeof(char) * (ts + 1));
        strncpy(data[size], start, ts);
        data[size][ts] = '\0';
        size++;
    }
    return data;
}

inline unsigned char* memreplicate(unsigned char* buffer, int size, int extent)
{
    unsigned char* out = 0;
    if(!(out = (unsigned char*) calloc(1, extent)))
        return 0;
    unsigned char* hout = out;
    int b = extent / size;
    for(int m = 0; m < b; ++m, out += size)
        memcpy(out, buffer, size);
    int r = extent - (out - hout);
    memcpy(out, buffer, r);
    return hout;
}

template <typename type_t> inline
type_t* load_buffer(const char* path, int& size)
{
    int fd = open(path, O_RDONLY);
    if(fd == -1)
        return 0;

    read(fd, &size, sizeof(int));
    type_t* buffer = (type_t*) malloc(sizeof(type_t) * size);
    read(fd, buffer, sizeof(type_t) * size);
    close(fd);
    return buffer;
}

template <typename type_t> inline
void save_buffer(const char* path, const type_t* type, int typen, node<message*>** errors)
{
    int fd = open(path, O_WRONLY | O_CREAT, S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH);
    if(fd == -1)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    write(fd, &typen, sizeof(int));
    write(fd, type, typen * sizeof(type_t));
    close(fd);
}

inline bool is_fatal(node<message*>** in)
{
    node<message*>* head = *in;
    while(head)
    {
        node<message*>* next = head->next;
        message* data = head->data;
        if(data->fatal)
            return true;
        head = next;
    }

    return false;
}

inline void command_line(int args, char** argv,
                         option* options, int optionsn, void* user_data, node<message*>** errors);
void echo_version(const char* a, const char* b, void*, node<message*>**);
void echo_help(const char*, const char*, void* user_data, node<message*>** errors);
void abort(const char* fmt, ...);
unsigned char* load_binary(const char* path, int* size, node<message*>** errors);

template <typename type_t> inline
type_t* get_array(node<type_t>* head, int* size_)
{
    int size = count_nodes(head);
    type_t* out = (type_t*)malloc(sizeof(type_t) * size);
    *size_ = size;
    int n = 0;
    while(head)
    {
        node<type_t>* next = head->next;
        out[n++] = head->data;
        head = next;
    }
    return out;
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

inline void release(queue<char*>* q)
{
    for(node<char*>* path = q->head; path;)
    {
        node<char*>* tpath = path;
        path = path->next;
        free(tpath->data);
        free(tpath);
    }
}

inline char* get_unix_safe_name(char* str)
{
    int size = strlen(str);
    for(int n = 0; n < strlen(str); ++n)
        if(str[n] == '/')
            str[n] = '-';
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

inline image* get_subimage(const image* const img, int x, int y, int width, int height)
{
    image* out = (image*)malloc(sizeof(image));
    out->width = width;
    out->height = height;
    out->channels = img->channels;
    out->data = (unsigned char*) malloc(width * height * img->channels);

    unsigned char* odata = img->data + (y * img->width * img->channels) + (x * out->channels);
    unsigned char* hdata = out->data;

    for(int k = 0; k < height; ++k)
    {
        memcpy(hdata, odata, width * img->channels);
        hdata += width * img->channels;
        odata += img->width * img->channels;
    }

    return out;
}

inline image* get_subimage(const image* img, rectangle rect)
{
    return get_subimage(img, rect.x, rect.y, rect.width, rect.height);
}

inline char** get_folder_paths(const char* path, const char* pattern, int type, int& filesn)
{
    DIR* dir;
    if(!(dir = opendir(path)))
        return 0;

    char** files = 0;
    struct dirent* ent;
    while((ent = readdir(dir)))
    {
        if(ent->d_type != type)
            continue;

        if(!strcmp(pattern, "*") ||
                !fnmatch(pattern, ent->d_name, 0))
        {
            char fpath[MAX_PATH];
            sprintf(fpath, "%s/%s", path, ent->d_name);

            files = (char**) realloc(files, sizeof(char*) * (filesn + 1));
            files[filesn] = (char*) malloc(strlen(fpath));
            strcpy(files[filesn], fpath);
            filesn++;
        }
    }

    closedir(dir);
    return files;
}

inline void* lsearchz(void* key, void* base, int n, int elemsize, int (funct)(void*, void*))
{
    for(int i = 0; i < n; ++i)
    {
        void* elemaddr = (char*)base + i * elemsize;
        if(!funct(key, elemaddr))
            return elemaddr;
    }

    return 0;
}

inline int strcmpz(const char** x, const char** y)
{
    return (strcmp(*x, *y));
}

inline char* load_file(const char* pathf, ...)
{
    char* path = NULL;
    va_list args;
    va_start(args, pathf);
    vasprintf(&path, pathf, args);
    va_end(args);

    int fd = open(path, O_RDONLY);
    if(fd == -1)
        return 0;

    struct stat file_info;
    fstat(fd, &file_info);
    if(!S_ISREG(file_info.st_mode))
    {
        close(fd);
        return 0;
    }

    int size = sizeof(char) * file_info.st_size;
    char* str = (char*)malloc(size + 1);
    read(fd, str, size);
    str[size] = '\0';
    close(fd);
    return str;
}

inline char** load_file_lines(const char* const path, int& n)
{
    char* str;
    if(!(str = load_file(path)))
        return 0;

    char** pstr = tokenizer(str, '\n', n, PARSE_SKIPBLANKS | PARSE_SKIPCOMMENTS);
    free(str);
    return pstr;
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

inline void command_line(int args, char** argv,
                  option* options, int optionsn, void* user_data, node<message*>** errors)
{
    int n = 1;
    for(; n < (int) args; ++n)
    {
        int m = 0;
        for(; m < optionsn; ++m)
        {
            option* o = &options[m];
            char shortname[3];
            shortname[0] = '-';
            shortname[1] = o->short_name;
            shortname[2] = '\0';
            char longname[OPTION_NAME + 2];
            strcpy(longname, "--");
            strcat(longname, o->name);
            if(strcmp(argv[n], shortname) && strcmp(argv[n], longname))
                continue;

            if(o->arg == option_type::system)
            {
                option_user a = {options, optionsn, user_data};
                (* (option_callback2) o->arg_data)(
                    o->name, argv[n + 1], (void*)&a, errors);
                n++;
                break;
            }
            else if(o->arg == option_type::system &&
                    o->flags & OPTION_FLAG_NO_ARG)
            {
                option_user a = {options, optionsn, user_data};
                (* (option_callback2) o->arg_data)(
                    o->name, NULL, (void*)&a, errors);
                break;
            }
            else if(o->arg == option_type::decimal && (n != (args - 1)))
            {
                *(float**)o->arg_data = (float*)malloc(sizeof(float));
                float val = atof(argv[n + 1]);
                memcpy(*(float**)o->arg_data, &val, sizeof(float));
                n++;
                break;
            }
            else if(o->arg == option_type::string && (n != (args - 1)))
            {
                *(char**)o->arg_data = (char*)malloc(sizeof(char) * strlen(argv[n + 1]));
                strcpy(*(char**)o->arg_data, argv[n + 1]);
                n++;
                break;
            }
            else if(o->arg == option_type::flag)
            {
                *(int**)o->arg_data = (int*)malloc(sizeof(int));
                break;
            }
            else if(o->arg == option_type::integer && (n != (args - 1)))
            {
                *(int**)o->arg_data = (int*)malloc(sizeof(int));
                int val = atoi(argv[n + 1]);
                memcpy(*(int**)o->arg_data, &val, sizeof(int));
                n++;
                break;
            }
            else if(o->arg == option_type::callback &&
                    o->flags & OPTION_FLAG_NO_ARG)
            {
                (* (option_callback2) o->arg_data)(
                    o->name, NULL, user_data, errors);
                break;
            }
            else if(o->arg == option_type::callback &&
                    o->flags & OPTION_FLAG_DUAL_ARG &&
                    (n != (args - 2)))
            {
                (* (option_callback2) o->arg_data)(
                    argv[n + 1], argv[n + 2], user_data, errors);

                n += 2;
                break;
            }
            else if(o->arg == option_type::callback &&
                    o->flags & OPTION_FLAG_TRIP_ARG &&
                    (n != (args - 3)))
            {
                (* (option_callback3) o->arg_data)(
                    argv[n + 1], argv[n + 2], argv[n + 3], user_data, errors);
                n += 3;
                break;
            }
            else if(n != (args - 1))
            {
                (* (option_callback2) o->arg_data)(
                    o->name, argv[n + 1], user_data, errors);
                n++;
                break;
            }
        }

        if(is_fatal(errors))
            return false;

        if(m == optionsn)
        {
            push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "invalid option - %s", argv[n]);
            return false;
        }
    }
}

inline void echo_version(const char* a, const char* b, void*, node<message*>**)
{
    fprintf(stdout, "%s %d.%d.%d\n", APPLICATION, MAJORVERSION, MINORVERSION, PATCHVERSION);
    fprintf(stdout, "%s\n", WEBSITE);
    fprintf(stdout, "%s\n", COPYRIGHT);
    fprintf(stdout, "%s\n", SUMMARY);
    fprintf(stdout, "%s\n", USAGE);
    fprintf(stdout, "%s\n", EXAMPLE);
    exit(EXIT_SUCCESS);
}

inline void echo_help(const char*, const char*, void* user_data, node<message*>** errors)
{
    const options_t* o = (options_t*) user_data;
    fprintf(stdout, "%s %d.%d.%d\n", APPLICATION, MAJORVERSION, MINORVERSION, PATCHVERSION);
    fprintf(stdout, "%s\n", WEBSITE);
    fprintf(stdout, "%s\n", COPYRIGHT);
    fprintf(stdout, "%s\n", SUMMARY);
    fprintf(stdout, "%s\n", USAGE);
    fprintf(stdout, "%s\n\n", EXAMPLE);
    fprintf(stdout, "Options:\n");
    for(int m = 0; m < o->size; ++m)
    {
        const option* option = &o->data[m];
        if(option->flags & OPTION_FLAG_HIDDEN)
            continue;

        int args = 1;
        if(option->flags & OPTION_FLAG_NO_ARG)
            args = 0;
        else if(option->flags & OPTION_FLAG_DUAL_ARG)
            args = 2;

        fprintf(stdout, "%30s %2c  %s. %s (%d)\n", option->name,
                option->short_name ? option->short_name : ' ',
                option->description, option->arg_description, args);
    }

    exit(EXIT_SUCCESS);
}

inline void abort(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    exit(1);
}

inline unsigned char* load_binary(const char* path, int* size, node<message*>** errors)
{
    int fd = open(path, O_RDONLY);
    if(fd == -1)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__,
                     "error: %s, %s", path, strerror(errno));
        return 0;
    }

    struct stat file_info;
    if(fstat(fd, &file_info) == -1)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__,
                     "error: %s, %s", path, strerror(errno));
        close(fd);
        return 0;
    }

    if(!S_ISREG(file_info.st_mode))
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__,
                     "Invalid path: %s", path);
        close(fd);
        return 0;
    }

    unsigned char* buffer = (unsigned char*)malloc(file_info.st_size + 1);
    if(!buffer)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad memory: %s", path);
        close(fd);
        return 0;
    }

    read(fd, buffer, file_info.st_size);
    close(fd);

    if(size)
        *size = file_info.st_size;

    return buffer;
}


inline int compare_color(const void* pkey, const void* pelem)
{
    const char* key = (char*) pkey;
    const color* clr = (color*) pelem;
    return strcmp(key, clr->name);
}

inline int sort_colors(const void* x, const void* y)
{
    const color* xx = (color*) x;
    const color* yy = (color*) y;
    return strcmp(xx->name, yy->name);
}

inline void convertToUpperCase(char* str)
{
    int ch, i;
    for(i = 0; i < strlen(str); i++)
    {
        ch = toupper(str[i]);
        str[i] = ch;
    }
}

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
