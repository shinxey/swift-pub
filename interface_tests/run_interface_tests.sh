#!/bin/sh

OUTPUT_DIR='./outputs'
EXPECTED_OUTPUT_DIR='./expected_outputs'
DIFF_DIR='./diffs'

mkdir -p "$OUTPUT_DIR"
mkdir -p "$DIFF_DIR"

gcc -Werror -Wall -Wextra test_interface.c -o test_interface

for filepath in ./inputs/*.swift; do
	filename=$(basename "$filepath")
	expected_path="$EXPECTED_OUTPUT_DIR/$filename.output"
	output_path="$OUTPUT_DIR/$filename.output"
	diff_path="$DIFF_DIR/$filename.output.diff"

	./test_interface "$filepath" > "$output_path"

	if [ ! -f "$expected_path" ]; then
		echo "File $expected_path with expected lexer output for $filepath not found"
		exit 1
	fi

	diff "$expected_path" "$output_path" > "$diff_path"

	if [ -s "$diff_path" ]; then
		# diff is not empty
		echo "❌ test $filepath failed! See $diff_path"
	else
		# diff is empty
		echo "✅ test $filepath succeded!"
	fi
done
