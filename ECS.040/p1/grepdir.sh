#! /bin/bash
# Christopher Chen (997549548) , Wai Shing Yung (996936848)

N=$#
directory=$1
pattern=$2
shift
shift
options=$@

if [[ "$N" -lt 2 ]]; then #argv number test
	echo usage: grepdir.sh directory pattern [-grep option]* 
	elif [ ! -d $directory ]; then #argv 1 directory test
		echo usage: grepdir.sh directory pattern [-grep option]*
	elif [ "$pattern" == '' ]; then #argv 2 pattern test
		echo usage: grepdir.sh directory pattern [-grep option]*
	elif [ ! "$options" == "-.*" ]; then #argv 3 command test
		echo usage: grepdir.sh directory pattern [-grep option]*
	else
		grep -R $options $pattern $directory# actual grep ing
fi