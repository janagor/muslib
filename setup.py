import subprocess
from setuptools import setup
from setuptools.command.build_ext import build_ext


class CMakeBuild(build_ext):
    def run(self):
        subprocess.check_call(['conan', 'install', '.', '--build=missing'])
        subprocess.check_call(['conan', 'build', '.'])
        super().run()


setup(
    name='muslib',
    version='0.1.0',
    cmdclass={'build_ext': CMakeBuild},
    package_dir={'muslib': 'muslib_python_config'},
    install_requires=['pybind11', 'numpy'],
    package_data={
        'muslib_python_config': ['*'],
    },
)
