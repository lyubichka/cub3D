#!/bin/bash

# Comprehensive Valgrind Memory Check Script for cub3D
# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
MAP_FILE="maps/text.cub"
SAVE_MODE=""
OUTPUT_DIR="valgrind_logs"
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
TEST_MODE="both"  # both, save-only, interactive-only, or quick
TIMEOUT=3         # seconds to run interactive mode before auto-exit
QUICK_MODE=false  # Quick test without logs

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --map)
            MAP_FILE="$2"
            shift 2
            ;;
        --save)
            TEST_MODE="save-only"
            shift
            ;;
        --interactive)
            TEST_MODE="interactive-only"
            shift
            ;;
        --quick)
            TEST_MODE="quick"
            QUICK_MODE=true
            shift
            ;;
        --timeout)
            TIMEOUT="$2"
            shift 2
            ;;
        --help)
            echo "Usage: ./valgrind_check.sh [OPTIONS]"
            echo ""
            echo "Options:"
            echo "  --map <file>       Specify map file (default: maps/text.cub)"
            echo "  --save             Test only save mode"
            echo "  --interactive      Test only interactive mode"
            echo "  --quick            Quick test (no detailed logs)"
            echo "  --timeout <sec>    Timeout for interactive test (default: 3)"
            echo "  --help             Show this help message"
            echo ""
            echo "Test Modes:"
            echo "  Default (no flags): Tests BOTH save and interactive modes"
            echo "  --quick: Fast test, ignores MLX 'still reachable' blocks"
            echo ""
            echo "Examples:"
            echo "  ./valgrind_check.sh                    # Full test (recommended)"
            echo "  ./valgrind_check.sh --quick            # Quick validation"
            echo "  ./valgrind_check.sh --save             # Only save mode"
            echo "  ./valgrind_check.sh --interactive      # Only interactive"
            echo "  ./valgrind_check.sh --timeout 5        # 5 sec interactive test"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

# Create output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

echo -e "${BLUE}╔════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║    cub3D Valgrind Memory Analysis Tool        ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════╝${NC}"
echo ""

# Check if executable exists
if [ ! -f "./cub3D" ]; then
    echo -e "${YELLOW}Executable not found. Building cub3D...${NC}"
    make
    if [ $? -ne 0 ]; then
        echo -e "${RED}Build failed!${NC}"
        exit 1
    fi
    echo -e "${GREEN}✓ Build successful${NC}"
fi

# Check if map file exists
if [ ! -f "$MAP_FILE" ]; then
    echo -e "${RED}Error: Map file '$MAP_FILE' not found${NC}"
    exit 1
fi

echo -e "${BLUE}Configuration:${NC}"
echo -e "  Map file:   ${GREEN}$MAP_FILE${NC}"
echo -e "  Test mode:  ${GREEN}$TEST_MODE${NC}"
echo -e "  Logs dir:   ${GREEN}$OUTPUT_DIR${NC}"
if [ "$TEST_MODE" = "both" ] || [ "$TEST_MODE" = "interactive-only" ]; then
    echo -e "  Timeout:    ${GREEN}${TIMEOUT}s${NC}"
fi
echo ""

# Function to run valgrind test
run_valgrind_test() {
    local mode=$1
    local args=$2
    local log_suffix=$3
    local timeout_val=$4

    local full_log="$OUTPUT_DIR/full_${log_suffix}_${TIMESTAMP}.log"
    local console_log="$OUTPUT_DIR/console_${log_suffix}_${TIMESTAMP}.log"

    echo -e "${YELLOW}Running Valgrind - $mode mode...${NC}"

    if [ -n "$timeout_val" ]; then
        # Interactive mode - auto-kill after timeout
        echo -e "${BLUE}(Will auto-terminate after ${timeout_val}s)${NC}"
        timeout "$timeout_val" valgrind \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --track-fds=yes \
            --verbose \
            --log-file="$full_log" \
            --error-exitcode=99 \
            ./cub3D "$MAP_FILE" $args 2>&1 | tee "$console_log" &

        local pid=$!
        wait $pid
        local exit_code=$?

        # Timeout exit code is 124, which is expected for interactive test
        if [ $exit_code -eq 124 ]; then
            echo -e "${GREEN}Interactive test completed (auto-terminated)${NC}"
            return 0
        fi
        return $exit_code
    else
        # Save mode - runs to completion
        valgrind \
            --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --track-fds=yes \
            --verbose \
            --log-file="$full_log" \
            --error-exitcode=99 \
            ./cub3D "$MAP_FILE" $args 2>&1 | tee "$console_log"

        return $?
    fi
}

# Determine which tests to run
ALL_EXIT_CODES=()
TEST_LOGS=()

# Quick mode - simple test
if [ "$QUICK_MODE" = true ]; then
    echo -e "${YELLOW}Running quick memory test...${NC}"
    echo ""

    OUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        ./cub3D "$MAP_FILE" 2>&1)

    echo "$OUTPUT" | grep -E "HEAP SUMMARY|definitely lost|ERROR SUMMARY"
    echo ""

    # Check for definite leaks (ignore "still reachable" from MLX)
    DEFINITE_LEAKS=$(echo "$OUTPUT" | grep "definitely lost:" | grep -oP '\d+(?= bytes)' || echo "0")
    ERRORS=$(echo "$OUTPUT" | grep "ERROR SUMMARY:" | grep -oP '^\d+' || echo "0")

    echo -e "${BLUE}╔════════════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║              Quick Test Results                ║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════════════╝${NC}"
    echo ""

    if [ "$DEFINITE_LEAKS" = "0" ] && [ "$ERRORS" = "0" ]; then
        echo -e "${GREEN}✓ PASSED - Your code is leak-free!${NC}"
        echo -e "${YELLOW}Note: 'Still reachable' blocks are from MLX library${NC}"
        exit 0
    else
        echo -e "${RED}✗ FAILED - Memory leaks detected in your code${NC}"
        echo -e "Definite leaks: $DEFINITE_LEAKS bytes"
        echo -e "Errors: $ERRORS"
        exit 1
    fi
fi

# Full mode - detailed testing
if [ "$TEST_MODE" = "both" ] || [ "$TEST_MODE" = "save-only" ]; then
    echo -e "${BLUE}═══════════════════════════════════════════════${NC}"
    echo -e "${BLUE}  TEST 1: Save Mode (Complete Lifecycle)${NC}"
    echo -e "${BLUE}═══════════════════════════════════════════════${NC}"
    echo ""

    run_valgrind_test "Save" "--save" "save" ""
    SAVE_EXIT=$?
    ALL_EXIT_CODES+=($SAVE_EXIT)
    TEST_LOGS+=("$OUTPUT_DIR/full_save_${TIMESTAMP}.log")

    echo ""
fi

if [ "$TEST_MODE" = "both" ] || [ "$TEST_MODE" = "interactive-only" ]; then
    echo -e "${BLUE}═══════════════════════════════════════════════${NC}"
    echo -e "${BLUE}  TEST 2: Interactive Mode (MLX/Graphics)${NC}"
    echo -e "${BLUE}═══════════════════════════════════════════════${NC}"
    echo ""

    run_valgrind_test "Interactive" "" "interactive" "$TIMEOUT"
    INTERACTIVE_EXIT=$?
    ALL_EXIT_CODES+=($INTERACTIVE_EXIT)
    TEST_LOGS+=("$OUTPUT_DIR/full_interactive_${TIMESTAMP}.log")

    echo ""
fi

# Use the worst exit code
VALGRIND_EXIT=0
for code in "${ALL_EXIT_CODES[@]}"; do
    if [ $code -eq 99 ]; then
        VALGRIND_EXIT=99
        break
    elif [ $code -ne 0 ] && [ $VALGRIND_EXIT -eq 0 ]; then
        VALGRIND_EXIT=$code
    fi
done

echo ""
echo -e "${BLUE}╔════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║              Analysis Results                  ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════╝${NC}"
echo ""

SUMMARY_LOG="$OUTPUT_DIR/summary_${TIMESTAMP}.txt"
echo "VALGRIND ANALYSIS SUMMARY - $(date)" > "$SUMMARY_LOG"
echo "========================================" >> "$SUMMARY_LOG"
echo "" >> "$SUMMARY_LOG"

TOTAL_LEAKS=0
TOTAL_ERRORS=0

# Analyze each test log
for i in "${!TEST_LOGS[@]}"; do
    FULL_LOG="${TEST_LOGS[$i]}"

    if [ ! -f "$FULL_LOG" ]; then
        continue
    fi

    # Determine test name
    if [[ "$FULL_LOG" == *"save"* ]]; then
        TEST_NAME="SAVE MODE"
    else
        TEST_NAME="INTERACTIVE MODE"
    fi

    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}Results: $TEST_NAME${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

    echo "" | tee -a "$SUMMARY_LOG"
    echo "=== $TEST_NAME ===" | tee -a "$SUMMARY_LOG"
    echo "" | tee -a "$SUMMARY_LOG"

    # Extract heap summary
    echo -e "${YELLOW}Heap Summary:${NC}" | tee -a "$SUMMARY_LOG"
    grep -A 2 "HEAP SUMMARY:" "$FULL_LOG" | tail -n 2 | tee -a "$SUMMARY_LOG"
    echo "" | tee -a "$SUMMARY_LOG"

    # Extract leak summary
    echo -e "${YELLOW}Leak Summary:${NC}" | tee -a "$SUMMARY_LOG"
    if grep -q "LEAK SUMMARY:" "$FULL_LOG"; then
        grep -A 5 "LEAK SUMMARY:" "$FULL_LOG" | tee -a "$SUMMARY_LOG"
    else
        echo "No leak summary (all clean!)" | tee -a "$SUMMARY_LOG"
    fi
    echo "" | tee -a "$SUMMARY_LOG"

    # Extract error summary
    ERROR_COUNT=$(grep "ERROR SUMMARY:" "$FULL_LOG" | grep -oP '\d+(?= errors)' || echo "0")
    echo -e "${YELLOW}Error Summary:${NC}" | tee -a "$SUMMARY_LOG"
    grep "ERROR SUMMARY:" "$FULL_LOG" | tee -a "$SUMMARY_LOG"
    echo "" | tee -a "$SUMMARY_LOG"

    # Check for memory leaks
    if grep -q "All heap blocks were freed -- no leaks are possible" "$FULL_LOG"; then
        echo -e "${GREEN}✓ No memory leaks detected!${NC}" | tee -a "$SUMMARY_LOG"
    elif grep -q "definitely lost: 0 bytes in 0 blocks" "$FULL_LOG" && \
         grep -q "indirectly lost: 0 bytes in 0 blocks" "$FULL_LOG"; then
        echo -e "${GREEN}✓ No definite leaks (may have reachable blocks)${NC}" | tee -a "$SUMMARY_LOG"
    else
        echo -e "${RED}✗ Memory leaks detected!${NC}" | tee -a "$SUMMARY_LOG"
        TOTAL_LEAKS=$((TOTAL_LEAKS + 1))

        LEAK_LOG="${FULL_LOG%.log}_leaks.log"
        grep -A 50 "LEAK SUMMARY:" "$FULL_LOG" > "$LEAK_LOG"
        echo -e "  See detailed report: ${YELLOW}$LEAK_LOG${NC}"
    fi

    # Check for errors
    if [ "$ERROR_COUNT" -eq 0 ]; then
        echo -e "${GREEN}✓ No errors detected!${NC}" | tee -a "$SUMMARY_LOG"
    else
        echo -e "${RED}✗ $ERROR_COUNT error(s) detected!${NC}" | tee -a "$SUMMARY_LOG"
        TOTAL_ERRORS=$((TOTAL_ERRORS + ERROR_COUNT))

        ERROR_LOG="${FULL_LOG%.log}_errors.log"
        grep -E "Invalid|Conditional|Uninitialised" "$FULL_LOG" > "$ERROR_LOG" 2>/dev/null
        echo -e "  See detailed report: ${YELLOW}$ERROR_LOG${NC}"
    fi

    echo "" | tee -a "$SUMMARY_LOG"
done

echo -e "${BLUE}╔════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║              Overall Summary                   ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════╝${NC}"
echo ""
echo "OVERALL SUMMARY" >> "$SUMMARY_LOG"
echo "===============" >> "$SUMMARY_LOG"

if [ "$TEST_MODE" = "both" ]; then
    echo -e "${YELLOW}Tests completed: ${GREEN}2/2${NC} (Save + Interactive)" | tee -a "$SUMMARY_LOG"
elif [ "$TEST_MODE" = "save-only" ]; then
    echo -e "${YELLOW}Tests completed: ${GREEN}1/1${NC} (Save only)" | tee -a "$SUMMARY_LOG"
else
    echo -e "${YELLOW}Tests completed: ${GREEN}1/1${NC} (Interactive only)" | tee -a "$SUMMARY_LOG"
fi

if [ $TOTAL_LEAKS -eq 0 ] && [ $TOTAL_ERRORS -eq 0 ]; then
    echo -e "${GREEN}✓✓✓ ALL TESTS PASSED - PROJECT IS LEAK-FREE! ✓✓✓${NC}" | tee -a "$SUMMARY_LOG"
else
    echo -e "${RED}✗ Issues found: $TOTAL_LEAKS leak test(s) failed, $TOTAL_ERRORS error(s)${NC}" | tee -a "$SUMMARY_LOG"
fi

echo ""
echo -e "${BLUE}Log files created:${NC}"
for log in "${TEST_LOGS[@]}"; do
    echo -e "  ${GREEN}$log${NC}"
done
echo -e "  Summary: ${GREEN}$SUMMARY_LOG${NC}"

echo ""
if [ $VALGRIND_EXIT -eq 99 ]; then
    echo -e "${RED}Valgrind detected errors (exit code 99)${NC}"
    exit 99
elif [ $VALGRIND_EXIT -ne 0 ]; then
    echo -e "${YELLOW}Program exited with code: $VALGRIND_EXIT${NC}"
    exit $VALGRIND_EXIT
else
    echo -e "${GREEN}✓ Valgrind analysis complete - All clean!${NC}"
    exit 0
fi
