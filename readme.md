# toy code to link with terrace

Build
-------
mkdir build;
cd build;
cmake -DTERRACE_COMPILE_DIR=/path/to/terrace/ ..
make; ./HELLO -src 9 -maxiters 5 -f data/slashdot.adj 
