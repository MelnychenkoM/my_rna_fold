from setuptools import setup
from setuptools import Extension

setup(
    name='Test RNA folding',
    version='1.0',
    ext_modules=[Extension('rna_fold', ['src/_fold_rna.c'])],
)