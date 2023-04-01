/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Copyright Enrico Sorichetti 2019 - 2019
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#include <stdio.h>

#define BASE 16
char enctab[BASE] ;
char dectab[256] ;

int main()
{
    int c ;
    char t = 0 ;

    for (c=0;c<256;c++)
        dectab[c] = -1 ;

    for (c='0';c<='9';c++)
    {
        enctab[t]=c;
        dectab[c]=t++;
    }

    for (c='A';c<='F';c++)
    {
        enctab[t]=c;
        dectab[c]=t;
        dectab[c+('a'-'A')]=t;
        t++;
    }

    dectab['=']=64 ;            /* byte delete char */

    /* print the guards */
    printf( "#ifndef base%d_tables_included\n", BASE) ;
    printf( "#define base%d_tables_included\n\n", BASE) ;

    /* print the forward and reverse tables */
    printf( "  const unsigned char tbl%denc[%d] = {\n", BASE, BASE ) ;
    for (t=0;t<BASE-1;t++)
        switch (t & 0xf)
        {
            case 0:  printf( "    '%c',", enctab[t] ) ;
                     break ;
            case 15: printf( "'%c',\n",   enctab[t] ) ;
                     break ;
            default: printf( "'%c',",     enctab[t] ) ;
                     break ;
        }
    printf( "'%c'} ;\n\n", enctab[BASE-1] ) ;

    printf( "  const unsigned char tbl%ddec[256] = {\n",BASE ) ;
    for (c=0;c<255;c++)
        switch (c & 0xf)
        {
            case 0:  printf( "    %2d,", dectab[c] ) ;
                     break ;
            case 15: printf( " %2d,\n",  dectab[c] ) ;
                     break ;
            default: printf( " %2d,",    dectab[c] ) ;
                     break ;
        }
    printf( " %2d} ;\n\n", dectab[255]) ;

    /* print the guards */
    printf( "#endif  //  #ifndef base%d_tables_included\n", BASE);

} /* main */
