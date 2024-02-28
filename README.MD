# Nussinov algorithm for nucleic acid secondary structure prediction
## Description

![](img/nussinov_algorithm.png)
[Eddy SR. How do RNA folding algorithms work? Nat Biotechnol. 2004 Nov;22(11):1457-8](https://www.molgen.mpg.de/3710236/eddy2004.pdf)

**Useful resources:** \
[Forna visualization website](http://rna.tbi.univie.ac.at/forna/) \
[Freiburg Bioinformatics Group](https://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Nussinov)
## Installation
```
python -m pip install git+https://github.com/MelnychenkoM/rna_fold.git
```
## Usage
```
import rna_fold
rna_fold.version()

seq = "AGACGACAAGGUUGAAUCGCACCCACAGUCUAUGAGUCGGUG"
rna_fold.fold(seq)

rna_fold.gc_content(seq)

rna_fold.nussinov_matix(seq)
```

