#! /usr/bin/env rexx


-- test with "foobar"
--   1    f        MY======
--   2    fo       MZXQ====
--   3    foo      MZXW6===
--   4    foob     MZXW6YQ=
--   5    fooba    MZXW6YTB
--   6    foobar   MZXW6YTBOI======

say
say "    test with 'foobar' "
do  l = 1 to "foobar"~length
  say right(l,3) "    >>"encode32( left("foobar", l) )"<<"
end

-- test with '      ' - a string of blanks
--   1    { }      EA======
--   2    {  }     EAQA====
--   3    {   }    EAQCA===
--   4    {    }   EAQCAIA=
--   5    {     }  EAQCAIBA
--   6    {      } EAQCAIBAEA======

say
say "    test with '      ' - a string of blanks"
do  l = 1 to "      "~length
  say right(l,3) "      >>"encode32( left("      ", l) )"<<"
end

-- test with '00'x to 'ff'x
say
say "    test with '00'x to 'ff'x "

--  compute
stak = .array~new
do i = 0 to 255
  if i <= 32 | i >= 128 then do
    stak[i+1] = right(i,3)  d2x(i,2)  "."           ">>"encode32(x2c(d2x(i,2)))"<<"
    iterate
  end
  stak[i+1] = right(i,3)  d2x(i,2)  x2c(d2x(i,2)) ">>"encode32(x2c(d2x(i,2)))"<<"
end

-- print
buf = ""
do  i = 1 to 256
    if buf = "" then do
      buf = stak[i]
      iterate
    end
    if i = 256 then ,
      buf = buf stak[i]
    else ,
      buf = buf stak[i]","
    if ( i // 4 ) = 0 then do
      say buf~strip(,"T")
      buf = ""
      iterate
    end
    -- say "/ " i "-" i / 4
    -- if ( i // 4 ) = 0 then say "//" i "-" i // 4
    -- if ( i %  4 ) = 0 then say "% " i "-" i %  4
end
if buf \= "" then,
  say buf~strip(",","T")

exit

::requires  "rxencode" LIBRARY

/*

    1    f        MY======
    2    fo       MZXQ====
    3    foo      MZXW6===
    4    foob     MZXW6YQ=
    5    fooba    MZXW6YTB
    6    foobar   MZXW6YTBOI======
    -    -        -
    7    { }      EA======
    8    {  }     EAQA====
    9    {   }    EAQCA===
    10   {    }   EAQCAIA=
    11   {     }  EAQCAIBA
    12   {      } EAQCAIBAEA======

*/
