
# example from
# http://stackoverflow.com/questions/248830/python-using-a-recursive-algorithm-as-a-generator
# fails on both Python 2.7.9 and Python 3.4.3

def getPermutations(string, prefix=""):
   if len(string) == 1:
      yield prefix + string             # <-----
   else:
      for i in range(len(string)):
         getPermutations(string[:i]+string[i+1:], prefix+string[i])

for permutation in getPermutations("abcd"):
   print(permutation)

