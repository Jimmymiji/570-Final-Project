g++ --std=c++11 efficient.cpp -o efficient
/usr/bin/time -a -f "%e\n%M" -o data/output_efficient.txt ./efficient data/input1.txt