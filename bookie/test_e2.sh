#!/bin/bash
TMPDIR=$(mktemp -d)
echo '#TEST1: Empty'
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST2: TS Prepared'
mkdir $TMPDIR/ts-00
cp data/e2/ts-00/run.inp $TMPDIR/ts-00
cp data/e2/ts-00/inp.xyz $TMPDIR/ts-00
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST3: TS-00 completed'
cp data/e2/ts-00/run.log $TMPDIR/ts-00
cp data/e2/ts-00/run.xyz $TMPDIR/ts-00
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST3: TS-01 completed'
cp data/e2/ts-01/run.log $TMPDIR/ts-01
cp data/e2/ts-01/run.xyz $TMPDIR/ts-01
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST4: NF-00 completed'
cp data/e2/nf-00/run.log $TMPDIR/nf-00
cp data/e2/nf-00/*.hess $TMPDIR/nf-00
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST5: NF-01 completed'
cp data/e2/nf-01/run.log $TMPDIR/nf-01
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST6: LS completed'
cp -r data/e2/ls* $TMPDIR/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST7: sdA-00 completed, but no run.xyz'
cp data/e2/sdA-00/run.log $TMPDIR/sdA-00/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST8: sdA-00 completed'
cp data/e2/sdA-00/run.xyz $TMPDIR/sdA-00/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST9: sdA-00 completed'
cp data/e2/sdA-01/run.xyz $TMPDIR/sdA-01/
cp data/e2/sdA-01/run.log $TMPDIR/sdA-01/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST10: sdB completed'
cp -r data/e2/sdB-*/ $TMPDIR/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST11: goR completed'
cp data/e2/goR-00/run.log $TMPDIR/goR-00/
cp data/e2/goR-00/run.xyz $TMPDIR/goR-00/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST12: goP completed'
cp data/e2/goP-00/run.log $TMPDIR/goP-00/
cp data/e2/goP-00/run.xyz $TMPDIR/goP-00/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

echo '#TEST13: nfR/nfP completed'
cp data/e2/nfP-00/run.log $TMPDIR/nfP-00/
cp data/e2/nfP-00/*.hess $TMPDIR/nfP-00/
cp data/e2/nfR-00/run.log $TMPDIR/nfR-00/
cp data/e2/nfR-00/*.hess $TMPDIR/nfR-00/
python -c "import workflow; wf = workflow.E2Workflow(); wf.read_path('$TMPDIR', verbose=True);"

rm -rf $TMPDIR
