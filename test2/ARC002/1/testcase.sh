#! /usr/bin/bash

case $1 in
    p*) exit 0;;
    n0) timeout 1 $2 < test2/ARC002/1/input.0 > $3 && diff $3 test2/ARC002/1/output.0;;
    n1) timeout 1 $2 < test2/ARC002/1/input.1 > $3 && diff $3 test2/ARC002/1/output.1;;
    n2) timeout 1 $2 < test2/ARC002/1/input.2 > $3 && diff $3 test2/ARC002/1/output.2;;
    n3) timeout 1 $2 < test2/ARC002/1/input.3 > $3 && diff $3 test2/ARC002/1/output.3;;
esac
