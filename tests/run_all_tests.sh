#!/bin/bash

# Master test runner - executes all test suites

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

TOTAL_PASSED=0
TOTAL_FAILED=0
SUITES_PASSED=0
SUITES_FAILED=0

echo ""
echo "========================================="
echo "    MY_SHELL - Complete Test Suite"
echo "========================================="
echo ""

# Compile first
echo -e "${BLUE}[1/7]${NC} Compiling my_shell..."
make -C .. > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ Compilation failed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Compilation successful${NC}"
echo ""

# Run test suites
run_suite() {
    local suite_name="$1"
    local suite_script="$2"
    
    echo -e "${BLUE}Running: $suite_name${NC}"
    echo "========================================="
    
    bash "$suite_script"
    local exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        SUITES_PASSED=$((SUITES_PASSED + 1))
        echo -e "${GREEN}✓ $suite_name completed successfully${NC}"
    else
        SUITES_FAILED=$((SUITES_FAILED + 1))
        echo -e "${RED}✗ $suite_name had failures${NC}"
    fi
    
    echo ""
    return $exit_code
}

# Execute all test suites
echo -e "${BLUE}[2/7]${NC} Lexer Tests"
echo "========================================="
run_suite "Lexer Tests" "test_lexer.sh"

echo -e "${BLUE}[3/7]${NC} Parser/AST Tests"
echo "========================================="
run_suite "Parser Tests" "test_parser.sh"

echo -e "${BLUE}[4/7]${NC} Heredoc Tests"
echo "========================================="
run_suite "Heredoc Tests" "test_heredoc.sh"

echo -e "${BLUE}[5/7]${NC} Signal & Exit Tests"
echo "========================================="
run_suite "Signal & Exit Tests" "test_signals.sh"

echo -e "${BLUE}[6/7]${NC} Signal State Management Tests"
echo "========================================="
run_suite "Signal State Tests" "test_signal_states.sh"

echo -e "${BLUE}[7/15]${NC} Integration Tests"
echo "========================================="
run_suite "Integration Tests" "test_integration.sh"

echo -e "${BLUE}[8/15]${NC} Builtin Commands Tests"
echo "========================================="
run_suite "Builtin Tests" "test_builtins.sh"

echo -e "${BLUE}[9/15]${NC} Redirection Tests"
echo "========================================="
run_suite "Redirection Tests" "test_redirections.sh"

echo -e "${BLUE}[10/15]${NC} Pipe Tests"
echo "========================================="
run_suite "Pipe Tests" "test_pipes.sh"

echo -e "${BLUE}[11/15]${NC} External Commands Tests"
echo "========================================="
run_suite "External Command Tests" "test_external_commands.sh"

echo -e "${BLUE}[12/15]${NC} Logical Operators Tests"
echo "========================================="
run_suite "Logical Operators Tests" "test_logical.sh"

echo -e "${BLUE}[13/15]${NC} Environment Variables Tests"
echo "========================================="
run_suite "Environment Variables Tests" "test_env_vars.sh"

echo -e "${BLUE}[14/15]${NC} File Operations Tests"
echo "========================================="
run_suite "File Operations Tests" "test_files.sh"

echo -e "${BLUE}[15/15]${NC} Segfault Detection Tests"
echo "========================================="
run_suite "Segfault Tests" "test_segfault.sh"

# Final summary
echo ""
echo "========================================="
echo "           FINAL SUMMARY"
echo "========================================="
echo ""
echo "Test Suites Run: $((SUITES_PASSED + SUITES_FAILED))"
echo -e "${GREEN}Suites Passed:   $SUITES_PASSED${NC}"
echo -e "${RED}Suites Failed:   $SUITES_FAILED${NC}"
echo ""

if [ $SUITES_FAILED -eq 0 ]; then
    echo -e "${GREEN}════════════════════════════════════════${NC}"
    echo -e "${GREEN}   ✓ ALL TEST SUITES PASSED!${NC}"
    echo -e "${GREEN}════════════════════════════════════════${NC}"
    exit 0
else
    echo -e "${RED}════════════════════════════════════════${NC}"
    echo -e "${RED}   ✗ SOME TEST SUITES FAILED${NC}"
    echo -e "${RED}════════════════════════════════════════${NC}"
    exit 1
fi
