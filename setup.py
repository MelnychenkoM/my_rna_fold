from setuptools import setup, Extension

setup(
    name='rnafold',
    version='1.0',
    ext_modules=[
        Extension('rna_fold', sources=['src/rna_fold_python.c', 'src/rna_fold.c'], include_dirs=['src'])
    ],
)