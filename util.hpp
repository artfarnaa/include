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
#include <regex.h>
#include "pod.hpp"
#include "echo.hpp"
#include "rgb.hpp"

#define JOIN24(R,G,B) R << 16 | G << 8 | B
#define JOIN32(R,G,B,A) A << 24 | R << 16 | G << 8 | B
#define JOIN4(K) K[0] << 24 | K[1] << 16 | K[2] << 8 | K[3]
#define MIN3(x,y,z)  ((y) <= (z) ?  ((x) <= (y) ? (x) : (y)) : ((x) <= (z) ? (x) : (z)))
#define MAX3(x,y,z)  ((y) >= (z) ?  ((x) >= (y) ? (x) : (y)) : ((x) >= (z) ? (x) : (z)))

static const char* const EMAILADDRESS = "tom.brinkman@reportbase.com";
static const char* const HOMEURL = "http://www.reportbase.net";
static const char* const GENURLPATH = "http://www.reportbase.net/gen/";
static const char* const SERVERPATH = "/srv/http/";
static const char* const SYMBOLSPATH = "/srv/http/symbols/";
static const char* const FONTSPATH = "/srv/http/fonts/";
static const char* const GENPATH = "/srv/http/";
static const char* const IGNOREPATH = "/srv/http/repos/ignore";
static const char* const COPYRIGHT = "copyright (c) 2013 Tom Brinkman";
static const char* const REFERENCENAME = "Reportbase";
static const char* const WEBNAME = "reportbase.net";
static const char* const FONTBINPATH = "/srv/http/gen/fonts";
static const char* const SYMBOLPACKPATH = "/srv/http/gen/sympack";

static const char                ASCII_BEGIN = ' ';
static const char                ASCII_END = '~';
static const int                 LETTERSIZE = 'Z' - 'A' + 1; //26
static const unsigned int        OPTION_STRING_SIZE = 0x1 << 8; //256
static const unsigned short      LABEL_SIZE = 0x1 << 7; //128
static const unsigned short      TITLE_SIZE = 0x1 << 8; //256
static const unsigned short      FULL_NAME_SIZE = 0x1 << 6; //64
static const unsigned short      OPTION_NAME = 0x1 << 5; //32
static const unsigned int        MAX_PATH = 0x1 << 8; //256
static const unsigned int        MAX_EXCHANGE_SYMBOLS = 0x1 << 15; //32768
static const unsigned int        LARGE_TEXT_BUFFER = 0x1 << 10; //1024
static const unsigned int        ASCII_COUNT = ASCII_END - ASCII_BEGIN + 1;
static const unsigned int        TEXT_BUFFER = 0x1 << 8; //256
static const unsigned int        NAME_SIZE = 0x1 << 5; //32
static const unsigned int        HISTORY_SIZE = 0x1 << 8; //256
static const unsigned int        BEKCHARTCOLS = 40;
static const unsigned int        BEKCHARTCOLS20 = 20;
static const unsigned int        MAX_SIZE = 0x1 << 8; //256
static const unsigned int        BEKVALUES = 0x1 << 6; //64
static const unsigned int        SECONDS_PER_DAY = 86400;
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
static const unsigned int        OPTION_FLAG_ARG2_OPTIONAL = 0x1 << 10; //1024
static const unsigned int        YOHLCV_SIZE = 7;
static const unsigned int        LEFT = 0x1 << 1;//2
static const unsigned int        CENTER = 0x1 << 2;//4
static const unsigned int        RIGHT = 0x1 << 3;//8
static const unsigned int        TOP = 0x1 << 4;//16
static const unsigned int        MIDDLE = 0x1 << 5;//32
static const unsigned int        HALFCENTER = 0x1 << 6; //64
static const unsigned int        BOTTOM = 0x1 << 7;//128
static const unsigned int        HALFBOTTOM = 0x1 << 8; //256
static const unsigned int        HALFPUSH = 0x1 << 10; //1024
static const unsigned int        HORIZONTAL = 0x1 << 11; //2056
static const unsigned int        HALFTOP = 0x1 << 12; //4096
static const unsigned int        OFFSET1 = 0x1 << 13;
static const unsigned int        NOCLIP = 0x1 << 14;
static const unsigned int        UPPER = 0x1 << 1;
static const int                 GIA_MAX = 500;
static const int                 SYMBOL_MAX = 5000;
static const int                 FIRSTLAYOUT = 440;
extern const char*               APPLICATION;
extern const char*               WEBSITE;
extern const char*               SUMMARY;
extern const char*               EXAMPLE;
extern const char*               USAGE;
extern const int                 MAJORVERSION;
extern const int                 MINORVERSION;
extern const int                 PATCHVERSION;
extern int*                      VERBOSE;
extern int*                      GIAWIDTH;
extern int*                      GIAHEIGHT;
extern int*                      AVAHEIGHT;
extern int*                      ZOEWIDTH;
extern int*                      FLOHEIGHT;
extern int*                      CHARTHEIGHT;
extern int*                      METASET;

#ifdef DEBUG
#define FPRINTF(fd, ...) fprintf (fd, __VA_ARGS__)
#define SPRINTF(path, ...) sprintf(path, __VA_ARGS__);
#define FREOPEN(path, fd) fd = freopen(path, "w", fd);
#define FCLOSE(fd) fclose(fd);
#define WRITEF(fd, ...) writef(fd, __VA_ARGS__);
#else
#define FPRINTF(fd, ...)
#define SPRINTF(path, ...)
#define FREOPEN(path, fd)
#define FCLOSE(fd)
#define WRITEF(fd, ...)
#endif

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

enum
{
    IMAGE_LAYOUT,//0
    IMAGE_HELP,//1
    IMAGE_HAL,//2
    IMAGE_IND,//3
    IMAGE_SIZE
};

enum
{
    COLOR_LINE1,
    COLOR_LINE2,
    COLOR_LINE3,
    COLOR_ZOESCROLLBACK,
    COLOR_ZOENUBACK,
    COLOR_BEKSCROLLBACK,
    COLOR_BEKNUBACK,
    COLOR_IMAGEBACK,
    COLOR_AVATEXT,
    COLOR_AVATEXTBK,
    COLOR_SIZE
};

enum
{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

enum
{
    STATE_DEFAULT,
    STATE_CURRENT,
    STATE_SELECTED,
    STATE_ENABLED,
    STATE_SELECTEDCURRENT,
    STATE_SELECTEDENABLED,
    STATE_CURRENTENABLED,
    STATE_SELECTEDCURRENTENABLED,
    STATE_SIZE
};

enum
{
    FEEDTYPE_ROC,
    FEEDTYPE_FI,
    FEEDTYPE_DPO,
    FEEDTYPE_AVG,
    FEEDTYPE_DIFF,
    FEEDTYPE_DIV,
    FEEDTYPE_AVG3,
    FEEDTYPE_TR,
    FEEDTYPE_TL,
    FEEDTYPE_RC,
    FEEDTYPE_FC,
    FEEDTYPE_AVG4,
    FEEDTYPE_CLV,
    FEEDTYPE_OBV,
    FEEDTYPE_WMA,
    FEEDTYPE_EMA,
    FEEDTYPE_SMA,
    FEEDTYPE_MIN,
    FEEDTYPE_MAX,
    FEEDTYPE_MULT,
    FEEDTYPE_MULTC,
    FEEDTYPE_SUB,
    FEEDTYPE_SUBC,
    FEEDTYPE_ADD,
    FEEDTYPE_ADDC,
    FEEDTYPE_RS,
    FEEDTYPE_STDEV,
    FEEDTYPE_CCI,
    FEEDTYPE_ULTOSC,
    FEEDTYPE_NDM,
    FEEDTYPE_PDM,
    FEEDTYPE_ACCDIST,
    FEEDTYPE_CMF,
    FEEDTYPE_BOL,
    FEEDTYPE_BOLL_PER,
    FEEDTYPE_STOCH,
    FEEDTYPE_WILL_PER,
    FEEDTYPE_PVT,
    FEEDTYPE_STOCHRSI,
    FEEDTYPE_MFR,
    FEEDTYPE_PSYLINE,
    FEEDTYPE_INDEX,
    FEEDTYPE_DEFAULT,
    FEEDTYPE_SIZE,
};

enum
{
    FEEDGROUP_1,
    FEEDGROUP_2,
    FEEDGROUP_3,
    FEEDGROUP_4,
    FEEDGROUP_5,
    FEEDGROUP_6,
};

enum
{
    FEED_YMD,
    FEED_OPEN,
    FEED_HIGH,
    FEED_LOW,
    FEED_CLOSE,
    FEED_VOLUME,
    FEED_UNUSED100,
    FEED_CHANGE,
    FEED_ROC,
    FEED_TL,
    FEED_TP,
    FEED_TPA16,
    FEED_CCI16,
    FEED_FI,
    FEED_WC,
    FEED_CLV,
    FEED_RS14,
    FEED_CLOSESMA16,
    FEED_CLOSESMA50,
    FEED_CLOSESMA16PENV,
    FEED_CLOSESMA16NENV,
    FEED_CLOSEEMA12,
    FEED_CLOSEEMA16,
    FEED_CLOSEEMA26,
    FEED_CLOSEEMA32,
    FEED_TYPICALPRICESMA16,
    FEED_TYPICALPRICESMA32,
    FEED_CLOSEROC16,
    FEED_CLOSSEROC8,
    FEED_VOLUMEEMA16,
    FEED_VOLUMEEMA32,
    FEED_RSI14,
    FEED_LOW16,
    FEED_HIGH16,
    FEED_RMF,
    FEED_BP,
    FEED_CLOSESTDEV16,
    FEED_DPO16,
    FEED_APO1632,
    FEED_UNUSED101,
    FEED_PPO1632,
    FEED_MACD1226,
    FEED_UNUSED102,
    FEED_ACCDIST,
    FEED_ACCDISTEMA3,
    FEED_ACCDISTEMA10,
    FEED_CHAIKINOSCILL310,
    FEED_MEAN,
    FEED_PVOSIGNAL16329,
    FEED_PPOSIGNAL16329,
    FEED_STOCHRSI,
    FEED_FIEMA16,
    FEED_MOM10,
    FEED_ONBALANCEVOLUME,
    FEED_MACDSIGNAL12269,
    FEED_STOCH16,
    FEED_STOCHSMA163,
    FEED_STOCHSMA1633,
    FEED_STDEVSMA16,
    FEED_UPPERBOLLINGER1616,
    FEED_LOWERBOLLINGER1616,
    FEED_BOLLINGER1616,
    FEED_BOLLWIDTH1616,
    FEED_MACDHIST12269,
    FEED_WILLIAMSPERC1616,
    FEED_UNUSED103,
    FEED_MFI14,
    FEED_TRUERANGE,
    FEED_UNUSED104,
    FEED_UNUSED105,
    FEED_UNUSED106,
    FEED_UNUSED107,
    FEED_UNUSED108,
    FEED_TEST,
    FEED_UNUSED109,
    FEED_UNUSED110,
    FEED_SIZE
};

enum
{
    GRAPH_RSI14,
    GRAPH_MA50CANDLE,
    GRAPH_MACD12269,
    GRAPH_HIGHAREA,
    GRAPH_HIGHBARS,
    GRAPH_VOLUMELINE,
    GRAPH_MA1632OHLC2,
    GRAPH_MA1632OHLC,
    GRAPH_UNUSED,
    GRAPH_MA1632HLC,
    GRAPH_PPO16329,
    GRAPH_ROC16,
    GRAPH_WILLIAMS16,
    GRAPH_OBV,
    GRAPH_CMF,
    GRAPH_MFI15,
    GRAPH_FI,
    GRAPH_TR,
    GRAPH_BOLLINGER1616,
    GRAPH_BOLPERC,
    GRAPH_BOLLWIDTH,
    GRAPH_STDEV,
    GRAPH_ACCDIST,
    GRAPH_PVO4,
    GRAPH_CHAIKINOSCILL310,
    GRAPH_STOCHRSI1,
    GRAPH_FASTSTO,
    GRAPH_SLOWSTO,
    GRAPH_SMAENV,
    GRAPH_KELTNERUP,
    GRAPH_PRICECHAN16,
    GRAPH_ATR,
    GRAPH_CCI16,
    GRAPH_ULTOSC,
    GRAPH_DPO,
    GRAPH_MA50CANDLE10,
    GRAPH_SIZE
};

enum
{
    METASET_TINY,
    METASET_SMALL,
    METASET_MEDIUM,
    METASET_MEDIUM_LARGE,
    METASET_LARGE,
    METASET_VER_LARGE,
    METASET_HUGE,
    METASET_SIZE
};

struct point
{
    int x;
    int y;
};

typedef pod<point> point_t;

struct fundamental
{
    char symbol[NAME_SIZE];//0
    char name[NAME_SIZE];//1
    char sector[NAME_SIZE];//2
    char industry[NAME_SIZE];//3
    char pe[NAME_SIZE];//4
    char eps[NAME_SIZE];//5
    char divyield[NAME_SIZE];//6
    char shares[NAME_SIZE];//7
    char dps[NAME_SIZE];//8
    char peg[NAME_SIZE];//9
    char pts[NAME_SIZE];//10
    char ptb[NAME_SIZE];//11
};

struct ind
{
    char name[NAME_SIZE];
    char title[TITLE_SIZE];
};

struct technical
{
    char symbol[NAME_SIZE];//0
    char previous[NAME_SIZE];//1
    char change[NAME_SIZE];//2
    char volumechange[NAME_SIZE];//3
    char weekhigh[NAME_SIZE];//4
    char weeklow[NAME_SIZE];//5
    char weekchange[NAME_SIZE];//6
    char avgweekchange[NAME_SIZE];//7
    char avgweekvolume[NAME_SIZE];//8
    char monthhigh[NAME_SIZE];//9
    char monthlow[NAME_SIZE];//10
    char monthchange[NAME_SIZE];//11
    char avgmonthchange[NAME_SIZE];//12
    char avgmonthvolume[NAME_SIZE];//13
    char yearhigh[NAME_SIZE];//14
    char yearlow[NAME_SIZE];//15
    char yearchange[NAME_SIZE];//16
    char avgyearchange[NAME_SIZE];//17
    char avgyearvolume[NAME_SIZE];//18
    char ma5[NAME_SIZE];//19
    char ma20[NAME_SIZE];//20
    char ma50[NAME_SIZE];//21
    char ma100[NAME_SIZE];//22
    char ma200[NAME_SIZE];//23
    char rsi14[NAME_SIZE];//24
    char sto9[NAME_SIZE];//25
    char wpr14[NAME_SIZE];//26
    char mtm14[NAME_SIZE];//27
    char roc14[NAME_SIZE];//28
    char ptc[NAME_SIZE];//29
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

typedef pod<rectangle> rectangle_t;

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

extern const image* EMAIMAGE;
extern const image* FLOIMAGE;
extern const image* ZOEIMAGE;
extern const char*  EXCHANGE;

typedef pod<image> image_t;

struct imageptr
{
    image** img;
    int size;
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

typedef std::function < int (IplImage* ipl, void* user_data = 0) > panel_t;

struct market
{
    char name[NAME_SIZE];
    char title[TITLE_SIZE];
    char url[TITLE_SIZE];
    char url2[TITLE_SIZE];
};

inline int compare_markets(const void* _a, const void* _b)
{
    const market* a = (market*) _a;
    const market* b = (market*) _b;
    return strcmp(a->name, b->name);
}

const market* const get_marketlst(int& size);
const char* const* const get_feedtypes();

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

inline char* ltrim(char* const s)
{
    int len;
    char* cur;

    if(s && *s)
    {
        len = strlen(s);
        cur = s;

        while(*cur && isspace(*cur))
            ++cur, --len;

        if(s != cur)
            memmove(s, cur, len + 1);
    }

    return s;
}

inline char* rtrim(char* const s)
{
    int len;
    char* cur;

    if(s && *s)
    {
        len = strlen(s);
        cur = s + len - 1;

        while(cur != s && isspace(*cur))
            --cur, --len;

        cur[isspace(*cur) ? 0 : 1] = '\0';
    }

    return s;
}

inline char* trim(char* const s)
{
    rtrim(s);
    ltrim(s);
    return s;
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

typedef void (*option_callback2)(const char*, const char*, void*, node<message*>**);
typedef void (*option_callback3)(const char*, const char*, const char*, void*, node<message*>**);

inline int find_position(const node<char*>* head, const char* str)
{
    int n = 0;
    while(head)
    {
        if(!strcmp(head->data, str))
            break;

        ++n;
        head = head->next;
    }

    return head ? n : -1;
};

template <typename type_t> inline
unsigned char linear_interpolate(type_t alpha, type_t val1, type_t val2)
{
    int size = sizeof(type_t) * 8;
    return ((val1 + 1) * alpha >> size) - ((val2 + 1) * alpha >> size) + val2;
}

template<typename T> inline
T clamp(T Value, T Min, T Max)
{
    return (Value < Min) ? Min : (Value > Max) ? Max : Value;
}

template <typename type_t> inline
bool equiv(const type_t A, const type_t B)
{
    return fabs(A - B) < std::numeric_limits<type_t>::epsilon();
}

template <typename node_t> inline
void reverse(node_t** head)
{
    node_t* prev = 0;
    while(*head)
    {
        node_t* next = (*head)->next;
        (*head)->next = prev;
        prev = *head;
        *head = next;
    }

    *head = prev;
}

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

inline void echo_rectangle(rectangle rect, FILE* file = stderr)
{
    fprintf(file, "%d,%d,%d,%d\n", rect.x, rect.y, rect.width, rect.height);
}

inline void echo_buffer(const unsigned char* buffer, int width, int height, int channels, FILE* file = stderr)
{
    fprintf(file, "%d,%d,%d\n", width, height, width * channels);
    for(int h = 0; h < height ; h++)
    {
        for(int w = 0; w < width * channels; w++)
            fprintf(file, " %02X", *(buffer + w));
        buffer += width * channels;
        fprintf(file, "\n");
    }

    fprintf(file, "\n");
}

inline void echo_image(const image* const i, bool showdata = false, FILE* file = stderr)
{
    fprintf(file, "%d,%d,%d\n", i->width, i->height, i->channels);

    if(showdata)
    {
        unsigned char* data = i->data;
        for(int h = 0; h < i->height ; h++)
        {
            for(int w = 0; w < i->width * i->channels; w++)
                fprintf(file, " %02X", *(data + w));
            data += i->width * i->channels;
            fprintf(file, "\n");
        }
    }

    fprintf(file, "\n");
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

template <typename type_t>
inline bool equiv(const type_t* a, const type_t* b, int size)
{
    int n;
    for(n = 0; n < size; ++n, ++a, ++b)
        if(*a != *b)
            break;
    return n == size;
}

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

inline void extentsplit(float* e, int size, int width)
{
    int empty_slots = 0;
    int awidth = 0;
    for(int n = 0; n < size; ++n)
    {
        if(e[n] < 1)
            e[n] = width * std::abs(e[n]);
        awidth += e[n];
        empty_slots += e[n] == 0 ? 1 : 0;
    }
    if(empty_slots == 0)
        return;
    int balance = width - awidth;
    if(balance <= 0)
        return;
    int slot_extent = (int)((float)balance / (float)empty_slots);
    int remainder = balance - (empty_slots *  slot_extent);
    float* g = e + (size - 1);
    for(int n = 0; n < size; ++n, --g)
    {
        if(*g)
            continue;
        int d = slot_extent;
        if(remainder-- >= 1)
            d++;
        *g = d;
    }
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

inline float normal_scale(float minv, float maxv, float val)
{
    float result = (std::abs(maxv - minv) > 0.001f) ? ((val - minv) / (maxv - minv)) : 0;
    return 1.0f - result;
}

inline float log_scale(float minv, float maxv, float val)
{
    float a = 1;
    float b = (float)log(val) / (float)log(minv);
    float c = (float)log(maxv) / (float)log(minv);
    return normal_scale(a, c, b);
}

inline char* lstrip(char* s)
{
    while(isspace(*s)) ++s;
    return s;
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

/*
DT_BLK      This is a block device.
DT_CHR      This is a character device.
DT_DIR      This is a directory.
DT_FIFO     This is a named pipe (FIFO).
DT_LNK      This is a symbolic link.
DT_REG      This is a regular file.
DT_SOCK     This is a UNIX domain socket.
DT_UNKNOWN  The file type is unknown.
*/

//path - path to files.  not filter.
inline queue<char*>* get_path_queue(const char* path, int type,
                                    int& size, node<message*>** errors = NULL)
{
    DIR* dir;
    if(!(dir = opendir(path)))
    {
        push_message(errors, 0, 0, 1, __FILE__, __PRETTY_FUNCTION__, __LINE__, "bad path: %s", path);
        return 0;
    }

    typedef queue<char*> queue_t;
    queue_t* q = (queue_t*) malloc(sizeof(queue_t));
    memset(q, 0, sizeof(queue_t));

    struct dirent* ent;
    while((ent = readdir(dir)))
    {
        if(ent->d_type != type)
            continue;

        node<char*>* n = (node<char*>*) malloc(sizeof(node<char*>));
        memset(n, 0, sizeof(node<char*>));
        char fpath[MAX_PATH];
        sprintf(fpath, "%s/%s", path, ent->d_name);
        n->data = (char*) malloc(MAX_PATH);
        strcpy(n->data, fpath);
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

        size++;
    }

    closedir(dir);
    return q;
}

struct fixed_rectangle
{
    static rectangle* get(int cols, int rows, int width, int height, int margin);
    rectangle* operator()(int cols, int rows, int width, int height, int margin)
    {
        return fixed_rectangle::get(cols, rows, width, height, margin);
    }
};

struct fitted_rectangle
{
    static rectangle* get(int cols, int rows, int width, int height, int margin);
    rectangle* operator()(int cols, int rows, int width, int height, int margin)
    {
        return fitted_rectangle::get(cols, rows, width, height, margin);
    }
};

struct uniform_rectangle
{
    static rectangle* get(int cols, int rows, int width, int height, int margin);
    rectangle* operator()(int cols, int rows, int width, int height, int margin)
    {
        return uniform_rectangle::get(cols, rows, width, height, margin);
    }
};

struct uniform_fitted_rectangle
{
    static rectangle* get(int cols, int rows, int width, int height, int margin);
    rectangle* operator()(int cols, int rows, int width, int height, int margin)
    {
        return uniform_fitted_rectangle::get(cols, rows, width, height, margin);
    }
};

image** str2imageptr(const image* const fnt, const char* str, int& strn);

inline void binary_split(int* arr, int size, int split)
{
    if(size <= split)
        return;

    arr[size - 1] = true;
    int n = (int)ceil(size / 2.0);
    binary_split(arr, n, split);
    binary_split(arr + n, size - n, split);
}

inline int* get_binary_split(int size, int split, int* out = NULL)
{
    int* arr = (int*) calloc(sizeof(int), size);
    arr[0] = 1;
    binary_split(arr, size, split);
    int* c = (int*) malloc(sizeof(int) * size);
    int* pc = c;
    for(int n = 0; n < size; ++n)
        if(arr[n])
            *pc++ = n;

    if(out)
        *out = pc - c;
    free(arr);
    return c;
}

const image* const get_images();

inline void to_upper(const char* src, char* dst, int size)
{
    for(int n = 0; n < size; ++n)
        dst[n] = toupper(src[n]);
    dst[size] = '\0';
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

inline void release_images(image* i, int n)
{
    image* hi = i;
    for(int g = 0; g < n; ++g, ++i)
        free(i->data);
    free(hi);
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

inline int is_bit_set(unsigned int val, int n)
{
    static unsigned int mask[] =
    {
        1, //0x1 << 0
        2, //0x1 << 1
        4, //0x1 << 2
        8, //0x1 << 3
        16, //0x1 << 4
        32, //0x1 << 5
        64, //0x1 << 6
        128, //0x1 << 7
        256, //0x1 << 8
        512, //0x1 << 9
        1024, //0x1 << 10
        2048, //0x1 << 11
        4096, //0x1 << 12
        8192, //0x1 << 13
        16384, //0x1 << 14
        32768, //0x1 << 15
        65536, //0x1 << 16
    };

    return val & mask[n];
}

point** get_fills(const float* data, float minv, float maxv, int width, int height, int size, int margin);

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

inline bool is_negative(float x)
{
    unsigned int* ui = (unsigned int*)&x;
    return (*ui & 0x80000000) != 0;
}

template<unsigned char b>
struct ByteBits
{
    enum
    {
        COUNT = ((b >> 0) & 1) +
                ((b >> 1) & 1) +
                ((b >> 2) & 1) +
                ((b >> 3) & 1) +
                ((b >> 4) & 1) +
                ((b >> 5) & 1) +
                ((b >> 6) & 1) +
                ((b >> 7) & 1)
    };
};

inline bool ispowerof2(int i)
{
    return i > 0 && (i & (i - 1)) == 0;
}

template <typename point_t> inline
double slope(point_t pt1, point_t pt2)
{
    return (pt1.y - pt2.y) / (double)(pt2.x - pt1.x);
}

inline void shuffle(int* card, int cardsn)
{
    for(int n = 0; n < cardsn; n++)
    {
        int adj = cardsn - n;
        int m = (rand() % adj) + n;
        int tmp = card[n];
        card[n] = card[m];
        card[m] = tmp;
    }
}

inline void reverse_string(char* A)
{
#define SWAPVAR(A,B) (A^=B, B^=A, A^=B)
    char* B = A;
    while(B && *B) ++B;
    for(--B; A < B; ++A, --B) SWAPVAR(*A, *B);
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
    return trim(str);
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

short* get_vertical_nubs(int rows, int nub, int height);
short* get_horizontal_nubs(int cols, int nub, int width);

inline shrink_rectangles(rectangle* rect, int size, int portrait, int landscape)
{
    for(int n = 0; n < size; ++n, ++rect)
    {
        rect->x += landscape;
        rect->y += portrait;
        rect->width -= landscape * 2;
        rect->height -= portrait * 2;
    }
}

#endif
