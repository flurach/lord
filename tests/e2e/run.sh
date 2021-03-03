RESET="\e[0m"
GREEN="\e[32m"
RED="\e[31m"

echo "=== E2E Testing ==="
all="1"

echo -e "\n => suite lp (lexer)"
for d in tests/e2e/*/; do
	dir="${d}"

	bin/lord -l $dir/code.lord > $dir/lex.out
	cmp $dir/lex.exp $dir/lex.out > /dev/null

	if [ $? -eq "0" ]; then
		echo -e " -$GREEN passed$RESET $(basename $d)"
	else
		echo " - failed $(basename $d)"
		all="0"
	fi
done

echo -e "\n => suite lp (parser)"
for d in tests/e2e/*/; do
	dir="${d}"

	bin/lord -p $dir/code.lord > $dir/parse.out
	cmp $dir/parse.exp $dir/parse.out > /dev/null

	if [ $? -eq "0" ]; then
		echo -e " -$GREEN passed$RESET $(basename $d)"
	else
		echo -e " -$RED failed$RESET $(basename $d)"
		all="0"
	fi
done

echo -e "\n => suite lc (analyse)"
for d in tests/e2e/*/; do
	dir="${d}"

	bin/lord -a $dir/code.lord > $dir/analyse.out
	cmp $dir/analyse.exp $dir/analyse.out > /dev/null

	if [ $? -eq "0" ]; then
		echo -e " -$GREEN passed$RESET $(basename $d)"
	else
		echo -e " -$RED failed$RESET $(basename $d)"
		all="0"
	fi
done

echo -e "\n => suite lc (raw)"
for d in tests/e2e/*/; do
	dir="${d}"

	bin/lord -b raw -c $dir/code.lord > $dir/raw.out
	cmp $dir/raw.exp $dir/raw.out > /dev/null

	if [ $? -eq "0" ]; then
		echo -e " -$GREEN passed$RESET $(basename $d)"
	else
		echo -e " -$RED failed$RESET $(basename $d)"
		all="0"
	fi
done

echo -e "\n => suite lc (gas-x86_64-intel)"
for d in tests/e2e/*/; do
	dir="${d}"

	bin/lord -b gas-x86_64-intel -c $dir/code.lord > $dir/gas-x86_64-intel.out
	cmp $dir/gas-x86_64-intel.exp $dir/gas-x86_64-intel.out > /dev/null

	if [ $? -eq "0" ]; then
		echo -e " -$GREEN passed$RESET $(basename $d)"
	else
		echo -e " -$RED failed$RESET $(basename $d)"
		all="0"
	fi
done

echo -e "\n => suite lc (gas-x86_64-intel + gcc)"
for d in tests/e2e/*/; do
	dir="${d}"

	mv $dir/gas-x86_64-intel.out $dir/gas-x86_64-intel.s
	gcc $dir/gas-x86_64-intel.s $dir/code.c -o $dir/program
	mv $dir/gas-x86_64-intel.s $dir/gas-x86_64-intel.out

	$dir/program > $dir/bin.out
	cmp $dir/bin.exp $dir/bin.out > /dev/null

	if [ $? -eq "0" ]; then
		echo -e " -$GREEN passed$RESET $(basename $d)"
	else
		echo -e " -$RED failed$RESET $(basename $d)"
		all="0"
	fi
done

if [ $all -eq "1" ]; then
	echo -e "$GREEN \nALL TESTS PASSED...$RESET"
else
	echo -e "$RED \nSOME TESTS FAILED...$RESET"
fi
