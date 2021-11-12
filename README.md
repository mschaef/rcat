# rcat

A Unix utility that reads from an input file and is tolerant of I/O
errors. This is intended for scenarios where the goal is to read as
much data as possible from a source that is known to be unreliable.
aRather than aborting the read entirely, `rcat` replaces blocks that
fail to read with equivalently sized blocks of zeros.

## License

Copyright © 2021 [Michael Schaeffer](http://www.mschaef.com/)

All Rights Reserved.

