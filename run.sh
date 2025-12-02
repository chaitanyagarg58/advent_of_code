#!/bin/bash

usage() {
    echo "Usage: $0 [Date] [Year]"
    echo "  Date = DD (default: today's day)"
    echo "  Year = YYYY (default: today's year)"
}


if [[ $# -gt 2 ]]; then
	usage
	exit 1
fi

today_date=$(date +%d)
today_year=$(date +%Y)

date="${1:-$today_date}"
year="${2:-$today_year}"

echo "Date = $date"
echo "Year = $year"

# Paths
folder="$year"
cpp_file="$folder/$date.cpp"
input_file="$folder/$date.input"
out_file="$folder/$date.out"

# --- Validation ---
if [ ! -d "$folder" ]; then
    echo "Error: Folder '$folder' does not exist."
    exit 1
fi

if [ ! -f "$cpp_file" ]; then
    echo "Error: File '$cpp_file' not found."
    exit 1
fi

if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found."
    exit 1
fi


# --- Compile ---
echo "Compiling: $cpp_file"
g++ -std=c++17 "$cpp_file" -o "$out_file"
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# --- Run ---
echo "Running $out_file with input from $input_file:"
echo "-----------------------------------------------"
"$out_file" < "$input_file"
echo "-----------------------------------------------"

rm "$out_file"
