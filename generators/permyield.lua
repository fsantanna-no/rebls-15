
-- example from
-- http://stackoverflow.com/questions/248830/python-using-a-recursive-algorithm-as-a-generator
-- ported from Python

local function getPermutations(str, prefix)
   prefix = prefix or ""
   if #str == 1 then
      coroutine.yield(prefix .. str)
   else
      for i = 1, #str do
         getPermutations(str:sub(1,i-1) .. str:sub(i+1), prefix..str:sub(i,i))
      end
   end
end

local function getPermutationsIter(str)
   return coroutine.wrap(function() getPermutations(str) end)
end

for permutation in getPermutationsIter("abcd") do
   print(permutation)
end

