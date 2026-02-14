#!/bin/bash
module load python
echo Creating virtual environment
virtualenv --no-download golay
echo Swapping to virtual environment
source golay/bin/activate
echo Updating pip
pip install --no-index --upgrade pip
echo Installing packages
python -m pip install simple_slurm