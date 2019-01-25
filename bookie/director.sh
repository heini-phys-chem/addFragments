#!/bin/bash

# Configuration
SALT="9ce7605f7185f8356a13f77782f73c59"
BASEURL="https://jinn.chemspacelab.org"
#BASEURL="http://localhost:5000"

# Code
NONCE=$RANDOM
TOKEN=$(echo -n $NONCE$SALT | md5sum | sed 's/ .*//')


#curl -F "nonce=$NONCE" -F "token=$TOKEN" \
#	 -F "payload=@data/run.tar" -F "feature=orca" -F "bucket=e2" \
#	-F "calc=snafu" -F "path=snafu/nf-00" $BASEURL/placebet

#curl -F "nonce=$NONCE" -F "token=$TOKEN" -F "promised=100" -F "features=orca" $BASEURL/callbet
curl -F "nonce=$NONCE" -F "token=$TOKEN" -F "betid=1543" $BASEURL/dlbet --output run.tar
#curl -F "nonce=$NONCE" -F "token=$TOKEN" -F "betid=1" $BASEURL/closebet

