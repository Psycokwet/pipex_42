# pipex_42

./pipex Makefile "grep :" "wc -l" outfile
echo $?
< Makefile grep : | wc -l > outfile
echo $?

./pipex Makefijle "grep :" "wc -l" outfile
echo $?
< Makefijle grep : | wc -l > outfile
echo $?

./pipex Makefijle "grept :" "wc -l" outfile
echo $?
< Makefijle grept : | wc -l > outfile
echo $?

./pipex Makefijle "grept :" "wic -l" outfile
echo $?
< Makefijle grept : | wic -l > outfile
echo $?

./pipex Makefile "grept :" "wc -l" outfile
echo $?
< Makefile grept : | wc -l > outfile
echo $?

./pipex Makefile "grept :" "wic -l" outfile
echo $?
< Makefile grept : | wic -l > outfile
echo $?

./pipex Makefile "grep :" "wic -l" outfile
echo $?
< Makefile grep : | wic -l > outfile
echo $?
