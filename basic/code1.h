#pragma once

#define INT_MAX 4294967295U
#define INT_SIGNED_MAX 2147483647
#ifdef __cplusplus
template <typename T>
struct basic_expn
{
    char *error;
    T reason;
    char *onRunning;
};
template <typename T>
basic_expn<T> cbasic_expn(char *error, T reason, char *onRunning)
{
    return basic_expn<T>{error, reason, onRunning};
}
#endif
struct basic_Decimal
{
    int top;
    unsigned int other[8];

#ifdef __cplusplus
protected:
#endif
    int scale;

#ifdef __cplusplus
public:
    basic_Decimal() : basic_Decimal(0) {}
    basic_Decimal(int v)
    {
        other[7] = v & 0x7fffffff;
        top = v < 0 ? 0x80000000 : 0;
        scale = 0;
    }
    basic_Decimal(basic_Decimal &v)
    {
        top = v.top;
        for (int i = 0; i < 8; i++)
        {
            other[i] = v.other[i];
        }
        scale = v.scale;
    }
    basic_Decimal(char v[])
    {
        char buffer;
        int ibuffer;
        int pos;
        int flag;
        int flip;

        pos = 0;
        flag = 0;
        flip = 0;

        do
        {
            buffer = v[pos];
            switch (buffer)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                ibuffer = (int)buffer - 48;
            case '.':
                flag = 1;
            case '-':
                flip = 1;
            case '\0':
                break;
            default:
                throw cbasic_expn(
                    "Unexpected Token",
                    buffer,
                    "basic_Decimal::basic_Decimal(char*)\non do...while(int)\non switch(char)");
            }
        } while (buffer == '\0');
    }
#endif
};
#define string char **

/* Returns absolute number */
basic_Decimal basic_abs(basic_Decimal);

/* Returns boolean AND or bitwise */
basic_Decimal basic_and(basic_Decimal, basic_Decimal);
#ifdef __cplusplus
basic_Decimal operatorAND(basic_Decimal &left, basic_Decimal &right)
{
    return basic_and(left, right);
}
#endif

/* Returns PETSCII raw intager */
basic_Decimal basic_asc(string);

/* Returns ArcTangent */
basic_Decimal basic_atn(basic_Decimal);

/* C128: Sets the RAM banks to use for PEEK, POKE, SYS
 * BANK m => RAM
 */
void basic_bank(unsigned char);

/* C128: Sets the RAM and ROM banks to use for PEEK, POKE, SYS
 * BANK m,n => RAM,ROM
 */
void basic_bank(unsigned char, unsigned char);

/* X16: String of binary value */
string basic_bin$(basic_Decimal);

/* X16: Read block of data from file */
string basic_binput(int, string &, int);

/* X16: Load headerles binary from disk -> memory */
string basic_bload(string, int, int, unsigned char);

/* X16: Force load AUTOBOOT.X16 PRG */
void x16_boot();