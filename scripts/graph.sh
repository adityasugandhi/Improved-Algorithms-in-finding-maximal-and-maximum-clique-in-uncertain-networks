#!/bin/bash

# Function to run uclique command and extract output
run_uclique() {
    local output
    output=$(./uclique "$1" "$2" "$3" "$4" "$5" "$6")
    echo "$output"
}
ls 
# Prompt user for the file path
#read -p "Enter the path to your dataset: " file_path
#file_path = ''
# Execute the uclique command for specified parameter ranges
for k in {6..15}; do
    for p in 0.01 0.1; do
        for alg in {1..6}; do
            for prune in 1 2; do
                echo "Running uclique for k=$k, p=$p, alg=$alg, prune=$prune..."

                # Execute uclique and store the output
                output=$(run_uclique "askubuntu" "$k" "$p" "$alg" "$prune")

                # Run Python script to extract and store information in CSV
                python3 bash.py "$output"
            done
        done
    done
done
