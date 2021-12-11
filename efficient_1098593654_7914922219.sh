g++ --std=c++11 efficient.cpp -o efficient
/usr/bin/time -a -f "%e\n%M" -o output.txt ./efficient input.txt