
UTILS="mktab16 mktab32 mktab64"

for util in ${UTILS} ; do
  $CC -o $util ${util}.c
  ./$util > "tables"${util:(-2)}".h"
  cp *.h ../lib/include
done
