#!/bin/bash
#SBATCH --job-name=99log
#SBATCH --account=def-cbright         # change to your allocation/account
#SBATCH --time=7-00:00:00             # 7 days (D-HH:MM:SS)
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=2G
#SBATCH --array=0-99
#SBATCH --output=logs/%x_%A_%a.out
#SBATCH --error=logs/%x_%A_%a.err

# Optional but common:
#SBATCH --mail-type=END,FAIL
#SBATCH --mail-user=lumsdent@uwindsor.ca
#SBATCH --requeue

set -euo pipefail

./build/debug/main 99 -c 3 1 --uncompress --paf=-2 --line=23 -n "${SLURM_ARRAY_TASK_COUNT}" -j "${SLURM_ARRAY_TASK_ID}"

if [[ "${SLURM_ARRAY_TASK_ID}" -eq "${SLURM_ARRAY_TASK_MIN}" ]]; then
  sbatch --account=def-cbright \
         --dependency=afterok:${SLURM_ARRAY_JOB_ID} \
         --time=24:00:00 --mem=5G \
         --wrap "./build/debug/main 99 -c 1 --paf=-2 -n ${SLURM_ARRAY_TASK_COUNT} --sort --match"
fi
