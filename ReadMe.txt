Alesandra Roger 
Jiayu Zeng         

*It’s a Advanced C++ course project coded by a team of two.

0. This is a hex board game simulation that player competes with an AI opponent.

1. This project contains two sets of files. Both sets share hexMain.cpp and GraphHex.h
   Both sets use Monte Carlo method to implement the AI, which chooses the best move after calculating the winning possibility of each spot for 1000 iterations. Specific codes using threading is in function monteCarlo( ). Library <omp.h> is included.
   

2. To test files.
    a. Threading version: input command "make", executable file "hexMian” will be created. The best performance of the AI is responding in 6 seconds
   

3. Threading vs. Non-threading
    Theocratically, using threading has a better performance because it separates a sequence progress into parts so that the calculation is sped up. However, the performance also depends on the hardware (multi-core) or other settings. 




