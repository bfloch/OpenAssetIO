from setuptools import setup, find_packages


setup(
    name='openassetio',
    version="1.0.0-alpha.1",
    package_dir={'': 'python'},
    packages=find_packages(where='python'),
    python_requires='>=3.7',
    extras_require={
        "codegen": ["jinja2==3.1.2", "pyyaml==5.4.1"]
    },
    entry_points={
        'console_scripts': ['openassetio-codegen=openassetio.codegen.cmd:main [codegen]'],
    }
)
