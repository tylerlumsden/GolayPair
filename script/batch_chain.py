from simple_slurm import Slurm
import datetime

def chain_jobs(jobs: list[Slurm]) -> Slurm:
    rev = jobs[::-1]
    for i in range(len(rev) - 1):
        a, b = rev[i], rev[i + 1]
        b.add_cmd(
            f"if [ {Slurm.SLURM_ARRAY_TASK_ID} -eq {Slurm.SLURM_ARRAY_TASK_MIN} ]; then\n"
            f"echo count: $SLURM_ARRAY_TASK_COUNT\n"
            f"echo array id: $SLURM_ARRAY_TASK_ID\n"
            f"echo array task min: $SLURM_ARRAY_TASK_MIN\n"
            f"echo array job id: $SLURM_ARRAY_JOB_ID\n"
            f"echo job id: $SLURM_JOB_ID\n"
            f"JOB_ID=${{{Slurm.SLURM_ARRAY_JOB_ID[1:]}:-{Slurm.SLURM_JOB_ID}}}\n"
            f"unset {Slurm.SLURM_ARRAY_JOB_ID[1:]}\n"
            f"sbatch --dependency=afterok:$JOB_ID << 'EOF-{i}'\n"
            f"{a.script(convert=False)}EOF-{i}\n"
            f"fi"
        )
    return jobs[0]

jobs = []
for i in range(24, 30):
    uncompress = Slurm(account="def-cbright", array=range(0, 100), job_name=f"uncompress99-{i}", time=datetime.timedelta(days=7))
    #uncompress.add_cmd(f"echo test-{i}")
    uncompress.add_cmd(f"./build/debug/main 99 -c 3 1 --uncompress --paf=-2 --line={i} -n {Slurm.SLURM_ARRAY_TASK_COUNT} -j {Slurm.SLURM_ARRAY_TASK_ID}")
    jobs.append(uncompress)

    match = Slurm(account="def-cbright", job_name=f"match99-{i}", time=datetime.timedelta(days=1), mem="5G")
    match.add_cmd("./build/debug/main 99 -c 1 --paf=-2 -n 100 --sort --match --append")
    #match.add_cmd(f"echo testmatch-{i}")
    jobs.append(match)

job = chain_jobs(jobs)

print(job.script())
job.sbatch()