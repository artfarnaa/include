#ifndef echo_hpp
#define echo_hpp

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
