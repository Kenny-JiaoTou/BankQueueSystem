/**
 * @file date.c
 * @brief 日期类及相关操作
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../include/util/Date.h"


Date get_cur_date() {
	Date date;
	time_t timet;
	struct tm* pTime;
	time(&timet);
	pTime = localtime(&timet);
	date.year = pTime->tm_year + 1900;
	date.month = pTime->tm_mon;
	date.day = pTime->tm_mday;
	date.hour = pTime->tm_hour;
	date.minute = pTime->tm_min;
	date.second = pTime->tm_sec;
	return date;
}

char* get_cur_date_str() {
    char* date_str = malloc(sizeof(char) * 64);
    time_t current_time;
    time(&current_time);        //获取当前的时间
    struct tm* p_time = localtime(&current_time);
    //将时间转换为字符串
    strftime(date_str, strlen(date_str), "%Y-%m-%d %H:%M:%S", p_time);
    return date_str;
}

void show_date(FILE* file, Date date) {
	fprintf(file, "[%d-%d-%d %d:%d:%d]", date.year, date.month, date.day, date.hour, date.minute, date.second);
}

time_t str_to_time(char* str_time)
{
	struct tm pTime;
	time_t timet;
	strptime(str_time, "%Y-%m-%d %H:%M:%S", &pTime);
	return mktime(&pTime);
}

/** 计算两个字符串时间日期之差 */
long get_date_diff(char* str_time1, char* str_time2)
{
    return str_to_time(str_time1) - str_to_time(str_time2);
}


static int conv_num(const char** buf, int* dest, int llim, int ulim)
{
	int result = 0;

	/* The limit also determines the number of valid digits. */
	int rulim = ulim;

	if (**buf < '0' || **buf > '9')
		return (0);

	do {
		result *= 10;
		result += *(*buf)++ - '0';
		rulim /= 10;
	} while ((result * 10 <= ulim) && rulim && **buf >= '0' && **buf <= '9');

	if (result < llim || result > ulim)
		return (0);

	*dest = result;
	return (1);
}

char* strptime(const char* buf, const char* fmt, struct tm* tm)
{
    char c;
    const char* bp;
    size_t len = 0;
    int alt_format, i, split_year = 0;

    bp = buf;

    while ((c = *fmt) != '\0') {
        /* Clear `alternate' modifier prior to new conversion. */
        alt_format = 0;

        /* Eat up white-space. */
        if (isspace(c)) {
            while (isspace(*bp))
                bp++;

            fmt++;
            continue;
        }

        if ((c = *fmt++) != '%')
            goto literal;


    again:    switch (c = *fmt++) {
    case '%': /* "%%" is converted to "%". */
        literal :
            if (c != *bp++)
                return (0);
        break;

        /*
         * "Alternative" modifiers. Just set the appropriate flag
         * and start over again.
         */
    case 'E': /* "%E?" alternative conversion modifier. */
        LEGAL_ALT(0);
        alt_format |= ALT_E;
        goto again;

    case 'O': /* "%O?" alternative conversion modifier. */
        LEGAL_ALT(0);
        alt_format |= ALT_O;
        goto again;

        /*
         * "Complex" conversion rules, implemented through recursion.
         */
    case 'c': /* Date and time, using the locale's format. */
        LEGAL_ALT(ALT_E);
        if (!(bp = strptime(bp, "%x %X", tm)))
            return (0);
        break;

    case 'D': /* The date as "%m/%d/%y". */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%m/%d/%y", tm)))
            return (0);
        break;

    case 'R': /* The time as "%H:%M". */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%H:%M", tm)))
            return (0);
        break;

    case 'r': /* The time in 12-hour clock representation. */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%I:%M:%S %p", tm)))
            return (0);
        break;

    case 'T': /* The time as "%H:%M:%S". */
        LEGAL_ALT(0);
        if (!(bp = strptime(bp, "%H:%M:%S", tm)))
            return (0);
        break;

    case 'X': /* The time, using the locale's format. */
        LEGAL_ALT(ALT_E);
        if (!(bp = strptime(bp, "%H:%M:%S", tm)))
            return (0);
        break;

    case 'x': /* The date, using the locale's format. */
        LEGAL_ALT(ALT_E);
        if (!(bp = strptime(bp, "%m/%d/%y", tm)))
            return (0);
        break;

        /*
         * "Elementary" conversion rules.
         */
    case 'A': /* The day of week, using the locale's form. */
    case 'a':
        LEGAL_ALT(0);
        for (i = 0; i < 7; i++) {
            /* Full name. */
            len = strlen(day[i]);
            if (strncmp(day[i], bp, len) == 0)
                break;

            /* Abbreviated name. */
            len = strlen(abday[i]);
            if (strncmp(abday[i], bp, len) == 0)
                break;
        }

        /* Nothing matched. */
        if (i == 7)
            return (0);

        tm->tm_wday = i;
        bp += len;
        break;

    case 'B': /* The month, using the locale's form. */
    case 'b':
    case 'h':
        LEGAL_ALT(0);
        for (i = 0; i < 12; i++) {
            /* Full name. */
            len = strlen(mon[i]);
            if (strncmp(mon[i], bp, len) == 0)
                break;

            /* Abbreviated name. */
            len = strlen(abmon[i]);
            if (strncmp(abmon[i], bp, len) == 0)
                break;
        }

        /* Nothing matched. */
        if (i == 12)
            return (0);

        tm->tm_mon = i;
        bp += len;
        break;

    case 'C': /* The century number. */
        LEGAL_ALT(ALT_E);
        if (!(conv_num(&bp, &i, 0, 99)))
            return (0);

        if (split_year) {
            tm->tm_year = (tm->tm_year % 100) + (i * 100);
        }
        else {
            tm->tm_year = i * 100;
            split_year = 1;
        }
        break;

    case 'd': /* The day of month. */
    case 'e':
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_mday, 1, 31)))
            return (0);
        break;

    case 'k': /* The hour (24-hour clock representation). */
        LEGAL_ALT(0);
        /* FALLTHROUGH */
    case 'H':
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_hour, 0, 23)))
            return (0);
        break;

    case 'l': /* The hour (12-hour clock representation). */
        LEGAL_ALT(0);
        /* FALLTHROUGH */
    case 'I':
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_hour, 1, 12)))
            return (0);
        if (tm->tm_hour == 12)
            tm->tm_hour = 0;
        break;

    case 'j': /* The day of year. */
        LEGAL_ALT(0);
        if (!(conv_num(&bp, &i, 1, 366)))
            return (0);
        tm->tm_yday = i - 1;
        break;

    case 'M': /* The minute. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_min, 0, 59)))
            return (0);
        break;

    case 'm': /* The month. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &i, 1, 12)))
            return (0);
        tm->tm_mon = i - 1;
        break;

    case 'p': /* The locale's equivalent of AM/PM. */
        LEGAL_ALT(0);
        /* AM? */
        if (strcmp(am_pm[0], bp) == 0) {
            if (tm->tm_hour > 11)
                return (0);

            bp += strlen(am_pm[0]);
            break;
        }
        /* PM? */
        else if (strcmp(am_pm[1], bp) == 0) {
            if (tm->tm_hour > 11)
                return (0);

            tm->tm_hour += 12;
            bp += strlen(am_pm[1]);
            break;
        }

        /* Nothing matched. */
        return (0);

    case 'S': /* The seconds. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_sec, 0, 61)))
            return (0);
        break;

    case 'U': /* The week of year, beginning on sunday. */
    case 'W': /* The week of year, beginning on monday. */
        LEGAL_ALT(ALT_O);
        /*
         * XXX This is bogus, as we can not assume any valid
         * information present in the tm structure at this
         * point to calculate a real value, so just check the
         * range for now.
         */
        if (!(conv_num(&bp, &i, 0, 53)))
            return (0);
        break;

    case 'w': /* The day of week, beginning on sunday. */
        LEGAL_ALT(ALT_O);
        if (!(conv_num(&bp, &tm->tm_wday, 0, 6)))
            return (0);
        break;

    case 'Y': /* The year. */
        LEGAL_ALT(ALT_E);
        if (!(conv_num(&bp, &i, 0, 9999)))
            return (0);

        tm->tm_year = i - TM_YEAR_BASE;
        break;

    case 'y': /* The year within 100 years of the epoch. */
        LEGAL_ALT(ALT_E | ALT_O);
        if (!(conv_num(&bp, &i, 0, 99)))
            return (0);

        if (split_year) {
            tm->tm_year = ((tm->tm_year / 100) * 100) + i;
            break;
        }
        split_year = 1;
        if (i <= 68)
            tm->tm_year = i + 2000 - TM_YEAR_BASE;
        else
            tm->tm_year = i + 1900 - TM_YEAR_BASE;
        break;

        /*
         * Miscellaneous conversions.
         */
    case 'n': /* Any kind of white-space. */
    case 't':
        LEGAL_ALT(0);
        while (isspace(*bp))
            bp++;
        break;


    default:  /* Unknown/unsupported conversion. */
        return (0);
    }
    }
    /* LINTED functional specification */
    return ((char*)bp);
}