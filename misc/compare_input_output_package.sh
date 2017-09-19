n=35
for (( i=1; i <= $n; i++))
do
    cat input/H_$i | ./prog > MY_$i
    diff=$(diff output/H_$i MY_$i)
    if [ "$diff" != "" ]
    then
        echo "Found difference."
            echo "Check diff result at "MY_$i
        break
    fi
    rm MY_$i
done
