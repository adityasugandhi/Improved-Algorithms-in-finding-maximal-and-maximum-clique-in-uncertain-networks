# Uncertain Clique Project README

This README provides instructions on how to compile and run the code for the Uncertain Clique project, along with details on additional scripts included for data generation and analysis. Our project focuses on approximating edge weights in graph data and exploring the impact of pruning on algorithm performance. The implementation has been optimized for performance, leveraging advanced hardware for execution.

## Compilation Instructions

To compile the project, ensure you have the necessary build tools installed on your system. Then, navigate to the project directory in your terminal and run the following command:

'''bash
make

This command will compile the source code and generate an executable file in the `./bin` directory.

## Running the Project

Once the project is compiled, you can run the main executable with the following command syntax:

'''bash
./bin/uncertainclique <file> <k-constraint> <p-probabilistic> <algorithm> <prune>

### Command Parameters:
- `<file>`: Path to the input dataset file.
- `<k-constraint>`: The k-constraint value for the clique.
- `<p-probabilistic>`: The probability threshold for considering an edge in the probabilistic graph model.
- `<algorithm>`: Specifies the algorithm to be used.
- `<prune>`: Indicates whether pruning should be applied (`true` or `false`).

## Additional Scripts

### Data Generation:
- `datageneration.py`: Generates graph data.
  - Usage: `python datageneration.py <outputfilename> <datasetfilepath>`
    - `<outputfilename>`: The name of the file to store the generated dataset.
    - `<datasetfilepath>`: Path to the original dataset file used as the basis for generation.

### Distribution Analysis:
- `different_prod_dist.py`: Analyzes product distributions.
  - Usage: `python different_prod_dist.py <outputfilename> <datasetfilename>`
    - `<outputfilename>`: The name of the file to store analysis results.
    - `<datasetfilename>`: Path to the dataset file to be analyzed.

## Implementation Details

Our approach approximates edge weights by incrementally assigning a weight of 1 for each interaction. This simplification leads to a dataset with uniform data characteristics and minimal variance, facilitating a clear analysis of algorithmic performance, particularly highlighting the efficiency gains from pruning techniques.

## Performance Considerations

The project's performance benefits significantly from the use of advanced hardware specifications. Specifically, we have optimized our implementation to run on an Intel Xeon Silver 4114 CPU operating at 2.20 GHz. This choice of hardware supports our goal of demonstrating reduced runtimes and enhanced performance, especially when leveraging pruned algorithms in our computations.

For further details on the project, including specific algorithms and pruning techniques used, please refer to the accompanying documentation and source code comments.

