try
{
    make all

    $total = [Diagnostics.Stopwatch]::StartNew()

    echo "Generating Candidates A"

    .\compressions_a

} finally 
{
    $total.Stop()
    Write-Host $total.Elapsed.TotalSeconds"s"
}
