


``` bash
python3 -m venv .venv
source ./.venv/bin/activate
pip3 install -r requirements.txt
conan profile detect
conan install . --output-folder=build --build=missing
conan build .


```
<!-- cd build -->
<!-- cmake .. -->
<!-- cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -->
<!-- cmake --build . -->
<!-- cd .. -->
