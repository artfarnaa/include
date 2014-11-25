#include <util.hpp>
#include <fnmatch.h>
#include </opt/intel/ipp/include/ipp.h>

market marketlst [] =
{
    {"AMEX", "American Stock Exchange", "www.nyse.com", "www.nyse.com"},
    {"AMS", "Euronext Amsterdam", "www.aex.nl", "www.aex.nl"},
    {"ASX", "Australian Stock Exchange", "www.asx.com.au", "www.asx.com.au"},
    {"BRU", "Euronext Brussels", "www.euronext.com", "www.euronext.com"},
    {"BSE", "Bombay Stock Exchange", "www.bseindia.com", "www.bseindia.com"},
    {"CBOT", "Chicago Board of Trade", "www.cmegroup.com", "www.cmegroup.com"},
    {"CFE", "Chicago Futures Exchange", "cfe.cboe.com", "cfe.cboe.com"},
    {"CME", "Chicago Merchantile Exchange", "www.cmegroup.com", "www.cmegroup.com"},
    {"COMEX", "New York Commodity Exchange", "www.cmegroup.com", "www.cmegroup.com"},
    {"EUREX", "EUREX Futures Exchange", "www.eurexchange.com", "www.eurexchange.com"},
    {"FOREX", "Foreign Exchange (Interbank)", "en.wikipedia.org", "en.wikipedia.org/wiki/Foreign_exchange_market"},
    {"HKEX", "Hong Kong Stock Exchange", "www.hkex.com.hk", "www.hkex.com.hk"},
    {"INDEX", "Global Indices", ""},
    {"KCBT", "Kansas City Board of Trade", "en.wikipedia.org", "en.wikipedia.org/wiki/Kansas_City_Board_of_Trade"},
    {"LIFFE", "London Futures Exchange", "en.wikipedia.org", "en.wikipedia.org/wiki/London_International_Financial_Futures_and_Options_Exchange"},
    {"LIS", "Euronext Lisbon", "en.wikipedia.org", "en.wikipedia.org/wiki/Euronext_Lisbon"},
    {"LSE", "London Stock Exchange", "www.londonstockexchange.com"},
    {"MGEX", "Minneapolis Grain Exchange", "www.mgex.com/"},
    {"MLSE", "Milan Stock Exchange", ""},
    {"MSE", "Madrid Stock Exchange", "en.wikipedia.org", "en.wikipedia.org/wiki/Madras_Stock_Exchange"},
    {"NASDAQ", "NASDAQ Stock Exchange", "www.nasdaq.com"},
    {"NSE", "National Stock Exchange of India", "www.nseindia.com/"},
    {"NYBOT", "New York Board of Trade", "en.wikipedia.org", "en.wikipedia.org/wiki/New_York_Board_of_Trade"},
    {"NYMEX", "New York Merchantile Exchange", "www.cmegroup.com"},
    {"NYSE", "New York Stock Exchange", "www.nyse.com"},
    {"NZX", "New Zealand Stock Exchange", "www.nzx.com"},
    {"OTCBB", "OTC Bulletin Board", "www.otcbb.com/"},
    {"PAR", "Euronext Paris", "www.euronext.com/"},
    {"SGX", "Singapore Stock Exchange", "www.sgx.com/"},
    {"TSX", "Toronto Stock Exchange", "www.tmx.com/"},
    {"TSXV", "Vancouver Stock Exchange", "www.tmx.com/"},
    {"USMF", "US Mutual Funds", ""},
    {"WCE", "Winnipeg Commodity Exchange", "en.wikipedia.org", "en.wikipedia.org/wiki/Winnipeg_Commodity_Exchange"},
};

const market* const get_marketlst(int& size)
{
    size = sizeof(marketlst) / sizeof(market);
    return marketlst;
}

const char* feedtypes_lst [FEED_SIZE] =
{
    "ROC",        //FEEDTYPE_ROC,
    "FI",         //FEEDTYPE_FI
    "DPO",        //FEEDTYPE_DPO
    "AVG",        //FEEDTYPE_AVG
    "DIFF",       //FEEDTYPE_DIFF
    "DIV",        //FEEDTYPE_DIV
    "AVG3",       //FEEDTYPE_AVG3
    "TR",         //FEEDTYPE_TR
    "TL",         //FEEDTYPE_TL
    "RC",         //FEEDTYPE_RC
    "FC",         //FEEDTYPE_FC
    "AVG4",       //FEEDTYPE_AVG4
    "CLV",        //FEEDTYPE_CLV
    "OBV",        //FEEDTYPE_OBV
    "WMA",        //FEEDTYPE_WMA
    "EMA",        //FEEDTYPE_EMA
    "SMA",        //FEEDTYPE_SMA
    "MIN",        //FEEDTYPE_MIN
    "MAX",        //FEEDTYPE_MAX
    "MULT",       //FEEDTYPE_MULT
    "MULTC",      //FEEDTYPE_MULTC
    "SUB",        //FEEDTYPE_SUB
    "SUBC",       //FEEDTYPE_SUBC
    "ADD",        //FEEDTYPE_ADD
    "ADDC",       //FEEDTYPE_ADDC
    "RS",         //FEEDTYPE_RS
    "STDEV",      //FEEDTYPE_STDEV
    "CCI",        //FEEDTYPE_CCI
    "ULTOSC",     //FEEDTYPE_ULTOSC
    "NDM",        //FEEDTYPE_NDM
    "PDM",        //FEEDTYPE_PDM
    "ACCDIST",    //FEEDTYPE_ACCDIST
    "CMF",        //FEEDTYPE_CMF
    "BOL",        //FEEDTYPE_BOL
    "BOL_PER",    //FEEDTYPE_BOLL_PER
    "STOCH",      //FEEDTYPE_STOCH
    "WILL_PER",   //FEEDTYPE_WILL_PER
    "PVT",        //FEEDTYPE_PVT
    "STOCHRSI",   //FEEDTYPE_STOCHRSI
    "MFR",        //FEEDTYPE_MFR
    "PSYLINE",    //FEEDTYPE_PSYLINE
    "INDEX",      //FEEDTYPE_INDEX
    "DEFAULT",    //FEEDTYPE_DEFAULT
};

const char* const* const get_feedtypes()
{
    return feedtypes_lst;
};

inline int compare_technicals(const void* _a, const void* _b)
{
    const technical* a = (technical*) _a;
    const technical* b = (technical*) _b;
    return strcmp(a->symbol, b->symbol);
}

inline int compare_fundamentals(const void* _a, const void* _b)
{
    const fundamental* a = (fundamental*) _a;
    const fundamental* b = (fundamental*) _b;
    return strcmp(a->symbol, b->symbol);
}

struct feedpack
{
    short id;
    short key;
    char name[LABEL_SIZE];
    char stitle[LABEL_SIZE];
    char title[LABEL_SIZE];
    char ltitle[LABEL_SIZE];
    short format;
    char describe[TEXT_BUFFER];
    short deps[4];
    short depsn;
    float parms[4];
    short parmsn;
    bool show;
}
feedpacklst [] =
{
    {
        //0
        FEED_YMD,     //id
        FEEDTYPE_DEFAULT,//key
        "DATE",        //name
        "Date",        //stitle
        "Date",        //title
        "Date",       //ltitle
        0,        //format
        "",           //describe
        {},           //deps
        0,            //depsn
        {},           //parms
        0,            //parmsn
        1,            //show
    },
    {
        //1
        FEED_OPEN,    //id
        FEEDTYPE_DEFAULT,//key
        "OPEN",       //name
        "Open",          //stitle
        "Open",       //title
        "Open",       //ltitle
        2,     //format
        "",           //describe
        {},           //deps
        0,            //depsn
        {},           //parms
        0,            //parmsn
        1,            //show
    },
    {
        //2
        FEED_HIGH,    //id
        FEEDTYPE_DEFAULT,//key
        "HIGH",       //name
        "High",          //stitle
        "High",       //title
        "High",       //ltitle
        2,     //format
        "",           //describe
        {},           //deps
        0,            //depsn
        {},           //parms
        0,            //parmsn
        1,            //show
    },
    {
        //3
        FEED_LOW,     //id
        FEEDTYPE_DEFAULT,//key
        "LOW",        //name
        "Low",          //stitle
        "Low",        //title
        "Low",        //ltitle
        2,     //format
        "",           //describe
        {},           //deps
        0,            //depsn
        {},           //parms
        0,            //parmsn
        1,            //show
    },
    {
        //4
        FEED_CLOSE,   //id
        FEEDTYPE_DEFAULT,//key
        "CLOSE",      //name
        "Close",          //stitle
        "Close",      //title
        "Close",      //ltitle
        2,     //format
        "",           //describe
        {},           //deps
        0,            //depsn
        {},           //parms
        0,            //parmsn
        1,            //show
    },
    {
        //5
        FEED_VOLUME,  //id
        FEEDTYPE_DEFAULT,//key
        "VOLUME",     //name
        "Volume",          //stitle
        "Volume",        //title
        "Volume",     //ltitle
        0,      //format
        "",           //describe
        {},           //deps
        0,            //depsn
        {},           //parms
        0,            //parmsn
        1,            //show
    },
    {
        //6
        FEED_UNUSED100,  //id
        FEEDTYPE_DEFAULT,//key
        "",     //name
        "",         //stitle
        "",         //title
        "",  //ltitle
        0,            //format
        "",           //describe
        {},           //deps
        0,            //depsn
        {},           //parms
        0,            //parmsn
        0,            //show
    },
    {
        //7
        FEED_CHANGE,  //id
        FEEDTYPE_DIFF,//key
        "PC",     //name
        "PC",         //stitle
        "Price Change", //title
        "Close (Today - Yesterday)", //ltitle
        2,     //format
        "",           //describe
        {FEED_CLOSE, FEED_CLOSE},//deps
        2,            //depsn
        {1, 0},       //parms
        2,            //parmsn
        1,            //show
    },
    {
        //8
        FEED_ROC,     //id
        FEEDTYPE_ROC, //key
        "ROC",        //name
        "ROC",        //stitle
        "Rate of Change",        //title
        "PC / Close(Yesterday), PC = Close(Today - Yesterday)",//ltitle
        2,            //format
        "" ,          //describe
        {FEED_CLOSE, FEED_CLOSE}, //deps
        1,            //depsn
        {1},          //parms
        1,            //parmsn
        1,            //show
    },
    {
        //9
        FEED_TL,      //id
        FEEDTYPE_TL,  //key
        "TL",         //name
        "TL",         //stitle
        "True Low",         //title
        "MIN ( Low(Today), Close(Yesterday) )",   //ltitle
        2,            //format
        "",           //describe
        {FEED_LOW, FEED_CLOSE}, //deps
        2,            //depsn
        {1},          //parms
        1,            //parmsn
        1,            //show
    },
    {
        //10
        FEED_TP,      //id
        FEEDTYPE_AVG3,//key
        "TP",         //name
        "TP",         //stitle
        "Typical Price",         //title
        "(High + Low + Close)/3",//ltitle
        2,            //format
        "",           //describe
        {FEED_HIGH, FEED_LOW, FEED_CLOSE},//deps
        3,             //depsn
        1,            //show
    },
    {
        //11
        FEED_TPA16,     //id
        FEEDTYPE_SMA,   //key
        "TPSMA16",      //name
        "TPSMA16",      //stitle
        "Typical Price, Simple Moving Average, 16-Days",      //title
        "(High + Low + Close)/3",             //ltitle
        2,         //format
        "",           //decsribe
        {FEED_TP},      //desp
        1,              //depsn
        {16},
        1,
        1,            //show
    },

    {
        //12
        FEED_CCI16,    //id
        FEEDTYPE_CCI,  //key
        "CCISMA16",       //name
        "CCISMA16",       //stitle
        "Commodity Channel Index, Simple Moving Average, 16-Days",       //title
        "(TP - SMA16 of TP) / (.015 x MeanDeviation)",//ltitle
        2,      //format
        "", //describe
        {FEED_TP, FEED_TPA16}, //desp
        2,             //despn
        {0.15, 20},    //parms
        2,             //parmsn
        1,            //show
    },
    {
        //13
        FEED_FI,
        FEEDTYPE_FI,
        "FI",
        "FI",
        "Force Index",
        "Close (Today - Yesterday) x Volume",
        0,
        "",
        {FEED_CLOSE, FEED_VOLUME},
        2,
        {},
        0,
        1,            //show
    },
    {
        //14
        FEED_WC,
        FEEDTYPE_AVG,
        "WCLOSE",
        "WCLOSE",
        "Weighted Close",
        "(High + Low + Close * 2)/4",
        2,
        "",
        {FEED_CLOSE, FEED_HIGH, FEED_LOW, FEED_CLOSE},
        4,
        1,            //show
    },
    {
        //15
        FEED_CLV,
        FEEDTYPE_CLV,
        "CLV",
        "CLV",
        "Close Location Value",
        "((Close - Low) - (High - Close)) / (High - Low)",
        2,
        "",
        {FEED_HIGH, FEED_LOW, FEED_CLOSE},
        3,
        1,            //show
    },
    {
        //16
        FEED_RS14,
        FEEDTYPE_RS,
        "RS14",
        "RS14",
        "Relative Strength, 14-Days",
        "(Average Gain 14-Days) / (Average Loss)",
        2,
        "",
        {FEED_CLOSE},
        1,
        {14},
        1,
        1,            //show
    },
    {
        //17
        FEED_CLOSESMA16,
        FEEDTYPE_SMA,
        "SMA16",
        "SMA16",
        "Simple Moving Average, Close, 16-Days",
        "(Sum 16 Periods) / 16",
        2,
        "",
        {FEED_CLOSE},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //18
        FEED_CLOSESMA50,
        FEEDTYPE_SMA,
        "SMA50",
        "SMA50",
        "Simple Moving Average, Close, 50-Days",
        "(Sum 50 Periods) / 50",
        2,
        "",
        {FEED_CLOSE},
        1,
        {50},
        1,
        1,            //show
    },
    {
        //19
        FEED_CLOSESMA16PENV,
        FEEDTYPE_MULTC,
        "PENV16",
        "PENV16",
        "Positive Envelope, Close SMA, 16-Days",
        "Positive Envelope, Close SMA, 16-Days",
        2,
        "",
        {FEED_CLOSESMA16},
        1,
        {1.025},
        1,
        1,            //show
    },
    {
        //20
        FEED_CLOSESMA16NENV,
        FEEDTYPE_MULTC,
        "NENV16",
        "NENV16",
        "Negative Envelope, Close SMA, 16-Days",
        "Negative Envelope, Close SMA, 16-Days",
        2,
        "",
        {FEED_CLOSESMA16},
        1,
        {0.975},
        1,
        1,            //show
    },
    {
        //21
        FEED_CLOSEEMA12,
        FEEDTYPE_EMA,
        "EMA12",
        "EMA12",
        "Exponential Moving Average, Close, 12-Days",
        "Exponential Moving Average, Close, 12-Days",
        2,
        "",
        {FEED_CLOSE},
        1,
        {12},
        1,
        1,            //show
    },
    {
        //22
        FEED_CLOSEEMA16,
        FEEDTYPE_EMA,
        "EMA16",
        "EMA16",
        "Exponential Moving Average, Close, 16-Days",
        "Exponential Moving Average, Close, 16-Days",
        2,
        "",
        {FEED_CLOSE},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //23
        FEED_CLOSEEMA26,
        FEEDTYPE_EMA,
        "EMA26",
        "EMA26",
        "Exponential Moving Average, Close, 26-Days",
        "Exponential Moving Average, Close, 26-Days",
        2,
        "",
        {FEED_CLOSE},
        1,
        {26},
        1,
        1,            //show
    },
    {
        //24
        FEED_CLOSEEMA32,
        FEEDTYPE_EMA,
        "EMA32",
        "EMA32",
        "Exponential Moving Average, Close, 32-Days",
        "Exponential Moving Average, Close, 32-Days",
        2,
        "",
        {FEED_CLOSE},
        1,
        {32},
        1,
        1,            //show
    },
    {
        //25
        FEED_TYPICALPRICESMA16,
        FEEDTYPE_SMA,
        "TP16",
        "TP16",
        "Typical Price, SMA, 16-Days",
        "Typical Price, SMA, 16-Days",
        2,
        "",
        {FEED_TP},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //26
        FEED_TYPICALPRICESMA32,
        FEEDTYPE_SMA,
        "TP32",
        "TP32",
        "Typical Price, SMA, 32-Days",
        "Typical Price, SMA, 32-Days",
        2,
        "",
        {FEED_TP},
        1,
        {32},
        1,
        1,            //show
    },
    {
        //27
        FEED_CLOSEROC16,
        FEEDTYPE_ROC,
        "ROC16",
        "ROC16",
        "Rate of Change, 16-Days",
        "Rate of Change, 16-Days",
        2,
        "",
        {FEED_CLOSE, FEED_CLOSE},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //28
        FEED_CLOSSEROC8,
        FEEDTYPE_ROC,
        "ROC8",
        "ROC8",
        "Rate of Change, 8-Days",
        "Rate of Change, 8-Days",
        2,
        "",
        {FEED_CLOSE, FEED_CLOSE},
        1,
        {8},
        1,
        1,            //show
    },
    {
        //29
        FEED_VOLUMEEMA16,
        FEEDTYPE_EMA,
        "VEMA16",
        "VEMA16",
        "Volume, EMA, 16-Days",
        "Volume, EMA, 16-Days",
        0,
        "",
        {FEED_VOLUME},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //30
        FEED_VOLUMEEMA32,
        FEEDTYPE_EMA,
        "VEMA32",
        "VEMA32",
        "Volume, EMA, 32-Days",
        "Volume, EMA, 32-Days",
        0,
        "",
        {FEED_VOLUME},
        1,
        {32},
        1,
        1,            //show
    },
    {
        //31
        FEED_RSI14,
        FEEDTYPE_INDEX,
        "RSI14",
        "RSI14",
        "Relative Strength Index, SMA, 14-Days",
        "Relative Strength Index, SMA, 14-Days",
        2,
        "",
        {FEED_RS14},
        1,
        {0},
        0,
        1,            //show
    },
    {
        //32
        FEED_LOW16,
        FEEDTYPE_MIN,
        "MINLOW16",
        "MINLOW16",
        "Minimum Low, 16-Days",
        "Minimum Low, 16-Days",
        2,
        "",
        {FEED_LOW},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //33
        FEED_HIGH16,
        FEEDTYPE_MAX,
        "MAXHIGH16",
        "MAXHIGH16",
        "Maximum High, 16-Days",
        "Maximum High, 16-Days",
        2,
        "",
        {FEED_HIGH},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //34
        FEED_RMF,
        FEEDTYPE_MULT,
        "",
        "",
        "",
        "",
        2,
        "",
        {0},
        1,
        {0},
        1,
        1,            //show
    },
    {
        //35
        FEED_BP,
        FEEDTYPE_DIFF,
        "BP",
        "BP",
        "Buying Pressure",
        "Buying Pressure",
        2,
        "",
        {FEED_CLOSE, FEED_TL},
        0,
        {0, 0},
        2,
        1,            //show
    },
    {
        //36
        FEED_CLOSESTDEV16,
        FEEDTYPE_STDEV,
        "STDEV16",
        "STDEV16",
        "Standard Deviation, 16-Days",
        "Standard Deviation, 16-Days",
        2,
        "",
        {FEED_CLOSE},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //37
        FEED_DPO16,
        FEEDTYPE_DPO,
        "DPO16",
        "DPO16",
        "Detrended Price Oscillator, Closing Price, 16-Days",
        "Detrended Price Oscillator, Closing Price, 16-Days",
        2,
        "",
        {FEED_CLOSE, FEED_CLOSESMA16},
        2,
        {16},
        1,
        1,            //show
    },
    {
        //38
        FEED_APO1632,
        FEEDTYPE_DIFF,
        "APO1632",
        "APO1632",
        "Absolute Price Oscillator, Close, SMA, 16,32-Days",
        "Absolute Price Oscillator, Close, SMA, 16,32-Days",
        2,
        "",
        {FEED_CLOSEEMA16, FEED_CLOSEEMA32},
        2,
        {0, 0},
        2,
        1,            //show
    },
    {
        //39
        FEED_UNUSED101,
        FEEDTYPE_ROC,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {0},
        0,
        0,            //show
    },
    {
        //40
        FEED_PPO1632,
        FEEDTYPE_ROC,
        "PPO1632",
        "PPO1632",
        "Percentage Price Oscillator, Close, SMA, 16,32-Days",
        "Percentage Price Oscillator, Close, SMA, 16,32-Days",
        2,
        "",
        {FEED_CLOSEEMA16, FEED_CLOSEEMA32},
        2,
        {0},
        1,
        1,            //show
    },
    {
        //41
        FEED_MACD1226,
        FEEDTYPE_DIFF,
        "MACD1226",
        "MACD1226",
        "Convergence Divergence, Close, EMA, 12,26 Days",
        "Convergence Divergence, Close, EMA, 12,26 Days",
        2,
        "",
        {FEED_CLOSEEMA12, FEED_CLOSEEMA26},
        2,
        {0, 0},
        2,
        1,            //show
    },
    {
        //42
        FEED_UNUSED102,
        FEEDTYPE_CMF,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {},
        0,
        0,            //show
    },
    {
        //43
        FEED_ACCDIST,
        FEEDTYPE_ACCDIST,
        "ACCDIST",
        "ACCDIST",
        "Accumulation/Distribution",
        "Accumulation/Distribution",
        0,
        "",
        {FEED_CLV, FEED_VOLUME},
        2,
        1,            //show
    },
    {
        //44
        FEED_ACCDISTEMA3,
        FEEDTYPE_EMA,
        "ACCDIST3",
        "ACCDIST3",
        "Accumulation/Distribution, 3-Days",
        "Accumulation/Distribution, 3-Days",
        2,
        "",
        {FEED_ACCDIST},
        1,
        {3},
        1,
        1,            //show
    },
    {
        //45
        FEED_ACCDISTEMA10,
        FEEDTYPE_EMA,
        "ACCDIST10",
        "ACCDIST10",
        "Accumulation/Distribution, 10-Days",
        "Accumulation/Distribution, 10-Days",
        2,
        "",
        {FEED_ACCDIST},
        1,
        {10},
        1,
        1,            //show
    },
    {
        //46
        FEED_CHAIKINOSCILL310,
        FEEDTYPE_DIFF,
        "CHAIK310",
        "CHAIK310",
        "Chaikin Oscillator, 3,10-Days",
        "Chaikin Oscillator, 3,10-Days",
        2,
        "",
        {FEED_ACCDISTEMA3, FEED_ACCDISTEMA10},
        2,
        {0, 0},
        2,
        1,            //show
    },
    {
        //47
        FEED_MEAN,
        FEEDTYPE_AVG,
        "MEAN",
        "MEAN",
        "Mean Price",
        "(High + Low)/2",
        2,
        "",
        {FEED_HIGH, FEED_LOW},
        2,
        1,            //show
    },
    {
        //48
        FEED_PVOSIGNAL16329,
        FEEDTYPE_EMA,
        "PVO16329",
        "PVO16329",
        "Price Volume Oscillator, 16,32,9 Days",
        "Price Volume Oscillator, 16,32,9 Days",
        2,
        "",
        {FEED_UNUSED101},
        1,
        {9},
        1,
        1,            //show
    },
    {
        //49
        FEED_PPOSIGNAL16329,
        FEEDTYPE_EMA,
        "PPOSIG16329",
        "PPOSIG16329",
        "Percentage Price Oscillator, 16,32,9 Days",
        "Percentage Price Oscillator, 16,32,9 Days",
        2,
        "",
        {FEED_PPO1632},
        1,
        {9},
        1,
        1,            //show
    },
    {
        //50
        FEED_STOCHRSI,
        FEEDTYPE_STOCHRSI,
        "STOCHRSI14",
        "STOCHRSI14",
        "Relative Strength Index, Stochastic, 14-Days",
        "Relative Strength Index, Stochastic, 14-Days",
        2,
        "",
        {FEED_RSI14},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //51
        FEED_FIEMA16,
        FEEDTYPE_EMA,
        "FF16",
        "FF16",
        "Force Family, 16-Days",
        "Force Family, 16-Days",
        2,
        "",
        {FEED_FI},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //52
        FEED_MOM10,
        FEEDTYPE_DIFF,
        "MOM10",
        "MOM10",
        "Momentum, Closing, 10-Days",
        "Momentum, Closing, 10-Days",
        2,
        "",
        {FEED_CLOSE, FEED_CLOSE},
        2,
        {0, 10},
        2,
        1,            //show
    },
    {
        //53
        FEED_ONBALANCEVOLUME,
        FEEDTYPE_OBV,
        "OBV",
        "OBV",
        "On Balance Volume",
        "On Balance Volume",
        0,
        "",
        {FEED_CLOSE, FEED_VOLUME},
        2,
        1,            //show
    },
    {
        //54
        FEED_MACDSIGNAL12269,
        FEEDTYPE_EMA,
        "MACDSIG12269",
        "MACDSIG12269",
        "MACD Signal 12,26,9 Days",
        "MACD Signal 12,26,9 Days",
        2,
        "",
        {FEED_MACD1226},
        1,
        {9},
        1,
        1,            //show
    },
    {
        //55
        FEED_STOCH16,
        FEEDTYPE_STOCH,
        "STOCHK16",
        "STOCHK16",
        "Fast Stochastics, 16-Days",
        "Fast Stochastics, 16-Days",
        2,
        "",
        {FEED_CLOSE, FEED_LOW16, FEED_HIGH16},
        3,
        1,            //show
    },
    {
        //56
        FEED_STOCHSMA163,
        FEEDTYPE_SMA,
        "DFASTOCH163",
        "DFASTOCH163",
        "DFast Stochastics, 16,3-Days",
        "DFast Stochastics, 16,3-Days",
        2,
        "",
        {FEED_STOCH16},
        1,
        {3},
        1,
        1,            //show
    },
    {
        //57
        FEED_STOCHSMA1633,
        FEEDTYPE_SMA,
        "FASTOCH1633",
        "FASTOCH1633",
        "Fast Stochastics, 16,3,3 Days",
        "Fast Stochastics, 16,3,3 Days",
        2,
        "",
        {FEED_STOCHSMA163},
        1,
        {3},
        1,
        1,            //show
    },
    {
        //58
        FEED_STDEVSMA16,
        FEEDTYPE_STDEV,
        "STDEV16",
        "STDEV16",
        "Standard Deviation, Close, EMA,  16-Days",
        "Standard Deviation, Close, EMA,  16-Days",
        2,
        "",
        {FEED_CLOSESMA16},
        1,
        {16},
        1,
        1,            //show
    },
    {
        //59
        FEED_UPPERBOLLINGER1616,
        FEEDTYPE_BOL,
        "BOLLT1616",
        "BOLLT1616",
        "Bollinger Top, 16,2 Days",
        "Bollinger Top, 16,2 Days",
        2,
        "",
        {FEED_CLOSESMA16, FEED_CLOSESTDEV16},
        2,
        {2},
        1,
        1,            //show
    },
    {
        //60
        FEED_LOWERBOLLINGER1616,
        FEEDTYPE_BOL,
        "BOLLB1616",
        "BOLLB1616",
        "Bollinger Bottom, 16,16 Days",
        "Bollinger Bottom, 16,16 Days",
        2,
        "",
        {FEED_CLOSESMA16, FEED_CLOSESTDEV16},
        2,
        { -2},
        1,
        1,            //show
    },
    {
        //61
        FEED_BOLLINGER1616,
        FEEDTYPE_BOLL_PER,
        "BBR1616",
        "BBR1616",
        "Bollinger %, 16,16 Days",
        "Bollinger %, 16,16 Days",
        2,
        "",
        {FEED_CLOSE, FEED_UPPERBOLLINGER1616, FEED_LOWERBOLLINGER1616},
        3,
        1,            //show
    },
    {
        //62
        FEED_BOLLWIDTH1616,
        FEEDTYPE_DIFF,
        "BBW1616",
        "BBW1616",
        "Bollinger Width, 16,16 Days",
        "Bollinger Width, 16,16 Days",
        2,
        "",
        {FEED_UPPERBOLLINGER1616, FEED_LOWERBOLLINGER1616},
        2,
        1,            //show
    },
    {
        //63
        FEED_MACDHIST12269,
        FEEDTYPE_DIFF,
        "MACDH12269",
        "MACDH12269",
        "MACD Histogram 12,26,9 Days",
        "MACD Histogram 12,26,9 Days",
        2,
        "",
        {FEED_MACD1226, FEED_MACDSIGNAL12269},
        2,
        {0, 0},
        2,
        1,            //show
    },
    {
        //64
        FEED_WILLIAMSPERC1616,
        FEEDTYPE_WILL_PER,
        "WILLR1616",
        "WILLR1616",
        "William %R, 16,16 Days",
        "William %R, 16,16 Days",
        2,
        "",
        {FEED_CLOSE, FEED_HIGH16, FEED_LOW16},
        3,
        1,            //show
    },
    {
        //65
        FEED_UNUSED103,
        FEEDTYPE_MFR,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {0},
        1,
        1,            //show
    },
    {
        //66
        FEED_MFI14,//todo unused
        FEEDTYPE_INDEX,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        1,
        {},
        0,
        1,            //show
    },
    {
        //67
        FEED_TRUERANGE,
        FEEDTYPE_TR,
        "TR",
        "TR",
        "True Range",
        "Max[(High - Low), Abs(High - Close(Yesterday)), Abs(Low - Close(Yesterday)]",
        2,
        "",
        {FEED_HIGH, FEED_LOW, FEED_CLOSE},
        3,
        1,            //show
    },
    {
        //68
        FEED_UNUSED104,
        FEEDTYPE_DIFF,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {0},
        0,
        0,            //show
    },
    {
        //69
        FEED_UNUSED105,
        FEEDTYPE_DIFF,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {},
        0,
        0,            //show
    },
    {
        //70
        FEED_UNUSED106,
        FEEDTYPE_EMA,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {},
        0,
        0,            //show
    },
    {
        //71
        FEED_UNUSED107,
        FEEDTYPE_MULTC,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {0},
        0,
        0,            //show
    },
    {
        //72
        FEED_UNUSED108,
        FEEDTYPE_ADD,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        0,            //show
    },
    {
        //73
        FEED_UNUSED109,
        FEEDTYPE_AVG,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        0,            //show
    },
    {
        //74
        FEED_UNUSED110,
        FEEDTYPE_ULTOSC,
        "",
        "",
        "",
        "",
        0,
        "",
        {},
        0,
        {},
        0,
        0,            //show
    },
};

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
    IppStatus operator()(float*, int size)
    {
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
        return ippsSub_32f(b + (int)c, a + (int)d, dest, size); // a - b = dest
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

inline void rs32f_test(const char*, const char*, void*, node<message*>** errors)
{
    int status;
    float data[] = {43.13, 42.66, 43.42, 44.57, 44.22, 44.18, 44.03, 45.35, 45.78, 46.45, 45.71, 46.25,
                    46.21, 45.64, 46.22, 46.41, 46.03, 46.00, 46.28, 46.28, 45.61, 46.03, 45.89, 46.08,
                    45.84, 45.42, 45.10, 44.83, 44.33, 43.61, 44.15, 44.09, 44.34
                   };

    float rs [] = {0.60701822435637, 0.49431092655862, 0.594999156777, 0.8336246868167,
                   0.72025005002827, 0.70824775083558, 0.66638402420065, 1.01705518638599, 1.20787462282414,
                   1.6579536425235, 1.27579435639859, 1.72161776689015, 1.69757052044223, 1.3795, 1.9722,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                  };

    unsigned long size = sizeof(data) / sizeof(float);
    float result[30] = {0};
    rs_32f(data, result, size, 14);

    echo()(data, rs, result, size);
}

inline void ema32f_test(const char*, const char*, void*, node<message*>** errors)
{
    int status = ippStsNoErr;
    float data[] = {22.17, 22.40, 23.10, 22.68, 23.33, 23.10, 23.19, 23.65, 23.87, 23.82, 23.63,
                    23.95, 23.83, 23.75, 24.05, 23.36, 22.61, 22.38, 22.39, 22.15, 22.29, 22.24, 22.43, 22.23,
                    22.13, 22.18, 22.17, 22.08, 22.19, 22.27
                   };

    float expected [] = {22.9155602300309, 23.0806847255934, 23.2313924423919, 23.2611240962568,
                         23.3901516732027, 23.4044076005811, 23.4725870673769, 23.5360508601273, 23.5099066068223,
                         23.4293969638939, 23.3420407336481, 23.2772053411254, 23.1273398613755, 22.9706598305701,
                         22.7968064595856, 22.517896783938, 22.3316960692576, 22.2696507513148, 22.2447731404959,
                         22.2119227272727, 22.22475, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                        };

    static unsigned long size = 30;
    float result[30] = {0};
    ippsSet_32f(std::numeric_limits<float>::quiet_NaN(), result, size);
    ema_32f(data, result, size, 10);

    echo()(data, expected, result, size);
}

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

void write_symbol_data(int fd, float* data, node<message*>** errors)
{
    float* hdata = data;

    feedpack* feeds = &feedpacklst[0];
    node<char*>* messages = 0;
    int feedpackn = sizeof(feedpacklst) / sizeof(feedpack);
    for(int n = FEED_CHANGE; n < feedpackn; ++n, ++feeds, data += HISTORY_SIZE)
    {
        const float* a = hdata + (feeds->deps[0] * HISTORY_SIZE);
        const float* b = hdata + (feeds->deps[1] * HISTORY_SIZE);
        const float* c = hdata + (feeds->deps[2] * HISTORY_SIZE);
        const float* d = hdata + (feeds->deps[3] * HISTORY_SIZE);

        int asize = HISTORY_SIZE;
        if(feeds->depsn >= 1)
            asize = get_safe_size(a, asize);
        if(feeds->depsn >= 2)
            asize = get_safe_size(b, asize);
        if(feeds->depsn >= 3)
            asize = get_safe_size(c, asize);
        if(feeds->depsn >= 4)
            asize = get_safe_size(d, asize);

        typedef std::function < IppStatus(float*, int) > func_t;
        func_t func_lst[] =
        {
            roc_feed_t()(a, b, feeds->parms[0]), //FEEDTYPE_ROC
            fi_index_t()(a, b), //FEEDTYPE_FI
            dpo_feed_t()(a, b, feeds->parms[0]), //FEEDTYPE_DPO
            avg_feed_t()(a, b),   //FEEDTYPE_AVG
            diff_feed_t()(a, b, feeds->parms[0], feeds->parms[1]), //FEEDTYPE_DIFF
            div_feed_t()(a, b), //FEEDTYPE_DIV
            avg3_feed_t()(a, b, c), //FEEDTYPE_AVG3
            tr_feed_t()(a, b, c), //FEEDTYPE_TR
            true_low_feed_t()(a, b), //FEEDTYPE_TL
            default_feed_t()(), //FEEDTYPE_RC
            default_feed_t()(), //FEEDTYPE_FC
            avg4_feed_t()(a, b, c, d), //FEEDTYPE_AVG4
            clv_feed_t()(a, b, c), //FEEDTYPE_CLV
            obv_feed_t()(a, b), //FEEDTYPE_OBV
            wma_feed_t()(a, feeds->parms[0]), //FEEDTYPE_WMA
            ema_feed_t()(a, feeds->parms[0]), //FEEDTYPE_EMA
            sma_feed_t()(a, feeds->parms[0]), //FEEDTYPE_SMA
            min_feed_t()(a, feeds->parms[0]), //FEEDTYPE_MIN
            max_feed_t()(a, feeds->parms[0]), //FEEDTYPE_MAX
            mult_feed_t()(a, b), //FEEDTYPE_MULT
            multc_feed_t()(a, feeds->parms[0]), //FEEDTYPE_MULTC
            sub_feed_t()(a, b), //FEEDTYPE_SUB
            subc_feed_t()(a, feeds->parms[0]), //FEEDTYPE_SUBC
            add_feed_t()(a, b), //FEEDTYPE_ADD
            addc_feed_t()(a, feeds->parms[0]), //FEEDTYPE_ADDC
            rs_feed_t()(a, feeds->parms[0]), //FEEDTYPE_RS
            stdev_feed_t()(a, feeds->parms[0]), //FEEDTYPE_STDEV
            cci_feed_t()(a, b, feeds->parms[0], (int) feeds->parms[1]), //FEEDTYPE_CCI
            ultoscc_feed_t()(a, b, feeds->parms[0], feeds->parms[1], feeds->parms[2]), //FEEDTYPE_ULTOSC
            ndm_feed_t()(a, b), //FEEDTYPE_NDM
            pdm_feed_t()(a, b), //FEEDTYPE_PDM
            accdist_feed_t()(a, b), //FEEDTYPE_ACCDIST
            cmf_feed_t()(a, b, feeds->parms[0]), //FEEDTYPE_CMF
            bollinger_feed_t()(a, b, feeds->parms[0]), //FEEDTYPE_BOL
            bollpercentage_feed_t()(a, b, c), //FEEDTYPE_BOLL_PER
            stochastic_feed_t()(a, b, c), //FEEDTYPE_STOCH
            williams_feed_t()(a, b, c), //FEEDTYPE_WILL_PER
            pvt_feed_t()(a, b), //FEEDTYPE_PVT
            stochrsi_feed_t()(a, feeds->parms[0]), //FEEDTYPE_STOCHRSI
            mfr_feed_t()(a, b, feeds->parms[0]), //FEEDTYPE_MFR
            psyline_feed_t()(a, feeds->parms[0]), //FEEDTYPE_PSYLINE
            index_feed_t()(a), //FEEDTYPE_INDEX
            default_feed_t()() //FEEDTYPE_DEFAULT,
        };

        int msize = sizeof(func_lst) / sizeof(func_t);
        assert(feeds->key < msize);

        IppStatus status = func_lst[feeds->key](data, asize);
        if(status != ippStsDivByZero && status != ippStsNoErr)
        {
            //push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__,
            //             "n=%d: name=%s title=%s key=%d error=%s, path=%s ", n, feeds->name,
            //             feeds->title, feeds->key, ippGetStatusString(status), path);
        }
    }

    data = hdata;
    for(int n = 0; n < feedpackn; ++n, data += HISTORY_SIZE)
    {
        write(fd, data, sizeof(float)*BEKCHARTCOLS);
    }

    data = hdata;
    for(int n = 0; n < feedpackn; ++n, data += HISTORY_SIZE)
    {
        int size = get_safe_size(data, BEKCHARTCOLS);
        float dest;
        ippsMin_32f(data, size, &dest);
        write(fd, &dest, sizeof(float));
    }

    data = hdata;
    for(int n = 0; n < feedpackn; ++n, data += HISTORY_SIZE)
    {
        int size = get_safe_size(data, BEKCHARTCOLS);
        float dest;
        ippsMax_32f(data, size, &dest);
        write(fd, &dest, sizeof(float));
    }

    data = hdata;
    for(int n = 0; n < feedpackn; ++n, data += HISTORY_SIZE)
    {
        int size = get_safe_size(data, BEKCHARTCOLS20);
        float dest;
        ippsMin_32f(data, size, &dest);
        write(fd, &dest, sizeof(float));
    }

    data = hdata;
    for(int n = 0; n < feedpackn; ++n, data += HISTORY_SIZE)
    {
        int size = get_safe_size(data, BEKCHARTCOLS20);
        float dest;
        ippsMax_32f(data, size, &dest);
        write(fd, &dest, sizeof(float));
    }
}

const feedpack* const get_feedpacklst(int* size)
{
    if(size)
        *size = sizeof(feedpacklst) / sizeof(feedpack);
    return feedpacklst;
}

void make_feedpack(const char*, const char*, void* app_, node<message*>** errors)
{
    const char* path = "/srv/http/gen/feedpack";
    int fd = open(path, O_WRONLY | O_TRUNC | O_CREAT,
                  S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH);
    if(fd == -1)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    int size = sizeof(feedpacklst) / sizeof(feedpack);
    const feedpack* const feed = feedpacklst;

    write(fd, &size, sizeof(int));

    for(int n = 0; n < size; ++n)
        write(fd, feed[n].name, LABEL_SIZE);
    for(int n = 0; n < size; ++n)
        write(fd, feed[n].title, LABEL_SIZE);
    for(int n = 0; n < size; ++n)
        write(fd, feed[n].stitle, LABEL_SIZE);
    for(int n = 0; n < size; ++n)
        write(fd, feed[n].ltitle, LABEL_SIZE);
    for(int n = 0; n < size; ++n)
        write(fd, &feed[n].format, sizeof(short));

    close(fd);
}

void eod_parse_line(float* dest, const char* str, int size, node<message*>** errors)
{
    //Symbol,Year-Month-Day,Open,High,Low,Close,Volume

    /*
    const char* str =
        "AAVX,20120430,157.58,157.95,157.1,157.11,400\r\n"
        "AAVX,20120427,156.8,160.4,156.52,159.92,2200\r\n"
        "AAVX,20120131,115.49,115.49,111.37,112.82,2000\r\n"
        "AAVX,20120130,111.2,113.67,111.2,113.58,900";
    */

    int lines = 0;
    float* y = (float*)&dest[FEED_YMD * HISTORY_SIZE];
    float* o = (float*)&dest[FEED_OPEN * HISTORY_SIZE];
    float* h = (float*)&dest[FEED_HIGH * HISTORY_SIZE];
    float* l = (float*)&dest[FEED_LOW * HISTORY_SIZE];
    float* c = (float*)&dest[FEED_CLOSE * HISTORY_SIZE];
    float* v = (float*)&dest[FEED_VOLUME * HISTORY_SIZE];

    char ch[100];
    const char* hstr = str;
    int row = 0;
    while(*str != '\0' && (str - hstr) < size && row++ < HISTORY_SIZE)
    {
        char* start = str;
        while(*str != ',' && *str != '\0') ++str;
        ++str;

        memcpy(ch, str, 4);
        ch[4] = '\0';
        str += 4;
        int year = atoi(ch);

        memcpy(ch, str, 2);
        ch[2] = '\0';
        str += 2;
        int month = atoi(ch);

        memcpy(ch, str, 2);
        ch[2] = '\0';
        str += 2;
        int day = atoi(ch);
        ++str;

        char* openstr = str;

        while(*str != ',' && *str != '\0') ++str;
        ++str;
        char* highstr = str;

        while(*str != ',' && *str != '\0') ++str;
        ++str;
        char* lowstr = str;

        while(*str != ',' && *str != '\0') ++str;
        ++str;
        char* closestr = str;

        while(*str != ',' && *str != '\0') ++str;
        ++str;
        char* volumestr = str;

        while(*str != '\r' && *str != '\0') ++str;

        int msize = highstr - openstr;
        memcpy(ch, openstr, msize);
        ch[msize] = '\0';
        float open = atof(ch);

        msize = lowstr - highstr;
        memcpy(ch, highstr, msize);
        ch[msize] = '\0';
        float high = atof(ch);

        msize = closestr - lowstr;
        memcpy(ch, lowstr, msize);
        ch[msize] = '\0';
        float low = atof(ch);

        msize = volumestr - closestr;
        memcpy(ch, closestr, msize);
        ch[msize] = '\0';
        float close = atof(ch);

        msize = str - volumestr;
        memcpy(ch, volumestr, msize);
        ch[msize] = '\0';
        float volume = atof(ch);

        tm m;
        memset(&m, 0, sizeof(tm));
        m.tm_mday = day;            /* day of the month */
        m.tm_mon = month - 1;       /* month */
        m.tm_year = year - 1900;    /* year */
        *y++ = (float)mktime(&m);
        *o++ = open;
        *h++ = high;
        *l++ = low;
        *c++ = close;
        *v++ = volume;

        while(*str != '\r' && *(str + 1) != '\n')
            ++str;
        ++str;
        ++str;
    }
}

void echo_csv(const char*, const char* path, void* app_, node<message*>** errors)
{
    /*
        const char* line =
        "AAC,20120426\r\n"
        "BBB,20120425\r\n";
    */
    int linesn;
    char** lines = load_file_lines(path, linesn);
    for(int n = 0; n < linesn; ++n)
    {
        int tokensn;
        char** tokens = tokenizer(lines[n], '\t', tokensn, PARSE_SKIPBLANKS | PARSE_SKIPCOMMENTS);
        printf("%s,", tokens[0]);
    }
}

ind* get_indlst(const char* path, int& rows, node<message*>** errors)
{
//Symbol    Name
    /*
        const char* str =
            "AAIT\tAC Asia Information Tech MSCI Ishares\r\n"
            "AALCP\tAmerican Airlines Group Inc.\r\n"
            "AAME\tAtlantic American Corp\r\n";
    */

    char* str = get_string_from_file(path, errors);
    if(!str)
        return 0;
    ind* indlst = (ind*) malloc(sizeof(ind) * MAX_EXCHANGE_SYMBOLS);
    ind* pindlst = indlst;

    while(*str != '\0')
    {
        char* name = str;
        while(*str != '\t' && *str != '\0') ++str;
        int nsize = str - name;
        ++str;

        char* title = str;
        while(*str != '\r' && *(str + 1) != '\n') ++str;
        int tsize = str - title;
        ++str;
        ++str;

        strncpy(pindlst->name, name, nsize);
        strncpy(pindlst->title, title, tsize);
        pindlst++;
    }
    rows = pindlst - indlst;
    return indlst;
}

void eod_parse_feed(const char* str, const char* exchange, void* app_, node<message*>** errors)
{
    /*
        const char* str =
        "AAC,20120426,30.3,30.36,30.3,30.36,1100\r\n"
        "AAC,20120425,30.27,30.3,30.25,30.3,1700\r\n"
        "AAC,20120130,28.7,28.89,28.7,28.89,400\r\n"
        "AAC,20120426,85.47,85.47,85.47,85.47,100\r\n"
        "AAPL,20120201,83.98,83.98,83.98,83.98,100\r\n"
        "AAPL,20120130,81.69,81.69,81.69,81.69,100\r\n"
        "AAPL,20120430,2.25,2.36,2.22,2.36,128300\r\n"
        "AAPL,20120427,2.3,2.32,2.22,2.26,126000\r\n"
        "AAXJ,20120130,2.47,2.55,2.44,2.55,142100\r\n"
        "AAXJ,20120426,15.75,15.75,15.75,15.75,1700\r\n"
        "AAXJ,20120202,15,15,14.7,14.7,1900\r\n"
        "AAXJ,20120201,14.98,15,14.98,15,600";
    */

    while(*str && isspace(*str))
        ++str;

    char* hstr = str;
    char** ptr = 0;
    char** names = 0;
    int ptrn = 0;
    while(*str != '\0')
    {
        char* start = str;
        while(*str != ',' && *str != '\0') ++str;
        int size = str - start;
        char title[LABEL_SIZE];
        memcpy(&title, start, size);
        title[size] = '\0';
        if(ptrn == 0 || strcmp(names[ptrn - 1], title))
        {
            ptr = (char**)realloc(ptr, sizeof(char*) * (ptrn + 1));
            names = (char**)realloc(names, sizeof(char*) * (ptrn + 1));
            ptr[ptrn] = start;
            names[ptrn] = (char*)malloc(sizeof(char) * (size + 1));
            memcpy(names[ptrn], title, size);
            names[ptrn][size] = '\0';
            ptrn++;
        }

        while(*str != '\r' && *(str + 1) != '\n')
            ++str;
        ++str;
        ++str;
    }

    char path[MAX_PATH];
    int fsize;

    const market* marketfind = (market*) bsearch(exchange,
                               marketlst, sizeof(marketlst) / sizeof(market), sizeof(market), compare_markets);
    if(!marketfind)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad market - %s", exchange);
        return;
    }

    sprintf(path, "/srv/http/bek/%s", exchange);
    int status = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(status && errno != EEXIST)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    sprintf(path, "/srv/http/mrv/%s", exchange);
    int mrv = open(path, O_WRONLY | O_TRUNC | O_CREAT,
                   S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH);
    if(mrv == -1)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    sprintf(path, "/srv/http/dog/%s", exchange);
    int dog = open(path, O_WRONLY | O_TRUNC | O_CREAT,
                   S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH);
    if(dog == -1)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    sprintf(path, "/srv/http/Names/%s.txt", exchange);
    int txtn;
    ind* txt = get_indlst(path, txtn, errors);
    if(!txt)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    int b = 0;
    write(dog, &b, sizeof(int));
    write(mrv, &b, sizeof(int));

    int size = FEED_SIZE * HISTORY_SIZE;
    int k = 0;
    float* data = (float*) malloc(sizeof(float) * size);
    for(int n = 0; n < ptrn; ++n)
    {
        const char* const name = get_unix_safe_name(names[n]);
        const ind* indfind = (ind*) bsearch(name, txt, txtn, sizeof(ind), compare_markets);
        if(!indfind)
            continue;

        b++;
        write(dog, indfind->name, NAME_SIZE);
        write(dog, indfind->title, TITLE_SIZE);

        sprintf(path, "/srv/http/bek/%s/%s", exchange, name);
        int fd = open(path, O_WRONLY | O_TRUNC | O_CREAT,
                      S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH);
        if(fd == -1)
        {
            push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
            continue;
        }

        ippsSet_32f(std::numeric_limits<float>::quiet_NaN(), data, size);

        char* start = ptr[n];
        char* end = (n == ptrn - 1) ? str : ptr[n + 1];
        eod_parse_line(data, start, end - start, errors);
        write_symbol_data(fd, data, errors);
        close(fd);

        float* hdata = data;
        int feedpackn = sizeof(feedpacklst) / sizeof(feedpack);
        for(int m = 0; m < feedpackn; ++m, hdata += HISTORY_SIZE)
            write(mrv, hdata, sizeof(float));
    }

    lseek(dog, 0, SEEK_SET);
    lseek(mrv, 0, SEEK_SET);
    write(dog, &b, sizeof(int));
    write(mrv, &b, sizeof(int));

    free(txt);
    close(mrv);
    close(dog);
    free(data);
}

void ohlcv_from_stdin(const char*, const char* exchange, void* app, node<message*>** errors)
{
    char* str = get_string_from_file();
    eod_parse_feed(str, exchange, app, errors);
    free(str);
}

void make_homlst_js(const char*, const char* path, void* app_, node<message*>** errors)
{
    int js = open(path, O_WRONLY | O_TRUNC | O_CREAT,
                  S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH);

    writef(js, "var homlst =\n");
    writef(js, "[\n");

    int marketn;
    const market* marketlst = get_marketlst(marketn);

    for(int n = 0; n < marketn; ++n, ++marketlst)
    {
        writef(js, "\t[\"%s\",\"%s\",\"%s\"],\n",
               marketlst->name, marketlst->title, marketlst->url);
    }

    writef(js, "];\n");
    close(js);
}

void echo_symbol_data(const float* data)
{
    static const feedpack* feedpack = feedpacklst;
    static const char** feedtypes = get_feedtypes();

    fprintf(stdout, "%10s%50s%30s%30s%20s%10s\t", "", "", "", "", "", "");
    for(int m = 0; m < BEKCHARTCOLS; ++m)
        fprintf(stdout, "%14d\t", m);

    fprintf(stdout, "\n");

    const float* hdata = data;
    fprintf(stdout, "%10s%50s%30s%30s%20s%10s\t", "", "", "", "", "", "");
    for(int m = 0; m < BEKCHARTCOLS; ++m)
        fprintf(stdout, "%.3f\t", *data++);
    data = hdata;

    fprintf(stdout, "\n");

    fprintf(stdout, "%10s%50s%30s%30s%20s%10s\t", "0", feedpack[0].title,
            feedpack[0].name, feedpack[0].name, feedtypes[feedpack[0].key], "");

    for(int m = 0; m < BEKCHARTCOLS; ++m)
    {
        float v = *data++;
        if(isnan(v))
        {
            fprintf(stdout, "%14s\t", "NAN");
            continue;
        }
        else if(isinf(v))
        {
            fprintf(stdout, "%14s\t", "INF");
            continue;
        }

        time_t t = (time_t) v;
        tm* tp = gmtime(&t);
        char str[LABEL_SIZE];
        strftime(str, LABEL_SIZE, " %m/%d/%Y", tp);
        fprintf(stdout, "%14s\t", str);
    }

    fprintf(stdout, "\n");
    for(int n = 1; n < FEED_SIZE; ++n)
    {
        fprintf(stdout, "%10d%50s%30s%30s%20s%10s\t", n, feedpack[n].title,
                feedpack[n].name, feedpack[n].name, feedtypes[feedpack[n].key], "");

        for(int m = 0; m < BEKCHARTCOLS; ++m)
        {
            float v = *data++;
            if(isnan(v))
            {
                fprintf(stdout, "%14s\t", "NAN");
                continue;
            }
            else if(isinf(v))
            {
                fprintf(stdout, "%14s\t", "INF");
                continue;
            }

            fprintf(stdout, "%14.3f\t", v);
        }

        fprintf(stdout, "\n");
    }
}

void echo_symbol_data(const char*, const char* path, void* app_, node<message*>** errors)
{
    application* app = (application*) app_;

    int fd = open(path, O_RDONLY);
    if(fd == -1)
    {
        push_message(errors, 0, 0, 1, __FILE__, __FUNCTION__, __LINE__, "bad path - %s", path);
        return;
    }

    int msize = sizeof(float) * FEED_SIZE * BEKCHARTCOLS;
    float* data = (float*)malloc(msize);
    read(fd, data, msize);
    close(fd);
    echo_symbol_data(data);
    free(data);
}

void make_dogpack(const char*, const char* exchange, void* app_, node<message*>** errors)
{
}
