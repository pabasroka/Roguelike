#!/usr/bin/fish
make clean
for file in (find);
    set filename ( echo $file | python3 -c "print(input().split('/')[-1])" )
    set extension ( echo $filename | sed 's/.*\.//' )
    if test $extension = "hpp"; or test $extension = "cpp"
        cat $file | sed "s/#include \""$argv[1].hpp"\"/#include \""$argv[2].hpp"\"/" | tee $file > /dev/null
    end;
    if test $filename = $argv[1].cpp; or test $filename = $argv[1].hpp
        echo $filename "->" $argv[2].$extension
        mv $filename $argv[2].$extension
    end;
end;
echo "----------"
ls *.hpp
echo "----------"
make run -j12 > /dev/null
