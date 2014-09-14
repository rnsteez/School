#! /bin/bash
# Christopher Chen (997549548) , Wai Shing Yung (996936848)
dir1=$1
dir2=$2
dir3=$3

if [[ -d "$dir1" && -d "$dir2" && ! -f "$dir3" ]]; then
	mkdir $dir3 2> /dev/null
	cp -u $dir1 $dir2 $dir3

	else
		echo usage: cpdir.sh source_directory1 source_directory2 dest_directory
fi