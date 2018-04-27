echo "removing prior results"
mkdir -p results
rm results/*.out
echo ""

echo "runnings samples through calculator"
for fn in samples/*.in; do
    echo "results/$(basename "$fn" .in).out"
    ./calculator <"$fn" >"results/$(basename "$fn" .in).out"
done
echo ""

echo "comparing results to sample outputs"
for fn in samples/*.out; do
    echo "$fn"
    echo "results/$(basename "$fn")"
    diff "$fn" "results/$(basename "$fn")"
    echo ""
done
