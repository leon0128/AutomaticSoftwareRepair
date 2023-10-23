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
TARGET_SCORE=40

## external softwares
PREPROCESSOR="cpp -P -I./test/ -D__extension__="
COMPILER="gcc"
BUILTIN="data/builtin.h"

## operation
ADD_PROBABILITY=0.1
SUB_PROBABILITY=0.1
SWAP_PROBABILITY=0.8
MAX_NUMBER_OF_FAILURES=1024

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
REDUCTION_THRESHOLD=0.2
NUMBER_OF_USE_EXTERNAL=32768

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
        --specified-log \
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
        --new-creation-prob 0.5 \
        $@
}

# notice
notice()
{
    post="Content-type:application/json"
    data='{"text":"'
    for e in $@
    do
        data+=$e
    done
    data+='"'
    data+="}"
    curl -X POST -H 'Content-type:application/json' \
        --data $data \
        $SLACK_WEBHOOK_URL
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
TARGETS=()
declare -A TARGET_TESTCASE_MAP
declare -A SAME_POOL_MAP
for CON in $(ls test2/)
do
    CONTESTS+=($CON)
    DIR="test2/"
    DIR+=$CON
    DIR+="/1/"

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
        TARGETS+=($FILE)
        TARGET_TESTCASE_MAP[$FILE]=$TEST_FILE
        SAME_POOL_MAP[$FILE]=$AC_DIR
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
    FILE_A="231023_random_identifier.csv"
    FILE_B="231023_duplicated_identifier.csv"
    FILE_C="231023_no_duplicated_identifier.csv"

    ## header
    echo target,is_repaired,score,tags,used_function_names,used_statement_ids,operated_positions,created_statement_id,used_identifier_ids,pop_count,execution_time,preprocessing_time,similarity_calculation_time,repair_time,repair_initialization_time,repair_rep_generation_time,repair_evalution_time,tag > "231023_random_identifier.csv"
    echo target,is_repaired,score,tags,used_function_names,used_statement_ids,operated_positions,created_statement_id,used_identifier_ids,pop_count,execution_time,preprocessing_time,similarity_calculation_time,repair_time,repair_initialization_time,repair_rep_generation_time,repair_evalution_time,tag > "231023_duplicated_identifier.csv"
    echo target,is_repaired,score,tags,used_function_names,used_statement_ids,operated_positions,created_statement_id,used_identifier_ids,pop_count,execution_time,preprocessing_time,similarity_calculation_time,repair_time,repair_initialization_time,repair_rep_generation_time,repair_evalution_time,tag > "231023_no_duplicated_identifier.csv"

    for TAR in ${TARGETS[@]}
    do
        TARGET_FILENAME=$TAR
        TEST_SCRIPT_FILENAME=${TARGET_TESTCASE_MAP[$TAR]}

        RESULT_FILENAME=tmp/random/
        RESULT_FILENAME+=$(basename $TARGET_FILENAME)
        executeASR $POOL_OPTION --random-identifier >> "231023_random_identifier.csv"
        RESULT_FILENAME=tmp/duplicated/
        RESULT_FILENAME+=$(basename $TARGET_FILENAME)
        executeASR $POOL_OPTION --duplicated-identifier >> "231023_duplicated_identifier.csv"
        RESULT_FILENAME=tmp/no_duplicated/
        RESULT_FILENAME+=$(basename $TARGET_FILENAME)
        executeASR $POOL_OPTION --no-duplicated-identifier >> "231023_no_duplicated_identifier.csv"
    done
}

# concurrency_test concurrency_time_log.csv

for i in {1..1}
do
    notice $(hostname) :: $$ :: start
    execute
    notice $(hostname) :: $$ :: end
done
