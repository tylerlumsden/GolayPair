from simple_slurm import Slurm
import datetime

def chain_jobs(jobs: list[Slurm]) -> Slurm:
    rev = jobs[::-1]
    for i in range(len(rev) - 1):
        a, b = rev[i], rev[i + 1]
        b.add_cmd(
            f"if [[ {Slurm.SLURM_ARRAY_TASK_ID} -eq {Slurm.SLURM_ARRAY_TASK_MIN} ]]; then\n"
            f"  sbatch --dependency=afterok:$SLURM_JOB_ID << 'EOF-{i}'\n"
            f"{a.script()}EOF-{i}\n"
            f"fi"
        )
    return jobs[0]

jobs = []
for i in range(24, 25):
    uncompress = Slurm(account="def-cbright", array=range(0, 100), job_name=f"uncompress99-{i}", time=datetime.timedelta(days=7))
    uncompress.add_cmd(f"./build/debug/main 99 -c 3 1 --uncompress --paf=-2 --line={i} -n $SLURM_ARRAY_TASK_COUNT -j $SLURM_ARRAY_TASK_ID")
    jobs.append(uncompress)

    match = Slurm(account="def-cbright", job_name=f"match99-{i}", time=datetime.timedelta(days=1), mem="5G")
    match.add_cmd("./build/debug/main 99 -c 1 --paf=-2 -n 100 --sort --match")
    jobs.append(match)

print(chain_jobs(jobs))