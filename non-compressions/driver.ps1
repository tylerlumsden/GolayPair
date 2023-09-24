$order = $args[0]
$define = '#define ORDER ' + $order.ToString()

(Get-Content ..\golay.h) -replace '#define ORDER \d+', $define | Set-Content ..\golay.h

make all

$total = [Diagnostics.Stopwatch]::StartNew()

echo "Generating Classes"
$classes = [Diagnostics.Stopwatch]::StartNew()
.\generate_classes
$classes.Stop()
$classes.Elapsed.TotalSeconds

$classes = [Math]::Truncate($classes.Elapsed.TotalSeconds * 10) / 10

echo "Matching Pairs"
$matching = [Diagnostics.Stopwatch]::StartNew()
.\match_pairs
$matching.Stop()
$matching.Elapsed.TotalSeconds

$matching = [Math]::Truncate($matching.Elapsed.TotalSeconds * 10) / 10

$total.Stop()
$total.Elapsed.TotalSeconds

$total = [Math]::Truncate($total.Elapsed.TotalSeconds * 10) / 10

$pairs = ((Get-Content .\results\$order-pairs-found)).Count
$CandA = ((Get-Content .\results\$order-unique-filtered-a-0)).Count
$CandB = ((Get-Content .\results\$order-unique-filtered-b-0)).Count

python -u "print_timings_table.py" $order $CandA $CandB $pairs $classes $matching $total | Tee-Object -FilePath 'results.table'

