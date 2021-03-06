import sys
import numpy as np

def get_coords(filename):
  lines = open(filename, 'r').readlines()

  coords = []

  for i,line in enumerate(lines):
    if i == 0 or i == 1: continue

    tokens = line.split()
    coords.append(np.array([float(tokens[1]), float(tokens[2]), float(tokens[3])]))

  return coords

if __name__ == "__main__":

  filename = sys.argv[1]

  mol = get_coords(filename)

  xY = mol[-1][0]
  yY = mol[-1][1]
  zY = mol[-1][2]

  dists = []

  for atom in mol[:-1]:
    x = atom[0]
    y = atom[1]
    z = atom[2]
    dist = np.sqrt( (xY - x)**2 + (yY - y)**2 + (zY - z)**2 )

    dists.append(dist)

  for distance in dists:
    if distance < 0.5: exit(1)

  exit(0)
