#!/bin/bash

# Configuration
SALT="9ce7605f7185f8356a13f77782f73c59"
BASEURL="https://jinn.chemspacelab.org"

# Code
NONCE=$RANDOM
TOKEN=$(echo -n $NONCE$SALT | md5sum | sed 's/ .*//')

# args
if [ "$#" -ne 5 ]
then
	echo 'Usage: placebet.sh archive feature calc bucket path'
	exit 2
fi

curl -F "nonce=$NONCE" -F "token=$TOKEN" \
	-F "payload=@$1" -F "feature=$2" -F "bucket=$4" \
	-F "calc=$3" -F "path=$5" $BASEURL/placebet
