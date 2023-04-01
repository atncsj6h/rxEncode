#ifndef encode_hpp_included
#define encode_hpp_included
/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Copyright Enrico Sorichetti 2019 - 2019
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

size_t encode16( char *, const char *, const size_t );
size_t encode32( char *, const char *, const size_t );
size_t encode64( char *, const char *, const size_t );

size_t decode16( char *, const char *, const size_t );
size_t decode32( char *, const char *, const size_t );
size_t decode64( char *, const char *, const size_t );

#endif  //  #ifndef encode_hpp_included
