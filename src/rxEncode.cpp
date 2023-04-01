/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Copyright Enrico Sorichetti 2019 - 2019
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "oorexxapi.h"

#include "encode.hpp"

#define  SUCCESS    0             /* Raise Rexx error           */
#define  FAILURE    10

#define  MALLOC_EXTRA 16

#define SD(_s) context->StringData(_s)
#define SL(_s) context->StringLength(_s)

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxRoutine1(RexxObjectPtr, rxEncode16, RexxStringObject, Srce)
{
  size_t  lSrce, lDest;
  char *  Dest;
  RexxStringObject Result ;

  lSrce = (size_t)SL(Srce);
  lDest = lSrce * 2 ;
  Dest = (char *)malloc(lDest+1+MALLOC_EXTRA);
  lDest = encode16( Dest, SD(Srce), lSrce );

  if ( lDest == 0 )
    Result = context->NullString();
  else
    Result = context->NewString((char *)Dest, lDest);

  free( Dest );
  return Result;
}

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxRoutine1(RexxObjectPtr, rxEncode32, RexxStringObject, Srce)
{
  size_t  lSrce, lDest;
  char *  Dest;
  RexxStringObject Result ;

  lSrce = (size_t)SL(Srce);
  lDest = ( lSrce * 8 ) / 5 + ( ( lSrce % 5  == 0 )  ? 0 : 8 );
  Dest = (char *)malloc(lDest+1+MALLOC_EXTRA);
  lDest = encode32( Dest, SD(Srce), lSrce );

  if ( lDest == 0 )
    Result = context->NullString();
  else
    Result = context->NewString((char *)Dest, lDest);

  free( Dest );
  return Result;
}

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxRoutine1(RexxObjectPtr, rxEncode64, RexxStringObject, Srce)
{
  size_t  lSrce, lDest;
  char *  Dest;
  RexxStringObject Result ;

  lSrce = (size_t)SL(Srce);
  lDest = ( lSrce * 4 ) / 3 + ( ( lSrce % 3  == 0 )  ? 0 : 4 );
  Dest = (char *)malloc(lDest+1+MALLOC_EXTRA);
  lDest = encode64( Dest, SD(Srce), lSrce );

  if ( lDest == 0 )
    Result = context->NullString();
  else
    Result = context->NewString((char *)Dest, lDest);

  free( Dest );
  return Result;
}

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxRoutine1(RexxObjectPtr, rxDecode16, RexxStringObject, Srce)
{
  size_t  lSrce, lDest;
  char *  Dest;
  RexxStringObject Result ;

  lSrce = (size_t)SL(Srce);
  Dest = (char *)malloc(lSrce+1+MALLOC_EXTRA);
  lDest = decode16( Dest, SD(Srce), lSrce );

  if ( lDest == 0 )
    Result = context->NullString();
  else
    Result = context->NewString((char *)Dest, lDest);

  free( Dest );
  return Result;
}

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxRoutine1(RexxObjectPtr, rxDecode32, RexxStringObject, Srce)
{
  size_t  lSrce, lDest;
  char *  Dest;
  RexxStringObject Result ;

  lSrce = (size_t)SL(Srce);
  Dest = (char *)malloc(lSrce+1+MALLOC_EXTRA);
  lDest = decode32( Dest, SD(Srce), lSrce );

  if ( lDest == 0 )
    Result = context->NullString();
  else
    Result = context->NewString((char *)Dest, lDest);

  free( Dest );
  return Result;
}

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxRoutine1(RexxObjectPtr, rxDecode64, RexxStringObject, Srce)
{
  size_t  lSrce, lDest;
  char *  Dest;
  RexxStringObject Result ;

  lSrce = (size_t)SL(Srce);
  Dest = (char *)malloc(lSrce+1+MALLOC_EXTRA);
  lDest = decode64( Dest, SD(Srce), lSrce );

  if ( lDest == 0 )
    Result = context->NullString();
  else
    Result = context->NewString((char *)Dest, lDest);

  free( Dest );
  return Result;
}

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxRoutineEntry rxEncodeRoutines[] =
{
  REXX_TYPED_ROUTINE(encode16 ,     rxEncode16  ),
  REXX_TYPED_ROUTINE(encode32 ,     rxEncode32  ),
  REXX_TYPED_ROUTINE(encode64 ,     rxEncode64  ),
  REXX_TYPED_ROUTINE(decode16 ,     rxDecode16  ),
  REXX_TYPED_ROUTINE(decode32 ,     rxDecode32  ),
  REXX_TYPED_ROUTINE(decode64 ,     rxDecode64  ),
  REXX_LAST_ROUTINE()
};

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
RexxPackageEntry rxEncode_package_entry =
{
  STANDARD_PACKAGE_HEADER
  REXX_INTERPRETER_5_0_0,             // anything after 4.0.0 will work
  "rxEncode",                         // name of the package
  "1.0.0",                            // package information
  NULL,                               // no loader function (run once at load time)
  NULL,                               // no unloader function (run once at shutdown time)
  rxEncodeRoutines,                   // the exported native routines
  NULL                                // no native methods
};

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
OOREXX_GET_PACKAGE(rxEncode);

