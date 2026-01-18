perf record -g -- "$@"
perf report --no-children --stdio --call-graph=fractal > perf_report.txt