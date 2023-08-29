Get-ChildItem -Path .\timings -Include * -File -Recurse | foreach { $_.Delete()}

make all
.\find
python -u "print_timings_table.py" | Tee-Object -FilePath 'results.table'

