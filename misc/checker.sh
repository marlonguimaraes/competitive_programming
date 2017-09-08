# Adapted from: https://gitlab.com/simiaosimis/cpnotebook/blob/master/miscellaneous/src/checker.cpp

# Export cmpp from your .bashrc by adding "export -f cmpp" to it
cmpp $1
mv prog a_prog

cmpp $2 
mv prog b_prog

while true
do
    python3 $3 > in_checker
    cat in_checker | ./a_prog > a_out
    cat in_checker | ./b_prog > b_out

    DIFF=$(diff a_out b_out)
    if [ "$DIFF" != "" ]
    then
        echo "BOOM! FOUND DIFFERENCE!"
        break
    fi
    echo "OK!"
done
