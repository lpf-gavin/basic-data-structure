#!/bin/sh
cd `dirname $0`
file="Singly Linked List"
g++ -c "$file.cpp" -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient  -fsanitize=address -fno-omit-frame-pointer -Wall
g++ "$file.o" -o "$file" -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient  -fsanitize=address -fno-omit-frame-pointer -Wall

cppcheck "$file.cpp"
read -p "Run the program now?y/n:" res

if [ $res = "y" ];then
 ./"$file"
fi
