in progress ...


probably you should have:
* python3
* g++
* cmake

some maybe used things
"""
python3 -m venv .venv
source ./.venv/bin/activate
pip3 install -r requirements.txt
"""
you might as well install via pip:numpy , conan. maybe venv not needed

then those will do all after having vanilla .conan2

``` bash
conan profile detect
conan install . --build=missing
conan build .


```
<!-- cd build -->
<!-- cmake .. -->
<!-- cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -->
<!-- cmake --build . -->
<!-- cd .. -->
