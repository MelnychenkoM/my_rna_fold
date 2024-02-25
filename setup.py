from setuptools import setup
from setuptools import Extension

setup(
    name='Test RNA folding',
    version='1',
    ext_modules=[Extension('rna_fold', ['_fold_rna.c'])],
)