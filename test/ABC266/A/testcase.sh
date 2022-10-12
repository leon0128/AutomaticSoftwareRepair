#! /usr/bin/bash

case $1 in
    p*) exit 0;;
    n0) timeout 2 $2 < test/ABC266/A/input.0 > $3 && diff $3 test/ABC266/A/output.0;;
    n1) timeout 2 $2 < test/ABC266/A/input.1 > $3 && diff $3 test/ABC266/A/output.1;;
    n2) exit 0;;
    n3) exit 0;;
esac