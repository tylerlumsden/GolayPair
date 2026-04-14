#!/bin/bash
#SBATCH --job-name=99-uncompress
#SBATCH --account=def-cbright         # change to your allocation/account
#SBATCH --time=7-00:00:00             # 7 days (D-HH:MM:SS)
#SBATCH --gpus-per-node=h100:1
#SBATCH --cpus-per-task=1
#SBATCH --mem=10G
#SBATCH --array=0-499

time ./build/release/main 99 -c 3 1 uncompress \
  --device gpu \
  --output $SLURM_ARRAY_TASK_ID \
  --prefix $SLURM_ARRAY_TASK_ID \
  --range_begin $SLURM_ARRAY_TASK_ID \
  --range_end 83279 \
  --range_step $SLURM_ARRAY_TASK_COUNT
