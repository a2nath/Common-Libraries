#!/bin/sh

CURRPWD=$(pwd) # current dir
OUT=$CURRPWD/practice.out
LOG=$CURRPWD/last_compile.log

rm $OUT
files=$(ls src)

echo -n "Compiling "
start=`date +%s`

g++ $files $1 -o $OUT -std=c++14 $options $macro -Wall -g 2>&1 | tee $LOG

end=`date +%s`

# g++ exit code instead of using g++ flag
gcc_exit_code=$(grep ": error:" $LOG)
if [ -z "$gcc_exit_code" ]; then
	exit_code=0
else
	exit_code=1
fi

# give confirmation of compilation
if [ -f $OUT ]; then
	echo "\n\n======================================================================================="
	echo "program compiled on $(date) and took $(( $end - $start )) seconds with exit code $exit_code"
	echo "======================================================================================="
fi
