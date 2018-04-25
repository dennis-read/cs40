echo "removing prior results"
rm results/*.out
echo ""

echo "runnings samples through calculator"
for fn in samples/*.in; do
    echo "results/$(basename "$fn" .in).out"
    ./calculator <"$fn" >"results/$(basename "$fn" .in).out"
done

echo ""
echo "diff summary"
diff -q -x *.in samples results

echo ""
echo "diff details"
diff -x *.in samples results