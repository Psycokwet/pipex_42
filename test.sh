#?/bin/bash
./pipex Makefile "sleep 5" "sleep 5" outfile
# Should wait only 5 second because parralelisme

echo '----------- TEST WITH :Makefile "./erter" "../solong_so/so_long_bonus" outfile'
./pipex Makefile "./erter" "../solong_so/so_long_bonus" outfile
echo $?
cat outfile
< Makefile ./erter | ../solong_so/so_long_bonus > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefile "./erter" "./pipex" outfile'
./pipex Makefile "./erter" "./pipex" outfile
echo $?
cat outfile
< Makefile ./erter | ./pipex > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefile "grep :" "/bin/ls " outfile'
./pipex Makefile "grep :" "/bin/ls " outfile
echo $?
cat outfile
< Makefile grep : | /bin/ls > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefile "grep :" "wc -l" outfile'
./pipex Makefile "grep :" "wc -l" outfile
echo $?
cat outfile
< Makefile grep : | wc -l > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefijle "grep :" "wc -l" outfile'
./pipex Makefijle "grep :" "wc -l" outfile
echo $?
cat outfile
< Makefijle grep : | wc -l > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefijle "grept :" "wc -l" outfile'
./pipex Makefijle "grept :" "wc -l" outfile
echo $?
cat outfile
< Makefijle grept : | wc -l > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefile "grept :" "wc -l" outfile'
./pipex Makefile "grept :" "wc -l" outfile
echo $?
cat outfile
< Makefile grept : | wc -l > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefile "grep :" "wc -lrger" outfile'
./pipex Makefile "grep :" "wc -lrger" outfile
echo $?
cat outfile
< Makefile grep : | wc -lrger > outfile
echo $?
cat outfile

echo '----------- TEST WITH :Makefile "ls :" "ls :" outfile'
./pipex Makefile "ls :" "ls :" outfile
echo $?
cat outfile
< Makefile ls : | ls : > outfile
echo $?
cat outfile
