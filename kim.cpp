#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <png.hpp>
#include <colors.hpp>
#include <util.hpp>

static const int GIACOLS = 7;
static const int GIAROWS = 5;
static const int GIASIZE = 35;
static const int CHARTCOLS = 10;
static const int CHARTROWS = 10;
static const int HALZOESIZE = 200;
static const int BEKCHARTROWS = 40;
static const int LINEWIDTH = 3;
static const int DIVEXENT = 2;
static const int ROWMARGIN = 2;
static const int GIAHEIGHTSTART = 320;
static const int LASTGIAHEIGHT = 644;
static const int DEVMARGIN = 2;
