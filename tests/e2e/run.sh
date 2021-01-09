echo "=== E2E Testing ==="
all="1"

echo " => suite lp (lexer)"
for d in tests/e2e/*/; do
	dir="${d}"

	bin/lord -l $dir/code.ld > $dir/lexer-result.out
	cmp $dir/lexer-result.out $dir/lexer-expected.out > /dev/null

	if [ $? -eq "0" ]; then
		echo " - passed $(basename $d)"
	else
		echo " - failed $(basename $d)"
		all="0"
	fi
done

echo " => suite lp (parser)"
for d in tests/e2e/*/; do
	dir="${d}"

	bin/lord -p $dir/code.ld > $dir/parser-result.out
	cmp $dir/parser-result.out $dir/parser-expected.out > /dev/null

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
