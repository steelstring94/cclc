# cclc

This program will calculate the `chmod` three-digit permissions code.  It accepts input either in binary or lettered argument form.

## Installation

Simply run the included `install` script.  The script will compile, link and attempt to automatically install `cclc`.  If automatic installation fails for any reason, you will need to copy `build/cclc` to an appropriate location for user-installed executables, and `man/cclc.1` to an appropriate location for manpages.

## Binary

In the binary form, you use 1 to grant a permission and 0 to deny.  In this case, the arguments must be in the order of `user group other` and within each argument, the 1s and 0s must be in the order of `read write execute`.

For example, permissions `rwx r-x r--` would be encoded as `cclc 111 101 100`.  Insignificant zeroes can be omitted, so `001` (execute only) could be written as just `1`.  Omitted permission arguments will not be granted, so it is not necessary to write `000` or `0` to deny a permission, just leave it off.  For example, `rwx rw- ---` could simply be `cclc 111 110`.

## Lettered

The more convenient  way of entering arguments involves using lettered codes to designate `user`, `group` or `other` (called "targets") and then following each such target with permissions `r`, `w` and/or `x`.  No ordering of arguments nor the letters within arguments is enforced, except that the permissions codes must immediately follow their respective targets codes, and the targets codes must be immediately preceded by a hyphen.

For example, to define `rwx r-x r--` in this manner, the appropriate command to issue is `cclc -u rwx -g rx -o r`.  If identical permissions are to be assigned to multiple targets, target arguments may be combined, so that `rwx rwx rwx` may be obtained with `cclc -ugo rwx`.  Again, with the exception of the requirement of the hyphen immediately before the targets, and that the permission codes must immediately follow their intended targets, there is no enforcement of order with the lettered argument form, so `cclc -ugo rwx` is entirely equivalent to `cclc -oug xrw`.

## Interpolation

The ideal use of `cclc` is as an interpolated command with `chmod`.  For example, you may do ```chmod `cclc -u rw`./somefile```.  The result of this will be `chmod 600 ./somefile`.  If you do not interpolate `cclc`'s output, it will simply be printed on `stdout`.

## Versioning

Versions follow the SemVer pattern

## Author

`cclc` is free software developed by steelstring94, who may be contacted under the same username on GitHub.  Email address is the same username at `gmail.com`.

## License

Copyright 2018 steelstring94

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

# cclc
