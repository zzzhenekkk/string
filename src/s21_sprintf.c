#include "s21_string.h"

int s21_virtual_num(int num, char ch_num) {
    if (num) {
        num *= 10;
        num += (int)ch_num - 48;
    } else {
        num = (int)ch_num - 48;
    }
    return num;
}

void s21_putstr(char *buffer, char *str, options *OP) {
    int i = 0, j = s21_strlen(str);
    if (OP->opt_decimal > 0 && OP->opt_decimal < s21_strlen(str) && OP->opt_spec == 's') {
        j = OP->opt_decimal;
    }
    switch (OP->opt_height) {
        case 'l':
            while (str[i] && j != 0) {
            *buffer++ = (wchar_t)str[i++];
            j--;
            }
            break;
        default:
            while (str[i] && j != 0) {
            *buffer++ = str[i++];
            j--;
            }
    }
    *buffer = '\0';
}

char *s21_itoa(int num, char *buffer, int base, options *OP) {
    int current = 0, num_digits = 0, sign = 0;
    int number = num, k = num;
    if (number >= 0 && OP->opt_flag[1] == '+') {
        buffer[current++] = '+';
        sign++;
    } else if (number >= 0 && OP->opt_flag[1] != '+' && OP->opt_flag[2] == ' ') {
        buffer[current++] = ' ';
        sign++;
    }
    if (OP->opt_dot && OP->opt_decimal < 1 && number == 0) {
        buffer[current] = '\0';
        return buffer;
    }
    if (number == 0 && (OP->opt_flag[1] == '+' || OP->opt_flag[2] == ' ')) {
        buffer[current++] = '0';
        if (OP->opt_decimal) {
            int zeros;
            zeros = OP->opt_decimal - 1;
            while (zeros > 0) {
                buffer[current++] = '0';
                num_digits++;
                zeros--;
            }
        }
        buffer[current] = '\0';
        return buffer;
    } else if (number == 0 && OP->opt_flag[1] != '+' && OP->opt_flag[2] != ' ') {
        if (OP->opt_decimal) {
            for (int i = OP->opt_decimal; i > 0; i--)
                buffer[current++] = '0';
        } else {
            buffer[current++] = '0';
        }
        buffer[current] = '\0';
        return buffer;
    } else if (number < 0) {
        if (base == 10) {
            buffer[current++] = '-';
            sign++;
            number *= - 1;
        }
        // else {
        //     return s21_NULL;
        // }
    }
    while (k) {
        num_digits++;
        k /= 10;
    }
    num_digits += sign;
    if (OP->opt_decimal) {
        int zeros;
        zeros = OP->opt_decimal - num_digits + sign;
        while (zeros > 0) {
            buffer[current++] = '0';
            num_digits++;
            zeros--;
        }
        buffer[current] = '\0';
    }
    while (current < num_digits) {
        int base_val = (int)pow(base, num_digits - 1 - current);
        int num_val = number / base_val;
        char value = num_val + '0';
        buffer[current++] = value;
        number -= base_val * num_val;
    }
    buffer[current] = '\0';
    return buffer;
}

char *s21_long_itoa(long long int num, char *buffer, int base, options *OP) {
    int current = 0, num_digits = 0, sign = 0;
    long long int number = num, k = num;
    if (number >= 0 && OP->opt_flag[1] == '+') {
        buffer[current++] = '+';
        sign++;
    } else if (number >= 0 && OP->opt_flag[1] != '+' && OP->opt_flag[2] == ' ') {
        buffer[current++] = ' ';
        sign++;
    }
    if (OP->opt_dot && OP->opt_decimal < 1 && number == 0) {
        buffer[current] = '\0';
        return buffer;
    }
    if (number == 0 && (OP->opt_flag[1] == '+' || OP->opt_flag[2] == ' ')) {
        buffer[current++] = '0';
        if (OP->opt_decimal) {
            int zeros;
            zeros = OP->opt_decimal - 1;
            while (zeros > 0) {
                buffer[current++] = '0';
                num_digits++;
                zeros--;
            }
        }
        buffer[current] = '\0';
        return buffer;
    } else if (number == 0 && OP->opt_flag[1] != '+' && OP->opt_flag[2] != ' ') {
        if (OP->opt_decimal) {
            for (int i = OP->opt_decimal; i > 0; i--)
                buffer[current++] = '0';
        } else {
            buffer[current++] = '0';
        }
        buffer[current] = '\0';
        return buffer;
    } else if (number < 0) {
        if (base == 10) {
            buffer[current++] = '-';
            sign++;
            number *= - 1;
        }
        // else {
        //     return s21_NULL;
        // }
    }
    while (k) {
        num_digits++;
        k /= 10;
    }
    num_digits += sign;
    if (OP->opt_decimal) {
        int zeros;
        zeros = OP->opt_decimal - num_digits + sign;
        while (zeros > 0) {
            buffer[current++] = '0';
            num_digits++;
            zeros--;
        }
        buffer[current] = '\0';
    }
    while (current < num_digits) {
        long long int base_val = (long long int)pow(base, num_digits - 1 - current);
        long long int num_val = number / base_val;
        char value = num_val + '0';
        buffer[current++] = value;
        number -= base_val * num_val;
    }
    buffer[current] = '\0';
    return buffer;
}

char *s21_short_itoa(short int num, char *buffer, int base, options *OP) {
    int current = 0, num_digits = 0, sign = 0;
    short int number = num, k = num;
    if (number >= 0 && OP->opt_flag[1] == '+') {
        buffer[current++] = '+';
        sign++;
    } else if (number >= 0 && OP->opt_flag[1] != '+' && OP->opt_flag[2] == ' ') {
        buffer[current++] = ' ';
        sign++;
    }
    if (OP->opt_dot && OP->opt_decimal < 1 && number == 0) {
        buffer[current] = '\0';
        return buffer;
    }
    if (number == 0 && (OP->opt_flag[1] == '+' || OP->opt_flag[2] == ' ')) {
        buffer[current++] = '0';
        if (OP->opt_decimal > 0) {
            int zeros;
            zeros = OP->opt_decimal - 1;
            while (zeros > 0) {
                buffer[current++] = '0';
                num_digits++;
                zeros--;
            }
        }
        buffer[current] = '\0';
        return buffer;
    } else if (number == 0 && OP->opt_flag[1] != '+' && OP->opt_flag[2] != ' ') {
        if (OP->opt_decimal) {
            for (int i = OP->opt_decimal; i > 0; i--)
                buffer[current++] = '0';
        } else {
            buffer[current++] = '0';
        }
        buffer[current] = '\0';
        return buffer;
    } else if (number < 0) {
        if (base == 10) {
            buffer[current++] = '-';
            sign++;
            number *= - 1;
        }
        // else {
        //     return s21_NULL;
        // }
    }
    while (k) {
        num_digits++;
        k /= 10;
    }
    num_digits += sign;
    if (OP->opt_decimal) {
        int zeros;
        zeros = OP->opt_decimal - num_digits + sign;
        while (zeros > 0) {
            buffer[current++] = '0';
            num_digits++;
            zeros--;
        }
        buffer[current] = '\0';
    }
    while (current < num_digits) {
        int base_val = (int)pow(base, num_digits - 1 - current);
        int num_val = number / base_val;
        char value = num_val + '0';
        buffer[current++] = value;
        number -= base_val * num_val;
    }
    buffer[current] = '\0';
    return buffer;
}

void s21_putnbr(char *buffer, long long int n, options *OP) {
    if (OP->opt_dot == 1 && OP->opt_decimal == 0 && n == 0 && OP->opt_flag[0] != '-' &&
        OP->opt_flag[1] != '+' && OP->opt_flag[2] != ' ') {
        buffer[0] = '\0';
    } else {
        switch (OP->opt_height) {
            case 'l': s21_long_itoa((long long int)n, buffer, 10, OP); break;
            case 'h': s21_short_itoa((short int)n, buffer, 10, OP); break;
            default: s21_itoa((int)n, buffer, 10, OP);
        }
    }
}

void s21_reverse(char *buffer, int len) {
    int i = 0, j = len - 1;
    while (i < j) {
        int temp = buffer[i];
        buffer[i++] = buffer[j];
        buffer[j--] = temp;
    }
}

char *s21_gcvt(double f, s21_size_t ndigit, char *buf, options *OP) {
    s21_size_t i;
    unsigned long long z, k;
    char *c = buf;
    double f2, t, scal;
    int sign = 0;

    // if ((int)ndigit == -1) {
    //     ndigit = 5;
    // }
    // if (ndigit > 20) {
    //     ndigit = 20;
    // }
    if (f < 0.0) {
        sign = 1;
        f = -f;
        *buf++ = '-';
    }
    if (OP->opt_flag[1] == '+' && !sign) {
        *buf++ = '+';
    }
    if (OP->opt_flag[1] != '+' && !sign && OP->opt_flag[2] == ' ') {
        *buf++ = ' ';
    }
    scal = 1;
    for (i = ndigit; i > 0; i--) {
        scal *= 10;
    }
    k = f + 0.1 / scal;
    f2 = f - k;
    if (!f) {
        *buf++ = '0';
        if (ndigit > 0) {
            *buf++ = '.';
        }
        for (i = 0; i < ndigit; i++) {
            *buf++ = '0';
        }
        *buf++ = 0;
        return c;
    }
    i = 1;
    while (f >= 10.0) {
        f /= 10.0;
        i++;
    }
    buf += i + ndigit + 1;
    *buf-- = 0;
    if (ndigit > 0) {
        t = f2 * scal;
        z = t + 0.5;
        for (i = 0; i < ndigit; i++) {
            *buf-- = '0' + (z % 10);
            z /= 10;
        }
        *buf-- = '.';
    }
    // else {
    //     *buf-- = 0;
    // }
    do {
        *buf-- = '0' + (k % 10);
        k /= 10;
    } while (k);
    return c;
}

void s21_putdbl(char *res, double n, options *OP) {
    if (OP->opt_dot && OP->opt_decimal < 1) {
        s21_putnbr(res, round(n), OP);
    } else {
        int len = 6;
        if (OP->opt_decimal > 0) {
            len = OP->opt_decimal;
        }
        s21_gcvt(n, len, res, OP);
    }
}

char *s21_utoa(unsigned int n, options *OP) {
    char *res, buf[512];
    unsigned int number = n;
    unsigned int i, counter = 0, num_digits = 0, k = n;
    for (; k; k /= 10) {
        num_digits++;
    }
    if (OP->opt_decimal) {
        if (number > 0) {
            for (int j = OP->opt_decimal - num_digits; j > 0; j--) {
                buf[counter++] = '0';
            }
        }
        // else {
        //     for (int j = OP->opt_decimal - 1; j > 0; j--) {
        //         buf[counter++] = '0';
        //     }
        // }
    }
    if (number == 0) {
        buf[counter++] = '0';
    }
    for (; number; number /= 10) {
        buf[counter++] = "0123456789" [number%10];
    }
    res = malloc((counter + 1) * sizeof(char));
    for (i = 0; i < counter - num_digits; i++) {
        res[i] = buf[i];
    }
    s21_reverse(&buf[i], num_digits);
    for (i = 0; i < counter; i++) {
        res[i] = buf[i];
    }
    res[counter] = '\0';
    return res;
}

char *s21_long_utoa(unsigned long long int n, options *OP) {
    char *res, buf[512];
    unsigned long long int number = n;
    unsigned long long int k = n;
    unsigned int i, counter = 0, num_digits = 0;
    for (; k; k /= 10) {
        num_digits++;
    }
    if (OP->opt_decimal) {
        if (number > 0) {
            for (int j = OP->opt_decimal - num_digits; j > 0; j--) {
                buf[counter++] = '0';
            }
        }
        // else {
        //     for (int j = OP->opt_decimal - 1; j > 0; j--) {
        //         buf[counter++] = '0';
        //     }
        // }
    }
    if (number == 0) {
        res = malloc(2 * sizeof(char));
        res[0] = '0';
        res[1] = '\0';
        return res;
    } else {
        for (; number; number /= 10) {
            buf[counter++] = "0123456789" [number%10];
        }
        res = malloc((counter + 1) * sizeof(char));
        for (i = 0; i < counter - num_digits; i++) {
            res[i] = buf[i];
        }
        s21_reverse(&buf[i], num_digits);
        for (i = 0; i < counter; i++) {
            res[i] = buf[i];
        }
        res[counter] = '\0';
    }
    return res;
}

char *s21_short_utoa(unsigned short int n, options *OP) {
    char *res, buf[512];
    unsigned short int number = n;
    unsigned int i, counter = 0, num_digits = 0, k = n;
    for (; k; k /= 10) {
        num_digits++;
    }
    if (OP->opt_decimal) {
        if (number > 0) {
            for (int j = OP->opt_decimal - num_digits; j > 0; j--) {
                buf[counter++] = '0';
            }
        }
        // else {
        //     for (int j = OP->opt_decimal - 1; j > 0; j--) {
        //         buf[counter++] = '0';
        //     }
        // }
    }
    if (number == 0) {
        res = malloc(2 * sizeof(char));
        res[0] = '0';
        res[1] = '\0';
        return res;
    } else {
        for (; number; number /= 10) {
            buf[counter++] = "0123456789" [number%10];
        }
        res = malloc((counter + 1) * sizeof(char));
        for (i = 0; i < counter - num_digits; i++) {
            res[i] = buf[i];
        }
        s21_reverse(&buf[i], num_digits);
        for (i = 0; i < counter; i++) {
            res[i] = buf[i];
        }
        res[counter] = '\0';
    }
    return res;
}

void s21_put_unsigned_nbr(char *buffer, unsigned long long int n, options *OP) {
    if (OP->opt_dot == 1 && OP->opt_decimal == 0 && n == 0 && OP->opt_flag[0] != '-' &&
        OP->opt_flag[1] != '+' && OP->opt_flag[2] != ' ') {
        buffer[0] = '\0';
    } else if (OP->opt_dot == 1 && OP->opt_decimal > 0 && n == 0) {
        for (int j = OP->opt_decimal; j > 0; j--) {
            *buffer++ = '0';
        }
        *buffer = '\0';
    } else {
        char *nbr;
        switch (OP->opt_height) {
            case 'l': nbr = s21_long_utoa((unsigned long long int)n, OP); break;
            case 'h': nbr = s21_short_utoa((unsigned short int)n, OP); break;
            default: nbr = s21_utoa((unsigned int)n, OP); break;
    }
    s21_putstr(buffer, nbr, OP);
    free(nbr);
    }
}

void s21_char(char *buff, int c, options *OP) {
    switch (OP->opt_height) {
        case 'l': *buff++ = (wint_t)c; break;
        default: *buff++ = c;
    }
    *buff = '\0';
}

void s21_identify(char *buff, options *OP, va_list arg) {
    switch (OP->opt_spec) {
        case 'c': s21_char(buff, va_arg(arg, int), OP); break;
        case 's': s21_putstr(buff, va_arg(arg, char *), OP); break;
        case 'd':
        case 'i': s21_putnbr(buff, va_arg(arg, long long int), OP); break;
        case 'u': s21_put_unsigned_nbr(buff, va_arg(arg, long long int), OP); break;
        case 'f': s21_putdbl(buff, va_arg(arg, double), OP); break;
        case '%': *buff++ = '%'; *buff = '\0';
    }
}

int s21_dot(char *parse_buff, char *numbers, options *OP) {
    int parse_len = 1;
    parse_buff++;
    while (*parse_buff) {
        int check = 0;
        for (int i = 0; i < 11; i++) {
            if (*parse_buff == numbers[i]) {
                OP->opt_decimal = s21_virtual_num(OP->opt_decimal, numbers[i]);
                check++;
            }
        }
        if (!check) {
            break;
        } else {
            parse_buff++;
            parse_len++;
        }
    }
    return parse_len;
}

int s21_post_parse(char spec, char *parse_buff, char *identify_buff, char *buffer, va_list arg) {
    char numbers[11] = "0123456789";
    options OP = {'\0'};
    while (*parse_buff) {
        for (int i = 0; i < 11; i++) {
            if (*parse_buff == numbers[i]) {
                OP.opt_width = s21_virtual_num(OP.opt_width, numbers[i]);
            }
        }
        switch (*parse_buff) {
            case '-': OP.opt_flag[0] = '-'; parse_buff++; break;
            case '+': OP.opt_flag[1] = '+'; parse_buff++; break;
            case ' ': OP.opt_flag[2] = ' '; parse_buff++; break;
            case '.': OP.opt_dot = 1; parse_buff += s21_dot(parse_buff, numbers, &OP); break;
            case 'h': OP.opt_height = 'h'; parse_buff++; break;
            case 'l': OP.opt_height = 'l'; parse_buff++; break;
            default: parse_buff++;
        }
    }
    OP.opt_spec = spec;
    s21_identify(identify_buff, &OP, arg);
    if (!OP.opt_width) {
        OP.opt_width = s21_strlen(identify_buff);
    }
    int space;
    if (OP.opt_width > s21_strlen(identify_buff) && OP.opt_flag[0] != '-') {
        space = OP.opt_width - s21_strlen(identify_buff);
        while (space > 0) {
            *buffer = ' ';
            buffer++, space--;
        }
    }
    if (s21_strlen(identify_buff) > OP.opt_width) {
        OP.opt_width = s21_strlen(identify_buff);
    }
    while (*identify_buff) {
        *buffer = *identify_buff;
        buffer++, identify_buff++;
    }
    if (OP.opt_width > s21_strlen(identify_buff) && OP.opt_flag[0] == '-') {
        space = OP.opt_width - s21_strlen(identify_buff);
        while (space > 0) {
            *buffer = ' ';
            buffer++, space--;
        }
    }
    return OP.opt_width;
}

void s21_parse(char *buffer, const char *str, va_list arg) {
    while (*str) {
        if (*str == '%') {
            str++;
            char parse_buff[4096];
            char identify_buff[4096];
            char buff[8] = "dcsifu%";
            char spec;
            int my_flag = 0;
            int index = 0;

            while (*str) {
                for (int i = 0; i < s21_strlen(buff); i++) {
                    if (*str == buff[i]) {
                        spec = *str;
                        my_flag++;
                        break;
                    }
                }
                if (my_flag) {
                    break;
                }
                parse_buff[index] = *str;
                str++, index++;
            }
            parse_buff[index] = '\0';
            buffer += s21_post_parse(spec, parse_buff, identify_buff, buffer, arg);
        } else {
            *buffer = *str;
            buffer++;
        }
        str++;
    }
    *buffer = '\0';
}

int s21_sprintf(char *buffer, const char *str, ...) {
    va_list arg;
    va_start(arg, str);
    s21_parse(buffer, str, arg);
    va_end(arg);
    return s21_strlen(buffer);
}
