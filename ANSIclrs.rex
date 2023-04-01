#! /usr/bin/env rexx
-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
--  Copyright (c) 2022, 2023 Enrico Sorichetti
--  Distributed under the Boost Software License, Version 1.0.
--  (See accompanying file BOOST_LICENSE_1_0.txt or copy at
--  http://www.boost.org/LICENSE_1_0.txt)
--

colrs = .array~of( ,
  "black"      , ,
  "red"        , ,
  "green"      , ,
  "yellow"     , ,
  "blue"       , ,
  "magenta"    , ,
  "cyan"       , ,
  "white"      )

parse arg c

if  c = "" then do
  say
  say "          normal background, normal foreground"
  line = "default"~left(8)
  do fg = 1 to colrs~dimension(1)
    line = line || " " .ANSIcolr~entry(colrs[fg]) || ,
      .ANSIback~entry("default") || colrs[fg]~left(8) || .ANSIreset
  end
  say line
  do bg = 1 to colrs~dimension(1)
    line = colrs[bg]~left(8)
      do fg = 1 to colrs~dimension(1)
        line = line || " " .ANSIcolr~entry(colrs[fg]) || ,
          .ANSIback~entry(colrs[bg]) || colrs[fg]~left(8) || .ANSIreset
      end
    say line
  end

  say
  say "          normal background, bright foreground"
  line = "default"~left(8)
  do fg = 1 to colrs~dimension(1)
    line = line || " " .ANSIcolr~entry("bright"colrs[fg]) || ,
      .ANSIback~entry("default") || (colrs[fg])~left(8) || .ANSIreset
  end
  say line

  do bg = 1 to colrs~dimension(1)
    line = colrs[bg]~left(8)
    do fg = 1 to colrs~dimension(1)
      line = line || " " .ANSIcolr~entry("bright"colrs[fg]) || ,
        .ANSIback~entry(colrs[bg]) || (colrs[fg])~left(8) || .ANSIreset
    end
    say line
  end

end

else ,
  say highlight(">"c"<", c)

exit

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
::requires  "highlight.cls"
