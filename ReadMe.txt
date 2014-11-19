Alesandra Roger (aroger1@ucsc.edu)
Jiayu Zeng          (jzen5@ucsc.edu)

*We missed the due date of handshaking in Crowgrader, but we co-operated to finish this assignment.

0. We chose to implement multithreading as an option for assignment 6.

1. This submission contains two sets of files. Two sets share hw06.cpp and GraphHex.h
    Both sets use Monte Calo method to implement AI (choosing a best move after 1000 iteration running on each spot.)
     a. one program uses multithreading for AI.  GraphHex.cpp and Makefile used. Specific codes using threading is 
        in function monteCalo( ). Library <omp.h> is included.
     b. another one does not use threading. GraphHex_no_thread.cpp and Makefile_no_thread are used.

2. To test both files.
    a. Threading version: input command "make", exectuable file "hw06" will be created. Most of time, it takes 50-65
       seconds for AI to respond for its first movement. We tested it about 30 times, once the program run 13-14 
       seconds for its first movement. 

    b. Non-threading version: "make -f Makefile_no_thread", exectuable file "hw06_no_thread" will be created. It takes
       15-20 seconds for AI to with for its first movement. (if we add -O3 in Makefile, the AI takes 6-7 seconds to 
       respond).

   *we tested the program in Lab 105.

3. Threading vs. Non-threading
    Theoratically, using threading should have a better performance because it separates a sequence progress into
    parts so that the calculation is sped up. However, the performance also depneds on the hardware (multi-core) 
    or other settings. In our case, which multi-threading version performs wores, we are not sure about the
    linux-environment, so it might be the reason that the removal service will not use multi-threads or does not 
    support it.

4. About user Input
   we set up the codes that the user just need to pick one number instead of inputing a co-ordinate, which we believe
   it will be more convinient. Hope you like it.




