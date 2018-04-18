import sys
import os
import numpy as np
import cclib

from cclib.parser import ccopen

if __name__ == "__main__":

  # read in filename and parse log file
  filename = sys.argv[2]
  mylogfile = ccopen(filename)
  data = mylogfile.parse()

  # if TS calculation
  if sys.argv[1] == "TS":
    energy = data.scfenergies

    print(energy)

  # if NF calculation
  if sys.argv[1] == "NF":
    G = data.freeenergy
    freqs = data.vibfreqs
    imaginary = freqs[freqs < 0]

    print(G, imaginary)

