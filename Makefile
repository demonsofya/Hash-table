FLAGS=-O3 -mavx -mavx2 -masm=intel -DNDEBUG -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: hash_table

hash_table : main.o list.o list_dump.o hash-table.o hash_table_dump.o buffer.o MyStrlen.o
	g++ main.o list.o list_dump.o hash-table.o hash_table_dump.o buffer.o MyStrlen.o -o hash_table $(FLAGS)

main.o : main.cpp list/list.h hash-table.h onegin/buffer.h
	g++ main.cpp -c $(FLAGS)

list.o : list/list.cpp list/list.h
	g++ -c list/list.cpp $(FLAGS)

list_dump.o : list/list_dump.cpp list/list.h
	g++ -c list/list_dump.cpp $(FLAGS)

hash_table_dump.o : hash_table_dump.cpp list/list.h hash-table.h
	g++ -c hash_table_dump.cpp $(FLAGS)

hash-table.o : hash-table.cpp list/list.h hash-table.h
	g++ -c hash-table.cpp $(FLAGS)

buffer.o : onegin/buffer.cpp onegin/buffer.h 
	g++ -c onegin/buffer.cpp $(FLAGS) 
