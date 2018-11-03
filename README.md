# Read and write variables to the World of Warcraft client 3.3.5
This project were compiled and used in the project https://github.com/Jacobth/wow_rl_notebook. The linked project use a nerual net to determine where an agent is allowed to walk. This project use Click to move to walk to the predicted position from the neural net.

## Compile for python usage
To compile the libenv.so file, MinGW 64-bit is used.

1. g++ -c Environment.cpp && g++ -c MemoryReader.cpp && g++ -c MemoryAction.cpp
2. g++ -shared -Wl,-soname,libenv.so -o libenv.so Environment.o MemoryAction.o MemoryReader.o
