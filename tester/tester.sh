#!/bin/bash

input="tester/execute.txt"
prompt="codyshell-3.0$ "

rm -f tester/output.txt
rm -f tester/output2.txt
rm -f tester/error.txt
rm -f tester/error2.txt

touch tester/output.txt
touch tester/output2.txt

./minishell < $input 2>> tester/error.txt | tail -n +2 >> tester/output.txt

sed -i .txt 's/codyshell: //g' tester/error.txt
sed -i .txt 's/codyshell-3.0$ //g' tester/output.txt
sed -i .txt '$ d' tester/error.txt

while IFS= read -r line2
do
  echo $line2 >> tester/output2.txt
  echo $line2 | bash 2>> tester/error2.txt 1>> tester/output2.txt 
done < "$input"
sed -i .txt 's/bash: line 1: //g' tester/error2.txt

diff tester/output.txt tester/output2.txt > tester/diff.txt
if [[ -s tester/diff.txt ]]
then
    cat < tester/diff.txt
else
   echo "OK"
fi
