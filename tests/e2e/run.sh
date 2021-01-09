echo "=== E2E Testing ==="
all="1"

echo " => suite lp/lexer"
for d in tests/e2e/lp/lexer/*; do
	dir="${d}"

	bin/lord -l $dir/code.ld > $dir/result.out
	cmp $dir/result.out $dir/expected.out > /dev/null

	if [ $? -eq "0" ]; then
		echo " - passed $(basename $d)"
	else
		echo " - failed $(basename $d)"
		all="0"
	fi
done

echo " => suite lp/parser"
for d in tests/e2e/lp/parser/*; do
	dir="${d}"

	bin/lord -p $dir/code.ld > $dir/result.out
	cmp $dir/result.out $dir/expected.out > /dev/null

	if [ $? -eq "0" ]; then
		echo " - passed $(basename $d)"
	else
		echo " - failed $(basename $d)"
		all="0"
	fi
done

if [ $all -eq "1" ]; then
	echo "=== ALL TESTS PASS ==="
else
	echo "=== SOME TESTS FAIL ==="
fi
