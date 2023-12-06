# TO COMPILE THE CODE

`` make``

# To RUN THE CODE

`` ./bin/uncertainclique <file> <k-constraint> <p-probabilistic> <algorithm> <prune>``

Scripts:

  

* datageneration.py `<outputfilename> <datasetfilepath>`
* different_prod_dist.py `<outputfilename> <datasetfilename>`

Our implementation approximated edge weights by incrementally assigning a weight of 1 for each interaction, leading to uniform data and minimal variance in algorithmic results, yet effectively showcased the reduced runtimes of pruned algorithms. Enhanced performance was also supported by our use of advanced hardware, an Intel Xeon Silver 4114 CPU at 2.20 GHz.
