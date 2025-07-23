#!/bin/bash

# Colors for output
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

PASS="[${GREEN}PASS${RESET}]"
FAIL="[${RED}FAIL${RESET}]"

PIPEX=./pipex
INFILE=infile_test
OUTFILE=outfile_test

total=0
success=0

# Create base dummy input
echo -e "apple\nbanana\navocado\napricot" > $INFILE

function test_case() {
	total=$((total+1))
	desc=$1
	cmd="$2"
	expected_code=$3

	eval "$cmd"
	actual=$?

	if [ "$actual" -eq "$expected_code" ]; then
		printf "$PASS %-60s (exit: %s)\n" "$desc" "$actual"
		success=$((success+1))
	else
		printf "$FAIL %-60s (exit: %s, expected: %s)\n" \
		 "$desc" "$actual" "$expected_code"
	fi
}

echo -e "\n🌐 PIPEX – BASH BEHAVIOR TEST SUITE\n"

# Bash : bash -c "grep a < infile_test | wc -l"
# Pipex: ./pipex infile_test "grep a" "wc -l" outfile_test
test_case "Valid command (grep | wc)" \
	"$PIPEX $INFILE \"grep a\" \"wc -l\" $OUTFILE" 0

# Bash : bash -c "doesnotexist < infile_test | wc -l"
# Pipex: ./pipex infile_test "doesnotexist" "wc -l" outfile_test
test_case "Invalid first command" \
	"$PIPEX $INFILE \"doesnotexist\" \"wc -l\" $OUTFILE" 0

# Bash : bash -c "grep a < infile_test | nosuchcmd"
# Pipex: ./pipex infile_test "grep a" "nosuchcmd" outfile_test
test_case "Invalid second command" \
	"$PIPEX $INFILE \"grep a\" \"nosuchcmd\" $OUTFILE" 127

# Bash : bash -c "nosuch1 < infile_test | nosuch2"
# Pipex: ./pipex infile_test "nosuch1" "nosuch2" outfile_test
test_case "Both commands invalid" \
	"$PIPEX $INFILE \"nosuch1\" \"nosuch2\" $OUTFILE" 127

# Bash : bash -c "grep a < missingfile | wc -l"
# Pipex: ./pipex missingfile "grep a" "wc -l" outfile_test
test_case "Missing input file" \
	"$PIPEX missingfile \"grep a\" \"wc -l\" $OUTFILE" 0

# Bash : bash -c "./nosuchcmd < infile_test | weqwec -l"
# Pipex: ./pipex infile_test "./nosuchcmd" "weqwec -l" outfile_test
test_case "Command with slash (./nosuchcmd)" \
	"$PIPEX $INFILE \"./nosuchcmd\" \"weqwec -l\" $OUTFILE" 127

# Bash : bash -c "cat < infile_test | grep xyz"
# Pipex: ./pipex infile_test "cat" "grep xyz" outfile_test
test_case "cmd2 returns logical exit 1 (grep no match)" \
	"$PIPEX $INFILE \"cat\" \"grep xyz\" $OUTFILE" 1

# Bash : bash -c "cat < infile_test | false"
# Pipex: ./pipex infile_test "cat" "false" outfile_test
test_case "cmd2 is 'false' (always returns 1)" \
	"$PIPEX $INFILE \"cat\" \"false\" $OUTFILE" 1

###############################
# Extended real-world tests 
###############################

# Bash : < infile.txt tr a-z A-Z | sort > org_result.txt
# Pipex: ./pipex infile.txt "tr a-z A-Z" "sort" result.txt
echo -e "apple\nzebra\nbanana\nlemon" > infile.txt
test_case "Basic text transformation and sorting" \
	"$PIPEX infile.txt \"tr a-z A-Z\" \"sort\" result.txt" 0

# Bash : < infile.txt grep Lorem | wc -l > org_outfile.txt
# Pipex: ./pipex infile.txt "grep Lorem" "wc -l" outfile.txt
echo -e "Lorem ipsum dolor\nHello world\nLorem again" > infile.txt
test_case "Pattern matching and counting (grep | wc)" \
	"$PIPEX infile.txt \"grep Lorem\" \"wc -l\" outfile.txt" 0

# Bash : < fruits.txt sort | uniq -c > org_counts.txt
# Pipex: ./pipex fruits.txt "sort" "uniq -c" counts.txt
echo -e "apple\nbanana\napple\norange\nbanana\nkiwi" > fruits.txt
test_case "Sorting and counting unique lines (uniq -c)" \
	"$PIPEX fruits.txt \"sort\" \"uniq -c\" counts.txt" 0

# Bash : < /etc/passwd cut -d: -f1 | sort -u > org_users.txt
# Pipex: ./pipex /etc/passwd "cut -d: -f1" "sort -u" users.txt
test_case "Extract usernames from /etc/passwd and sort uniquely" \
	"$PIPEX /etc/passwd \"cut -d: -f1\" \"sort -u\" users.txt" 0

# Bash : < mix.txt tr '[:upper:]' '[:lower:]' | head -n 3 > org_head3.txt
# Pipex: ./pipex mix.txt "tr '[:upper:]' '[:lower:]'" "head -n 3" head3.txt
echo -e "HELLO\nWorld\nTEST\nExample" > mix.txt
test_case "Convert to lowercase and limit lines (head)" \
	"$PIPEX mix.txt \"tr '[:upper:]' '[:lower:]'\" \"head -n 3\" head3.txt" 0

# Bash : < date.txt sed 's/-/\//g' | grep 05 > org_result1.txt
# Pipex: ./pipex date.txt "sed s/-/\\\/g" "grep 05" result1.txt
echo -e "2023-05-15\n2023-06-20\n2023-05-30\n2023-07-10" > date.txt
test_case "Replace hyphens and grep 05" \
	"$PIPEX date.txt \"sed s/-/\\\\\\\\\\//g\" \"grep 05\" result1.txt" 0

# Bash : < infile.txt /usr/bin/wc -c | /usr/bin/wc -l > org_absout.txt
# Pipex: ./pipex infile.txt "/usr/bin/wc -c" "/usr/bin/wc -l" absout.txt
test_case "Use absolute paths for wc commands" \
	"$PIPEX infile.txt \"/usr/bin/wc -c\" \"/usr/bin/wc -l\" absout.txt" 0

#######################
# Error handling tests
#######################

# Bash : < nofile.txt grep a | wc -l > out.txt
# Pipex: ./pipex nofile.txt "grep a" "wc -l" out.txt
test_case "Error: non-existent input file" \
	"$PIPEX nofile.txt \"grep a\" \"wc -l\" out.txt" 0

# Bash : < hello.txt foobar | wc -l > out.txt
# Pipex: ./pipex hello.txt "foobar" "wc -l" out.txt
echo "Hello, world!" > hello.txt
test_case "Error: non-existent command" \
	"$PIPEX hello.txt \"foobar\" \"wc -l\" out.txt" 0

### Summary

echo -e "\n📊 Result: $success out of $total tests passed."

# Clean up
rm -f $INFILE $OUTFILE infile.txt outfile.txt fruits.txt mix.txt date.txt \
hello.txt absout.txt result.txt users.txt counts.txt head3.txt result1.txt