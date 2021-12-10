g++ --std=c++11 basic.cpp -o basic
/usr/bin/time -a -f "%e\n%M" -o data/output_basic.txt ./basic test/input/10.txt