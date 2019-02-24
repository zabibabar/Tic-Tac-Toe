from __future__ import print_function
from os import listdir, getcwd, access, X_OK
from os.path import isfile, join, splitext
import optparse
from subprocess import Popen, PIPE, STDOUT
from collections import defaultdict
import sys
import re

def main():

    parser = optparse.OptionParser(usage='usage: %prog tictactoe.c')
    opts, args = parser.parse_args()

    if len(args) != 2: 
        print("error: must provide a compiled program and a test file.")
        exit(1)

    with open(args[1]) as f:
        lines = [l.strip() for l in f.read().split()]
    game = 0
    game_lines = defaultdict(list)
    for l in lines:
        game_lines[game].append(l)
        if l == 'y' or l == 'n':
            game = game + 1
            
    inputs = ''
    must_win = {}
    for g in range(game):
        must_win[g] = int(game_lines[g][0])
        inputs = inputs + '\n'.join(game_lines[g][1:])
        inputs = inputs + '\n'
    
    p = Popen([join(getcwd(), args[0])], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    outs, errs = p.communicate(input=inputs)
    p.wait()
    reg = re.compile("(Player \d wins!|The game has ended in a draw)",flags=re.IGNORECASE)
    out_game = reg.split(outs)
    
    for g in range(game):
        res = re.match(r'Player (\d) wins!', out_game[g*2+1],re.IGNORECASE)
        if res:
            won = int(res.group(1))
        else:
            won = 0
        print('game ' + str(g) + ' test', end='')
        if (must_win[g] == won):
            print(": PASSED")
        else:
            print(": FAILED")

if __name__ == "__main__":
    main()

