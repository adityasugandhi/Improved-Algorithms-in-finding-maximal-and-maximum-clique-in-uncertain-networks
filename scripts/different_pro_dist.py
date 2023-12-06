import math
import argparse as ap
import gzip

parser = ap.ArgumentParser()
parser.add_argument("filename", help="Enter-Filename")
parser.add_argument("filepath", help="Enter-filepath")
args = parser.parse_args()

filename = args.filename
filepath = args.filepath

# Dictionary to store edge weights
edge_weights = {}

# Check if the file is gzipped
if filepath.endswith('.gz'):
    file_opener = gzip.open
else:
    file_opener = open

# Uncompress the dataset and read it line by line
with file_opener(filepath, 'rt') as file:
    next(file)
    for line in file:
        data = line.split()
        if len(data) < 2:
            # Skip lines with less than 2 columns
            continue

        src, tgt = data[:2]  # Take the first two columns as source and target
        edge = (src, tgt)

        # Increment the weight (count) for the edge in the dictionary
        if edge in edge_weights:
            edge_weights[edge] += 1
        else:
            edge_weights[edge] = 1

# Get the total number of vertices and edges
total_vertices = len(set(v for edge in edge_weights for v in edge))
total_edges = len(edge_weights)

# Loop through lambda values from 2 to 6
for lambda_value in range(2, 7):
    # Dictionary to store edge probabilities
    edge_probabilities = {}

    # Calculate probabilities using the exponential cumulative distribution with lambda_value
    for edge, weight in edge_weights.items():
        probability = 1 - math.exp(-weight / lambda_value)

        # Round off the probability to two decimal places
        rounded_probability = round(probability, 2)

        edge_probabilities[edge] = rounded_probability

    # Write total vertices and total edges as the first line in the output file
    output_filename = f"/home/csgroup/Database_project/RAW_DATA/pro_vary/{filename}_lambda{lambda_value}.csv"
    with open(output_filename, 'w') as output_file:
        output_file.write(f"{total_vertices} {total_edges}\n")

        # Write vertices and their probabilities to the output file
        for edge, probability in edge_probabilities.items():
            src, tgt = edge
            output_file.write(f"{src}, {tgt}, {probability}\n")

    print(f"Output for lambda {lambda_value} written to {output_filename}")
