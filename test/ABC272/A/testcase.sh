#! /usr/bin/bash

case $1 in
    n0) timeout 2 $2 < test/ABC272/A/input.0 > $3 && diff $3 test/ABC272/A/output.0;;
    n1) timeout 2 $2 < test/ABC272/A/input.1 > $3 && diff $3 test/ABC272/A/output.1;;
esac