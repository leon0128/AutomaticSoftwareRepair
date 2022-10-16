#!/usr/bin/bash

# parameter
## general
EXECUTION_NAME="./asr"
TARGET_FILENAME="target.c"
TARGET_FUNCTIONS=()
EXTERNAL_PATHS=()
RESULT_FILENAME="result.c"

EXEC_EXTENSION=""
NULL_FILENAME="/dev/null"

## test case
TEST_SCRIPT_FILENAME="testcase.sh"
POSITIVE_PREFIX="p"
NEGATIVE_PREFIX="n"
NUMBER_OF_POSITIVE=0
NUMBER_OF_NEGATIVE=4
POSITIVE_TEST_WEIGHT=1
NEGATIVE_TEST_WEIGHT=10
TARGET_SCORE=41

## external softwares
PREPROCESSOR="cpp -P -I./test/ -D__extension__="
COMPILER="gcc"
BUILTIN="builtin.h"

## operation
ADD_PROBABILITY=0.2
SUB_PROBABILITY=0.2
SWAP_PROBABILITY=0.6
MAX_NUMBER_OF_FAILURES=64

## genetic algorithm
POPULATION=1000
GENERATION=10
NUMBER_OF_ELITE=2
TOURNAMENT_SIZE=3

## similarity
ORIGINAL_GRAM_SIZE=1
TYPE1_GRAM_SIZE=4
TYPE2_GRAM_SIZE=4
TYPE3_GRAM_SIZE=4
REDUCTION_THRESHOLD=1.0
NUMBER_OF_USE_EXTERNAL=64

## others
NUMBER_OF_CONCURRENCY=32
MAX_RECURSION=16

# execution
TARGET=""
for VALUE in "${TARGET_FUNCTIONS[@]}"
do
    TARGET+="--target ${VALUE} "
done

POOL=""
for VALUE in "${EXTERNAL_PATHS[@]}"
do
    POOL+="--pool ${VALUE} "
done

executeASR()
{
    $EXECUTION_NAME \
        "$TARGET_FILENAME" \
        $TARGET \
        $POOL \
        --result "$RESULT_FILENAME" \
        --preprocessor "$PREPROCESSOR" \
        --compiler "$COMPILER" \
        --builtin "$BUILTIN" \
        --test "$TEST_SCRIPT_FILENAME" \
        --exec-extension "$EXEC_EXTENSION" \
        --null-filename "$NULL_FILENAME" \
        --pos-prefix "$POSITIVE_PREFIX" \
        --neg-prefix "$NEGATIVE_PREFIX" \
        --num-pos "$NUMBER_OF_POSITIVE" \
        --num-neg "$NUMBER_OF_NEGATIVE" \
        --pos-weight "$POSITIVE_TEST_WEIGHT" \
        --neg-weight "$NEGATIVE_TEST_WEIGHT" \
        --goal "$TARGET_SCORE" \
        --failure "$MAX_NUMBER_OF_FAILURES" \
        --pop "$POPULATION" \
        --gen "$GENERATION" \
        --elite "$NUMBER_OF_ELITE" \
        --tournament "$TOURNAMENT_SIZE" \
        --add-prob "$ADD_PROBABILITY" \
        --sub-prob "$SUB_PROBABILITY" \
        --swap-prob "$SWAP_PROBABILITY" \
        --num-concurrency "$NUMBER_OF_CONCURRENCY" \
        --max-recursion "$MAX_RECURSION" \
        --original "$ORIGINAL_GRAM_SIZE" \
        --type1 "$TYPE1_GRAM_SIZE" \
        --type2 "$TYPE2_GRAM_SIZE" \
        --type3 "$TYPE3_GRAM_SIZE" \
        --capacity "$REDUCTION_THRESHOLD" \
        $@
}

# concurrency test
concurrency_test()
{
    echo .concurrency,.isSuccess,.created,.totalTime,.repairTime, >> $1
    for i in {1..32}
    do
        echo -n $i, >> $1
        NUMBER_OF_CONCURRENCY=$i
        executeASR >> $1
        echo >> $1
    done
}

CONTESTS=()
EXTERNAL_DIRS=()
TARGETS=("test/ABC272/A/WA/35469736.c")
declare -A TARGET_TESTCASE_MAP
for CON in $(ls test/)
do
    CONTESTS+=($CON)
    DIR="test/"
    DIR+=$CON
    DIR+="/A/"

    TEST_FILE=$DIR
    TEST_FILE+=testcase.sh

    AC_DIR=$DIR
    AC_DIR+=AC/
    EXTERNAL_DIRS+=($AC_DIR)

    WA_DIR=$DIR
    WA_DIR+=WA/
    for TAR in $(ls $WA_DIR)
    do
        FILE=$WA_DIR
        FILE+=$TAR
        # TARGETS+=($FILE)
        TARGET_TESTCASE_MAP[$FILE]=$TEST_FILE
    done
done

POOL_OPTION=""
for EX in ${EXTERNAL_DIRS[@]}
do
    POOL_OPTION+="--pool $EX "
done

# 0. 
## no use external sources.

# 1.
## use external sources. 
## but, no use similarity.

# 2.
## use similarity.
## and external sources are reducted.

# 3.
## use similarity.
## and prob of external sources is changed.

# 4.
## use similarity.
## and external sources are redected.
## and prob of external sources is changed.

execute()
{
    ## header
    echo -n target, >> $1
    for i in {0..4}
    do
        echo -n $i.isSuccess,$i.created,$i.totalTime,$i.repairTime, >> $1
    done
    echo >> $1
    for TAR in ${TARGETS[@]}
    do
        TARGET_FILENAME=$TAR
        TEST_SCRIPT_FILENAME=${TARGET_TESTCASE_MAP[$TAR]}

        echo -n $TARGET_FILENAME, >> $1

        # executeASR --no-use-similarity --num-use-external 100000 >> $1
        executeASR $POOL_OPTION --no-use-similarity --num-use-external 100000
        # executeASR $POOL_OPTION --no-change-prob --num-use-external 64 >> $1
        # executeASR $POOL_OPTION --num-use-external 100000 >> $1
        # executeASR $POOL_OPTION --num-use-external 64 >> $1

        echo >> $1
    done
}

# concurrency_test concurrency_time_log.csv

for i in {1..1}
do
    execute repair_time_test.csv
done