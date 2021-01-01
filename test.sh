for f in _tests/*
do
	valgrind _bin/lord -p $f
done
