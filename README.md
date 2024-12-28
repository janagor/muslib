## Requirements

* python 3.12
* g++
* cmake
* clang-tidy
* cppcheck

# Build

## Environment installation

### Linux

``` bash
python3 -m venv .venv
source ./.venv/bin/activate
pip3 install -r requirements.txt
```

### Windows

``` cmd
python -m venv .venv
.\.venv\Scripts\activate
pip install -r requirements.txt
```

## Libraries and binaries installation

``` bash
conan profile detect
conan install . --build=missing
conan build .
```

## Python library installation

```bash
pip install .
```

Now you can use the library with:

```python
import muslib
```

## Windows


# Docs

To generate documentation via Doxygen

```
doxygen Doxyfile
```
