#ifndef	DS_LIB_H
#define	DS_LIB_H

#define DS_MAGIC_STRING "$DSMAGIC"
#define DS_MAGIC_NUMBER 0xbadf00d

#define DS_STR_HELPER(X) #X
#define DS_STR(X) DS_STR_HELPER(X)
#define DS_NEWLINE '\n'

#define DS_ROUND(X) ( (X) > 0 ? (((X) - (int)(X)) < 0.50) ? (int)(X) : (int)(X)+1 : ((-(X) - (int)(X)) < 0.50) ? (int)(X) : (int)(X)+(-1) )
#define DS_MIN(a,b) ((a) < (b) ? (a) : (b))
#define DS_MAX(a,b) ((a) > (b) ? (a) : (b))
#define DS_PI 3.14159265358979323846f
//#define DS_PI 3.141592653 
#define DS_DEG2RAD(a) ((a)*(DS_PI/180))
#define DS_RAD2DEG (a) ((a)*(180/DS_PI))

#define DS_ISEVEN(n)   ((n%2 == 0) ? 1 : 0)
#define DS_ISODD(n)    ((n%2 != 0) ? 1 : 0)

#define DS_ISNULL(X)    ((X == NULL) ? printf("%s\n", "IS NULL!") : 0)
#define DS_PRINTB(X)    ((X == FALSE) ? printf("%s\n", "dslib: FALSE") : printf("%s\n", "dslib: TRUE") )
#define DS_ISBETWEEN(value, min, max) (value < max && value > min) // if(DS_ISBETWEEN(5, 1, 101)){ ... }

#define DS_HEXTONIBBLE(c) (*(c) >= 'A' ? (*(c) - 'A')+10 : (*(c)-'0'))
#define DS_HEXTOBYTE(c) (DS_HEXTONIBBLE(c)*16 + DS_HEXTONIBBLE(c+1))

//#define ISHEX(X) (X[strspn(X, "0123456789abcdefABCDEF")] == 0) ? 1 : 0
//#define ISHEXBYTE(X) (strlen(X) == 2 && (X[strspn(X, "0123456789abcdefABCDEF")] == 0)) ? 1 : 0


/* types */
#ifndef FALSE
 #define FALSE (0)
#endif
#ifndef TRUE
 #define TRUE (!FALSE)
#endif
#ifndef boolean
 #define boolean unsigned char
#endif
/*
#ifndef byte
 #define byte unsigned char
#endif
#ifndef var
 #define var unsigned int
#endif
*/


typedef enum {
    DSE_TYPE_START = 64, 
    DSE_TYPE_CHAR, 
    DSE_TYPE_UCHAR, 
    DSE_TYPE_FLOAT, 
    DSE_TYPE_DOUBLE, 
    DSE_TYPE_LDOUBLE, 
    DSE_TYPE_SHORT, 
    DSE_TYPE_USHORT, 
    DSE_TYPE_INT, 
    DSE_TYPE_UINT, 
    DSE_TYPE_LONG, 
    DSE_TYPE_ULONG, 
    DSE_TYPE_END, 
} DSTypeEnum;





#endif
