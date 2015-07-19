# rebls-15

## loopless/

```
> cd <ceu>/
> ceu <loopless>/a.ceu
> gcc main.c
> ./a.out
```

I found an online reference:
<http://roth.cs.kuleuven.be/w-ess/index.php/Loopless_algorithms_for_combinatorics>

The version in Céu is not exactly O(1).
For every occurrence of `NEXT`, the runtime traverses all "stack frames".
Each "stack frame" is implicitly waiting for its immediate deeper "stack frame" 
to calculate the next iteration, i.e., `traverse` is has an implicit `await`.
Only the deepest "stack frame" has an actual `await` (`await NEXT`):

```
<level 0>
    ...
    traverse 0+1;
        <level 1>
            traverse 0+1+1;
                ...
                    <level N>
                        await NEXT;
```

Hence, the complexity is proportional to the size of the tuple, e.g., to 
generate the next item of a triple, the runtime traverses three levels of 
"stack frames", but doesn't do any work expect for the last level (which is 
O(1)).

## bts-python/ vs bts-ceu/

```
> cd <bts-python>/
> python domain.py

> cd <ceu-sdl>/
> make CEUFILE=<bts-ceu>/domain.ceu
> <bts-ceu>/domain.exe
```

It would be interesting to compare the implementation of the BT runtimes as 
well as the domain applications in the languages.
