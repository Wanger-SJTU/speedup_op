
aarch64-linux-android30-clang -c neon.s -o neon.o
aarch64-linux-android30-clang -c gflops_main.c -o main.o
aarch64-linux-android30-clang  main.o neon.o -o main

adb push main /data/local/tmp/main
# cat sys/devices/system/cpu/cpu7/cpufreq/scaling_available_frequencies 
adb shell "cd /data/local/tmp/ && ./main"

rm *.o 
rm main