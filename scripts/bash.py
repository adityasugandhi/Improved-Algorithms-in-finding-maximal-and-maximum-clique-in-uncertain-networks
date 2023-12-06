# bash.py

import sys
import re
import csv

def extract_and_store(output):
    # Define regular expressions to extract values
    max_memory_pattern = re.compile(r'Max memory\s+(\d+)\s+kb')
    alg_prune_pattern = re.compile(r'alg=(\d+),\s+prune=(\d+)')
    all_time_pattern = re.compile(r'All time\s+([\d.]+)\s+ms')
    alg_pattern = re.compile(r'Alg (\d+)')

    # Extract values using regular expressions
    max_memory_match = max_memory_pattern.search(output)
    alg_prune_match = alg_prune_pattern.search(output)
    all_time_match = all_time_pattern.search(output)
    alg_match = alg_pattern.search(output)

    # Get the values or set default values if not found
    max_memory = max_memory_match.group(1) if max_memory_match else 'N/A'
    alg, prune = alg_prune_match.groups() if alg_prune_match else ('N/A', 'N/A')
    all_time = all_time_match.group(1) if all_time_match else 'N/A'
    alg_value = alg_match.group(1) if alg_match else 'N/A'

    return {'Max Memory': max_memory, 'Alg': alg_value, 'Prune': prune, 'All Time': all_time}

# Get the output from the command-line arguments
uclique_output = sys.argv[1]

# Extract and print the values
result = extract_and_store(uclique_output)
print(result)

# Append to CSV (use 'a' for append mode)
with open('output.csv', 'a', newline='') as csvfile:
    fieldnames = ['Max Memory', 'Alg', 'Prune', 'All Time']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

    # Check if the file is empty and write header if needed
    if csvfile.tell() == 0:
        writer.writeheader()

    writer.writerow(result)

print("CSV file updated successfully.")
