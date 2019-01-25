#!/bin/bash

# Configuration
SALT="9ce7605f7185f8356a13f77782f73c59"
BASEURL="https://jinn.chemspacelab.org"

# Code
NONCE=$RANDOM
TOKEN=$(echo -n $NONCE$SALT | md5sum | sed 's/ .*//')

# identify cluster
RESPONSE=$(scontrol show config | grep ClusterName | sed 's/.* = //')
if [ "$RESPONSE" == "cluster" ]
then
	CLUSTERNAME="alchemy"
elif [ "$RESPONSE" == "scicore" ]
then
	CLUSTERNAME="scicore"
else
	echo "Cannot detect cluster. Sorry."
	exit
fi

# setup paths
if [ "$CLUSTERNAME" == "scicore" ]
then
	module load OpenMPI/2.0.1-iccifort-2017.1.132-GCC-5.4.0-2.26
	ORCAPATH="/scicore/home/lilienfeld/rudorff/SHARE-NOBACKUP/orca_4_0_1_2_linux_x86-64_openmpi202"
	export PATH="$ORCAPATH:$PATH"

	source /scicore/home/lilienfeld/rudorff/share/slurm-watchdog.sh
	SOLIDCURL="/scicore/home/lilienfeld/rudorff/share/solidcurl"
	BASEDIR="/scicore/home/lilienfeld/rudorff/BOOKIE"
fi
if [ "$CLUSTERNAME" == "alchemy" ]
then
	TMPDIR="/scratch/$(whoami)/phileas"
	mkdir -p $TMPDIR &> /dev/null

	module load mpi/mpich-3.2-x86_64
	export PATH="/home/vonrudorff/orca/orca_4_0_1_2_linux_x86-64_openmpi202:$PATH"
	ORCAPATH="/home/vonrudorff/orca/orca_4_0_1_2_linux_x86-64_openmpi202"

	source /home/vonrudorff/workcopies/tb-alchemy/src/slurm-watchdog.sh
	BASEDIR="/home/vonrudorff/BOOKIE"
	viahead() { ssh alchemy -C "curl $1"; }
	SOLIDCURL="viahead"
fi

while true; do
	echo 'Query jinn on ' $(hostname) " at " $(date)

	# calculate remaining time
	TIMESPEC=$(squeue -h -j $SLURM_JOB_ID -o "%L")
	REMAINING=$(timespec_to_seconds $TIMESPEC)
	REMAINMIN=$((($(timespec_to_seconds $TIMESPEC)-120)/60))
	if [ $REMAINMIN -lt 0 ]; then REMAINMIN=0; fi

	# Get next open bet
	BETID=$($SOLIDCURL "-F \"nonce=$NONCE\" -F \"token=$TOKEN\" -F \"promised=$REMAINMIN\" -F \"features=orca\" -s $BASEURL/callbet")
	[[ "$BETID" =~ ^[0-9]+$ ]] || exit

	TARDIR="$BASEDIR/$BETID"
	echo $TARDIR
	mkdir -p $TARDIR

	$SOLIDCURL "-s -F \"nonce=$NONCE\" -F \"token=$TOKEN\" -F \"betid=$BETID\" $BASEURL/dlbet --output \"$TARDIR/run.tgz\""
	cd $TMPDIR
	mkdir "bet-$BETID"
	cd "bet-$BETID"
	tar xf "$TARDIR/run.tgz"
	rm "$TARDIR/run.tgz"
	cd *

	# run orca
	timeout $(($REMAINING-120)) $ORCAPATH/orca run.inp &> run.log
	rm *.tmp *.gbw *aa.tmp.*

	cd "$TMPDIR/bet-$BETID"
	tar czf "$TARDIR/result.tgz" *
	chmod -R 777 "$TARDIR"
	cd "$TARDIR"
	rm -rf "$TMPDIR/bet-$BETID"

	$SOLIDCURL "-s -F \"nonce=$NONCE\" -F \"token=$TOKEN\" -F \"betid=$BETID\" $BASEURL/closebet"
done

