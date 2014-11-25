#ifndef _png_hpp_
#define _png_hpp_

#include <png.h>
#include <util.hpp>

inline unsigned char* read_png(char* path, int& width,
                               int& height, int& channels)
{
    unsigned char color_type;
    unsigned char bit_depth;
    FILE* fp;
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep* row_pointers;
    unsigned char* buf = 0;
    unsigned char* hbuf = 0;
    char header[8];

    fp = fopen(path, "rb");
    if(!fp)
        goto fopen_failed;

    fread(header, 1, 8, fp);
    if(png_sig_cmp(header, 0, 8))
        goto fopen_failed;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr)
        goto png_create_write_struct_failed;

    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
        goto png_create_write_struct_failed;

    if(setjmp(png_jmpbuf(png_ptr)))
        goto png_failure;

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    channels = png_get_channels(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if(setjmp(png_jmpbuf(png_ptr)))
        goto png_failure;

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++)
        row_pointers[y] = (unsigned char*) malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, row_pointers);
    buf = (unsigned char*) malloc(width * height * channels);
    hbuf = buf;
    for(int y = 0; y < height; y++, buf += width * channels)
        memcpy(buf, row_pointers[y], width * channels);

png_failure:
png_create_info_struct_failed:
    png_destroy_read_struct(&png_ptr, 0, 0);
png_create_write_struct_failed:
    fclose(fp);
fopen_failed:

    return hbuf;
}

inline image* read_png(char* path)
{
    if(access(path, F_OK) == -1)
        return 0;

    image* i = 0;
    image img;
    unsigned char* data = read_png(path, img.width, img.height, img.channels);
    if(data)
    {
        i = (image*) calloc(sizeof(image), 1);
        memcpy(i, &img, sizeof(img));
        i->data = data;
    }

    return i;
}


//PNG_COLOR_TYPE_RGB PNG_COLOR_TYPE_RGBA
inline int save_png(int type, const unsigned char* buffer, int width,
                    int height, const char* pathf, ...)
{
    float* a;
    png_unknown_chunk foNT;
    png_byte* chunk_names = "foNT";
    char* path = NULL;
    va_list args;
    va_start(args, pathf);
    vasprintf(&path, pathf, args);
    va_end(args);

    FILE* fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    int x, y;
    unsigned char** row_pointers = NULL;
    int status = -1;
    int channels = type == PNG_COLOR_TYPE_RGB ? 3 : 4;

    fp = fopen(path, "wb");
    if(!fp)
        return status;

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(png_ptr == NULL)
        goto png_create_write_struct_failed;

    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL)
        goto png_create_info_struct_failed;

    if(setjmp(png_jmpbuf(png_ptr)))
        goto png_failure;

    png_set_IHDR(png_ptr,
                 info_ptr,
                 width,
                 height,
                 8,
                 type,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    row_pointers = (unsigned char**)png_malloc(png_ptr, height * sizeof(unsigned char*));
    for(y = 0; y < height; ++y)
    {
        unsigned char* row = (unsigned char*) png_malloc(png_ptr, sizeof(unsigned char) * width * channels);
        row_pointers[y] = row;
        memcpy(row, buffer, width * channels);
        buffer += width * channels;
    }

    png_init_io(png_ptr, fp);

    png_text title_text;
    title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    title_text.key = "Author";
    title_text.text = "Tom Brinkman";
    png_set_text(png_ptr, info_ptr, &title_text, 1);
    title_text.key = "License";
    title_text.text = "Tom Brinkman All Rights Reserved";
    //png_set_text(png_ptr, info_ptr, &title_text, 1);

    static int siz = sizeof(float) * 2;
    a = (float*) malloc(siz);
    for(int n = 0; n < 2; ++n)
        a[n] = n;
    foNT.name[0] = 'f';
    foNT.name[1] = 'o';
    foNT.name[2] = 'N';
    foNT.name[3] = 'T';
    foNT.name[4] = 0;
    foNT.size = siz;
    foNT.data = (png_byte*) a;
    //png_set_keep_unknown_chunks(png_ptr, PNG_HANDLE_CHUNK_ALWAYS, chunk_names, 1);
    //png_set_unknown_chunk_location(png_ptr, info_ptr, 0, PNG_HAVE_IHDR);
    //png_set_unknown_chunks(png_ptr, info_ptr, &foNT, 1);

    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
    status = 0;

    for(y = 0; y < height; y++)
        png_free(png_ptr, row_pointers[y]);
    png_free(png_ptr, row_pointers);

png_failure:
png_create_info_struct_failed:
    png_destroy_write_struct(&png_ptr, &info_ptr);
png_create_write_struct_failed:
    fclose(fp);
fopen_failed:
    free(path);

    return status;
}

inline void is_png(const char*, const char* path, void* app_, node<message*>** errors)
{
    static const int PNG_BYTES_TO_CHECK = 4;
    char buf[PNG_BYTES_TO_CHECK];

    FILE* fp;
    if((fp = fopen(path, "rb")) == NULL)
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);

    if(fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "not png - %s", path);

    if(png_sig_cmp(buf, (png_size_t)0, PNG_BYTES_TO_CHECK))
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "not png - %s", path);
}

inline void echo_png(const char*, const char* path, void* app_, node<message*>** errors)
{
    FILE* fp;
    if((fp = fopen(path, "rb")) == NULL)
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);

    for(int n = 0; n < 100; ++n)
    {
        char buf[1];
        if(fread(buf, 1, 1, fp))
            printf("%x %c\n", buf[0], buf[0]);
    }

}

#endif

