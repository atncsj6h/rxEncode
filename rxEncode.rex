#! /usr/bin/env rexx
/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Copyright Enrico Sorichetti 2018 - 2019
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
*/
parse arg times copies

if  copies = "" then ,
    copies = 100

if  times = "" then ,
    times = 100

say
say highlight("Starting validation and performance tests", "red")

call runbench times, copies, "loremipsum", "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor "

call runbench times, copies, "hexdata",    xrange('00'x,'FF'x)

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
test = "'foobar'"~left(12)
say highlight("running" test "tests", "red")
foobar  = "foobar"
foobar_32 = .array~of(,
    "MY======"        , ,
    "MZXQ===="        , ,
    "MZXW6==="        , ,
    "MZXW6YQ="        , ,
    "MZXW6YTB"        , ,
    "MZXW6YTBOI======")

do  l = 1 to 6

    enc = encode16( left(foobar, l) )
    if  enc \= c2x(foobar~left(l)) then do
        say "-- base 16 encode failure for length("l")"
        say ">"enc"<"
        say ">"c2x(foobar[l])"<"
    end

    dec = decode16(enc)
    if  dec \= foobar~left(l) then do
        say "-- base 16 decode failure for length("l")"
        say ">"left(foobar, l)"<"
        say ">"dec"<"
    end

    dec = decode16( c2x(foobar~left(l))~lower)
    if  dec \= left(foobar, l) then do
        say "-- base 16 decode failure for length("l") [with lower case alphabet]"
        say ">"left(foobar, l)"<"
        say ">"dec"<"
    end

    enc = encode32(foobar~left(l))
    if  enc \= foobar_32[l] then do
        say "-- base 32 encode failure for length("l")"
        say ">"enc"<"
        say ">"foobar_32[l]"<"
    end

    dec = decode32(enc)
    if  dec \= foobar~left(l) then do
        say "-- base 32 decode failure for length("l")"
        say ">"foobar~left(l)"<"
        say ">"dec"<"
    end

    dec = decode32(foobar_32[l]~lower)
    if  dec \= foobar~left(l) then do
        say "-- base 32 decode failure for length("l") [with lower case alphabet]"
        say ">"foobar~left(l)"<"
        say ">"dec"<"
    end

    enc = encode64(foobar~left(l))
    if  enc \= foobar~left(l)~encodebase64 then do
        say "-- base 64 encode failure for length("l")"
        say ">"enc"<"
        say ">"foobar~left(l)~encodebase64"<"
    end

    dec = decode64(enc)
    if  dec \= foobar~left(l) then do
        say "-- base 64 decode failure for length("l")"
        say ">"foobar~left(l)"<"
        say ">"dec"<"
    end

end

say ""
say highlight("Done", "red")
say ""
exit

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
runbench: procedure

times  = arg(1)
copies = arg(2)

test   = ("'"arg(3)"'")~left(12)
data   = arg(4)~copies(copies)

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
say highlight("running" test "tests times("times")," "copies("copies")," "base_length("arg(4)~length")", "red")

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
say highlight("-- base16 encode/decode (c2x/x2c)", "red")

say "encode16()~length      :" "("encode16(data)~length")"
say "c2x~length             :" "("c2x(data)~length")"

say "encode16()~left(10)    :" ">"encode16(data)~left(10)"<"
say "c2x~left(10)           :" ">"c2x(data)~left(10)"<"

say "encode16()~right(10)   :" ">"encode16(data)~right(10)"<"
say "c2x~right(10)          :" ">"c2x(data)~right(10)"<"

enc = encode16(data)
if  enc \= c2x(data) then do
    say "-- base 16 encode failure"
    if  copies = 1 then do
        say ">"enc"<"
        say ">"c2x(data)"<"
    end
end

dec = decode16(enc)
if  dec \= data then do
    say "-- base 16 decode failure"
    if  copies = 1 then do
        say ">"enc"<"
        say ">"dec"<"
    end
end


/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
say highlight("-- encode16/decode16 'rxEncode' LIBRARY", "red")
z = time("r")
do times
    enc = encode16(data)
    dec = decode16(enc)
end
say "elapsed" time(e)

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
say highlight("-- c2x/x2c ooRexx", "red")
z = time("r")
do times
    enc = c2x(data)
    dec = x2c(enc)
end
say "elapsed" time(e)

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
say highlight("-- base64 encode/decode (~encodebase64/~decodebase64)", "red")

say "encode64()~length      :" "("encode64(data)~length")"
say "~encodeBase64~length   :" "("data~encodebase64~length")"

say "encode64()~left(10)    :" ">"encode64(data)~left(10)"<"
say "~encodeBase64~left(10) :" ">"data~encodebase64~left(10)"<"

say "encode64()~right(10)   :" ">"encode64(data)~right(10)"<"
say "~encodeBase64~right(10):" ">"data~encodebase64~right(10)"<"

enc = encode64(data)
if  enc \= data~encodebase64 then do
    say "-- base 64 encode failure"
    if  copies = 1 then do
        say ">"enc"<"
        say ">"data~encodebase64"<"
    end
end

dec = decode64(enc)
if  dec \= data then do
    say "-- base 64 decode failure"
    if  copies = 1 then do
        say ">"enc"<"
        say ">"dec"<"
    end
end

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
say highlight("-- encode64/decode64 'rxEncode' LIBRARY", "red")
z = time("r")
do times
    enc = encode64(data)
    dec = decode64(enc)
end
say "elapsed" time(e)

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
say
say highlight("-- ~encodebase64/~decodebase64 ooRexx", "red")
z = time("r")
do times
    enc = data~encodebase64
    dec = enc~decodebase64
end
say "elapsed" time(e)


return

/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*/
::requires  "highlight.cls"

::requires  "rxEncode" LIBRARY
