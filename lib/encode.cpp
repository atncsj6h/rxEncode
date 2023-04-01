/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Copyright Enrico Sorichetti 2019 - 2019
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "tables16.h"
#include "tables32.h"
#include "tables64.h"

size_t encode16(  char *Dest, const  char *Srce, const size_t lSrce )
{
  char *pDest = ( char *)Dest;
  char *pSrce = ( char *)Srce;
  size_t i;

  for ( i = 0; i < lSrce; i++)
  {
    *pDest++ = tbl16enc[ (pSrce[i] & 0xf0) >> 4 ] ;
    *pDest++ = tbl16enc[ (pSrce[i] & 0x0f) ] ;
  }

#ifdef NULL_TERMINATED_STRINGS
    *pDest = '\x0' ;
#endif
  return pDest-Dest ;
}

size_t encode32(  char *Dest, const  char *Srce, const size_t lSrce)
{
  char *pDest = ( char *)Dest;
  char *pSrce = ( char *)Srce;
  size_t i,j,r;
  char wrk[5];
  r = lSrce % 5 ;
  for ( i = 0; i < lSrce-r; i+=5)
  {
    *pDest++ = tbl32enc[ (pSrce[i  ] & 0xf8) >> 3 ] ;
    *pDest++ = tbl32enc[((pSrce[i  ] & 0x07) << 2) | ((pSrce[i+1] & 0xc0) >> 6) ];
    *pDest++ = tbl32enc[ (pSrce[i+1] & 0x3e) >> 1  ];
    *pDest++ = tbl32enc[((pSrce[i+1] & 0x01) << 4) | ((pSrce[i+2] & 0xf0) >> 4) ];
    *pDest++ = tbl32enc[((pSrce[i+2] & 0x0f) << 1) | ((pSrce[i+3] & 0x80) >> 7) ];
    *pDest++ = tbl32enc[ (pSrce[i+3] & 0x7f) >> 2  ];
    *pDest++ = tbl32enc[((pSrce[i+3] & 0x03) << 3) | ((pSrce[i+4] & 0xe0) >> 5) ];
    *pDest++ = tbl32enc[  pSrce[i+4] & 0x1f ] ;
  }
  if ( r > 0 )
  {
    #pragma unroll
    for (j=0; j<5; j++)
      wrk[j]= ( j < r  ? pSrce[i+j] : 0 );
    i = lSrce - r ; // ???
    *pDest++ =                tbl32enc[ (wrk[  0] & 0xf8) >> 3  ] ;
    *pDest++ =                tbl32enc[((wrk[  0] & 0x07) << 2) | ((wrk[ 1] & 0xc0) >> 6) ] ;
    *pDest++ = (r < 2 ? '=' : tbl32enc[ (wrk[  1] & 0x3e) >> 1  ] ) ;
    *pDest++ = (r < 2 ? '=' : tbl32enc[((wrk[  1] & 0x01) << 4) | ((wrk[ 2] & 0xf0) >> 4) ] );
    *pDest++ = (r < 3 ? '=' : tbl32enc[((wrk[  2] & 0x0f) << 1) | ((wrk[ 3] & 0x80) >> 7) ] );
    *pDest++ = (r < 4 ? '=' : tbl32enc[ (wrk[  3] & 0x7f) >> 2  ] );
    *pDest++ = (r < 4 ? '=' : tbl32enc[((wrk[  3] & 0x03) << 3) | ((wrk[ 4] & 0xe0) >> 5) ] );
    *pDest++ = (r < 5 ? '=' : tbl32enc[  wrk[  4] & 0x1f ] );
  }

#ifdef NULL_TERMINATED_STRINGS
  *pDest = '\x0' ;
#endif
  return pDest-Dest ;
}

size_t encode64(  char *Dest, const  char *Srce, const size_t lSrce )
{
  char *pDest = ( char *)Dest;
  char *pSrce = ( char *)Srce;

  size_t i,j,r;
  char wrk[3];
  r = lSrce % 3 ;
  for ( i = 0; i < lSrce-r; i+=3)
  {
    *pDest++ = tbl64enc[ (pSrce[i  ] & 0xfc) >> 2 ];
    *pDest++ = tbl64enc[((pSrce[i  ] & 0x03) << 4) | ((pSrce[i+1] & 0xf0) >> 4) ] ;
    *pDest++ = tbl64enc[((pSrce[i+1] & 0x0f) << 2) | ((pSrce[i+2] & 0xc0) >> 6) ] ;
    *pDest++ = tbl64enc[  pSrce[i+2] & 0x3f ] ;
  }
  if ( r > 0 )
  {
    #pragma unroll
    for (j=0; j<3; j++)
      wrk[j]= ( j < r  ? pSrce[i+j] : 0 );
    i = lSrce - r ; //???
    *pDest++ = tbl64enc[ (wrk[0  ] & 0xfc) >> 2 ];
    *pDest++ = tbl64enc[((wrk[0  ] & 0x03) << 4) | ((wrk[1] & 0xf0) >> 4) ] ;
    *pDest++ = (r < 2 ? '=' : tbl64enc[((wrk[1] & 0x0f) << 2) | ((wrk[2] & 0xc0) >> 6) ]  );
    *pDest++ = (r < 3 ? '=' : tbl64enc[wrk[2] & 0x3f ] );
  }

#ifdef NULL_TERMINATED_STRINGS
  *pDest = '\x0' ;
#endif
  return pDest-Dest ;
}

size_t decode16(  char *Dest, const  char *Srce, const size_t lSrce )
{
  char *pDest = ( char *)Dest;
  char *pSrce = ( char *)Srce;

  size_t i,j;
  char buf[2] ;

  if( !pDest || !pSrce || ( lSrce % 2 != 0 ) )
    return 0 ;

  for ( i = 0; i < lSrce; i+=2)
  {
    buf[0] = tbl16dec[ *pSrce++ ];
    if ( buf[0] < 0 )
      return 0 ;
    buf[1] = tbl16dec[ *pSrce++ ];
    if ( buf[1] < 0 )
      return 0 ;
    *pDest++ = ((buf[0] << 4) | buf[1]);
  }

#ifdef NULL_TERMINATED_STRINGS
  *pDest = '\x0' ;
#endif
  return pDest-Dest ;
}

size_t decode32(  char *Dest, const  char *Srce, const size_t lSrce )
{
  char *pDest = ( char *)Dest;
  char *pSrce = ( char *)Srce;
  size_t i,j;
  char buf[8];

  if( !pDest || !pSrce || ( lSrce % 8 != 0 ) )
    return 0 ;

  for ( i = 0; i < lSrce/8 ; i++)
  {
    #pragma unroll
    for ( j = 0; j < 8 ; j++)
    {
      buf[j] = tbl32dec[ *pSrce++ ];
      if ( buf[j] < 0 )
        return 0 ;
    }
    *pDest++ = ((buf[0] & 0x1f) << 3) | ((buf[1] & 0x1c) >> 2);
    *pDest++ = ((buf[1] & 0x03) << 6) | ((buf[2] & 0x1f) << 1) | ((buf[3] & 0x10) >> 4);
    *pDest++ = ((buf[3] & 0x0f) << 4) | ((buf[4] & 0x1e) >> 1);
    *pDest++ = ((buf[4] & 0x01) << 7) | ((buf[5] & 0x1f) << 2) | ((buf[6] & 0x18) >> 3);
    *pDest++ = ((buf[6] & 0x07) << 5) |  (buf[7] & 0x1f);
  }

  if  ( buf[7] == 64 )
  {
    --pDest;
    assert ( (buf[6] == 64 && buf[5] == 64 ) || ( buf[6] != 64 ) ) ;
    if  ( buf[5] == 64 )
    {
      --pDest;
      if  ( buf[4] == 64 )
      {
        --pDest;
        assert ( (buf[3] == 64 && buf[2] == 64 ) || ( buf[2] != 64 ) ) ;
        if  ( buf[2] == 64 )
        {
          --pDest;
        }
      }
    }
  }

#ifdef NULL_TERMINATED_STRINGS
  *pDest = '\x0' ;
#endif
  return pDest-Dest ;
}

size_t decode64(  char *Dest, const  char *Srce, const size_t lSrce )
{
  char *pDest = ( char *)Dest;
  char *pSrce = ( char *)Srce;
  size_t i,j;
  char buf[4];

  if( !pDest || !pSrce || ( lSrce % 4 != 0 ) )
    return 0 ;

  for ( i = 0; i < lSrce/4 ; i++)
  {
    #pragma unroll
    for ( j = 0; j < 4 ; j++)
    {
      buf[j] = tbl64dec[ *pSrce++ ];
      if ( buf[j] < 0 )
        return 0 ;
    }

    *pDest++ = ((buf[0] & 0x3f) << 2) | ((buf[1] & 0x30) >> 4);
    *pDest++ = ((buf[1] & 0x0f) << 4) | ((buf[2] & 0x3c) >> 2);
    *pDest++ = ((buf[2] & 0x03) << 6) |  (buf[3] & 0x3f);

    if (buf[3] == 64 )
    {
      --pDest;
      if (buf[2] == 64 )
        {
          --pDest;
        }
      }
    }

#ifdef NULL_TERMINATED_STRINGS
  *pDest = '\x0' ;
#endif
  return pDest-Dest ;
}
