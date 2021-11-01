# pipex_42

./pipex Makefile "sleep 5" "sleep 5" outfile
Should wait only 5 second because parralelisme

./pipex Makefile "./erter" "../solong_so/so_long_bonus" outfile
echo $?
< Makefile ./erter | ../solong_so/so_long_bonus > outfile
echo $?
OK

./pipex Makefile "grep :" "/bin/ls " outfile
echo $?
< Makefile grep : | /bin/ls > outfile
echo $?
OK

./pipex Makefile "grep :" "wc -l" outfile
echo $?
< Makefile grep : | wc -l > outfile
echo $?
OK

./pipex Makefijle "grep :" "wc -l" outfile
echo $?
< Makefijle grep : | wc -l > outfile
echo $?
OK

./pipex Makefijle "grept :" "wc -l" outfile
echo $?
< Makefijle grept : | wc -l > outfile
echo $?
OK

./pipex Makefijle "grept :" "wic -l" outfile
echo $?
< Makefijle grept : | wic -l > outfile
echo $?
OK

./pipex Makefile "grept :" "wc -l" outfile
echo $?
< Makefile grept : | wc -l > outfile
echo $?
OK

./pipex Makefile "grept :" "wic -l" outfile
echo $?
< Makefile grept : | wic -l > outfile
echo $?
OK

./pipex Makefile "grep :" "wic -l" outfile
echo $?
< Makefile grep : | wic -l > outfile
echo $?
OK

./pipex Makefile "grep :" "wc -lrger" outfile
echo $?
< Makefile grep : | wc -lrger > outfile
echo $?
OK

./pipex Makefile "ls :" "ls :" outfile
echo $?
< Makefile ls : | ls : > outfile
echo $?
OK