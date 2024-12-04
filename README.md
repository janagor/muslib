## Requirements

* python
* g++
* cmake
* clang-tidy
* cppcheck

# Build

"""
python3 -m venv .venv
source ./.venv/bin/activate
pip3 install -r requirements.txt
"""

``` bash
conan profile detect
conan install . --build=missing
conan build .

```
And then:

```bash
pip install .
```
