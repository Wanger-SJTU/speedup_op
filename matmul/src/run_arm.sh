
sed -i 's/clang++/\$\{NDK_CXX\}/g' Makefile

make matmul
adb push main /data/tmp/matmul


adb shell "cd /data/tmp && chmod +x matmul && ./matmul 3 512 512"

sed -i 's/${NDK_CXX}/clang++/g' Makefile
make clean