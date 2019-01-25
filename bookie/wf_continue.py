#!/usr/bin/env python
import sys
sys.path.append('/home/grudorff/workdirs/addFG/bookie')
import os.path
import workflow
import glob

def scan_dir(wf, path, globpattern):
	""" Prints INPROGRESS stages with their matching folders."""
	directories = glob.glob('%s/%s' % (path, globpattern))
	for directory in directories:
		if not os.path.isdir(directory):
			continue
		complete, states = wf.read_path(directory)
		for stage in states[workflow.StageStates.INPROGRESS]:
			lastfolder = wf._stages[0].get_folders(directory, label=stage)[-1]
			print (lastfolder, lastfolder.split('/')[-2])

wf = workflow.E2Workflow()
scan_dir(wf, '/mnt/ECHO/bookie/e2', 'e2ts*')
