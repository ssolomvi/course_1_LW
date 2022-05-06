#! /bin/bash

tracing=0
counter=0

if [ -z "$1" ] # -z returns true if $1 is null
	then
	printf "$0: illegal option $1\nusage: $0 [-t]... FILE... \nuse -? option for help\n"
	exit 1
else

while [ -n "$1" ] # while all arguments will not be read, -n returns true if not null
do
    if [ -z $(echo "$1" | tr -d ',') ]; then
        printf "$0: illegal option $1\nusage: $0 [-t]... FILE... \nuse -? option for help\n"
        exit 1
    else
        value=$(echo "$1" | tr -d ',')
    fi
	case "$value" in
		-t|--tracing) # check tracing
			shift
			tracing=1
		;;

		-?|--help) # check help bar
			shift
			printf "NAME
\t  $0 -- deletes files with matching suffix.

SYNOPSIS
\t  $0 FILE... 
\t  $0 [-?]

DESCRIPTION
\t  Compares the specified file with all other files that have the same suffix, with the deletion of matching files.
\t  -t, --tracing  enable tracing.
\t  -?, --help\t show help (this menu) and exits\n" 
		exit 1
		;;


    *) 
			if [ ! -f "$value" ] # -f is true if file exists and is a regular file.
			then
			    printf "$0: illegal option $value\nusage: $0 [-t]... FILE... \nuse -? option for help\n"
				exit 1 
		    else
		    	file=$value
		    	break	
		    fi
		;;

	esac
done #end of reading arguments
fi


#program
if [[ -z $file ]]; then
	printf "$0: illegal option $value\nusage: $0 [-t]... FILE... \nuse -? option for help\n"
	exit 1
fi

if [ $tracing -eq 1 ] 
		then
			set -x
fi


suf=$(echo $file | cut -f 2 -d.)
fail=$(find ./ -maxdepth 1 -name "*\.$suf" | grep -v $file)

for f in $fail
do
	if [ -e $f ] & $(cmp -s $file $f); then
	    rm $f
        (( counter++ ))
	fi
done

if [ $counter -eq 0 ]; then
    echo "There is the only file in this directory with specified suffix."
else
    printf "The program deleted %d file(s) with the same suffix as specified.\n" "$counter"
fi



exit 0
