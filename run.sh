valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all --suppressions=r.supp ./minishell
# --track-fds=yes
#  --trace-children=yes