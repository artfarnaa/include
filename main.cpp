#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <unistd.h>
#include <ft2build.h>
#include <libgen.h>
#include <png.hpp>
#include <util.hpp>

#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_CACHE_H

const char* APPLICATION = "loki";
const char* WEBSITE = "http://www.reportbase.com";
const char* SUMMARY = "Update reportbase application resources";
const char* USAGE = "loki [options...] [path]";
const char* EXAMPLE = "loki";
const int MAJORVERSION = 1.0;
const int MINORVERSION = 1.0;
const int PATCHVERSION = 1.0;
int* VERBOSE = 0;
int* GIAWIDTH = 0;
int* AVAHEIGHT = 0;
int* GIAHEIGHT = 0;
int* ZOEWIDTH = 0;
int* FLOHEIGHT = 0;
int* CHARTHEIGHT = 0;
int* METASET = 0;

void make_gia_panel(const char*, const char* path, void* app_, node<message*>** errors);
void ohlcv_from_stdin(const char*, const char*, void* app_, node<message*>** errors);
void make_feed_bin(const char*, const char* output, void* app_, node<message*>** errors);
void make_name_bin(const char*, const char* path, void* app_, node<message*>** errors);
void make_history_bin(const char*, const char* path, void* app_, node<message*>** errors);
void echo_bin_octal(const char*, const char* path, void* app, node<message*>** errors);
void echo_base64_encode(const char*, const char* path, void* app_, node<message*>** errors);
void rs32f_test(const char*, const char*, void*, node<message*>** errors);
void ema32f_test(const char*, const char*, void*, node<message*>** errors);
void echo_symbol(const char*, const char*, void* app_, node<message*>** errors);
void init_symbols_default(const char*, const char* path, void* app_, node<message*>** errors);
void is_png(const char*, const char* path, void* app_, node<message*>** errors);
void echo_png(const char*, const char* path, void* app_, node<message*>** errors);
void echo_symbol_data(const char*, const char* path, void* app_, node<message*>** errors);
void make_dogpack(const char*, const char* path, void* app_, node<message*>** errors);
void make_feedpack(const char*, const char* path, void* app_, node<message*>** errors);
void make_homlst_js(const char*, const char* exchange, void* app_, node<message*>** errors);
void eod_parse_feed(const char*, const char* exchange, void* app_, node<message*>** errors);
void echo_csv(const char*, const char* exchange, void* app_, node<message*>** errors);

static option opts[] =
{
    { "help", 'h', OPTION_FLAG_NO_ARG, option_type::system, (void*) echo_help, 0, "Show help", "", 0, 0},
    { "version", 0, OPTION_FLAG_NO_ARG, option_type::callback, (void*) echo_version, 0, "Show version", "", 0, 0},
    { "verbose", 'v', OPTION_FLAG_NO_ARG, option_type::flag, &VERBOSE, 0, "Set verbosity", "", 0, 0},
    { "giawidth", 0, 0, option_type::integer, &GIAWIDTH, 0, "Set verbosity", "", 0, 0},
    { "giaheight", 0, 0, option_type::integer, &GIAHEIGHT, 0, "Set verbosity", "", 0, 0},
    { "avaheight", 0, 0, option_type::integer, &AVAHEIGHT, 0, "Set verbosity", "", 0, 0},
    { "zoewidth", 0, 0, option_type::integer, &ZOEWIDTH, 0, "Set verbosity", "", 0, 0},
    { "FLOHEIGHT", 0, 0, option_type::integer, &FLOHEIGHT, 0, "Set verbosity", "", 0, 0},
    { "chartheight", 0, 0, option_type::integer, &CHARTHEIGHT, 0, "Set verbosity", "", 0, 0},
    { "metaset", 0, 0, option_type::integer, &METASET, 0, "Set verbosity", "", 0, 0},
    { "ohlcv-from-stdin", 0, 0, option_type::callback, (void*) ohlcv_from_stdin, 0, "", "", 0, 0},
    { "echo-bin-octal", 0, 0, option_type::callback, (void*) echo_bin_octal, 0, "", "", 0, 0},
    { "echo-symbol-data", 0, OPTION_FLAG_DUAL_ARG, option_type::callback, (void*) echo_symbol_data, 0, "", "", 0, 0},
    { "echo-base64-encode", 0, 0, option_type::callback, (void*) echo_base64_encode, 0, "", "", 0, 0},
    { "is-png", 0, 0, option_type::callback, (void*) is_png, 0, "", "", 0, 0},
    { "echo-png", 0, 0, option_type::callback, (void*) echo_png, 0, "", "", 0, 0},
    { "make-dogpack", 0, OPTION_FLAG_DUAL_ARG, option_type::callback, (void*) make_dogpack, 0, "", "", 0, 0},
    { "make-feedpack", 0, OPTION_FLAG_NO_ARG, option_type::callback, (void*) make_feedpack, 0, "", "", 0, 0},
    { "make-homlst-js", 0, 0, option_type::callback, (void*) make_homlst_js, 0, "", "", 0, 0},
    { "eod-parse-feed", 0, 0, option_type::callback, (void*) eod_parse_feed, 0, "", "", 0, 0},
    { "echo-csv", 0, 0, option_type::callback, (void*) echo_csv, 0, "", "", 0, 0},
};

int main(int args, char** argv)
{
    setlocale(LC_NUMERIC, "");
    application* app = (application*) calloc(sizeof(application), 1);
    node<message*>* messages = 0;
    command_line(args, argv, opts, sizeof(opts) / sizeof(option), app, &messages);
    return echo_messages(messages);
}

/*
void echo_image_octal(const char*, const char* path, void* app_, node<message*>** errors)
{
    IplImage* ipl;
    if(!(ipl = cvLoadImage(path, CV_LOAD_IMAGE_UNCHANGED)))
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    char szpath[MAX_PATH];
    strcpy(szpath, basename(path));
    szpath[strlen(szpath) - 4] = '\0';
    printf("image %s = \n{\n\t%d,%d,%d,0,0,0,0,\n",
           szpath, ipl->width, ipl->height, ipl->nChannels);

    unsigned char* buffer = (unsigned char*)&ipl->imageData[0];
    for(unsigned long y = 0; y < ipl->height; ++y)
    {
        printf("\t\"");
        unsigned char* buf = buffer;
        for(unsigned long x = 0; x < ipl->width; ++x)
        {
            if(ipl->nChannels == 3)
            {
                unsigned char r = *buf++;
                unsigned char g = *buf++;
                unsigned char b = *buf++;
                printf("\\%o", b);
                printf("\\%o", g);
                printf("\\%o", r);
            }
            else if(ipl->nChannels == 1)
            {
                printf("\\%o", *buf++);
            }
        }
        printf("\"\n");
        buffer += ipl->widthStep;
    }

    printf("};\n\n");
    cvReleaseImage(&ipl);
}
*/

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'
                               };

static int mod_table[] = {0, 2, 1};

char* base64_encode(const unsigned char* data, int input_length, int* output_length)
{
    *output_length = (size_t)(4.0 * ceil((double) input_length / 3.0));
    char* encoded_data = malloc(*output_length);

    for(int i = 0, j = 0; i < input_length;)
    {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for(int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';
    return encoded_data;
}

void echo_base64_encode(const char*, const char* path, void* app_, node<message*>** errors)
{
    int size;
    unsigned char* buffer = load_binary(path, &size, errors);
    if(*errors)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path: %s", path);
        return;
    }

    int len;
    char* str = base64_encode(buffer, size, &len);

    char ch[LARGE_TEXT_BUFFER];
    strncpy(ch, str, len);
    ch[len] = '\0';
    fprintf(stdout, "imageObj.src = \"data:image/png;base64,%s\"\n", ch);

    free(str);
    free(buffer);
}

void echo_bin_octal(const char*, const char* path, void* app_, node<message*>** errors)
{
    int size;
    unsigned char* buffer = load_binary(path, &size, errors);
    if(*errors)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path: %s", path);
        return;
    }

    fprintf(stdout, "%s\n", path);
    for(unsigned long n = 0; n < size; ++n)
        fprintf(stdout, "\\%o", buffer[n]);
    fprintf(stdout, "\n\n");
    free(buffer);
    return 0;
}

int compare_color(const void* pkey, const void* pelem)
{
    const char* key = (char*) pkey;
    const color* clr = (color*) pelem;
    return strcmp(key, clr->name);
}

int sort_colors(const void* x, const void* y)
{
    const color* xx = (color*) x;
    const color* yy = (color*) y;
    return strcmp(xx->name, yy->name);
}

void convertToUpperCase(char* str)
{
    int ch, i;
    for(i = 0; i < strlen(str); i++)
    {
        ch = toupper(str[i]);
        str[i] = ch;
    }
}

/*
image* flatimage(image** i, int size, int mwidth)
{
    int w = 0;
    int h = 0;
    int n = 0;
    for(; n < size; ++n)
    {
        image* p = i[n];
        int right = n < (size - 1) ? p->width : p->right;
        if(mwidth && (w + right) >= mwidth)
            break;

        w += right;
        h = (std::max)(h, p->height);
    }

    size = n;

    image* out = (image*) malloc(sizeof(image));
    memset(out, 0, sizeof(image));
    out->width = w;
    out->height = h;
    out->channels = 1;
    out->data = (unsigned char*) malloc(w * h);
    memset(out->data, 0, w * h);
    unsigned char* data = out->data;
    for(int n = 0; n < size; ++n)
    {
        image* p = i[n];
        int right = n < (size - 1) ? p->width : p->right;
        IppiSize roi = {right, p->height};
        ippiCopy_8u_C1R(p->data, p->width, data, out->width, roi);
        data += right;
    }

    return out;
}
*/

void command_line(int args, char** argv,
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

void echo_version(const char* a, const char* b, void*, node<message*>**)
{
    fprintf(stdout, "%s %d.%d.%d\n", APPLICATION, MAJORVERSION, MINORVERSION, PATCHVERSION);
    fprintf(stdout, "%s\n", WEBSITE);
    fprintf(stdout, "%s\n", COPYRIGHT);
    fprintf(stdout, "%s\n", SUMMARY);
    fprintf(stdout, "%s\n", USAGE);
    fprintf(stdout, "%s\n", EXAMPLE);
    exit(EXIT_SUCCESS);
}

void echo_help(const char*, const char*, void* user_data, node<message*>** errors)
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

void abort(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    exit(1);
}

unsigned char* load_binary(const char* path, int* size, node<message*>** errors)
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

rectangle* uniform_fitted_rectangle::get(int cols, int rows, int width, int height, int margin)
{
    if(width < 0 || height < 0)
        return 0;

    int size = cols * rows;
    int n = 0;
    int y = 0;
    int iheight = height + margin;
    int rwidth = width + margin;
    int ww = (int)(rwidth / (float) cols);
    int hh = (int)(iheight / (float) rows);

    rectangle* rect = (rectangle*) calloc(size, sizeof(rectangle));
    rectangle* hrect = rect;
    int hadj = height - hh * rows + 1;
    int wadj = width - ww * cols + 1;

    for(int row = 0; row < rows; ++row)
    {
        int h = hh - margin;
        int x = 0;
        int wadja = wadj;
        for(int col = 0; col < cols; ++col, ++n, ++rect)
        {
            int w = ww - margin;
            rect->x = x;
            rect->y = y;
            rect->width = w;
            rect->height = h;
            int m = wadja-- > 0 ? 1 : 0;
            x += w + margin + m;
        }

        int m = hadj-- > 0 ? 1 : 0;
        y += h + margin + m;
    }

    return hrect;
}

rectangle* uniform_rectangle::get(int cols, int rows, int width, int height, int margin)
{
    if(width < 0 || height < 0)
        return 0;

    int size = cols * rows;
    int n = 0;
    int y = 0;
    int iheight = height + margin;
    int rwidth = width + margin;
    int ww = (int)(rwidth / (float) cols);
    int hh = (int)(iheight / (float) rows);
    rectangle* rect = (rectangle*) calloc(size, sizeof(rectangle));

    rectangle* hrect = rect;
    for(int row = 0; row < rows; ++row)
    {
        int h = hh - margin;
        int x = 0;
        for(int col = 0; col < cols; ++col, ++n, ++rect)
        {
            int w = ww - margin;
            rect->x = x;
            rect->y = y;
            rect->width = w;
            rect->height = h;
            x += w + margin;
        }

        y += h + margin;
    }

    return hrect;
}

rectangle* fixed_rectangle::get(int cols, int rows,
                                int width, int height, int margin)
{
    if(width < 0 || height < 0)
        return 0;

    int x = 0;
    int y = 0;
    int outn = 0;
    int size = cols * rows;
    rectangle* out = (rectangle*) calloc(size, sizeof(rectangle));

    for(int n = 0; n < rows; ++n)
    {
        for(int m = 0; m < cols; ++m)
        {
            int w = width / cols;
            if(x + w > width)
                w = width - x;

            int h = height / rows;
            if(y + h > height)
                h = height - y;

            rectangle r = {x, y, w, h};
            memcpy(&out[outn++], &r, sizeof(rectangle));
            x += width / cols;
        }

        y += height / rows;
        x = 0;
    }

    return out;
}

rectangle* fitted_rectangle::get(int cols, int rows, int width, int height, int margin)
{
    if(width < 0 || height < 0)
        return 0;

    int size = cols * rows;
    int n = 0;
    int y = 0;
    int iheight = height + margin;
    int rwidth = width + margin;
    int ww = (int)(rwidth / (float) cols);
    int hh = (int)(iheight / (float) rows);
    int xadj = rwidth - (cols * ww);
    int yadj = iheight - (rows * hh);
    rectangle* rect = (rectangle*) malloc(size * sizeof(rectangle));

    rectangle* hrect = rect;
    for(int row = 0; row < rows; ++row)
    {
        int h = hh - margin;
        if(yadj-- >= 1)
            h++;
        int x = 0;
        int xadj_ = xadj;
        for(int col = 0; col < cols; ++col, ++n, ++rect)
        {
            int w = ww - margin;
            if(xadj-- >= 1)
                w++;
            rect->x = x;
            rect->y = y;
            rect->width = w;
            rect->height = h;
            x += w + margin;
        }
        xadj = xadj_;
        y += h + margin;
    }

    return hrect;
}

int echo_messages(node<message*>* head, FILE* file = stderr)
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



