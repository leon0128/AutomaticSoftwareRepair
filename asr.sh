#!/usr/bin/bash

# parameter
## general
EXECUTION_NAME="./asr"
TARGET_FILENAME="test/test.c"
TARGET_FUNCTIONS=()
EXTERNAL_PATHS=()
RESULT_FILENAME="test/result.c"

EXEC_EXTENSION=""
NULL_FILENAME="/dev/null"

## test case
TEST_SCRIPT_FILENAME="test/test.sh"
POSITIVE_PREFIX="p"
NEGATIVE_PREFIX="n"
NUMBER_OF_POSITIVE=0
NUMBER_OF_NEGATIVE=1
POSITIVE_TEST_WEIGHT=1
NEGATIVE_TEST_WEIGHT=10
TARGET_SCORE=10

## external softwares
PREPROCESSOR="cpp -P -I./test/ " #-D__extension__= -D__builtin_offsetof(TYPE,MEMBER)=((size_t)&((TYPE*)0)->MEMBER)"
COMPILER="gcc"

## operation
ADD_PROBABILITY=0.2
SUB_PROBABILITY=0.2
SWAP_PROBABILITY=0.6
MAX_NUMBER_OF_FAILURES=16

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
NUMBER_OF_USE_EXTERNAL=10

## others
NUMBER_OF_CONCURRENCY=64
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

$EXECUTION_NAME \
    "$TARGET_FILENAME" \
    $TARGET \
    $POOL \
    --result "$RESULT_FILENAME" \
    --time-log \
    --repair-log \
    --preprocessor "$PREPROCESSOR" \
    --compiler "$COMPILER" \
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
    --use-similarity \
    --original "$ORIGINAL_GRAM_SIZE" \
    --type1 "$TYPE1_GRAM_SIZE" \
    --type2 "$TYPE2_GRAM_SIZE" \
    --type3 "$TYPE3_GRAM_SIZE" \
    --capacity "$REDUCTION_THRESHOLD" \
    --num-use-external "$NUMBER_OF_USE_EXTERNAL" \
    --change-prob