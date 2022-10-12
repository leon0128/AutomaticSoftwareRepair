#! /usr/bin/bash

case $1 in
    p*) exit 0;;
    n0) timeout 2 $2 < test/ABC269/A/input.0 > $3 && diff $3 test/ABC269/A/output.0;;
    n1) timeout 2 $2 < test/ABC269/A/input.1 > $3 && diff $3 test/ABC269/A/output.1;;
    n2) timeout 2 $2 < test/ABC269/A/input.2 > $3 && diff $3 test/ABC269/A/output.2;;
    n3) exit 0;;
esac