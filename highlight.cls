-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--  Copyright (c) 2022, 2023 Enrico Sorichetti
--  Distributed under the Boost Software License, Version 1.0.
--  (See accompanying file BOOST_LICENSE_1_0.txt or copy at
--  http://www.boost.org/LICENSE_1_0.txt)
--

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
escape      = "1b"x
reset       = "[0m"

bold        = "[1m"
dim         = "[2m"
underscore  = "[4m"
blink       = "[5m"
reverse     = "[7m"
hidden      = "[8m"

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--  basic controls
.local~ANSIescape       = escape
.local~ANSIreset        = escape || reset

.local~ANSIbold         = escape || bold
.local~ANSIdim          = escape || dim
.local~ANSIunderscore   = escape || underscore
.local~ANSIblink        = escape || blink
.local~ANSIreverse      = escape || reverse
.local~ANSIhidden       = escape || hidden

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--  foreground colors escape sequence
colr = .directory~new

colr~setEntry( "black"          , escape"[1;30m" )
colr~setEntry( "red"            , escape"[1;31m" )
colr~setEntry( "green"          , escape"[1;32m" )
colr~setEntry( "yellow"         , escape"[1;33m" )
colr~setEntry( "blue"           , escape"[1;34m" )
colr~setEntry( "magenta"        , escape"[1;35m" )
colr~setEntry( "cyan"           , escape"[1;36m" )
colr~setEntry( "white"          , escape"[1;37m" )
colr~setEntry( "default"        , escape"[1;39m" )
colr~setEntry( "brightblack"    , escape"[1;90m" )
colr~setEntry( "brightred"      , escape"[1;91m" )
colr~setEntry( "brightgreen"    , escape"[1;92m" )
colr~setEntry( "brightyellow"   , escape"[1;93m" )
colr~setEntry( "brightblue"     , escape"[1;94m" )
colr~setEntry( "brightmagenta"  , escape"[1;95m" )
colr~setEntry( "brightcyan"     , escape"[1;96m" )
colr~setEntry( "brightwhite"    , escape"[1;97m" )

colr~setEntry( "lightgrey"      , escape"[1;37m" )
colr~setEntry( "grey"           , escape"[1;90m" )

.local~ANSIcolr = colr

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--  background colors escape sequence
back = .directory~new

back~setentry( "black"          , escape"[1;40m" )
back~setentry( "red"            , escape"[1;41m" )
back~setentry( "green"          , escape"[1;42m" )
back~setentry( "yellow"         , escape"[1;43m" )
back~setentry( "blue"           , escape"[1;44m" )
back~setentry( "magenta"        , escape"[1;45m" )
back~setentry( "cyan"           , escape"[1;46m" )
back~setentry( "white"          , escape"[1;47m" )
back~setentry( "default"        , escape"[1;49m" )
back~setentry( "brightblack"    , escape"[1;100m" )
back~setentry( "brightred"      , escape"[1;101m" )
back~setentry( "brightgreen"    , escape"[1;102m" )
back~setentry( "brightyellow"   , escape"[1;103m" )
back~setentry( "brightblue"     , escape"[1;104m" )
back~setentry( "brightmagenta"  , escape"[1;105m" )
back~setentry( "brightcyan"     , escape"[1;106m" )
back~setEntry( "brightwhite"    , escape"[1;107m" )

back~setEntry( "lightgrey"      , escape"[1;47m" )
back~setEntry( "grey"           , escape"[1;100m" )

.local~ANSIback = back

do  name over back
   .local~setEntry('ANSIback.'name,back[name])
end

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
::routine HighLight public
use strict arg text, colr, back="default"
    FG = colr~space(0)~lower
    BG = back~space(0)~lower
    return .ANSIcolr~entry(FG) || .ANSIback~entry(BG) || text || .ANSIreset
