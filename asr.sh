#!/usr/bin/bash

# parameter
## general
EXECUTION_NAME="./asr"
TARGET_FILENAME="test/test.c"
TARGET_FUNCTIONS=()
EXTERNAL_PATHS=("test/test.c")
RESULT_FILENAME="test/result.c"
TEMPORARY_FILENAME="test/__test.c"
TEMPORARY_EXECUTION_NAME="test/__test"

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
PREPROCESSOR="cpp -P -D__extension__"
COMPILER="gcc"

## operation
ADD_PROBABILITY=0.4
SUB_PROBABILITY=0.2
SWAP_PROBABILITY=0.4
MAX_NUMBER_OF_FAILURES=10

## genetic algorithm
POPULATION=100
GENERATION=10
NUMBER_OF_ELITE=2
TOURNAMENT_SIZE=3


# execution
TARGET=""
for VALUE in "${TARGET_FUNCTIONS[@]}"
do
    TARGET+="--target \"${VALUE}\" "
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
    --preprocessor "$PREPROCESSOR" \
    --compiler "$COMPILER" \
    --test-script "$TEST_SCRIPT_FILENAME" \
    --test-filename "$TEMPORARY_FILENAME" \
    --execution "$TEMPORARY_EXECUTION_NAME" \
    --pos-prefix "$POSITIVE_PREFIX" \
    --neg-prefix "$NEGATIVE_PREFIX" \
    --num-pos "$NUMBER_OF_POSITIVE" \
    --num-neg "$NUMBER_OF_NEGATIVE" \
    --pos-weight "$POSITIVE_TEST_WEIGHT" \
    --neg-weight "$NEGATIVE_TEST_WEIGHT" \
    --goal "$TARGET_SCORE" \
    --failure "$MAX_NUMBER_OF_FAILURES" \
    --pop "$POPULATION" \
    --max "$GENERATION" \
    --elite "$NUMBER_OF_ELITE" \
    --tournament "$TOURNAMENT_SIZE" \
    --add-prob "$ADD_PROBABILITY" \
    --sub-prob "$SUB_PROBABILITY" \
    --swap-prob "$SWAP_PROBABILITY"