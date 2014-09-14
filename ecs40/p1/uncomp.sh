#! /bin/bash
# Christopher Chen (997549548) , Wai Shing Yung (996936848)

if [[ "$#" -lt 1 ]]; then 
echo usage: uncomp.sh {filelist}+
else
	while [ $# -gt 0 ] ; do
file=$1
case ${file##*.} in
			tar) tar -xf $file ;;
			gz) tar -xzf $file ;;
			Z) tar -xZf $file ;;
			zip) tar -xzf $file ;;
			*) echo $file has no compression extension.;;
		esac
		shift
	done	
fi 