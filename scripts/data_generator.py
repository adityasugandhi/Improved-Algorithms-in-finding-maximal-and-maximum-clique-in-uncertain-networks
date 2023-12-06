import math
import argparse as ap
import random
parser = ap.ArgumentParser()
parser.add_argument("filename",help="Enter-Filename")
parser.add_argument("filepath",help= "Enter-filepath")
args = parser.parse_args()
filename= args.filename
filepath = args.filepath
# Dictionary to store edge weights
edge_weights = {}

# Uncompress the dataset and read it line by line
with open(filepath, 'rt') as file:
    next(file)
    for line in file:
        print(line)
        src, tgt, _= line.split()
        edge = (src, tgt)
        
        # Increment the weight (count) for the edge in the dictionary
        if edge in edge_weights:
            edge_weights[edge] += 1
        else:
            edge_weights[edge] = 1

# Dictionary to store edge probabilities
edge_probabilities = {}

# Calculate probabilities using the exponential cumulative distribution with λ = 2
for edge, weight in edge_weights.items():
    lambda_value = 2.0
   # weight = random.randint(1, 10)
    probability = 1 - math.exp(-edge_weights[edge] / lambda_value)
    
    # Round off the probability to two decimal places
    rounded_probability = round(probability, 2)
    
    edge_probabilities[edge] = rounded_probability

# Get the total number of vertices and edges
total_vertices = len(set(v for edge in edge_weights for v in edge))
total_edges = len(edge_weights)

# Write total vertices and total edges as the first line in the output file
with open(filename, 'w') as output_file:
    output_file.write(f"{total_vertices} {total_edges}\n")

# Write vertices and their probabilities to the output file
with open(filename, 'a') as output_file:
    for edge, probability in edge_probabilities.items():
        src, tgt = edge
        output_file.write(f"{src}, {tgt}, {probability}\n")
