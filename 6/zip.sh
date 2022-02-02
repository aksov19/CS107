#!/bin/bash
if ! command -v zip &> /dev/null
then
	echo "install zip command"
	exit
fi

config_file=~/.config/paradigms

if [[ -f "$config_file" ]]; then
	source $config_file
fi

if [[ -z "$emailid" ]]; then
	read -p "enter id: " emailid
	echo "emailid=$emailid" > $config_file
fi

# TODO
zip $emailid account.h account.c action.h action.c bank.h bank.c bankdriver.c branch.h branch.c debug.h debug.c error.h report.h report.c teller.h teller.c
