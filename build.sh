mkdir -p  out
g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) -g brain_pybind/brain.cpp -g src/*/*.cpp -I include -std=c++17 -o out/brain$(python3-config --extension-suffix)
cp py/brain out/brain-py
