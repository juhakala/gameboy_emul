echo "Are you sure to delete SDL2-2.0.12 directory and included libs? [y/n]"
read input
if [ $input = "y" ]; then
	make delete
	echo "SDL2-2.0.12 deleted"
else
	echo "SDL2-2.0.12 not deleted"
fi