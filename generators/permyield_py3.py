
# example from
# http://stackoverflow.com/questions/248830/python-using-a-recursive-algorithm-as-a-generator
# tested on Python 3.4.3
# uses 'yield from' introduced in Python 3.3

def getPermutations(string, prefix=""):
   if len(string) == 1:
      yield prefix + string             # <-----
   else:
      for i in range(len(string)):
         yield from getPermutations(string[:i]+string[i+1:], prefix+string[i])

for permutation in getPermutations("abcd"):
   print(permutation)

