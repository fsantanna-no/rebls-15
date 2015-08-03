
# example from
# http://stackoverflow.com/questions/248830/python-using-a-recursive-algorithm-as-a-generator
# works on Python 2.7.9 and Python 3.4.3

def getPermutations(string, storage, prefix=""):
   if len(string) == 1:
      storage.append(prefix + string)   # <-----
   else:
      for i in range(len(string)):
         getPermutations(string[:i]+string[i+1:], storage, prefix+string[i])

storage = []
getPermutations("abcd", storage)
for permutation in storage: print(permutation)

