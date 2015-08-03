
-- example from
-- http://stackoverflow.com/questions/248830/python-using-a-recursive-algorithm-as-a-generator
-- ported from Python

local function getPermutations(str, storage, prefix)
   prefix = prefix or ""
   if #str == 1 then
      table.insert(storage, prefix .. str)
   else
      for i = 1, #str do
         getPermutations(str:sub(1,i-1) .. str:sub(i+1), storage, prefix..str:sub(i,i))
      end
   end
end

local storage = {}
getPermutations("abcd", storage)
for _, permutation in ipairs(storage) do
   print(permutation)
end

