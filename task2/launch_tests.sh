#! /bin/bash

echo "----------------------------------------------------------------------------------------------"
echo "    LAUNCH TESTS:"
echo "----------------------------------------------------------------------------------------------"
for test in $(ls Tests)
do
	./task2.out < Tests/$test > Outs/$test
done

if diff Refs/ Outs/
then
	echo "Tests OK!"
else
	echo "Tests NOT OK!"
fi	