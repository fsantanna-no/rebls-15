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

### References

* <https://outforafight.wordpress.com/2014/07/15/behaviour-behavior-trees-for-ai-dudes-part-1/>
* <http://livestream.com/accounts/1422055/events/4185971>
* <https://github.com/eykd/owyl/>
* <http://gamasutra.com/blogs/BenWeber/20120308/165151/ABL_versus_Behavior_Trees.php>
* <https://github.com/Johnicholas/EldritchCopy/blob/master/Projects/Eldritch/Raw/Config/bt.config>
* <http://www.chrishecker.com/My_Liner_Notes_for_Spore#Behavior_Tree_AI>
* <http://www.naimadgames.com/publications/teaching/behavior_trees/behavior_trees.pdf>
* <https://fai.cs.uni-saarland.de/hoffmann/cff.html>
* <http://www.gamasutra.com/view/feature/130663/gdc_2005_proceeding_handling_.php>
* <http://web.cs.wpi.edu/~rich/courses/imgd4000-d09/lectures/halo3.pdf>
* <http://chrishecker.com/My_liner_notes_for_spore/Spore_Behavior_Tree_Docs>
* <https://docs.unrealengine.com/latest/INT/Engine/AI/BehaviorTrees/NodeReference/index.html>
* <https://docs.unrealengine.com/latest/INT/Engine/AI/BehaviorTrees/HowUE4BehaviorTreesDiffer/index.html>
