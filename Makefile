SRC = srcs/nm.c
SRC += srcs/nm_lib.c
SRC += srcs/otool.c

OBJ = $(SRC:.c=.o)
LIB = srcs/libft/libft.a
FLAG = -Wall -Werror -Wextra
CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m
INC = -I ./includes/

all: start
	@echo "\033[K$(CY)[NM] :$(CE) $(CG)Compiling nm ...$(CE)";
	-@make -C srcs/libft nohd
	@gcc -o ft_nm srcs/nm.c srcs/nm_lib.c $(FLAG) $(INC)  $(LIB);
	@echo "\033[K$(CY)[OTOOL] :$(CE) $(CG)Compiling otool ...$(CE)";
	@gcc -o ft_otool srcs/otool.c $(FLAG) $(INC) $(LIB);


start:
	@echo "\n";
	@echo "			$(CG)      ::::    :::   :::   :::    :::::::: ::::::::::: ::::::::   ::::::::  :::  $(CE)";
	@echo "			$(CG)     :+:+:   :+:  :+:+: :+:+:  :+:    :+:    :+:    :+:    :+: :+:    :+: :+:   $(CE)";
	@echo "			$(CG)    :+:+:+  +:+ +:+ +:+:+ +:+ +:+    +:+    +:+    +:+    +:+ +:+    +:+ +:+    $(CE)";
	@echo "			$(CG)   +#+ +:+ +#+ +#+  +:+  +#+ +#+    +:+    +#+    +#+    +:+ +#+    +:+ +#+     $(CE)";
	@echo "			$(CG)  +#+  +#+#+# +#+       +#+ +#+    +#+    +#+    +#+    +#+ +#+    +#+ +#+      $(CE)";
	@echo "			$(CG) #+#   #+#+# #+#       #+# #+#    #+#    #+#    #+#    #+# #+#    #+# #+#       $(CE)";
	@echo "			$(CG)###    #### ###       ###  ########     ###     ########   ########  ########## $(CE)";
	@echo "\n";

%.o: %.c
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Compiling $<$(CE) \033[1A";
	@gcc $(FLAG) -c $< -o $@ $(INC)

clean: start
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Cleaning Malloc objects$(CE)\033[1A";
	-@make -C srcs/libft nohdclean;
	@/bin/rm -rf $(OBJ);

fclean: start clean
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Cleaning 42sh ...$(CE)\033[1A";
	-@make -C srcs/libft nohdfclean;
	@/bin/rm -f ft_nm ft_otool;

re: fclean all

.PHONY: all clean fclean re