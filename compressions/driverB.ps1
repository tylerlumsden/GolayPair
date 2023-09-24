try {
make all

$total = [Diagnostics.Stopwatch]::StartNew()

echo "Generating Candidates B"

.\compressions_b

} finally 
{
$total.Stop()
Write-Host $total.Elapsed.TotalSeconds"s"
}
