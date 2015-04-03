#include </opt/intel/ipp/include/ipp.h>

inline IppStatus wma_32f(const float* src, float* dest, int size, int factor)
{
    if(!factor || !size)
        return ippStsBadArgErr;

    float a, c;
    IppStatus status = ippStsNoErr;
    static float w[] = {40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24,
                        23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
                       };

    int wn = sizeof(w) / sizeof(float);
    float* pw = (float*) & w[wn - factor];
    if(status = ippsSum_32f(pw, factor, &a, ippAlgHintFast))
        return status;

    for(int n = 0; n < size; ++n, ++src, ++dest)
    {
        float b[HISTORY_SIZE];
        if((status = ippsMul_32f(src, pw, b, factor)) ||  //pw * src = b
                (status = ippsSum_32f(b, factor, &c, ippAlgHintFast))) //b + factor = c
            return status;
        * dest = c / a;
    }
    return status;
}

inline IppStatus ema_32f(const float* src, float* dest, int size, int factor)
{
    //SMA: 10 period sum / 10
    //Multiplier: (2 / (Time periods + 1) ) = (2 / (10 + 1) ) = 0.1818 (18.18%)
    //EMA: {Close - EMA(previous day)} x multiplier + EMA(previous day).

    int n = size - factor - 1;
    if(n <= 0)
        return ippStsNoErr;

    float k = 2.0f / (factor + 1.0f);
    const float* hout = dest;

    src += n;
    dest += n;

    IppStatus status = ippStsNoErr;
    if(status = ippsMean_32f(src, factor, dest, ippAlgHintFast))
        return status;

    do
    {
        --dest;
        --src;
        *dest = ((*src - * (dest + 1)) * k) + *(dest + 1);
    }
    while(hout != dest);
    return status;
}

inline IppStatus rs_32f(const float* src, float* dest, int size, int factor)
{
    int n = size - factor - 1;
    if(n <= 0)
        return ippStsNoErr;

    float* u = (float*)malloc(sizeof(float) * size);
    float* d = (float*)malloc(sizeof(float) * size);
    ippsSet_32f(std::numeric_limits<float>::quiet_NaN(), u, size);
    ippsSet_32f(std::numeric_limits<float>::quiet_NaN(), d, size);

    for(int m = 0; m < (size - 1); ++m)
    {
        float diff = src[m] - src[m + 1];
        if(diff > 0)
        {
            d[m] = 0;
            u[m] = std::abs(diff);
        }
        else
        {
            d[m] = std::abs(diff);
            u[m] = 0;
        }
    }

    float loss;
    float gain;
    IppStatus status = ippStsNoErr;
    if((status = ippsMean_32f(&d[n], factor, &loss, ippAlgHintFast)) ||
            (status = ippsMean_32f(&u[n], factor, &gain, ippAlgHintFast)))
        return status;

    dest[n] = (std::abs(loss - 0.0f) < 0.01f) ? 100.0f : gain / loss;

    for(int m = n; m >= 0; --m)
    {
        gain = ((gain * (factor - 1)) + u[m]) / factor;
        loss = ((loss * (factor - 1)) + d[m]) / factor;
        dest[m] = (std::abs(loss - 0.0f) < 0.01f) ? 100.0f : gain / loss;
    }

    free(u);
    free(d);
    return  status;
}

inline IppStatus sd_32f(const float* src, float* dest, int size, int days)
{
    float* deviation = (float*)malloc(sizeof(float) * size);

    IppStatus status = ippStsNoErr;
    for(int n = 0; n < size - days + 1; ++n)
    {
        float sum;
        float mean;
        if((status = ippsMean_32f(&src[n], days, &mean, ippAlgHintFast)) || //1) mean
                (status = ippsSubC_32f(&src[n], mean, deviation, days)) ||  //2) mean - src = deviation
                (status = ippsSqr_32f(deviation, deviation, days)) || //3) deviation = deviation*deviation
                (status = ippsSum_32f(deviation, days, &sum, ippAlgHintFast))) //4)  c = sum(b[..])
            break;
        dest[n] = (float)sqrt(sum / (float)days);//5,6) dest = c / days
    }

    free(deviation);
    return status;
}

struct default_feed
{
    IppStatus operator()(float* a, int size)
    {
//echo()(a,size);
        return ippStsNoErr;
    }
};

struct stochastic_feed
{
    const float* close;
    const float* low;
    const float* high;
    IppStatus operator()(float* dest, int size)
    {
        /*
        %K = (Current Close - Lowest Low)/(Highest High - Lowest Low) * 100
                   (close   -    low)   /  (high     -    low)
                            n           /           d

        %D = 3-day SMA of %K
        Lowest Low = lowest low for the look-back period
        Highest High = highest high for the look-back period
        %K is multiplied by 100 to move the decimal point two places
        */

        float n[HISTORY_SIZE];
        float d[HISTORY_SIZE];

        IppStatus status = ippStsNoErr;
        if((status = ippsSub_32f(low, close, n, size)) ||  //close - low = n
                (status = ippsSub_32f(low, high, d, size)) ||  //high - low = d
                (status = ippsDiv_32f(d, n, dest, size)) ||  // n / d = dest
                (status = ippsMulC_32f_I(100.0f, dest, size)))   //dest * 100.0f = dest
        {
        }

        return status;
    }
};

struct williams_feed
{
    const float* close;
    const float* high;
    const float* low;
    IppStatus operator()(float* dest, int size)
    {
        float n[HISTORY_SIZE];
        float d[HISTORY_SIZE];
        IppStatus status;
        if((status = ippsSub_32f(close, high, n, size))  || //high - close = n
                (status = ippsSub_32f(low, high, d, size))  || //high - low = b
                (status = ippsDiv_32f(d, n, dest, size))  || // n / d = dest
                (status = ippsMulC_32f_I(-100.0f, dest, size)))   //dest * -100 = dest
        {
        }
        return status;
    }
};

struct diff_feed
{
    const float* a;
    const float* b;
    float c;
    float d;
    IppStatus operator()(float* dest, int size)
    {
        IppStatus status = ippsSub_32f(b + (int)c, a + (int)d, dest, size); // a - b = dest
//echo()(a,b,dest,size);
        return status;
    }
};

struct avg_feed
{
    const float* a;
    const float* b;
    IppStatus operator()(float* dest, int size)
    {
        IppStatus status;
        if((status = ippsAdd_32f(a, b, dest, size))   || // h + l = d
                (status = ippsDivC_32f(dest, 2.0f, dest, size)))  // dest / 2.0 = dest
        {
        }

        return status;
    }
};

struct div_feed
{
    const float* a;
    const float* b;
    IppStatus operator()(float* dest, int size)
    {
        return ippsDiv_32f(b, a, dest, size); //a / b = dest
    }
};

struct avg3_feed
{
    const float* a;
    const float* b;
    const float* c;
    IppStatus operator()(float* dest, int size)
    {
        float d[HISTORY_SIZE];
        IppStatus status;
        if((status = ippsAdd_32f(a, b, d, size))  || // a + b = d
                (status = ippsAdd_32f(d, c, d, size))  || // d + c = d
                (status = ippsDivC_32f(d, 3.0f, dest, size)))   // d / 3.0 = dest
        {
        }

        return status;
    }
};

struct avg4_feed
{
    const float* a;
    const float* b;
    const float* c;
    const float* d;
    IppStatus operator()(float* dest, int size)
    {
        IppStatus status;
        if((status = ippsAdd_32f(a, b, dest, size)) ||  // a+b = dest
                (status = ippsAdd_32f(c, dest, dest, size)) ||  // c+dest = dest
                (status = ippsAdd_32f(d, dest, dest, size)) ||  // d+dest = dest
                (status = ippsDivC_32f(dest, 4.0f, dest, size))) // dest / 4.0 = dest
        {
        }
        return status;
    }
};

struct tr_feed
{
    const float* h;
    const float* l;
    const float* c;
    IppStatus operator()(float* dest, int size)
    {
        float a[HISTORY_SIZE];
        float b[HISTORY_SIZE];
        float e[HISTORY_SIZE];
        IppStatus status;
        if((status = ippsSub_32f(l, h, a, size)) ||  //h - l = a  High(Today) - Low(Today)
                (status = ippsSub_32f(c + 1, h, b, size)) ||  //h - c1 = b High(Today) - Close(Yesterday)
                (status = ippsSub_32f(c + 1, l, e, size)) ||  //l - c1 = e Low(Today) - Close(Yesterday)
                (status = ippsAbs_32f_I(b, size)) ||
                (status = ippsAbs_32f_I(e, size)))
            return status;
        dest[HISTORY_SIZE - 1] = 0;
        float* ha = a;
        float* hb = b;
        float* he = e;
        for(int n = 0; n < size - 1; ++n, ++ha, ++hb, ++he, ++dest)
            *dest = (std::max)(*ha, (std::max)(*hb, *he));
        return status;
    }
};

struct true_low_feed
{
    const float* l;
    const float* c;
    IppStatus operator()(float* dest, int size)
    {
        for(int n = 0; n < (size - 1); ++n, ++dest, ++l, ++c)
            *dest = (std::min)(*l, *(c + 1));
        return ippStsNoErr;
    }
};

struct roc_feed
{
    const float* a;
    const float* b;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        //((a - b) / b) * 100
        IppStatus status;
        if((status = ippsSub_32f(b + parm, a, dest, size))  || // a - b = dest
                (status = ippsDiv_32f_I(a, dest, size)) ||   //dest / b = dest
                (status = ippsMulC_32f_I(100.0, dest, size)))  //dest * 100 = dest
        {
        }

//echo()(a,b,dest,size);
        return status;
    }
};

struct fi_index
{
    const float* c;
    const float* v;
    IppStatus operator()(float* dest, int size)
    {
        //Force Index = {Close (current period)  -  Close (prior period)} x Volume
        IppStatus status;
        if((status = ippsSub_32f(c + 1, c, dest, size - 1))  || //c - c1 = dest
                (status = ippsMul_32f(dest, v, dest, size - 1))) //dest * v = dest
        {
        }
        return status;
    }
};

struct clv_feed
{
    const float* h;
    const float* l;
    const float* c;
    IppStatus operator()(float* dest, int size)
    {
        float a[HISTORY_SIZE];
        float b[HISTORY_SIZE];
        float f[HISTORY_SIZE];

        // ((c-l)-(h-c))/(h-l)
        // (a-b)/d
        // f/d

        IppStatus status;
        if((status = ippsSub_32f(l, c, a, size))  || //c - l = a
                (status = ippsSub_32f(c, h, b, size))  || //h - c = b
                (status = ippsSub_32f(b, a, f, size))  || //a - b = f
                (status = ippsSub_32f(l, h, dest, size))  || //h - l = dest
                (status = ippsDiv_32f(dest, f, dest, size)))  //f / dest = dest
        {
        }
        return status;
    }
};

struct obv_feed
{
    const float* close;
    const float* volume;
    IppStatus operator()(float* dest, int size)
    {
        float val = 0;
        for(int n = size - 2; n >= 0; --n)
        {
            if(isnan(volume[n]))
                continue;

            if(close[n] > close[n + 1])
                val += volume[n];
            else
                val -= volume[n];
            dest[n] = val;
        }

        return ippStsNoErr;
    }
};

struct wma_feed
{
    const float* a;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        return wma_32f(a, dest, size, parm);
    }
};

struct sma_feed
{
    const float* a;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        IppStatus status = ippStsNoErr;
        for(int n = 0; n < (size - parm); ++n, ++a, ++dest)
            if(status = ippsMean_32f(a, parm, dest, ippAlgHintFast))
                break;
        return status;
    }
};

struct ema_feed
{
    const float* a;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        return ema_32f(a, dest, size, parm);
    }
};

struct min_feed
{
    const float* a;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        IppStatus status = ippStsNoErr;
        for(int n = 0; n < size - parm; ++n, ++a, ++dest)
            if(status = ippsMin_32f(a, parm, dest))
                break;
        return status;
    }
};

struct max_feed
{
    const float* a;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        IppStatus status = ippStsNoErr;
        for(int n = 0; n < size - parm; ++n, ++a, ++dest)
            if(status = ippsMax_32f(a, parm, dest))
                break;
        return status;
    }
};

struct addc_feed
{
    const float* a;
    float b;
    IppStatus operator()(float* dest, int size)
    {
        return ippsAddC_32f(a, b, dest, size);//a + b = dest
    }
};

struct sub_feed
{
    const float* a;
    const float* b;
    IppStatus operator()(float* dest, int size)
    {
        return ippsSub_32f(b, a, dest, size);//b - a = dest
    }
};

struct subc_feed
{
    const float* a;
    float b;
    IppStatus operator()(float* dest, int size)
    {
        return ippsSubC_32f(a, b, dest, size);//b - a = dest
    }
};

struct add_feed
{
    const float* a;
    const float* b;
    IppStatus operator()(float* dest, int size)
    {
        return ippsAdd_32f(a, b, dest, size);//a + b = dest
    }
};

struct multc_feed
{
    const float* a;
    float b;
    IppStatus operator()(float* dest, int size)
    {
        return ippsMulC_32f(a, b, dest, size); //a * b = dest
    }
};

struct mult_feed
{
    const float* a;
    const float* b;
    IppStatus operator()(float* dest, int size)
    {
        return ippsMul_32f(a, b, dest, size);
    }
};

struct rs_feed
{
    const float* a;
    long parm;
    IppStatus operator()(float* dest, int size)
    {
        return rs_32f(a, dest, size, parm);
    }
};

struct stdev_feed
{
    const float* a;
    long parm;
    IppStatus operator()(float* dest, int size)
    {
        return sd_32f(a, dest, size, parm);
    }
};

struct cci_feed
{
    const float* tp;
    const float* tpa;
    float parm;
    int parm1;
    IppStatus operator()(float* dest, int size)
    {
        //CCI = (Typical Price  -  20-period SMA of TP) / (.015 x Mean Deviation)
        //Typical Price (TP) = (High + Low + Close)/3

        float mdev[HISTORY_SIZE];
        float pdev[HISTORY_SIZE];
        float pdest[HISTORY_SIZE];
        for(int n = 0; n < size - parm; ++n)
        {
            float sum = 0;
            for(int m = n; m < n + parm1; ++m)
                sum += std::abs(tp[m] - tpa[n]);
            mdev[n] = sum / parm;
        }

        IppStatus status;
        if((status = ippsMulC_32f(mdev, parm, pdev, size)) || //parm * mdev = pdev
                (status = ippsSub_32f(tpa, tp, pdest, size)) ||  //tp - tpa = pdest
                (status = ippsDiv_32f(pdev, pdest, dest, size)) ||   //dest = pdest / pdev
                (status = ippsMulC_32f_I(100.0f, dest, size)))   //dest * 100.0f = dest
        {
        }

        return status;
    }
};

struct ultoscc_feed
{
    const float* bp;
    const float* tr;
    int periods;
    int periods1;
    int periods2;
    IppStatus operator()(float* dest, int size)
    {
        /*
        BP = Close - Minimum(Low or Prior Close).
        TR = Maximum(High or Prior Close)  -  Minimum(Low or Prior Close)
        Average7 = (7-period BP Sum) / (7-period TR Sum)
        Average14 = (14-period BP Sum) / (14-period TR Sum)
        Average28 = (28-period BP Sum) / (28-period TR Sum)
        UO = 100 x [(4 x Average7)+(2 x Average14)+Average28]/(4+2+1)
        */

        IppStatus status = ippStsNoErr;
        for(int n = 0; n < (size - periods2); ++n, ++bp, ++tr, ++dest)
        {
            float bpsum1, bpsum2, bpsum3, trsum1, trsum2, trsum3;
            if((status = ippsSum_32f(bp, periods, &bpsum1, ippAlgHintFast)) ||
                    (status = ippsSum_32f(bp, periods1, &bpsum2, ippAlgHintFast)) ||
                    (status = ippsSum_32f(bp, periods2, &bpsum3, ippAlgHintFast))  ||
                    (status = ippsSum_32f(tr, periods, &trsum1, ippAlgHintFast))  ||
                    (status = ippsSum_32f(tr, periods1, &trsum2, ippAlgHintFast))  ||
                    (status = ippsSum_32f(tr, periods2, &trsum3, ippAlgHintFast)))
                return status;
            if(!trsum1 || !trsum2 || !trsum3)
            {
                *dest = std::numeric_limits<float>::infinity();
                continue;
            }
            float RawUO = (4 * (bpsum1 / trsum1)) +
                          (2 * (bpsum2 / trsum2)) + (bpsum3 / trsum3);
            *dest = (RawUO / (4 + 2 + 1)) * 100;
        }
        return status;
    }
};

struct pdm_feed
{
    const float* high;
    const float* low;
    IppStatus operator()(float* dest, int size)
    {
        //Positive Directional Movement
        IppStatus status = ippStsNoErr;
        if(status = ippsSet_32f(0, dest, size))
            return status;
        for(int n = 0; n < size - 1; ++n, ++high, ++low, ++dest)
            if((*high - * (high + 1)) > (*(low + 1) - *low))
                *dest = (std::max)(*high - * (high + 1), 0.0f);
        return status;
    }
};

struct ndm_feed
{
    const float* high;
    const float* low;
    IppStatus operator()(float* dest, int size)
    {
        //Negative Directional Movement
        IppStatus status = ippStsNoErr;
        if(status = ippsSet_32f(0, dest, size))
            return status;
        for(int n = 0; n < size - 1; ++n, ++high, ++low, ++dest)
            if((*(low + 1) - *low) > (*high - * (high + 1)))
                *dest = (std::max)(*(low + 1) - *low, 0.0f);
        return status;
    }
};

struct stochrsi_feed
{
    const float* rsi;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        // stochrsi = (RSI - Lowest Low RSI) / (Highest High RSI - Lowest Low RSI)
        float h[HISTORY_SIZE];
        float l[HISTORY_SIZE];
        float n[HISTORY_SIZE];
        float d[HISTORY_SIZE];

        min_feed mins = {rsi, parm};
        max_feed maxs = {rsi, parm};
        mins(l, size);
        maxs(h, size);

        IppStatus status;
        if((status = ippsSub_32f(l, h, d, size - parm)) ||  //h - l = d
                (status = ippsSub_32f(l, rsi, n, size - parm)) ||  //rsi - l = n
                (status = ippsDiv_32f(d, n, dest, size - parm))) //n / d = dest
        {
        }

        return status;
    }
};

struct dpo_feed
{
    const float* close;
    const float* sma;
    int parm;
    IppStatus operator()(float* dest, int size)
    {
        //Price {X/2 + 1} periods ago less the X-period simple moving average.
        //DPO(20) equals price 11 days ago less the 20-day SMA

        int a = parm / (float)2 + 1;
        IppStatus status;
        if((status = ippsSub_32f(sma, close + a, dest, size))) //p - p[11] = dest
        {
        }

        return status;
    }
};

struct bollpercentage_feed
{
    const float* close;
    const float* upper;
    const float* lower;
    IppStatus operator()(float* dest, int size)
    {
        float n[HISTORY_SIZE];
        float d[HISTORY_SIZE];
        IppStatus status = ippStsNoErr;
        if((status = ippsSub_32f(lower, close, n, size)) ||  //close - lower = n
                (status = ippsSub_32f(lower, upper, d, size))  || //upper - lower = d
                (status = ippsDiv_32f(d, n, dest, size)))   //n / d = dest
        {
        }

        return status;
    }
};

struct bollinger_feed
{
    const float* mean;
    const float* stdev;
    long parm;
    IppStatus operator()(float* dest, int size)
    {
        IppStatus status = ippStsNoErr;
        if((status = ippsMulC_32f(stdev, parm, dest, size)) ||  //STDEV * periods = dest
                (status = ippsAdd_32f_I(mean, dest, size)))   //dest + mean = dest
        {
        }

        return status;
    }
};

struct cmf_feed
{
    const float* clv;
    const float* volume;
    int periods;
    IppStatus operator()(float* dest, int size)
    {
        ////(close-low)-(high-close)/(high-low)
        //1. Money Flow Multiplier = [(Close  -  Low) - (High - Close)] /(High - Low)
        //2. Money Flow Volume = Money Flow Multiplier x Volume for the Period
        //3. CMF = Sum of Money Flow Volume / Sum of Volume
        float sad;
        float sv;
        float ad[HISTORY_SIZE];
        IppStatus status;
        if(status = ippsMul_32f(clv, volume, ad, size))
            return status;

        for(int n = 0; n < size - periods; ++n)
        {
            if((status = ippsSum_32f(&ad[n], periods, &sad, ippAlgHintFast)) ||
                    (status = ippsSum_32f(&volume[n], periods, &sv, ippAlgHintFast)))
                break;
            dest[n] = sv > 0 ? (sad / sv) : std::numeric_limits<float>::infinity();
        }

        return status;
    }
};

struct accdist_feed
{
    const float* clv;
    const float* v;
    IppStatus operator()(float* dest, int size)
    {
        ////(close-low)-(high-close)/(high-low)
        //1. Money Flow Multiplier = [(Close  -  Low) - (High - Close)] /(High - Low)
        //2. Money Flow Volume = Money Flow Multiplier x Volume for the Period
        //3. ADL = Previous ADL + Current Period's Money Flow Volume

        const float* hout = dest;
        float val = 0;
        float had[HISTORY_SIZE];
        float* ad = &had[0];
        IppStatus status;
        if(status = ippsMul_32f(clv, v, ad, size)) //v * clv = ad
            return status;
        dest += size;
        ad += size;
        do
        {
            --ad;
            --dest;
            val += *ad;
            *dest = val;
        }
        while(dest != hout);
        return status;
    }
};

struct index_feed
{
    const float* a;
    IppStatus operator()(float* dest, int size)
    {
        float b[HISTORY_SIZE];
        IppStatus status;
        if((status = ippsSet_32f(100, b, size)) ||
                (status = ippsAddC_32f(a, 1.0f, dest, size)) ||  //a + 1 = dest
                (status = ippsDiv_32f(dest, b, dest, size)) ||  //b / dest = dest
                (status = ippsSub_32f(dest, b, dest, size)))   //b - dest = dest
        {
        }
        return status;
    }
};

struct psyline_feed
{
    const float* c;
    int periods;
    IppStatus operator()(float* dest, int size)
    {
        for(int n = 0; n < (size - periods); ++n, ++dest)
        {
            int u = 0;
            for(int m = n; m < (n + periods); ++m)
                if(c[m] > 0)
                    u++;
            *dest = (float)u / (float)periods;
        }
        return ippStsNoErr;
    }
};

struct pvt_feed
{
    const float* close;
    const float* volume;
    IppStatus operator()(float* dest, int size)
    {
        float pvt = 0;
        for(int n = size - 1; n >= 1; --n)
        {
            pvt += volume[n] * ((close[n] - close[n + 1]) / close[n + 1]);
            dest[n] = pvt;
        }
        return ippStsNoErr;
    }
};

struct mfr_feed
{
    const float* tp;
    const float* vol;
    long periods;
    IppStatus operator()(float* dest, int size)
    {
        //money flow ratio
        float rmf[HISTORY_SIZE];
        float pmf[HISTORY_SIZE];
        float nmf[HISTORY_SIZE];
        float pmfs[HISTORY_SIZE];
        float nmfs[HISTORY_SIZE];
        memset(&rmf, 0, sizeof(rmf));
        memset(&pmf, 0, sizeof(pmf));
        memset(&nmf, 0, sizeof(nmf));
        memset(&nmfs, 0, sizeof(nmfs));
        memset(&pmfs, 0, sizeof(nmfs));

        IppStatus status;
        if(status = ippsMul_32f(tp, vol, rmf, size)) //tp * vol = rmf
            return status;

        for(int n = 0; n < (size - 1); ++n)
        {
            if(tp[n] > tp[n + 1])
                pmf[n] = rmf[n];
            else
                nmf[n] = rmf[n];
        }

        for(int n = 0; n < (size - periods); ++n)
        {
            if((status = ippsSum_32f(&pmf[n], periods, &pmfs[n], ippAlgHintFast)) ||
                    (status = ippsSum_32f(&nmf[n], periods, &nmfs[n], ippAlgHintFast)))
                return status;
        }

        return ippsDiv_32f(nmfs, pmfs, dest, (size - periods));
    }
};

struct chaikins_volatility_feed
{
    const float* hlrange;
    int periods;
    IppStatus operator()(float* dest, int size)
    {
        float a[HISTORY_SIZE];
        const float* pa = (float*) & a[0];
        const float* pb = (float*) & a[periods];
        IppStatus status;
        if((status = ema_32f(hlrange, a, size, periods)) ||
                (status = ippsSub_32f(pb, pa, dest, size))  || // a - b = dest
                (status = ippsDiv_32f(pb, dest, dest, size - periods)))   //dest / b = dest
        {
        }
        return status;
    }
};

typedef pod<dpo_feed> dpo_feed_t;
typedef pod<avg_feed> avg_feed_t;
typedef pod<diff_feed> diff_feed_t;
typedef pod<div_feed> div_feed_t;
typedef pod<avg3_feed> avg3_feed_t;
typedef pod<tr_feed> tr_feed_t;
typedef pod<true_low_feed> true_low_feed_t;
typedef pod<roc_feed> roc_feed_t;
typedef pod<fi_index> fi_index_t;
typedef pod<avg4_feed> avg4_feed_t;
typedef pod<clv_feed> clv_feed_t;
typedef pod<obv_feed> obv_feed_t;
typedef pod<wma_feed> wma_feed_t;
typedef pod<ema_feed> ema_feed_t;
typedef pod<sma_feed> sma_feed_t;
typedef pod<min_feed> min_feed_t;
typedef pod<max_feed> max_feed_t;
typedef pod<mult_feed> mult_feed_t;
typedef pod<multc_feed> multc_feed_t;
typedef pod<sub_feed> sub_feed_t;
typedef pod<subc_feed> subc_feed_t;
typedef pod<add_feed> add_feed_t;
typedef pod<addc_feed> addc_feed_t;
typedef pod<rs_feed> rs_feed_t;
typedef pod<accdist_feed> accdist_feed_t;
typedef pod<stdev_feed> stdev_feed_t;
typedef pod<cci_feed> cci_feed_t;
typedef pod<ultoscc_feed> ultoscc_feed_t;
typedef pod<ndm_feed> ndm_feed_t;
typedef pod<pdm_feed> pdm_feed_t;
typedef pod<accdist_feed> accdist_feed_t;
typedef pod<cmf_feed> cmf_feed_t;
typedef pod<bollinger_feed> bollinger_feed_t;
typedef pod<bollpercentage_feed> bollpercentage_feed_t;
typedef pod<stochastic_feed> stochastic_feed_t;
typedef pod<williams_feed> williams_feed_t;
typedef pod<pvt_feed> pvt_feed_t;
typedef pod<stochrsi_feed> stochrsi_feed_t;
typedef pod<mfr_feed> mfr_feed_t;
typedef pod<psyline_feed> psyline_feed_t;
typedef pod<index_feed> index_feed_t;
typedef pod<default_feed> default_feed_t;


